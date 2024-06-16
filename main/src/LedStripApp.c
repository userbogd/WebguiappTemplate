 /* Copyright 2024 Bogdan Pilyugin
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
 *   File name: LedStripApp.c
 *     Project: WebguiappTemplate
 *  Created on: 2024-06-16
 *      Author: bogdan
 * Description:	
 */

#include "AppConfiguration.h"
#include "webguiapp.h"

led_strip_handle_t led_strip;

led_strip_handle_t * LEDStripGetHandle()
{
    return &led_strip;
}

void LEDStripInit(int gpio)
{

    led_strip_config_t strip_config = {
            .strip_gpio_num = gpio, // The GPIO that connected to the LED strip's data line
            .max_leds = CONFIG_LED_STRIP_NUMBER, // The number of LEDs in the strip,
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
