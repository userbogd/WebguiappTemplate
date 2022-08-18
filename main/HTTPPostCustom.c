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
 *  	 \file HTTPPostCustom.c
 *    \version 1.0
 * 		 \date 2022-08-18
 *     \author Bogdan Pilyugin
 * 	    \brief    
 *    \details 
 *	\copyright Apache License, Version 2.0
 */
#include "HTTPServer.h"

const char pg_40[] = "index40.html";
const char pg_42[] = "index42.html";
const char pg_43[] = "index43.html";
const char pg_44[] = "index44.html";

static HTTP_IO_RESULT HTTPPostIndex40(httpd_req_t *req, char *PostData);
static HTTP_IO_RESULT HTTPPostIndex42(httpd_req_t *req, char *PostData);
static HTTP_IO_RESULT HTTPPostIndex43(httpd_req_t *req, char *PostData);
static HTTP_IO_RESULT HTTPPostIndex44(httpd_req_t *req, char *PostData);

HTTP_IO_RESULT AfterPostHandlerCustom(httpd_req_t *req, const char *filename, char *PostData)
{


    if (!memcmp(filename, pg_40, sizeof(pg_40)))
        return HTTPPostIndex40(req, PostData);
    if (!memcmp(filename, pg_42, sizeof(pg_42)))
        return HTTPPostIndex42(req, PostData);
    if (!memcmp(filename, pg_43, sizeof(pg_43)))
        return HTTPPostIndex43(req, PostData);
    if (!memcmp(filename, pg_44, sizeof(pg_44)))
        return HTTPPostIndex44(req, PostData);


    return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostIndex40(httpd_req_t *req, char *PostData)
{
    char tmp[8];
    if (httpd_query_key_value(PostData, "cmd", tmp, 4) == ESP_OK)
    {
        if (!strcmp(tmp, (const char*) "1"))
        {
           // SetCTRL_BAT(ON);
        }
        else if (!strcmp(tmp, (const char*) "2"))
        {
           // SetCTRL_BAT(OFF);
        }
        else if (!strcmp(tmp, (const char*) "3"))
        {
            //MQTTStart();
        }
        else if (!strcmp(tmp, (const char*) "4"))
        {
            // MQTTStop();
        }
        else if (!strcmp(tmp, (const char*) "5"))
        {

        }
        else if (!strcmp(tmp, (const char*) "6"))
        {

        }
        else if (!strcmp(tmp, (const char*) "7"))
        {
            //SetDefaultNetIF(GetETHNetifAdapter());
        }
        else if (!strcmp(tmp, (const char*) "8"))
        {
            //SetDefaultNetIF(GetSTANetifAdapter());
        }
        else if (!strcmp(tmp, (const char*) "9"))
        {
            //SetDefaultNetIF(GetPPPNetifAdapter());
        }
        else if (!strcmp(tmp, (const char*) "10"))
        {
            //NextDefaultNetIF();
        }
        else if (!strcmp(tmp, (const char*) "11"))
        {
            //PrintNetifs();
        }
        else if (!strcmp(tmp, (const char*) "12"))
        {
           // SendTestEvent();
        }

    }
    return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostIndex42(httpd_req_t *req, char *PostData)
{
    return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostIndex43(httpd_req_t *req, char *PostData)
{
    return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostIndex44(httpd_req_t *req, char *PostData)
{
    return HTTP_IO_DONE;
}

