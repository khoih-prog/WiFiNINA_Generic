/****************************************************************************************************************************
  server_drv.h - Library for Arduino WifiNINA module/shield.
  
  Based on and modified from WiFiNINA libarary https://www.arduino.cc/en/Reference/WiFiNINA
  to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, Adafruit's nRF52 boards, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
  Licensed under MIT license
  Version: 1.5.2
   
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
  
  Version Modified By   Date      Comments
 ------- -----------  ---------- -----------
  1.5.0   K Hoang      27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                  such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  1.5.1   K Hoang      22/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, 
                                  Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, etc.         
  1.5.2   K Hoang      09/05/2020 Port FirmwareUpdater to permit nRF52 boards to update W102 firmware and SSL certs on IDE   
                                  Update default pin-outs.                             
 *****************************************************************************************************************************/

#ifndef Server_Drv_h
#define Server_Drv_h

#include <inttypes.h>
#include "wifi_spi.h"

typedef enum eProtMode {TCP_MODE, UDP_MODE, TLS_MODE, UDP_MULTICAST_MODE}tProtMode;

class ServerDrv
{
public:

    // Start server TCP on port specified
    static void startServer(uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);

    static void startServer(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);

    static void startClient(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);

    static void startClient(const char* host, uint8_t host_len, uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);

    static void stopClient(uint8_t sock);
                                                                                  
    static uint8_t getServerState(uint8_t sock);

    static uint8_t getClientState(uint8_t sock);

    static bool getData(uint8_t sock, uint8_t *data, uint8_t peek = 0);

    static bool getDataBuf(uint8_t sock, uint8_t *data, uint16_t *len);

    static bool insertDataBuf(uint8_t sock, const uint8_t *_data, uint16_t _dataLen);

    static uint16_t sendData(uint8_t sock, const uint8_t *data, uint16_t len);

    static bool sendUdpData(uint8_t sock);

    static uint16_t availData(uint8_t sock);

    static uint8_t availServer(uint8_t sock);

    static uint8_t checkDataSent(uint8_t sock);

    static uint8_t getSocket();
};

extern ServerDrv serverDrv;

#endif
