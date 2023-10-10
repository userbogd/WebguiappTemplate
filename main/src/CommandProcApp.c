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

#define OBJECTS_NUMBER_APP (1)
#define EXEC_ACTIONS_MAX_NUMBER_APP (2)

static int ExecCommandParseApp(char *cmd);

static void APPLICATION_TEST1_handle(char *obj, char *com, char *arg)
{
    ESP_LOGI(TAG, "Object:%s, Command:%s, Argument %s",obj, com, arg);
}

static void APPLICATION_TEST2_handle(char *obj, char *com, char *arg)
{
    ESP_LOGI(TAG, "Object:%s, Command:%s, Argument %s",obj, com, arg);
}

typedef struct
{
    int index;
    char object_name[EXEC_OBJECT_NAME_MAX_LENGTH];
    char allowed_actions[EXEC_ACTIONS_MAX_NUMBER_APP][EXEC_ACTION_NAME_MAX_LENGTH];
    void (*command_handlers[EXEC_ACTIONS_MAX_NUMBER_APP])(char *obj, char *com, char *arg);
} app_obj_struct_t;

const app_obj_struct_t app_com_obj_arr[] = {
        {
                .index = 0,
                .object_name = "APPLICATION",
                .allowed_actions = { "TEST1", "TEST2" },
                .command_handlers = { &APPLICATION_TEST1_handle, &APPLICATION_TEST2_handle }
        }
};

void GetAppObjectsInfo(char *data)
{
    struct jWriteControl jwc;
    jwOpen(&jwc, data, VAR_MAX_VALUE_LENGTH, JW_ARRAY, JW_COMPACT);
    for (int idx = 0; idx < OBJECTS_NUMBER_APP; idx++)
    {
        jwArr_object(&jwc);
        jwObj_string(&jwc, "object", app_com_obj_arr[idx].object_name);
        jwObj_array(&jwc, "actions");
        for (int i = 0; i < EXEC_ACTIONS_MAX_NUMBER_APP; i++)
        {
            if ((app_com_obj_arr[idx].allowed_actions[i])[0] != NULL)
                jwArr_string(&jwc, app_com_obj_arr[idx].allowed_actions[i]);
        }
        jwEnd(&jwc);
        jwEnd(&jwc);
    }
    jwClose(&jwc);
}

int ExecAppCommand(char *cmd)
{
    return ExecCommandParseApp(cmd);
}

static int ExecCommandParseApp(char *cmd)
{
    char *obj = NULL, *com = NULL, *arg = NULL;
    int err = 0;
    int commlen = strlen(cmd);
    if (commlen > EXEC_COMMAND_MAX_LENGTH)
        return 1;
    char comm[EXEC_COMMAND_MAX_LENGTH + 1];
    const char del1 = ',';
    const char del2 = 0x00;
    strcpy(comm, cmd);
    obj = strtok(comm, &del1);
    com = strtok(NULL, &del1);
    arg = strtok(NULL, &del2);
    if (!obj)
        return 2;
    if (!com)
        return 2;
    err = 4;
    for (int idx = 0; idx < OBJECTS_NUMBER_APP; idx++)
    {
        if (!strcmp(obj, app_com_obj_arr[idx].object_name))
        {
            err = 5;
            for (int i = 0; i < EXEC_ACTIONS_MAX_NUMBER_APP; i++)
            {
                if (!strcmp(com, app_com_obj_arr[idx].allowed_actions[i]))
                {
                    if (app_com_obj_arr[idx].command_handlers[i] != NULL)
                    {
                        app_com_obj_arr[idx].command_handlers[i](obj, com, arg);
                        err = 0;
                    }
                    else
                        err = 6;
                }
            }
        }
    }
    return err;
}

