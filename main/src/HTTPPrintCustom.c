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
 *  	 \file HTTPPrintCustom.c
 *    \version 1.0
 * 		 \date 2022-08-18
 *     \author Bogdan Pilyugin
 * 	    \brief    
 *    \details 
 *	\copyright Apache License, Version 2.0
 */
#include "webguiapp.h"
#include "jWrite.h"
#include "AppConfiguration.h"
#include "CronTimers.h"

static void HTTPPrint_crontmr(char *VarData, void *arg)
{
   int idx = *((int*)(arg));
   if(idx < CRON_TIMERS_NUMBER)
   {
    char data[256];
    cron_timer_t T;
    memcpy(&T, &GetAppConf()->Timers[idx], sizeof(cron_timer_t));
    jwOpen(data, sizeof(data), JW_OBJECT, JW_COMPACT);
    jwObj_int("num", (unsigned int) T.num);
    jwObj_int("del", (T.del)?1:0);
    jwObj_int("enab", (T.enab)?1:0);
    jwObj_int("prev", (T.prev)?1:0);
    jwObj_string("name", T.name);
    jwObj_int("obj", (unsigned int) T.obj);
    jwObj_int("act", (unsigned int) T.act);
    jwObj_string("cron", T.cron);
    jwEnd();
    jwClose();
    snprintf(VarData, MAX_DYNVAR_LENGTH, "%s", data);
   }
}

static void HTTPPrint_cronerr(char *VarData, void *arg)
{
    snprintf(VarData, MAX_DYNVAR_LENGTH, GetCronError());
}

//Default string if not found handler
static void HTTPPrint_DEF(char *VarData, void *arg)
{
    snprintf(VarData, MAX_DYNVAR_LENGTH, "#DEF");
}

static void HTTPPrint_status_fail(char *VarData, void *arg)
{
    snprintf(VarData, MAX_DYNVAR_LENGTH, "none");
}

dyn_var_handler_t HANDLERS_ARRAY_CUST[] = {

        { "crontmr", sizeof("crontmr") - 1, &HTTPPrint_crontmr },
        { "cronerr", sizeof("cronerr") - 1, &HTTPPrint_cronerr },
        /*ERROR report*/
        { "status_fail", sizeof("status_fail") - 1, &HTTPPrint_status_fail },

};


int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var, int arg)
{
    char VarData[MAX_DYNVAR_LENGTH];
    bool fnd = false;
    //searching for tag in handles array
    for (int i = 0; i < (sizeof(HANDLERS_ARRAY_CUST) / sizeof(HANDLERS_ARRAY_CUST[0])); ++i)
    {
        if (strcmp(var, HANDLERS_ARRAY_CUST[i].tag) == 0
                && HANDLERS_ARRAY_CUST[i].HandlerRoutine != NULL)
        {
            HANDLERS_ARRAY_CUST[i].HandlerRoutine(VarData, (void*) &arg);
            fnd = true;
            break;
        }
    }
    if (!fnd)
    {
            HTTPPrint_DEF(VarData, NULL);
    }
    int dLen = strlen(VarData);
    memcpy(buf, VarData, dLen);
    return dLen;
}
