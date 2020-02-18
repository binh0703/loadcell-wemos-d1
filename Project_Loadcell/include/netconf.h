/**
  **************************************************************************************************
  * @file   netconf.h
  * @brief  Header file for netconf module.
  * @by     khanhcq | 06-August-2018 | Launch for ZenSensor-FWCore.
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

#ifndef _NETCONF_H
#define _NETCONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Public macros ---------------------------------------------------------------------------------*/

/* Public data types -----------------------------------------------------------------------------*/

typedef struct
{
    char ip[16];
    char netmask[16];
    char gateway[16];
} netconf_ip_t;

/* Public function prototypes --------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _NETCONF_H */

/* END OF FILE ************************************************************************************/
