#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "esp_err.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "soc/gpio_num.h"
#include "webguiapp.h"
#include "AppConfiguration.h"
#include "driver/gpio.h"
#include "driver/dedic_gpio.h"

void UserMQTTEventHndlr(int idx, void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
void SaveUserConf();

void app_main(void)
{
    regUserEventHandler(&UserMQTTEventHndlr, NULL);
    regCustomSaveConf(&SaveUserConf);
    regCustomPayloadTypeHandler(NULL);
    RegAppVariables();
    RegObjects();

    WebGuiAppInit();
    if (GetUserAppNeedReset())
    {
        SetUserAppNeedReset(false);
        ESP_ERROR_CHECK(InitAppConfig());
    }
    ESP_ERROR_CHECK(InitAppConfig());

    // mDNSstart();
    //LEDStripInit(CONFIG_LED_STRIP_GPIO);

    gpio_set_direction(1, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(2, GPIO_MODE_INPUT_OUTPUT);

	while(1) {

	vTaskDelay(pdMS_TO_TICKS(100));
	gpio_set_level(GPIO_NUM_2, 1);

	vTaskDelay(pdMS_TO_TICKS(100));
	gpio_set_level(GPIO_NUM_2, 0);	

    }


	/*   
    dedic_gpio_bundle_handle_t bundle;
    int bidir_array[] = { 1, 2 };
    dedic_gpio_bundle_config_t bidir_config = { .gpio_array = bidir_array, .array_size = 2, .flags = { .out_en = 1, .in_en = 1 } };

    dedic_gpio_new_bundle(&bidir_config, &bundle);
    static uint32_t data[1024];
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        for (int i = 0; i < 1024; ++i)
        {
            dedic_gpio_bundle_write(bundle, 1 << 0, 1 << 0);
            dedic_gpio_bundle_write(bundle, 1 << 0, 0 << 0);
        }

        for (uint16_t i = 0; i < 1024; ++i)
        {
            dedic_gpio_bundle_write(bundle, 1 << 1, 1 << 1);
            dedic_gpio_bundle_write(bundle, 1 << 1, 0 << 1);
            *(data + i) = dedic_gpio_bundle_read_out(bundle);
        }
    }
	*/


}
