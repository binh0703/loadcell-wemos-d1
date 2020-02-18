/* Created by matix21
 * MIT License
 */

#include "wifi.h"
#include "tcp.h"
#include "esp_common.h"
#include "user_config.h"
#include "esp_libc.h"


void wifi_handle_event_cb(System_Event_t *evt)
{
    switch (evt->event_id)
    {
        case EVENT_STAMODE_CONNECTED:
        printf("connect to ssid %s, channel %d\n", evt->event_info.connected.ssid, evt->event_info.connected.channel);
        break;

        case EVENT_STAMODE_DISCONNECTED:
        printf("disconnect from ssid %s, reason %d\n", evt->event_info.disconnected.ssid, evt->event_info.disconnected.reason);
        system_deep_sleep_set_option(0);
        system_deep_sleep(SLEEP_BETWEEN_MEASUREMENTS_US);
        break;

        case EVENT_STAMODE_AUTHMODE_CHANGE:
        printf("authmode change: %d -> %d\n", evt->event_info.auth_change.old_mode, evt->event_info.auth_change.new_mode);
        break;

        case EVENT_STAMODE_GOT_IP:
        get_thingspeak_ip();
        break;

        default:
        printf("Unknown event: %x", evt->event_id);
        break;
    }
}

bool ICACHE_FLASH_ATTR user_set_station_config(void)
{
    struct station_config stationConf;
    stationConf.bssid_set = 0; //no need to check MAC address of AP

    memset(&stationConf.ssid, 0, sizeof(stationConf.ssid));
    memset(&stationConf.password, 0, sizeof(stationConf.password));

    memcpy(&stationConf.ssid, WIFI_SSID, strlen(WIFI_SSID));
    memcpy(&stationConf.password, WIFI_PASSWORD, strlen(WIFI_PASSWORD));

    printf("%s\n\r", __FUNCTION__);
    return wifi_station_set_config(&stationConf);
}