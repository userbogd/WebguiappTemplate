/*
 * PortExtender.c
 *
 *  Created on: 22 окт. 2021 г.
 *      Author: bogd
 */
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "PortExtender.h"
#include "esp_log.h"

#if CONFIG_PORTS_EXTENDER_ENABLE
#define VGPO_MOSI_PIN   (CONFIG_VGPO_MOSI_PIN)
#define VGPO_CLK_PIN   (CONFIG_VGPO_CLK_PIN)
#define VGPO_LAT_PIN   (CONFIG_VGPO_LAT_PIN)

#define TAKE_TIMEOUT pdMS_TO_TICKS(5000)

#define SHIFR_REGS_CHAIN 5

uint8_t VGPO[SHIFR_REGS_CHAIN] = { 0xff, 0xff, 0xff, 0b00000111, 0b10001000 };
SemaphoreHandle_t xSemaphoreVGPOHandle = NULL;
StaticSemaphore_t xSemaphoreVGPOBuf;

void UpdateVGPO(void)
{
    for (uint8_t byte = 0; byte < sizeof(VGPO); ++byte)
    {
        for (uint8_t bit = 0; bit < 8; ++bit)
        {
            GPIO.out_w1tc = ((uint32_t) 1 << VGPO_CLK_PIN);
            if (VGPO[byte] & 0x80 >> bit)
                GPIO.out_w1ts = ((uint32_t) 1 << VGPO_MOSI_PIN);
            else
                GPIO.out_w1tc = ((uint32_t) 1 << VGPO_MOSI_PIN);
            GPIO.out_w1ts = ((uint32_t) 1 << VGPO_CLK_PIN);
        }
    }
    GPIO.out_w1tc = ((uint32_t) 1 << VGPO_MOSI_PIN);
    GPIO.out_w1tc = ((uint32_t) 1 << VGPO_CLK_PIN);
    GPIO.out_w1ts = ((uint32_t) 1 << VGPO_LAT_PIN);
    GPIO.out_w1tc = ((uint32_t) 1 << VGPO_LAT_PIN);
}



void InitVGPO(void)
{
    gpio_pad_select_gpio(VGPO_MOSI_PIN);
    gpio_pad_select_gpio(VGPO_CLK_PIN);
    gpio_pad_select_gpio(VGPO_LAT_PIN);
    gpio_set_direction(VGPO_MOSI_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(VGPO_MOSI_PIN, 0);
    gpio_set_direction(VGPO_CLK_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(VGPO_CLK_PIN, 0);
    gpio_set_direction(VGPO_LAT_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(VGPO_LAT_PIN, 0);
    xSemaphoreVGPOHandle = xSemaphoreCreateBinaryStatic(&xSemaphoreVGPOBuf);
    xSemaphoreGive(xSemaphoreVGPOHandle);
    UpdateVGPO();
}

void SetADCInput(uint8_t N)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    if (N > 0)
    {
        if (N <= 8)
            VGPO[SHIFR_REGS_CHAIN - 1] = (0x80 | ((N - 1) & 0x7));
        else
            VGPO[SHIFR_REGS_CHAIN - 1] = (0x08 | (((N - 1) & 0x7) << 4));
    }
    else
    {
        VGPO[SHIFR_REGS_CHAIN - 1] = 0x88;
    }
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetRS485_RE(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 0)) | (level << 0);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetCTRL_BAT(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 1)) | (level << 1);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetCHECK_BAT(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 2)) | (level << 2);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetPGM1(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 3)) | (level << 3);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetPGM2(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 4)) | (level << 4);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetLORA_RST(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 5)) | (level << 5);
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetGSM_PWR(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 6)) | (level << 6);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetETH_RST(uint8_t level)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - 2] = (VGPO[SHIFR_REGS_CHAIN - 2] & ~(1 << 7)) | (level << 7);
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

void SetLEDSRegister(uint8_t addr, uint8_t data)
{
    xSemaphoreTake(xSemaphoreVGPOHandle, TAKE_TIMEOUT);
    VGPO[SHIFR_REGS_CHAIN - (3 + addr)] = data;
    UpdateVGPO();
    xSemaphoreGive(xSemaphoreVGPOHandle);
}

#endif
