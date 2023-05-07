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
 *   File name: CronTimers.h
 *     Project: webguiapp_ref_implement
 *  Created on: 2023-04-15
 *      Author: bogdan
 * Description:	
 */

#ifndef MAIN_INCLUDE_CRONTIMERS_H_
#define MAIN_INCLUDE_CRONTIMERS_H_
#include "esp_err.h"
#include "cron.h"
#include "jobs.h"
#include "ccronexpr.h"

esp_err_t InitCronSheduler();
esp_err_t ReloadCronSheduler();
char* GetCronError();
void DebugTimer();

/**
 * \brief Handle all actions under all objects
 * \param obj  Index of the object
 * \param act  Index of the action
 */
void custom_cron_execute(int obj, int act);

#endif /* MAIN_INCLUDE_CRONTIMERS_H_ */
