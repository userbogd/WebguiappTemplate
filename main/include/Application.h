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

HTTP_IO_RESULT HTTPPostCustomAPI(httpd_req_t *req, char *PostData);


#endif /* MAIN_INCLUDE_APPLICATION_H_ */
