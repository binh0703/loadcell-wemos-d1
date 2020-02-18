/* Created by matix21
 * MIT License
 */

#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include "lwip/ip_addr.h"
#include "espconn.h"

#define UART_SPEED 115200

#define SLEEP_BETWEEN_MEASUREMENTS_US 60 * 1000 * 1000 // 1 minute
#define SLEEP_BETWEEN_READ_FAILS_US 10 * 1000 * 1000

#define WIFI_SSID "Tho_Sua_Ong_Nuoc"
#define WIFI_PASSWORD "@0988456917@"

#define THINGSPEAK_HOST "api.thingspeak.com"
#define THINGSPEAK_API_KEY "PNXS882XWJIEOI18"

#endif
