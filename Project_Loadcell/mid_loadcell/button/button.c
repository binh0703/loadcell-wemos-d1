/**
  **************************************************************************************************
  * @file   button.c
  * @brief  Button facilities.
  * @by     khanhcq | 31-June-2018 | Launch for ZenSensor-FWCore.
  **************************************************************************************************
  *
  * Copyright (C) 2018 Leanwell Technology Co.,Ltd. All rights reserved.
  *
  * All information contained herein is the property of Leanwell Technology Co.,Ltd. The intellectual
  * and technical concepts contained herein are proprietary to Leanwell Technology Co.,Ltd and are
  * protected by trade secret or copyright law. Dissemination of this information or reproduction of
  * this material is strictly forbidden unless prior written permission is obtained from Leanwell
  * Technology Co.,Ltd.
  *
  * This file is part of ZenSensor-FWCore.
  **************************************************************************************************
  */

/*  Indent using spaces
    Tab width   : 4 spaces
    Line width  : 100 characters
    Line ending : LF (0x0A) */

/* Includes --------------------------------------------------------------------------------------*/

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

/* ESP8266. */
#include "esp_common.h"
#include "gpio.h"
#include "espressif/airkiss.h"

/* Private macros --------------------------------------------------------------------------------*/
#define B_GPIO_PIN                          GPIO_Pin_4 //D2
#define B_GPIO_NUM                          4
/* Private data types ----------------------------------------------------------------------------*/

/* Private variables -----------------------------------------------------------------------------*/
static int led_state = 0;
bool check_mode = true;
/* Private function prototypes -------------------------------------------------------------------*/

/* Public function bodies ------------------------------------------------------------------------*/

/**
  * @brief      Initializes a button.
  * @param      None.
  * @retval     None.
  */
void
button_open(void)
{
    GPIO_ConfigTypeDef io_in_conf;

    io_in_conf.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    io_in_conf.GPIO_Mode = GPIO_Mode_Output;
    io_in_conf.GPIO_Pin = B_GPIO_PIN;
    io_in_conf.GPIO_Pullup = GPIO_PullUp_EN;
    // io_in_conf.GPIO_Pullup = GPIO_PullUp_DIS;
    gpio_config(&io_in_conf);

    return;
}



// void task_led(void *pvParameters)
// {
//     for(;;){
//         vTaskDelay(100);
//         GPIO_OUTPUT_SET(LED_GPIO_NUM, led_state);
//         led_state ^=1;
//     }

//     vTaskDelete(NULL);
// }

// void task_printf(void *pvParameters)
// {
//   float resistance;
//   char result[20] = "";
//   // char buffer [sizeof(float)*8+1];
//   // long a;
//     for(;;){
      
//       resistance = hx711_get_units(5);
//       dtostrf(resistance, 7, 2, result);

//       printf("%sgram\n", result);
//       // a = hx711_read_average(5);
//       // ltoa(a,buffer,10);
//       // printf("%s\n",buffer);
//       hx711_power_down();
//       vTaskDelay(200 / portTICK_RATE_MS);
//       hx711_power_up();

//     }
//     vTaskDelete(NULL);
// }
/**
  * @brief      Check if a button is pressed.
  * @param      None.
  * @retval     true: pressed button.
  *             false: released button.
  */
bool button_is_pressed (void)
{
    bool b_pressed = false;

    if (0 == GPIO_INPUT_GET(B_GPIO_NUM))
    {
        b_pressed = true;
    }

    return b_pressed;
}


// void app_button(void)
// {

//      uart_set_baud(0, BIT_RATE_9600);
        
//       hx711_init();
//       hx711_set_gain(128);
//       hx711_set_offset(8369950);
//       hx711_set_scale(391.40f);
//       gb_gr = hx711_get_units(5);
//       set_gb_gram(gb_gr);

//       user_set_station_config();
//       wifi_set_opmode(STATION_MODE);
//       wifi_set_event_handler_cb (wifi_handle_event_cb);

// }
/* Private function bodies -----------------------------------------------------------------------*/

/* END OF FILE ************************************************************************************/
