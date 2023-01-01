#include <stdio.h>
#include <string.h>
#include "Display.h"

#include "ssd1306/ssd1306.h"
#include "ssd1306/ssd1306_draw.h"
#include "ssd1306/ssd1306_font.h"
#include "ssd1306/ssd1306_default_if.h"

#include "sh1106/sh1106.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_idf_version.h"


#define USE_I2C_DISPLAY
//#define USE_SPI_DISPLAY

#if defined USE_I2C_DISPLAY
static const int I2CDisplayAddress = 0x3C;
static const int I2CDisplayWidth = 128;
static const int I2CDisplayHeight = 64;
static const int I2CResetPin = -1;
struct SSD1306_Device I2CDisplay;
char buf[8][22];
static const char *TAG = "DisplayModule";
#endif

#define TAKE_TIMEOUT pdMS_TO_TICKS(5000)
SemaphoreHandle_t xSemaphoreDispHandle = NULL;
StaticSemaphore_t xSemaphoreDispBuf;

static bool isDisplayPresent = false;

bool DefaultBusInit(void)
{
    assert(SSD1306_I2CMasterInitDefault() == true);
    assert(
           SSD1306_I2CMasterAttachDisplayDefault( &I2CDisplay, I2CDisplayWidth, I2CDisplayHeight, I2CDisplayAddress, I2CResetPin ) == true);
    SSD1306_SetHFlip(&I2CDisplay, true);
    SSD1306_SetVFlip(&I2CDisplay, true);
    return true;
}

void InitDisplay(void)
{
    xSemaphoreDispHandle = xSemaphoreCreateBinaryStatic(&xSemaphoreDispBuf);
    xSemaphoreGive(xSemaphoreDispHandle);
#ifdef DISPLAY_TYPE_SSD1306
  if (DefaultBusInit() == true)
  {
    isDisplayPresent = true;
    SSD1306_Clear(&I2CDisplay, SSD_COLOR_BLACK);
    SSD1306_SetFont(&I2CDisplay, &Font_droid_sans_fallback_24x28);
    SSD1306_FontDrawString(&I2CDisplay, 15, 12, "\"IoTronic\"", SSD_COLOR_XOR);
    SSD1306_SetFont(&I2CDisplay, &Font_droid_sans_mono_7x13);
    SSD1306_FontDrawString(&I2CDisplay, 8, 12 + 28 + 4, "LoRaWAN End Node", SSD_COLOR_XOR);
    SSD1306_Update(&I2CDisplay);
  }
#endif
#ifdef  DISPLAY_TYPE_SH1106
    if (sh1106_init() != ESP_OK)
        return;
    isDisplayPresent = true;
#endif
}

void ClearDisplay(void)
{
    if (!isDisplayPresent)
        return;
    xSemaphoreTake(xSemaphoreDispHandle, TAKE_TIMEOUT);
#ifdef DISPLAY_TYPE_SSD1306
    SSD1306_Clear(&I2CDisplay, SSD_COLOR_BLACK);
    SSD1306_Update(&I2CDisplay);
#endif
#ifdef  DISPLAY_TYPE_SH1106
    task_sh1106_display_clear(NULL);
#endif
    xSemaphoreGive(xSemaphoreDispHandle);
}

void ReadDisplay(char *str, int strnum)
{
    if (!isDisplayPresent)
        return;
    xSemaphoreTake(xSemaphoreDispHandle, TAKE_TIMEOUT);
#ifdef DISPLAY_TYPE_SSD1306
memcpy(str, &buf[strnum][0], 18);
#endif
#ifdef  DISPLAY_TYPE_SH1106
    memcpy(str, &buf[strnum][0], 22);
#endif
    xSemaphoreGive(xSemaphoreDispHandle);
}

void WriteDisplay(char *str, int strnum)
{
    if (!isDisplayPresent)
        return;
    xSemaphoreTake(xSemaphoreDispHandle, TAKE_TIMEOUT);
#ifdef DISPLAY_TYPE_SSD1306
    memcpy(&buf[strnum][0], str, 18);
    buf[strnum][18] = 0x00;
#endif
#ifdef  DISPLAY_TYPE_SH1106
    memcpy(&buf[strnum][0], str, 22);
    task_sh1106_write_string(str, strnum);
#endif
    xSemaphoreGive(xSemaphoreDispHandle);
}

void UpdateDisplay(void)
{
    if (!isDisplayPresent)
        return;
#ifdef DISPLAY_TYPE_SSD1306
    SSD1306_Clear(&I2CDisplay, SSD_COLOR_BLACK);
    SSD1306_FontDrawString(&I2CDisplay, 0, 0, &buf[0][0], SSD_COLOR_XOR);
    SSD1306_FontDrawString(&I2CDisplay, 0, 13, &buf[1][0], SSD_COLOR_XOR);
    SSD1306_FontDrawString(&I2CDisplay, 0, 13 * 2, &buf[2][0], SSD_COLOR_XOR);
    SSD1306_FontDrawString(&I2CDisplay, 0, 13 * 3, &buf[3][0], SSD_COLOR_XOR);
    SSD1306_FontDrawString(&I2CDisplay, 0, 13 * 4, &buf[4][0], SSD_COLOR_XOR);
    SSD1306_Update(&I2CDisplay);
#endif
#ifdef  DISPLAY_TYPE_SH1106
    //for compatibility with other displays
    return;
    task_sh1106_display_clear(NULL);
    task_sh1106_write_string(&buf[0][0], 0);
    task_sh1106_write_string(&buf[1][0], 1);
    task_sh1106_write_string(&buf[2][0], 2);
    task_sh1106_write_string(&buf[3][0], 3);
    task_sh1106_write_string(&buf[4][0], 4);
    task_sh1106_write_string(&buf[5][0], 5);
    task_sh1106_write_string(&buf[6][0], 6);
    task_sh1106_write_string(&buf[7][0], 7);
#endif
}
