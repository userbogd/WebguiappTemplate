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

#include "MQTT.h"
#include "SystemConfiguration.h"
#include "esp_log.h"
#define TAG "MQTTCustom"


void UserMQTTEventHndlr(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
       esp_mqtt_event_handle_t event = event_data;
       esp_mqtt_client_handle_t client = event->client;
       mqtt_client_t *ctx = (mqtt_client_t*) event->user_context;
       int msg_id;
       char topic[CONFIG_WEBGUIAPP_MQTT_MAX_TOPIC_LENGTH];
       switch ((esp_mqtt_event_id_t) event_id)
       {
           case MQTT_EVENT_CONNECTED:
               ComposeTopic(topic,
                            GetSysConf()->mqttStation[ctx->mqtt_index].RootTopic,
                            "DOWNLINK",
                            GetSysConf()->mqttStation[ctx->mqtt_index].ClientID,
                            "USER");
               //Subscribe to the service called "USER"
               msg_id = esp_mqtt_client_subscribe(client, (const char*) topic, 0);
               ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

           break;
           case MQTT_EVENT_DATA:
               ComposeTopic(topic,
                            GetSysConf()->mqttStation[ctx->mqtt_index].RootTopic,
                            "DOWNLINK",
                            GetSysConf()->mqttStation[ctx->mqtt_index].ClientID,
                            "USER");
               if (!memcmp(topic, event->topic, event->topic_len))
               {
                   //Here data for service called "USER"
                   ESP_LOGI(TAG, "USER data handler on client %d", ctx->mqtt_index);
               }
           break;

           default:
               ESP_LOGI(TAG, "Other event id:%d", event->event_id);
           break;
       }
}
