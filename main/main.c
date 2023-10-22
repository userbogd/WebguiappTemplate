#include <CronTimers.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "webguiapp.h"
#include "cron.h"
#include "jobs.h"
#include "AppConfiguration.h"

void UserMQTTEventHndlr(int idx, void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
void SaveUserConf();

sys_error_code CustomPayloadHandler(data_message_t *MSG)
{
    return SYS_ERROR_HANDLER_NOT_SET;
}

const char my_context_data[] = "MyContextDataPassedIntoMQTTHandler";

void app_main(void)
{
    regUserEventHandler(&UserMQTTEventHndlr, (void*) my_context_data);
    regCustomSaveConf(&SaveUserConf);
    regCustomPayloadTypeHandler(&CustomPayloadHandler);

    RegAppVariables();
    RegObjects();

    WebGuiAppInit();
    if (GetUserAppNeedReset())
    {
        SetUserAppNeedReset(false);
        ESP_ERROR_CHECK(InitAppConfig());
    }
    ESP_ERROR_CHECK(InitAppConfig());

    while (true)
    {
        sleep(1);
    }
}
