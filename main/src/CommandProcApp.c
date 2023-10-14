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
 *   File name: CommandProcApp.c
 *     Project: WebguiappTemplate
 *  Created on: 2023-10-09
 *      Author: bogdan
 * Description:	
 */

#include "webguiapp.h"

#define TAG "COMMAND_PROC_APP"

static void APPLICATION_TEST1_handle(char *obj, char *com, char *arg)
{
    ESP_LOGI(TAG, "Object:%s, Command:%s, Argument %s",obj, com, arg);
}

static void APPLICATION_TEST2_handle(char *obj, char *com, char *arg)
{
    ESP_LOGI(TAG, "Object:%s, Command:%s, Argument %s",obj, com, arg);
}


const obj_struct_t app_com_obj_arr[] = {
        {
                .index = 0,
                .object_name = "APPLICATION",
                .allowed_actions = { "TEST1", "TEST2" },
                .command_handlers = { &APPLICATION_TEST1_handle, &APPLICATION_TEST2_handle }
        },
        {
                .index = 1,
                .object_name = "APPLICATION2",
                .allowed_actions = { "TEST1", "TEST2", "TEST3" },
                .command_handlers = { &APPLICATION_TEST1_handle, &APPLICATION_TEST2_handle }
        },
        { 0 }
};

void RegObjects(void)
{
    SetCustomObjects((obj_struct_t*) app_com_obj_arr);
}


