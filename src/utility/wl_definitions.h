/**********************************************************************************************************************************
  wl_definitions.h - Library for Arduino WiFiNINA module/shield.

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

/*****************************
  wl_definitions.h

  Created on: Mar 6, 2011
  Author: dlafauci
 *****************************/

// Maximum size of a SSID
#define WL_SSID_MAX_LENGTH        32

// Length of passphrase. Valid lengths are 8-63.
#define WL_WPA_KEY_MAX_LENGTH     63

// Length of key in bytes. Valid values are 5 and 13.
#define WL_WEP_KEY_MAX_LENGTH     13

// Size of a MAC-address or BSSID
#define WL_MAC_ADDR_LENGTH        6

// Size of a MAC-address or BSSID
#define WL_IPV4_LENGTH            4

// Maximum size of a SSID list
#define WL_NETWORKS_LIST_MAXNUM   10

// Maxmium number of socket
#define WIFI_MAX_SOCK_NUM         10

// Socket not available constant
#define SOCK_NOT_AVAIL            255

// Default state value for WiFi state field
#define NA_STATE                  -1

////////////////////////////////////////

typedef enum
{
  WL_NO_SHIELD      = 255,
  WL_NO_MODULE      = WL_NO_SHIELD,
  WL_IDLE_STATUS    = 0,
  WL_NO_SSID_AVAIL,
  WL_SCAN_COMPLETED,
  WL_CONNECTED,
  WL_CONNECT_FAILED,
  WL_CONNECTION_LOST,
  WL_DISCONNECTED,
  WL_AP_LISTENING,
  WL_AP_CONNECTED,
  WL_AP_FAILED
} wl_status_t;

////////////////////////////////////////

/* Encryption modes */
enum wl_enc_type
{
  /* Values map to 802.11 encryption suites... */
  ENC_TYPE_WEP      = 5,
  ENC_TYPE_TKIP     = 2,
  ENC_TYPE_CCMP     = 4,
  /* ... except these two, 7 and 8 are reserved in 802.11-2007 */
  ENC_TYPE_NONE     = 7,
  ENC_TYPE_AUTO     = 8,

  ENC_TYPE_UNKNOWN  = 255
};

////////////////////////////////////////

