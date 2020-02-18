/* C standard library. */
#include <stdint.h>
#include <float.h>
#include <stdlib_noniso.h>

/* Application. */
#include "app_loadcell.h"

/* Middleware. */
#include "button.h"
#include "HX711.h"
#include "tcp.h"
#include "uart.h"
#include "esp_wifi.h"
#include "wifi.h"
#include "smartconfig.h"

/* RTOS. */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

/* ESP8266. */
#include "esp_common.h"
#include "gpio.h"
#include "espressif/airkiss.h"

/* Global configuration. */
static float gb_gr = 0;


/* Middleware. */

#include "button.h"
#include "HX711.h"
/* Private function prototypes -------------------------------------------------------------------*/

/* Public function bodies ------------------------------------------------------------------------*/


// void loadcell_task(void *pvParameters)
// {

//     char result[20] = "";
//     long resistance = hx711_read_average(10);
//     dtostrf(resistance, 7, 1, result);

//     for(;;){

//         printf("Gia tri can");

//         printf("%sGia tri do:\n", result);
//     }

//     vTaskDelete(NULL);
// }

/* END OF FILE ************************************************************/

void
app_loadcell(void){


    uart_set_baud(0, BIT_RATE_9600);
        
    hx711_init();
    hx711_set_gain(128);
    hx711_set_offset(8369950);
    hx711_set_scale(391.40f);
    // gb_gr = hx711_get_units(5);
    // set_gb_gram(gb_gr);

    user_set_station_config();
    wifi_set_opmode(STATION_MODE);
    wifi_set_event_handler_cb (wifi_handle_event_cb);


	// xTaskCreate(loadcell_task, "loadcell_task", 256, NULL, 2, NULL);

}