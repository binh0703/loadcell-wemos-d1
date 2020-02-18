/**
  **************************************************************************************************
  * @file   button.h
  * @brief  Header file for button module.
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

#ifndef _BUTTON_H
#define _BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

/* ESP8266. */
#include "esp_common.h"

/* Public macros ---------------------------------------------------------------------------------*/

/* Public data types -----------------------------------------------------------------------------*/

/* Public function prototypes --------------------------------------------------------------------*/

/**
  * @brief      Initializes a button.
  * @param      None.
  * @retval     None.
  */
void button_open (void);

/**
  * @brief      Check if a button is pressed.
  * @param      None.
  * @retval     true: pressed button.
  *             false: released button.
  */
bool button_is_pressed (void);

void app_button(void);

#ifdef __cplusplus
}
#endif

#endif /* _BUTTON_H */

/* END OF FILE ************************************************************************************/
