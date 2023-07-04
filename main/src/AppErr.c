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
 *  	 \file SpiralControllerErr.c
 *    \version 1.0
 * 		 \date 2023-06-03
 *     \author Bogdan Pilyugin
 * 	    \brief    
 *    \details 
 *	\copyright Apache License, Version 2.0
 */
#include "Application.h"

#define TAG "AppErr"

typedef struct
{
    app_error_code errcode;
    char *errbreaf;
    char *errdescr;
} spiral_error_t;

const spiral_error_t Errors[] = {
        {APP_OK_DATA, "APP_OK_DATA", "Result successful, data attached" },
        {APP_OK, "APP_OK", "Result successful" },

        { APP_ERROR_WRONG_JSON_FORMAT, "APP_ERROR_WRONG_JSON_FORMAT", "Wrong JSON format or not JSON data" },
        { APP_ERROR_PARSE_DATA, "APP_ERROR_PARSE_PAYLOAD", "Payload object not found"},
        { APP_ERROR_SHA256_DATA, "APP_ERROR_SHA256_PAYLOAD", "SHA256 signature is not valid"},
        { APP_ERROR_PARSE_SIGNATURE, "APP_ERROR_PARSE_SIGNATURE", "Key 'signature' not found"},
        { APP_ERROR_PARSE_MESSAGEID, "APP_ERROR_PARSE_MESSAGEID", "Key 'msgid' not found or have illegal value" },
        { APP_ERROR_PARSE_MSGTYPE, "APP_ERROR_PARSE_MSGTYPE", "Key 'msgtype' not found or have illegal value"},
        { APP_ERROR_PARSE_PAYLOADTYPE, "APP_ERROR_PARSE_PAYLOADTYPE", "Key 'payloadtype' not found or have illegal value"},

        { APP_ERROR_PARSE_KEY1, "APP_ERROR_PARSE_KEY1", "Key 'key1' not found or have illegal value"},
        { APP_ERROR_PARSE_KEY2, "APP_ERROR_PARSE_KEY2", "Key 'key2' not found or have illegal value"},

        { APP_ERROR_NO_MEMORY, "APP_ERROR_NO_MEMORY", "ERROR allocate memory for JSON parser" },
        { APP_ERROR_UNKNOWN, "APP_ERROR_UNKNOWN", "Unknown ERROR" }

};

void GetAppErrorDetales(app_error_code err, const char **br, const char **ds)
{
    *br = Errors[sizeof(Errors) / sizeof(spiral_error_t) - 1].errbreaf;
    *ds = Errors[sizeof(Errors) / sizeof(spiral_error_t) - 1].errdescr;

    for (int i = 0; i < sizeof(Errors) / sizeof(spiral_error_t); i++)
    {
        if (err == Errors[i].errcode)
        {
            *br = Errors[i].errbreaf;
            *ds = Errors[i].errdescr;
            return;
        }
    }
    return;
}

