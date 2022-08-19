#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "esp_system.h"
#include "sdkconfig.h"

#include "SystemConfiguration.h"
#include "HTTPServer.h"
#include "MQTT.h"

#define MANUAL_RESET 0

int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var);
HTTP_IO_RESULT AfterPostHandlerCustom(httpd_req_t *req, const char *filename, char *PostData);
void UserDataHndlr(char *data, uint32_t len, int idx);

void app_main(void)
{

    WebGuiAppInit();
    regHTTPPrintCustom(&HTTPPrintCustom);
    regAfterPostHandlerCustom(&AfterPostHandlerCustom);
    regUserDataHandler(&UserDataHndlr);


    while (true)
    {
        sleep(1);
    }
}
