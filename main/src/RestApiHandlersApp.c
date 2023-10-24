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

#include "webguiapp.h"
#include "AppConfiguration.h"

extern APP_CONFIG AppConfig;


static void funct_time(char *argres, int rw)
{
    time_t now;
    time(&now);
    snprintf(argres, VAR_MAX_VALUE_LENGTH, "%d", (int) now);
}

const rest_var_t ApplicationVariables[] =
        {
                /*FUNCTIONS*/

                { 0, "mytime", &funct_time, VAR_FUNCT, R, 0, 0 },
                { 0, "myvar", &AppConfig.test, VAR_INT, R, 0, 0 }

        };

void RegAppVariables(void)
{
    SetAppVars((rest_var_t*) ApplicationVariables, sizeof(ApplicationVariables) / sizeof(rest_var_t));
}
