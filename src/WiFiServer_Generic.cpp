/****************************************************************************************************************************
  WiFiServer_Generic.cpp - Library for Arduino WifiNINA module/shield.

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

#include <string.h>
#include "utility/server_drv.h"

#define _WIFININA_LOGLEVEL_         4

extern "C" 
{
  #include "utility/debug.h"
}

#include "WiFi_Generic.h"
#include "WiFiClient_Generic.h"
#include "WiFiServer_Generic.h"

// See Version 1.4.0 can break code that uses more than one WiFiServer and socket
// (https://github.com/arduino-libraries/WiFiNINA/issues/87
#if USING_MULTI_SERVER_ISSUE_FIX
WiFiServer::WiFiServer(uint16_t port) : _sock(NO_SOCKET_AVAIL)
#else
WiFiServer::WiFiServer(uint16_t port) : _sock(NO_SOCKET_AVAIL), _lastSock(NO_SOCKET_AVAIL)
#endif
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

// KH, New 1.5.3
void WiFiServer::begin(uint16_t port)
{
  _port = port;
  begin();
}

// KH New, wrong
//bool WiFiServer::hasClient()
//{
//  if (_sock != NO_SOCKET_AVAIL)
//    return true;
//  return false;
//}


WiFiClient WiFiServer::available(byte* status)
{
  int sock = NO_SOCKET_AVAIL;

  if (_sock != NO_SOCKET_AVAIL) 
  {
// See Version 1.4.0 can break code that uses more than one WiFiServer and socket
// (https://github.com/arduino-libraries/WiFiNINA/issues/87
#if USING_MULTI_SERVER_ISSUE_FIX
    sock = ServerDrv::availServer(_sock);
#else
    // check previous received client socket
    if (_lastSock != NO_SOCKET_AVAIL) 
    {     
      WiFiClient client(_lastSock);
      
      // KH, from v1.6.0 debug
      NN_LOGDEBUG1("WiFiServer::available: _lastSock =", _lastSock);
      
      if (client.connected()) 
        NN_LOGDEBUG("WiFiServer::available: client.connected");
        
      if (client.available()) 
        NN_LOGDEBUG("WiFiServer::available: client.available");
        
      
      //////

      if (client.connected() && client.available()) 
      {
        sock = _lastSock;
        
        // KH, from v1.6.0 debug
        NN_LOGDEBUG1("WiFiServer::available: sock/_lastSock =", sock);
      }
    }

    if (sock == NO_SOCKET_AVAIL) 
    {
      // check for new client socket
      sock = ServerDrv::availServer(_sock);
      
      // KH, from v1.6.0 debug
      //NN_LOGDEBUG1("WiFiServer::available: sock =", sock);
      //////
    }
#endif
    
  }

  if (sock != NO_SOCKET_AVAIL) 
  {
    WiFiClient client(sock);

    if (status != NULL) 
    {
      *status = client.status();
    }

// See Version 1.4.0 can break code that uses more than one WiFiServer and socket
// (https://github.com/arduino-libraries/WiFiNINA/issues/87
#if !USING_MULTI_SERVER_ISSUE_FIX
    _lastSock = sock;
#endif
    
    // KH, from v1.6.0 debug
    NN_LOGDEBUG1("WiFiServer::available: Client OK, sock =", sock);
    //////

    return client;
  }

  // KH, from v1.6.0 debug
  //NN_LOGDEBUG("WiFiServer::available: Client not OK");
  //////
    
  return WiFiClient(255);
}

uint8_t WiFiServer::status() 
{
  if (_sock == NO_SOCKET_AVAIL) 
  {
    return CLOSED;
  } 
  else 
  {
    return ServerDrv::getServerState(_sock);
  }
}


size_t WiFiServer::write(uint8_t b)
{
  return write(&b, 1);
}

size_t WiFiServer::write(const uint8_t *buffer, size_t size)
{
  if (size == 0)
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
