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
#include "led_strip.h"
#include "math.h"

extern APP_CONFIG AppConfig;

static void funct_time(char *argres, int rw)
{
    time_t now;
    time(&now);
    snprintf(argres, VAR_MAX_VALUE_LENGTH, "%d", (int) now);
}

#define GAMMA_R  (1.70)
#define GAMMA_G  (1.70)
#define GAMMA_B  (1.70)

static int GammaCorrection(int input, float gamma)
{
    return (int) ((float) 255 * pow(((float) input / 255), gamma));
}

static void funct_RGB(char *argres, int rw)
{
    struct jReadElement result;
    jRead(argres, "", &result);
    if (result.dataType == JREAD_OBJECT)
    {
        int R = jRead_int(argres, "{'R'", 0);
        int G = jRead_int(argres, "{'G'", 0);
        int B = jRead_int(argres, "{'B'", 0);

        R = GammaCorrection(R, GAMMA_R);
        G = GammaCorrection(G, GAMMA_G);
        B = GammaCorrection(B, GAMMA_B);

        led_strip_set_pixel(*LEDStripGetHandle(), 0, R, G, B);
        led_strip_refresh(*LEDStripGetHandle());

        struct jWriteControl jwc;
        jwOpen(&jwc, argres, VAR_MAX_VALUE_LENGTH, JW_OBJECT, JW_COMPACT);
        jwObj_int(&jwc, "R", R);
        jwObj_int(&jwc, "G", G);
        jwObj_int(&jwc, "B", B);
        jwEnd(&jwc);
        jwClose(&jwc);
    }
}

const rest_var_t ApplicationVariables[] =
{
    /*FUNCTIONS*/

    {   0, "mytime", &funct_time, VAR_FUNCT, R, 0, 0},
    {   0, "myvar", &AppConfig.test, VAR_INT, R, 0, 0},
    {   0, "RGB", &funct_RGB, VAR_FUNCT, R, 0, 0},

};

void RegAppVariables(void)
{
    SetAppVars((rest_var_t*) ApplicationVariables, sizeof(ApplicationVariables) / sizeof(rest_var_t));
}
