/****************************************************************************************************************************
  WiFiServer_Generic.cpp - Library for Arduino WifiNINA module/shield.
  
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

#include <string.h>
#include "utility/server_drv.h"

extern "C" {
  #include "utility/debug.h"
}

#include "WiFi_Generic.h"
#include "WiFiClient_Generic.h"
#include "WiFiServer_Generic.h"

WiFiServer::WiFiServer(uint16_t port) :
  _sock(NO_SOCKET_AVAIL),
  _lastSock(NO_SOCKET_AVAIL)
{
    _port = port;
}

void WiFiServer::begin()
{
    _sock = ServerDrv::getSocket();
    if (_sock != NO_SOCKET_AVAIL)
    {
        ServerDrv::startServer(_port, _sock);
    }
}

WiFiClient WiFiServer::available(byte* status)
{
    int sock = NO_SOCKET_AVAIL;

    if (_sock != NO_SOCKET_AVAIL) {
      // check previous received client socket
      if (_lastSock != NO_SOCKET_AVAIL) {
          WiFiClient client(_lastSock);

          if (client.connected() && client.available()) {
              sock = _lastSock;
          }
      }

      if (sock == NO_SOCKET_AVAIL) {
          // check for new client socket
          sock = ServerDrv::availServer(_sock);
      }
    }

    if (sock != NO_SOCKET_AVAIL) {
        WiFiClient client(sock);

        if (status != NULL) {
            *status = client.status();
        }

        _lastSock = sock;

        return client;
    }

    return WiFiClient(255);
}

uint8_t WiFiServer::status() {
    if (_sock == NO_SOCKET_AVAIL) {
        return CLOSED;
    } else {
        return ServerDrv::getServerState(_sock);
    }
}


size_t WiFiServer::write(uint8_t b)
{
    return write(&b, 1);
}

size_t WiFiServer::write(const uint8_t *buffer, size_t size)
{
    if (size==0)
    {
        setWriteError();
        return 0;
    }

    size_t written = ServerDrv::sendData(_sock, buffer, size);
    if (!written)
    {
        setWriteError();
        return 0;
    }

    if (!ServerDrv::checkDataSent(_sock))
    {
        setWriteError();
        return 0;
    }

    return written;
}
