/****************************************************************************************************************************
  wl_definitions.h - Library for Arduino WifiNINA module/shield.

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
  
  Version: 1.8.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0   K Hoang      27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                  such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  1.5.1   K Hoang      22/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense,
                                  Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, etc.
  1.5.2   K Hoang      09/05/2020 Port FirmwareUpdater to permit nRF52, Teensy, SAMD21, SAMD51, etc. boards to update WiFiNINA
                                  W101/W102 firmware and SSL certs on IDE. Update default pin-outs.
  1.5.3   K Hoang      14/07/2020 Add function to support new WebSockets2_Generic Library
  1.6.0   K Hoang      19/07/2020 Sync with Arduino WiFiNINA Library v1.6.0 (new Firmware 1.4.0 and WiFiStorage)
  1.6.1   K Hoang      24/07/2020 Add support to all STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards 
  1.6.2   K Hoang      28/07/2020 Fix WiFiStorage bug from v1.6.0  
  1.7.0   K Hoang      06/08/2020 Sync with Arduino WiFiNINA Library v1.7.0 : Add downloadOTA() and verify length/CRC
  1.7.1   K Hoang      27/08/2020 Sync with Arduino WiFiNINA Library v1.7.1 : new Firmware 1.4.1
  1.7.2   K Hoang      05/11/2020 Add support to Adafruit Airlift M4 boards: METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4
  1.8.0   K Hoang      19/11/2020 Sync with Arduino WiFiNINA Library v1.8.0 : new Firmware 1.4.2. Add WiFiBearSSLClient.
 *****************************************************************************************************************************/

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

// Default state value for Wifi state field
#define NA_STATE                  -1

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

