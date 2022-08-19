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
#include "HTTPServer.h"

//Default string if not found handler
static void HTTPPrint_DEF(char *VarData, void *arg)
{
    snprintf(VarData, MAX_DYNVAR_LENGTH, "#DEF");
}

void HTTPPrint_topic2(char *VarData, void *arg)
{
    snprintf(VarData, MAX_DYNVAR_LENGTH, "%s", "custom-dyn_var");
}

static void HTTPPrint_status_fail(char *VarData, void *arg)
{
    snprintf(VarData, MAX_DYNVAR_LENGTH, "none");
}

dyn_var_handler_t HANDLERS_ARRAY_CUST[] = {

        /*ERROR report*/
        { "topic2", sizeof("topic2") - 1, &HTTPPrint_topic2 },
        { "status_fail", sizeof("status_fail") - 1, &HTTPPrint_status_fail },

};


int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var)
{
    char VarData[MAX_DYNVAR_LENGTH];
    const char incPat[] = "inc:";
    const int incPatLen = sizeof(incPat) - 1;
    if (!memcmp(var, incPat, incPatLen))
    {
        const char rootFS[] = "/";
        char filename[32];
        filename[0] = 0x00;
        var += incPatLen;
        strcat(filename, rootFS);
        strcat(filename, var);
        espfs_file_t *file = espfs_fopen(fs, filename);
        struct espfs_stat_t stat;
        if (file)
        {
            espfs_fstat(file, &stat);
            int readBytes = espfs_fread(file, buf, stat.size);
            espfs_fclose(file);
            return readBytes;
        }
    }

    bool fnd = false;
    char *p2 = var + strlen(var) - 1; //last var symbol
    int arg = 0;
    //searching for tag in handles array
    for (int i = 0; i < (sizeof(HANDLERS_ARRAY_CUST) / sizeof(HANDLERS_ARRAY_CUST[0])); ++i)
    {
        if (*p2 == ')')
        { //found close brace
            char *p1 = p2;
            while ((*p1 != '(') && (p1 > var))
                --p1;
            if (*p1 == '(')
            { //found open brace
                *p1 = 0x00; //trim variable to name part
                ++p1; //to begin of argument
                *p2 = 0x00; //set end of argument
                arg = atoi(p1);
            }
        }
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
