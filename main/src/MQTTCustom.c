/*! Copyright 2022 Bogdan Pilyugin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  	 \file MQTTCustom.c
 *    \version 1.0
 * 		 \date 2022-08-19
 *     \author Bogdan Pilyugin
 * 	    \brief    
 *    \details 
 *	\copyright Apache License, Version 2.0
 */

#include "webguiapp.h"

#define TAG "MQTTCustom"

#define APP_SERVICE_NAME "APPNAME"          // Dedicated service name
#define APP_UPLINK_SUBTOPIC "UPLINK"        // Device publish to this topic
#define APP_DOWNLINK_SUBTOPIC "DWLINK"      // Device listen from this topic

#define MQTT_CUSTOM_HANDLER_DEBUG  CONFIG_WEBGUIAPP_MQTT_DEBUG_LEVEL

esp_err_t AppServiceMQTTSend(char *data, int len, int idx)
{
    if (GetMQTTHandlesPool(idx)->mqtt_queue == NULL)
        return ESP_ERR_NOT_FOUND;
    char *buf = (char*) malloc(len);
    if (buf)
    {
        memcpy(buf, data, len);
        MQTT_DATA_SEND_STRUCT DSS;
        ComposeTopic(DSS.topic, idx, APP_SERVICE_NAME, APP_UPLINK_SUBTOPIC);
        DSS.raw_data_ptr = buf;
        DSS.data_length = len;
        DSS.keep_memory_onfinish = false;
        if (xQueueSend(GetMQTTHandlesPool(idx)->mqtt_queue, &DSS, 0) == pdPASS)
            return ESP_OK;
        else
        {
            free(buf);
            return ESP_ERR_TIMEOUT;
        }
    }
    return ESP_ERR_NO_MEM;
}


#define MAX_MQTT_LOG_MESSAGE (1024)

#define APP_LOG_TAG "Application"
esp_err_t AppLog(esp_log_level_t level, char *format, ...)
{
    char data[MAX_MQTT_LOG_MESSAGE];
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    vsnprintf(data, MAX_MQTT_LOG_MESSAGE,  format, arg);
    switch(level)
    {
        case ESP_LOG_INFO:
            case ESP_LOG_DEBUG:
            case ESP_LOG_VERBOSE:
            case ESP_LOG_NONE:
            ESP_LOGI(APP_LOG_TAG, "%s", data);
            break;
        case ESP_LOG_WARN:
            ESP_LOGW(APP_LOG_TAG, "%s", data);
            break;
        case ESP_LOG_ERROR:
            ESP_LOGE(APP_LOG_TAG, "%s", data);
            break;
    }

    for (int idx = 0; idx < 2; idx++)
    {
        if (GetMQTTHandlesPool(idx)->mqtt_queue == NULL)
            continue;
        char time[RFC3339_TIMESTAMP_LENGTH];
        GetRFC3339Time(time);
        char *buf = (char*) malloc(strlen(data) + RFC3339_TIMESTAMP_LENGTH + 2);
        if (buf)
        {
            strcpy(buf, time);
            strcat(buf, "  ");
            strcat(buf, data);
            MQTT_DATA_SEND_STRUCT DSS;
            ComposeTopic(DSS.topic, idx, "LOG", APP_UPLINK_SUBTOPIC);
            DSS.raw_data_ptr = buf;
            DSS.data_length = strlen(buf);
            DSS.keep_memory_onfinish = false;
            if (xQueueSend(GetMQTTHandlesPool(idx)->mqtt_queue, &DSS, 0) != pdPASS)
                free(buf);
            continue;
        }
        return ESP_ERR_NO_MEM;
    }
    return ESP_OK;
}

void UserMQTTEventHndlr(int idx, void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    char topic[CONFIG_WEBGUIAPP_MQTT_MAX_TOPIC_LENGTH];
    switch ((esp_mqtt_event_id_t) event_id)
    {
        case MQTT_EVENT_CONNECTED:
            ComposeTopic(topic, idx, APP_SERVICE_NAME, APP_DOWNLINK_SUBTOPIC);
            //Subscribe to the service called "APP"
            msg_id = esp_mqtt_client_subscribe(client, (char*) topic, 0);
#if(MQTT_CUSTOM_HANDLER_DEBUG > 0)
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            ESP_LOGI(TAG, "Subscribe to %s", topic);
#endif

        break;
        case MQTT_EVENT_DATA:
            ComposeTopic(topic, idx, APP_SERVICE_NAME, APP_DOWNLINK_SUBTOPIC);
            if (!memcmp(topic, event->topic, event->topic_len))
            {
                char *respbuf = malloc(EXPECTED_MAX_DATA_SIZE);
                if (respbuf != NULL)
                {
                    data_message_t M = { 0 };
                    M.inputDataBuffer = event->data;
                    M.inputDataLength = event->data_len;
                    M.chlidx = idx;
                    M.outputDataBuffer = respbuf;
                    M.outputDataLength = EXPECTED_MAX_DATA_SIZE;
                    ServiceDataHandler(&M);
                    AppServiceMQTTSend(M.outputDataBuffer, strlen(M.outputDataBuffer), idx);
                    free(respbuf);
#if(MQTT_CUSTOM_HANDLER_DEBUG > 0)
                    ESP_LOGI(TAG, "SERVICE data handler on client %d", idx);
#endif
                }
                else
                    ESP_LOGE(TAG, "Out of free RAM for MQTT API handle");
            }
        break;

        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

void PublishTestApp(int idx)
{
    char tmp[10];
    char resp[256];
    char data[512];
    struct jWriteControl jwc;
    jwOpen(&jwc, data, sizeof(data), JW_OBJECT, JW_PRETTY);
    time_t now;
    time(&now);
    jwObj_int(&jwc,"time", (unsigned int) now);
    jwObj_string(&jwc,"event", "APP_TEST_MESSAGE");
    strcpy(resp, "mqtt://");
    strcat(resp, GetSysConf()->mqttStation[idx].ServerAddr);
    itoa(GetSysConf()->mqttStation[idx].ServerPort, tmp, 10);
    strcat(resp, ":");
    strcat(resp, tmp);
    jwObj_string(&jwc,"url", resp);
    ComposeTopic(resp, idx, APP_SERVICE_NAME, APP_UPLINK_SUBTOPIC);
    jwObj_string(&jwc,"tx_topic", resp);
    ComposeTopic(resp, idx, APP_SERVICE_NAME, APP_DOWNLINK_SUBTOPIC);
    jwObj_string(&jwc,"rx_topic", resp);
    jwEnd(&jwc);
    jwClose(&jwc);
    AppServiceMQTTSend(data, strlen(data), idx);
}
