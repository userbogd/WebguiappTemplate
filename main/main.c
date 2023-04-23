#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "webguiapp.h"
#include "cron.h"
#include "jobs.h"
#include "AppConfiguration.h"
#include "CronTimers.h"

int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var, int arg);
HTTP_IO_RESULT AfterPostHandlerCustom(httpd_req_t *req, const char *filename, char *PostData);
void UserMQTTEventHndlr(int idx, void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
void TimeObtainHandler(struct timeval* tm);


const char my_context_data[] = "MyContextDataPassedIntoMQTTHandler";

void app_main(void)
{
    regHTTPPrintCustom(&HTTPPrintCustom);
    regAfterPostHandlerCustom(&AfterPostHandlerCustom);
    regUserEventHandler(&UserMQTTEventHndlr, (void*)my_context_data);
    regTimeSyncCallback(&TimeObtainHandler);

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
