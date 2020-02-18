/* Created by matix21
 * MIT License
 */

#ifndef TCP_H
#define TCP_H

#include "espconn.h"



void ICACHE_FLASH_ATTR tcp_connected(void *arg);
void ICACHE_FLASH_ATTR tcp_disconnected(void *arg);
void ICACHE_FLASH_ATTR get_thingspeak_ip();
void ICACHE_FLASH_ATTR uart_set_baud(int uart, int baud_rate);

struct espconn thingspeak_connection;
ip_addr_t thingspeak_ip;
esp_tcp thingspeak_tcp;

#endif
