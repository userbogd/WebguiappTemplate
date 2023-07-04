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
 *   File name: HTTPAPICustom.c
 *     Project: webguiapp_ref_implement
 *  Created on: 2023-06-10
 *      Author: bogdan
 * Description:	
 */

#include "webguiapp.h"
#include "Application.h"

#define USER_API_VER "1.00"
#define TAG "HTTPAPICustom"

HTTP_IO_RESULT HTTPPostCustomAPI(httpd_req_t *req, char *PostData)
{
    char data[1024];
    httpd_req_get_hdr_value_str(req, "Content-Type", (char*) data, 31);
    if (!memcmp(data, "application/json", sizeof("application/json")))
    {
        char *respbuf = malloc(EXPECTED_MAX_DATA_RESPONSE_SIZE);
        if (respbuf)
        {
            data_message_t M = { 0 };
            M.inputDataBuffer = PostData;
            M.inputDataLength = strlen(PostData);
            M.chlidx = 100;
            M.outputDataBuffer = respbuf;
            M.outputDataLength = EXPECTED_MAX_DATA_RESPONSE_SIZE;
            AppServiceDataHandler(&M);
            httpd_resp_sendstr(req, respbuf);
            free(respbuf);
            return HTTP_IO_DONE_API;
        }
        else
        {
            ESP_LOGE(TAG, "Out of free RAM for HTTP API handle");
            httpd_resp_set_status(req, HTTPD_500);
            return HTTP_IO_DONE_API;
        }
    }

    httpd_resp_set_status(req, HTTPD_400);
    return HTTP_IO_DONE_API;
}
