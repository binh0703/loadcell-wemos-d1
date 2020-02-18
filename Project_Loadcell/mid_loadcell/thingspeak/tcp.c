/* Created by matix21
 * MIT License
 */

#include "measurements.h"
#include "esp_common.h"
#include "tcp.h"
#include "user_config.h"
#include "uart.h"
#include "esp_libc.h"

bool check_conn = true;


static uint16_t ICACHE_FLASH_ATTR prepare_thingspeak_request(measurements *meas, char *buffer)
{
    char value_buf[100];

    sprintf(value_buf, "field2=%d\r\n", (int)(meas->gram));
    sprintf(buffer, "POST /update HTTP/1.1\r\nHost: %s\r\nConnection: close\r\nX-THINGSPEAKAPIKEY: %s\r\nContent-Type: \
        application/x-www-form-urlencoded\r\nContent-Length: %d\r\n\r\n%s", THINGSPEAK_HOST, THINGSPEAK_API_KEY, strlen(value_buf), value_buf);

    return strlen(buffer);
}

static void ICACHE_FLASH_ATTR data_received(void *arg, char *pdata, unsigned short len)
{
    // struct espconn *conn = arg;
    struct espconn *pespconn = (struct espconn *)arg;
    char *status = strstr(pdata, "Status");
    printf("Received %d bytes\n%s\n", len, strtok(status, "\r"));
    espconn_disconnect(pespconn);
    // wifi_station_disconnect();
    check_conn = true;

}

static void ICACHE_FLASH_ATTR host_ip_found(const char *name, ip_addr_t *ipaddr, void *arg)
{

    if (ipaddr == NULL)
    {
        printf("Unable to find IP for %s\nDisconnecting wifi\n", THINGSPEAK_HOST);
        wifi_station_disconnect();
    }

    printf("host %s found %d.%d.%d.%d\n", THINGSPEAK_HOST, *((uint8 *)&ipaddr->addr), *((uint8 *)&ipaddr->addr + 1),
             *((uint8 *)&ipaddr->addr + 2), *((uint8 *)&ipaddr->addr + 3));



    struct espconn *pespconn = (struct espconn *)arg;
    pespconn->type = ESPCONN_TCP;
    pespconn->state = ESPCONN_NONE;
    pespconn->proto.tcp=&thingspeak_tcp;
    pespconn->proto.tcp->local_port = espconn_port();
    pespconn->proto.tcp->remote_port = 80;
    memcpy (pespconn->proto.tcp->remote_ip, &ipaddr->addr, 4);



    espconn_regist_connectcb (pespconn, tcp_connected);
    espconn_regist_disconcb (pespconn, tcp_disconnected);
            
    if (espconn_connect(pespconn) != ESPCONN_OK)
    {
         printf("Unable to connect to %s\nDisconnecting wifi\n", THINGSPEAK_HOST);
         wifi_station_disconnect();
    }
        // vTaskDelay(portMAX_DELAY / portTICK_RATE_MS);
         //3s
}

void ICACHE_FLASH_ATTR get_thingspeak_ip()
{
     while(1){

        printf("check_conn = %d",check_conn);

        if(check_conn)
        {
            check_conn = false;
            // struct espconn pespconn;
            // pespconn = &thingspeak_connection;
            // *pespconn = NULL;
            struct espconn pespconn;

            espconn_gethostbyname (&pespconn, THINGSPEAK_HOST, &thingspeak_ip, host_ip_found);
        }

        vTaskDelay(30000 / portTICK_RATE_MS);
    }
}

void ICACHE_FLASH_ATTR tcp_connected(void *arg)
{
    // struct espconn *conn = arg;
    struct espconn *pespconn = (struct espconn *)arg;
    measurements meas;
    char buffer[512];


    printf("Connected to: %s\n", THINGSPEAK_HOST);
    espconn_regist_recvcb(pespconn, data_received);

 
    

    // while(1){
    prepare_measurements(&meas);

    uint16_t request_len = prepare_thingspeak_request(&meas, buffer);
    int result = espconn_send(pespconn, buffer, request_len);

    if(result == ESPCONN_OK)
    {
        printf("%s", buffer);
    }
    else
    {
        printf("Send error: %d\r\n", result);
    }
    // }
}

void ICACHE_FLASH_ATTR tcp_disconnected(void *arg)
{
    printf("Disconnected from: %s\n", THINGSPEAK_HOST);
    wifi_station_disconnect();
}

void ICACHE_FLASH_ATTR 
uart_set_baud(int uart, int baud_rate)
{
    UART_Port uart_no;
    uart_div_modify(uart_no, UART_CLK_FREQ / baud_rate);
}
