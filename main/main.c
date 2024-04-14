#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "webguiapp.h"
#include "AppConfiguration.h"

//#define LED_STRIP_GPIO 21
#define LED_STRIP_GPIO 33

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

    LEDStripInit(LED_STRIP_GPIO);

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
