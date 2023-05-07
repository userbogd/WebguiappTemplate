/* Copyright 2023 Bogdan Pilyugin
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
 *   File name: CronTimers.c
 *     Project: webguiapp_ref_implement
 *  Created on: 2023-04-15
 *      Author: bogdan
 * Description:	
 */

#include "CronTimers.h"
#include "AppConfiguration.h"
#include "esp_log.h"

#define TAG "CRON_TIMER"

const char *cron_objects[] = { "RELAY1", "RELAY2", "RELAY3", "RELAY4", "RELAY5", "SYSTEM" };
const char *cron_actions[] = { "ON", "OFF", "REBOOT" };

static cron_job *JobsList[CRON_TIMERS_NUMBER];
static char cron_express_error[CRON_EXPRESS_MAX_LENGTH];

char* GetCronError()
{
    return cron_express_error;
}

/**
 * \brief Handle all actions under all objects
 * \param obj  Index of the object
 * \param act  Index of the action
 */
void custom_cron_execute(int obj, int act)
{



}

void custom_cron_job_callback(cron_job *job)
{
    int act = ((cron_timer_t*) job->data)->act;
    int obj = ((cron_timer_t*) job->data)->obj;
    char *name = ((cron_timer_t*) job->data)->name;
    //here call all timers jobs depends on object and action
    time_t now;
    time(&now);
    ESP_LOGI(TAG, "Executed timer '%s' action %d under object %d at time %d", name, act, obj, (unsigned int )now);
    custom_cron_execute(obj, act);
    return;
}

esp_err_t InitCronSheduler()
{
    esp_err_t res = ESP_OK;
    return res;
}

const char* check_expr(const char *expr)
{
    const char *err = NULL;
    cron_expr test;
    memset(&test, 0, sizeof(test));
    cron_parse_expr(expr, &test, &err);
    return err;
}


static void ExecuteLastAction()
{
    int obj;
    for (obj = 0; obj < sizeof(cron_objects); obj++)
    {
        int shdl;
        time_t now;
        time(&now);
        time_t delta = now;
        int act = -1;

        for (shdl = 0; shdl < CRON_TIMERS_NUMBER; shdl++)
        {
            if (GetAppConf()->Timers[shdl].enab &&
                    !GetAppConf()->Timers[shdl].del &&
                    GetAppConf()->Timers[shdl].prev &&
                    GetAppConf()->Timers[shdl].obj == obj)
            {
                cron_expr cron_exp = { 0 };
                cron_parse_expr(GetAppConf()->Timers[shdl].cron, &cron_exp, NULL);
                time_t prev = cron_prev(&cron_exp, now);
                if ((now - prev) < delta)
                {
                    delta = (now - prev);
                    act = GetAppConf()->Timers[shdl].act;
                }
            }
        }

        if(act != -1)
        {
            ESP_LOGW(TAG, "Needed execute lost action %d with object %d", act, obj);
            custom_cron_execute(obj, act);
        }

    }

}

void TimeObtainHandler(struct timeval *tm)
{
    ESP_LOGW(TAG, "Current time received with value %d", (unsigned int )tm->tv_sec);
    ReloadCronSheduler();
    ExecuteLastAction();
}

void DebugTimer()
{
    time_t now;
    time(&now);
    ESP_LOGW(TAG, "Timestamp %d", (unsigned int )now);
    for (int i = 0; i < CRON_TIMERS_NUMBER; i++)
    {
        if (GetAppConf()->Timers[i].del)
            continue;
        ESP_LOGW(TAG, "Cron expression:%s", GetAppConf()->Timers[i].cron);
        cron_expr cron_exp = { 0 };
        cron_parse_expr(GetAppConf()->Timers[i].cron, &cron_exp, NULL);
        ESP_LOGW(TAG, "Timer %d prev: %u", i, (unsigned int )cron_prev(&cron_exp, now));
        ESP_LOGW(TAG, "Timer %d next: %u", i, (unsigned int )cron_next(&cron_exp, now));
    }
}

esp_err_t ReloadCronSheduler()
{
    //remove all jobs
    ESP_LOGI(TAG, "Cron stop call result %d", cron_stop());
    cron_job_clear_all();
    //check if we have jobs to run
    bool isExpressError = false;
    for (int i = 0; i < CRON_TIMERS_NUMBER; i++)
    {
        const char *err = check_expr(GetAppConf()->Timers[i].cron);
        if (err)
        {
            snprintf(cron_express_error, CRON_EXPRESS_MAX_LENGTH - 1, "In timer %d expression error:%s", i + 1, err);
            ESP_LOGE(TAG, "%s", cron_express_error);
            isExpressError = true;
            continue;
        }
        else if (!GetAppConf()->Timers[i].del && GetAppConf()->Timers[i].enab)
        {
            JobsList[i] = cron_job_create(GetAppConf()->Timers[i].cron, custom_cron_job_callback,
                                          (void*) &GetAppConf()->Timers[i]);
        }
    }
    if (!isExpressError)
        cron_express_error[0] = 0x00; //clear last cron expression parse
    int jobs_num = cron_job_node_count();
    ESP_LOGI(TAG, "In config presents %d jobs", jobs_num);

    if (jobs_num > 0)
        ESP_LOGI(TAG, "Cron start call result %d", cron_start());
    return ESP_OK;
}

