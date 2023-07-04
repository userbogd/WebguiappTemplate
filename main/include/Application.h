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
 *   File name: Application.h
 *     Project: webguiapp_ref_implement
 *  Created on: 2023-06-10
 *      Author: bogdan
 * Description:	
 */

#ifndef MAIN_INCLUDE_APPLICATION_H_
#define MAIN_INCLUDE_APPLICATION_H_

#include "webguiapp.h"
#include "esp_err.h"
#include "jRead.h"
#include "jWrite.h"
#include "AppConfiguration.h"

#define EXPECTED_MAX_DATA_RESPONSE_SIZE (2048)

typedef enum
{
    APP_OK_DATA = 0,
    APP_OK,

    APP_ERROR_WRONG_JSON_FORMAT = 200,
    APP_ERROR_PARSE_DATA,
    APP_ERROR_SHA256_DATA,

    APP_ERROR_PARSE_SIGNATURE,
    APP_ERROR_PARSE_MESSAGEID,
    APP_ERROR_PARSE_MSGTYPE,
    APP_ERROR_PARSE_PAYLOADTYPE,

    APP_ERROR_PARSE_KEY1,
    APP_ERROR_PARSE_KEY2,

    APP_ERROR_NO_MEMORY = 300,
    APP_ERROR_UNKNOWN,

} app_error_code;

typedef enum
{
    APP_MSG_COMMAND = 1,
    APP_MSG_REQUEST,
    APP_MSG_RESPONSE
} app_msg_type;

typedef struct
{
int key1;
int key2;

} payload_type_1;


#define DATA_MESSAGE_TYPE_COMMAND  (1)
#define DATA_MESSAGE_TYPE_REQUEST  (2)
#define DATA_MESSAGE_TYPE_RESPONSE  (3)

typedef struct
{
    char *inputDataBuffer;
    int inputDataLength;
    int chlidx;
    char *outputDataBuffer;
    int outputDataLength;
    struct
    {
        uint64_t msgID;
        time_t time;
        int msgType;
        int payloadType;
        void *payload;
        unsigned char sha256[32];
    } parsedData;
    int err_code;
} data_message_t;

typedef struct
{
    char transID[64];
    char transTime[32];
    int64_t transact_sm_timer;            // ocpp state machine timeout timer
    int64_t interpulse_timer;
    bool isActive;

    bool isInitialised;
    int idx;
} app_handle_t;


esp_err_t AppServiceDataHandler(data_message_t *MSG);
void GetAppErrorDetales(app_error_code err, const char **br, const char **ds);

HTTP_IO_RESULT HTTPPostCustomAPI(httpd_req_t *req, char *PostData);


#endif /* MAIN_INCLUDE_APPLICATION_H_ */
