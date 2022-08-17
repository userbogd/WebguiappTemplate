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

void app_main(void)
{

    esp_err_t err = nvs_flash_init();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND || MANUAL_RESET == 1)
    {
        // 1.OTA app partition table has a smaller NVS partition size than the non-OTA
        // partition table. This size mismatch may cause NVS initialization to fail.
        // 2.NVS partition contains data in new format and cannot be recognized by this version of code.
        // If this happens, we erase NVS partition and initialize NVS again.
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
        ESP_ERROR_CHECK(ResetInitSysConfig());
    }
    ESP_ERROR_CHECK(InitSysConfig());

    //init rom file system
    init_rom_fs("/espfs");

#if CONFIG_WEBGUIAPP_GPRS_ENABLE
    /*Start PPP modem*/
    if (GetSysConf()->gsmSettings.Flags1.bIsGSMEnabled)
        PPPModemStart();
#endif

#if CONFIG_WEBGUIAPP_ETHERNET_ENABLE
    /*Start Ethernet connection*/
    if (GetSysConf()->ethSettings.Flags1.bIsETHEnabled)
        EthStart();
#endif

#if CONFIG_WEBGUIAPP_WIFI_ENABLE
    /*Start WiFi connection*/
    if (GetSysConf()->wifiSettings.Flags1.bIsWiFiEnabled)
    {
        if (GetSysConf()->wifiSettings.Flags1.bIsAP)
            WiFiAPStart();
        else
            WiFiSTAStart();
    }
#endif

    /*Start time synchronization*/
    if (CONFIG_WEBGUIAPP_GPRS_ENABLE ||
    CONFIG_WEBGUIAPP_ETHERNET_ENABLE ||
            (CONFIG_WEBGUIAPP_WIFI_ENABLE && GetSysConf()->wifiSettings.Flags1.bIsAP))
    {
        StartTimeGet();
        if (GetSysConf()->mqttStation[0].Flags1.bIsGlobalEnabled
                || GetSysConf()->mqttStation[1].Flags1.bIsGlobalEnabled)
        {
            MQTTRun();
        }
    }

    /*Start web server*/
    if (CONFIG_WEBGUIAPP_GPRS_ENABLE ||
    CONFIG_WEBGUIAPP_ETHERNET_ENABLE ||
    CONFIG_WEBGUIAPP_WIFI_ENABLE)
        ESP_ERROR_CHECK(start_file_server());

    while (true)
    {
        printf("Hello from app_main!\n");
        sleep(1);
    }
}
