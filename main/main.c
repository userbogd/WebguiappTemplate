#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "NetTransport.h"
#include "esp_err.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "webguiapp.h"
#include "AppConfiguration.h"

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
    LEDStripInit(CONFIG_LED_STRIP_GPIO);
 PrintNetifs();
    

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
