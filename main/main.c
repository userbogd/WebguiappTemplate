#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "webguiapp.h"
#include "AppConfiguration.h"
#include "driver/gpio.h"

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

	//mDNSstart();
    LEDStripInit(CONFIG_LED_STRIP_GPIO);
    
    static bool BtnPressed = false;
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
        /*
		if(gpio_get_level(GPIO_NUM_41) == 0 && !BtnPressed)
        {
            PublicTestMQTT(MQTT1);
            PublicTestMQTT(MQTT2);
            BtnPressed = true;
        }
        if(gpio_get_level(GPIO_NUM_41) == 1 && BtnPressed)
            BtnPressed = false;
		*/
    }
}
