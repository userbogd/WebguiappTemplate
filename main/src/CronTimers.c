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

static cron_job *JobsList[CRON_TIMERS_NUMBER];

void custom_cron_job_callback(cron_job *job)
{
    int act = ((cron_timer_t*) job->data)->act;
    int obj = ((cron_timer_t*) job->data)->obj;
    char *name = ((cron_timer_t*) job->data)->name;
    //here call all timers jobs depends on object and action
    ESP_LOGI(TAG, "Executed timer '%s' action %d under object %d", name, act, obj);
    return;
}

esp_err_t InitCronSheduler()
{
    esp_err_t res = ESP_OK;
    return res;
}

esp_err_t ReloadCronSheduler()
{
    //remove all jobs
    ESP_LOGI(TAG,"Cron stop call result %d",cron_stop());
    cron_job_clear_all();
    //check if we have jobs to run
    for (int i = 0; i < CRON_TIMERS_NUMBER; i++)
    {
        if (!GetAppConf()->Timers[i].del && GetAppConf()->Timers[i].enab)
        {
            JobsList[i] = cron_job_create(GetAppConf()->Timers[i].cron, custom_cron_job_callback,
                                          (void*) &GetAppConf()->Timers[i]);
        }
    }
    int jobs_num = cron_job_node_count();
    ESP_LOGI(TAG, "In config presents %d jobs", jobs_num);

    if (jobs_num > 0)
        ESP_LOGI(TAG,"Cron start call result %d",cron_start());
    return ESP_OK;
}

