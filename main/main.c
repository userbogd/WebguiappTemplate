#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "SystemConfiguration.h"
#include "romfs.h"
#include "NetTransport.h"
#include "HTTPServer.h"

#define MANUAL_RESET 0

int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var);
HTTP_IO_RESULT AfterPostHandlerCustom(httpd_req_t *req, const char *filename, char *PostData);

void app_main(void)
{

    WebGuiAppInit();



    /*Start web server*/
    if (CONFIG_WEBGUIAPP_GPRS_ENABLE ||
    CONFIG_WEBGUIAPP_ETHERNET_ENABLE ||
    CONFIG_WEBGUIAPP_WIFI_ENABLE)
    {
        ESP_ERROR_CHECK(start_file_server());
        regHTTPPrintCustom(&HTTPPrintCustom);
        regAfterPostHandlerCustom(&AfterPostHandlerCustom);

    }
    while (true)
    {
        printf("Hello from app_main!\n");
        sleep(5);
    }
}
