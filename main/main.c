#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "webguiapp.h"
#include "cron.h"
#include "jobs.h"
#include "AppConfiguration.h"

int HTTPPrintCustom(httpd_req_t *req, char *buf, char *var, int arg);
HTTP_IO_RESULT AfterPostHandlerCustom(httpd_req_t *req, const char *filename, char *PostData);
void UserMQTTEventHndlr(int idx, void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

const char my_context_data[] = "MyContextDataPassedIntoMQTTHandler";

void app_main(void)
{
    regHTTPPrintCustom(&HTTPPrintCustom);
    regAfterPostHandlerCustom(&AfterPostHandlerCustom);
    regUserEventHandler(&UserMQTTEventHndlr, (void*)my_context_data);
    WebGuiAppInit();
    if (GetUserAppNeedReset())
    {
        SetUserAppNeedReset(false);
        ESP_ERROR_CHECK(InitAppConfig());
    }
    ESP_ERROR_CHECK(InitAppConfig());

    void test_cron_job_sample_callback(cron_job *job)
    {
        //int N = *((int*)(job->data));
        int N = 0;
        //ESP_LOGW("MAIN", "Cron job executed with data %d", N);
        return;
    }

    cron_job *jobs[2];
    //jobs[0]=cron_job_create("* * * * * *",test_cron_job_sample_callback,(void *)0);
    jobs[1] = cron_job_create("* * * * * *", test_cron_job_sample_callback, (void*) 10000);
    cron_start();

    while (true)
    {
        sleep(1);
    }
}
