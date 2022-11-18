/**********************************************************************************************************************************
  wifi_spi.h - Library for Arduino WiFiNINA module/shield.

  Based on and modified from WiFiNINA library https://www.arduino.cc/en/Reference/WiFiNINA
  to support nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, etc. boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR400, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiNINA_Generic
  Licensed under MIT license

  Copyright (c) 2018 Arduino SA. All rights reserved.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Version: 1.8.15-1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0      K Hoang    27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                   such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  ...
  1.8.13     K Hoang    03/08/2021 Sync with WiFiNINA v1.8.13 : new FW v1.4.8. Add support to ADAFRUIT_MATRIXPORTAL_M4_EXPRESS
  1.8.14-1   K Hoang    25/11/2021 Fix examples to support ATmega4809 such as UNO_WIFI_REV2 and NANO_EVERY
  1.8.14-2   K Hoang    31/12/2021 Add support to Nano_RP2040_Connect using arduino-pico core
  1.8.14-3   K Hoang    31/12/2021 Fix issue with UDP for Nano_RP2040_Connect using arduino-pico core
  1.8.14-4   K Hoang    01/05/2022 Fix bugs by using some PRs from original WiFiNINA. Add WiFiMulti-related examples
  1.8.14-5   K Hoang    23/05/2022 Fix bug causing data lost when sending large files
  1.8.14-6   K Hoang    17/08/2022 Add support to Teensy 4.x using WiFiNINA AirLift. Fix minor bug
  1.8.14-7   K Hoang    11/11/2022 Modify WiFiWebServer example to avoid crash in arduino-pico core
  1.8.15-0   K Hoang    14/11/2022 Fix severe limitation to permit sending much larger data than total 4K
  1.8.15-1   K Hoang    18/11/2022 Using new WiFi101_Generic library to permit sending larger data than total 4K
 ***********************************************************************************************************************************/

#pragma once

#include <inttypes.h>
#include "utility/wl_definitions.h"

////////////////////////////////////////

#define CMD_FLAG            0
#define REPLY_FLAG          1<<7
#define DATA_FLAG           0x40

////////////////////////////////////////

#define WIFI_SPI_ACK        1
#define WIFI_SPI_ERR        0xFF

////////////////////////////////////////

#define TIMEOUT_CHAR        1000

////////////////////////////////////////

//#define MAX_SOCK_NUM      4 /**< Maxmimum number of socket  */
#define NO_SOCKET_AVAIL     255

////////////////////////////////////////

#define START_CMD           0xE0
#define END_CMD             0xEE
#define ERR_CMD             0xEF
#define CMD_POS             1       // Position of Command OpCode on SPI stream
#define PARAM_LEN_POS       2       // Position of Param len on SPI stream

////////////////////////////////////////

enum
{
  SET_NET_CMD           = 0x10,
  SET_PASSPHRASE_CMD    = 0x11,
  SET_KEY_CMD           = 0x12,
  //  TEST_CMD          = 0x13,
  SET_IP_CONFIG_CMD     = 0x14,
  SET_DNS_CONFIG_CMD    = 0x15,
  SET_HOSTNAME_CMD      = 0x16,
  SET_POWER_MODE_CMD    = 0x17,
  SET_AP_NET_CMD        = 0x18,
  SET_AP_PASSPHRASE_CMD = 0x19,
  SET_DEBUG_CMD         = 0x1A,
  GET_TEMPERATURE_CMD   = 0x1B,
  GET_REASON_CODE_CMD   = 0x1F,

