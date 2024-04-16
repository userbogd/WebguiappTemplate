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
 *  	 \file AppConfiguration.c
 *    \version 1.0
 * 		 \date 2023-03-08
 *     \author Bogdan Pilyugin
 * 	    \brief    
 *    \details 
 *	\copyright Apache License, Version 2.0
 */

#include "AppConfiguration.h"
#include "stdlib.h"
#include "string.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "Helpers.h"
#include "esp_intr_alloc.h"
#include "sdkconfig.h"
#include "webguiapp.h"


#define STORAGE_NAMESPACE "storage"
#define TAG "AppConfiguration"

APP_CONFIG AppConfig;

void SaveUserConf()
{
    WriteNVSAppConfig(&AppConfig);
}

void UserAppInit(void)
{
    if (GetUserAppNeedReset())
    {
        SetUserAppNeedReset(false);
        ESP_ERROR_CHECK(InitAppConfig());
    }
    ESP_ERROR_CHECK(InitAppConfig());
}

void UserInitIO(void)
{
    ESP_LOGI(TAG, "Application GPIO's initialized OK");
}

void InitSPI(void)
{

}

void InitI2C(void)
{
#ifdef CONFIG_I2C_ENABLE
    i2c_config_t i2c_config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = CONFIG_I2C_SDA_GPIO,
            .scl_io_num = CONFIG_I2C_SCL_GPIO,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = CONFIG_I2C_CLOCK
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
    ESP_LOGI(TAG, "I2C initialized OK");
#else
    ESP_LOGI(TAG, "I2C bus disabeled in config");
#endif
}
APP_CONFIG* GetAppConf(void)
{
    return &AppConfig;
}

esp_err_t InitAppConfig(void)
{
    esp_err_t err;
    err = ReadNVSAppConfig(&AppConfig);
    if (err == ESP_ERR_INVALID_CRC || err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGW(TAG, "Reset and write default app configuration");
        ResetAppConfig(&AppConfig);
        err = WriteNVSAppConfig(&AppConfig);
        return err;
    }
    else if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "Read system configuration OK");
    }
    else
        ESP_LOGW(TAG, "Error reading NVS app configuration:%s", esp_err_to_name(err));
    return err;

}

esp_err_t ResetInitAppConfig(void)
{
    ESP_LOGI(TAG, "Reset and write default configuration");
    ResetAppConfig(&AppConfig);
    return WriteNVSAppConfig(&AppConfig);
}

void ResetAppConfig(APP_CONFIG *Conf)
{
    //default init test param
    GetAppConf()->test = 0;

}

esp_err_t ReadNVSAppConfig(APP_CONFIG *AppConf)
{
    nvs_handle_t my_handle;
    esp_err_t err;
    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
        return err;

// obtain required memory space to store blob being read from NVS
    size_t L = (size_t) sizeof(APP_CONFIG);
    ESP_LOGI(TAG, "Size of APP_CONFIG structure to read is %d", L);
    err = nvs_get_blob(my_handle, "app_conf", AppConf, &L);
    if (err != ESP_OK)
        goto nvs_operation_err;

    unsigned char sha256_saved[32];
    unsigned char sha256_calculated[32];
    unsigned char sha_print[32 * 2 + 1];
    sha_print[32 * 2] = 0x00;
    L = 32;
    err = nvs_get_blob(my_handle, "app_conf_sha256", sha256_saved, &L);
    if (err != ESP_OK)
        goto nvs_operation_err;

    SHA256Hash((unsigned char*) AppConf, sizeof(APP_CONFIG), sha256_calculated);
    BytesToStr(sha256_saved, sha_print, 32);
    ESP_LOGI(TAG, "Saved hash of APP_CONFIG structure is %s", sha_print);
    BytesToStr(sha256_calculated, sha_print, 32);
    ESP_LOGI(TAG, "Calculated hash of APP_CONFIG structure is %s", sha_print);

    if (memcmp(sha256_calculated, sha256_saved, L))
    {
        err = ESP_ERR_INVALID_CRC;
        goto nvs_operation_err;
    }

    nvs_close(my_handle);
    return ESP_OK;

nvs_operation_err:
    nvs_close(my_handle);
    return err;
}

esp_err_t WriteNVSAppConfig(APP_CONFIG *AppConf)
{
    nvs_handle_t my_handle;
    esp_err_t err;
    // Open
    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
        return err;

    size_t L = (size_t) sizeof(APP_CONFIG);
    ESP_LOGI(TAG, "Size of APP_CONFIG structure to write is %d", L);
    err = nvs_set_blob(my_handle, "app_conf", AppConf, L);
    if (err != ESP_OK)
        goto nvs_wr_oper_err;

    unsigned char sha256[32];
    unsigned char sha_print[32 * 2 + 1];

    SHA256Hash((unsigned char*) AppConf, sizeof(APP_CONFIG), sha256);
    BytesToStr(sha256, sha_print, 32);
    sha_print[32 * 2] = 0x00;
    ESP_LOGI(TAG, "SHA256 of APP_CONFIG structure to write is %s", sha_print);
    L = 32;
    err = nvs_set_blob(my_handle, "app_conf_sha256", sha256, L);
    if (err != ESP_OK)
        goto nvs_wr_oper_err;

    // Commit
    err = nvs_commit(my_handle);
    if (err != ESP_OK)
        goto nvs_wr_oper_err;

    nvs_close(my_handle);
    return ESP_OK;

nvs_wr_oper_err:
    nvs_close(my_handle);
    return err;

}


led_strip_handle_t led_strip;

led_strip_handle_t * LEDStripGetHandle()
{
    return &led_strip;
}

void LEDStripInit(int gpio)
{

    led_strip_config_t strip_config = {
            .strip_gpio_num = gpio, // The GPIO that connected to the LED strip's data line
            .max_leds = 49, // The number of LEDs in the strip,
            .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
            .led_model = LED_MODEL_WS2812, // LED strip model
            .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
            };

    led_strip_rmt_config_t rmt_config = {

    .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
    .resolution_hz = 10 * 1000 * 1000, // 10MHz
    .flags.with_dma = true, // whether to enable the DMA feature

            };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));


    /*

    led_strip_config_t strip_config = {
        .strip_gpio_num = gpio, // The GPIO that connected to the LED strip's data line
        .max_leds = 49, // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812, // LED strip model
        .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
    };

    led_strip_spi_config_t spi_config = {
        .clk_src = SPI_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .flags.with_dma = true, // Using DMA can improve performance and help drive more LEDs
        .spi_bus = SPI3_HOST,   // SPI bus ID
    };
    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
    */

}
