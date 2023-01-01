#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "webguiapp.h"

int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var, int arg);
HTTP_IO_RESULT AfterPostHandlerCustom(httpd_req_t *req, const char *filename, char *PostData);
void UserMQTTEventHndlr(int idx, void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

void app_main(void)
{
    regHTTPPrintCustom(&HTTPPrintCustom);
    regAfterPostHandlerCustom(&AfterPostHandlerCustom);
    regUserEventHandler(&UserMQTTEventHndlr);
    WebGuiAppInit();

    while (true)
    {
        sleep(1);
    }
}