  GET_CONN_STATUS_CMD   = 0x20,
  GET_IPADDR_CMD        = 0x21,
  GET_MACADDR_CMD       = 0x22,
  GET_CURR_SSID_CMD     = 0x23,
  GET_CURR_BSSID_CMD    = 0x24,
  GET_CURR_RSSI_CMD     = 0x25,
  GET_CURR_ENCT_CMD     = 0x26,
  SCAN_NETWORKS         = 0x27,
  START_SERVER_TCP_CMD  = 0x28,
  GET_STATE_TCP_CMD     = 0x29,
  DATA_SENT_TCP_CMD     = 0x2A,
  AVAIL_DATA_TCP_CMD    = 0x2B,
  GET_DATA_TCP_CMD      = 0x2C,
  START_CLIENT_TCP_CMD  = 0x2D,
  STOP_CLIENT_TCP_CMD   = 0x2E,
  GET_CLIENT_STATE_TCP_CMD = 0x2F,
  DISCONNECT_CMD        = 0x30,
  //  GET_IDX_SSID_CMD  = 0x31,
  GET_IDX_RSSI_CMD      = 0x32,
  GET_IDX_ENCT_CMD      = 0x33,
  REQ_HOST_BY_NAME_CMD  = 0x34,
  GET_HOST_BY_NAME_CMD  = 0x35,
  START_SCAN_NETWORKS   = 0x36,
  GET_FW_VERSION_CMD    = 0x37,
  //  GET_TEST_CMD      = 0x38,
  SEND_DATA_UDP_CMD     = 0x39,
  GET_REMOTE_DATA_CMD   = 0x3A,
  GET_TIME_CMD          = 0x3B,
  GET_IDX_BSSID         = 0x3C,
  GET_IDX_CHANNEL_CMD   = 0x3D,
  PING_CMD              = 0x3E,
  GET_SOCKET_CMD        = 0x3F,

  // All command with DATA_FLAG 0x40 send a 16bit Len
  SET_ENT_CMD           = 0x40,

  SEND_DATA_TCP_CMD     = 0x44,
  GET_DATABUF_TCP_CMD   = 0x45,
  INSERT_DATABUF_CMD    = 0x46,

  // regular format commands
  SET_PIN_MODE          = 0x50,
  SET_DIGITAL_WRITE     = 0x51,
  SET_ANALOG_WRITE      = 0x52,
  GET_DIGITAL_READ      = 0x53,
  GET_ANALOG_READ       = 0x54,

  // regular format commands
  WRITE_FILE            = 0x60,
  READ_FILE             = 0x61,
  DELETE_FILE           = 0x62,
  EXISTS_FILE           = 0x63,
  DOWNLOAD_FILE         = 0x64,
  APPLY_OTA_COMMAND     = 0x65,
  RENAME_FILE           = 0x66,

  // New from v1.7.0
  DOWNLOAD_OTA          = 0x67,
  //////
};

////////////////////////////////////////

enum wl_tcp_state
{
  CLOSED      = 0,
  LISTEN      = 1,
  SYN_SENT    = 2,
  SYN_RCVD    = 3,
  ESTABLISHED = 4,
  FIN_WAIT_1  = 5,
  FIN_WAIT_2  = 6,
  CLOSE_WAIT  = 7,
  CLOSING     = 8,
  LAST_ACK    = 9,
  TIME_WAIT   = 10
};

////////////////////////////////////////

enum numParams
{
  PARAM_NUMS_0,
  PARAM_NUMS_1,
  PARAM_NUMS_2,
  PARAM_NUMS_3,
  PARAM_NUMS_4,
  PARAM_NUMS_5,
  PARAM_NUMS_6,
  MAX_PARAM_NUMS
};

////////////////////////////////////////

#define MAX_PARAMS        MAX_PARAM_NUMS-1
#define PARAM_LEN_SIZE    1

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  uint8_t       paramLen;
  char*         param;
}
tParam;

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  uint16_t      dataLen;
  char*         data;
}
tDataParam;

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  unsigned char cmd;
  unsigned char tcmd;
  unsigned char nParam;
  tParam        params[MAX_PARAMS];
}
tSpiMsg;

typedef struct  __attribute__((__packed__))
{
  unsigned char cmd;
  unsigned char tcmd;
  unsigned char nParam;
  tDataParam    params[MAX_PARAMS];
}
tSpiMsgData;

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  unsigned char cmd;
  unsigned char tcmd;
  //unsigned char totLen;
  unsigned char nParam;
}
tSpiHdr;

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  uint8_t     paramLen;
  uint32_t    param;
}
tLongParam;

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  uint8_t     paramLen;
  uint16_t    param;
}
tIntParam;

////////////////////////////////////////

typedef struct  __attribute__((__packed__))
{
  uint8_t     paramLen;
  uint8_t     param;
}
tByteParam;

////////////////////////////////////////

