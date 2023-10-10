/*! Copyright 2023 Bogdan Pilyugin
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
 *  	 \file RestApiHandlersApp.c
 *    \version 1.0
 * 		 \date 2023-08-17
 *     \author Bogdan Pilyugin
 * 	    \brief    
 *    \details 
 *	\copyright Apache License, Version 2.0
 */

#include <CronTimers.h>
#include "webguiapp.h"
#include "AppConfiguration.h"

extern APP_CONFIG AppConfig;

static void funct_cronrecs(char *argres, int rw)
{
    struct jWriteControl jwc;
    jwOpen(&jwc, argres, VAR_MAX_VALUE_LENGTH, JW_ARRAY, JW_COMPACT);
    for (int idx = 0; idx < CRON_TIMERS_NUMBER; idx++)
    {
        cron_timer_t T;
        memcpy(&T, &GetAppConf()->Timers[idx], sizeof(cron_timer_t));
        jwArr_object(&jwc);
        jwObj_int(&jwc, "num", (unsigned int) T.num);
        jwObj_int(&jwc, "del", (T.del) ? 1 : 0);
        jwObj_int(&jwc, "enab", (T.enab) ? 1 : 0);
        jwObj_int(&jwc, "prev", (T.prev) ? 1 : 0);
        jwObj_string(&jwc, "name", T.name);
        jwObj_int(&jwc, "obj", (unsigned int) T.obj);
        jwObj_int(&jwc, "act", (unsigned int) T.act);
        jwObj_string(&jwc, "cron", T.cron);
        jwEnd(&jwc);
    }
    jwClose(&jwc);
}

static void funct_cronobjs(char *argres, int rw)
{
    struct jWriteControl jwc;
    jwOpen(&jwc, argres, VAR_MAX_VALUE_LENGTH, JW_ARRAY, JW_COMPACT);
    for (int idx = 0; idx < CRON_OBJECTS_NUMBER; idx++)
    {
        jwArr_object(&jwc);
        jwObj_string(&jwc, "name", GetAppConf()->CronObjects[idx].objname);
        jwObj_raw(&jwc, "acts", GetCronActAvail(idx));
        jwEnd(&jwc);
    }
    jwClose(&jwc);
}

static void funct_cronacts(char *argres, int rw)
{
    struct jWriteControl jwc;
    jwOpen(&jwc, argres, VAR_MAX_VALUE_LENGTH, JW_ARRAY, JW_COMPACT);
    for (int idx = 0; idx < CRON_OBJECTS_NUMBER; idx++)
    {
        jwArr_string(&jwc, GetCronActionName(idx));
    }
    jwClose(&jwc);
}

static void funct_time(char *argres, int rw)
{
    time_t now;
    time(&now);
    snprintf(argres, MAX_DYNVAR_LENGTH, "%d", (int) now);
}

const rest_var_t ApplicationVariables[] =
        {
                /*FUNCTIONS*/
                { 0, "cronrecs", &funct_cronrecs, VAR_FUNCT, R, 0, 0 },
                { 0, "cronobjs", &funct_cronobjs, VAR_FUNCT, R, 0, 0 },
                { 0, "cronacts", &funct_cronacts, VAR_FUNCT, R, 0, 0 },

                { 0, "mytime", &funct_time, VAR_FUNCT, R, 0, 0 },
                { 0, "myvar", &AppConfig.test, VAR_INT, R, 0, 0 }

        };

void RegAppVariables(void)
{
    SetAppVars((rest_var_t*) ApplicationVariables, sizeof(ApplicationVariables) / sizeof(rest_var_t));
}
