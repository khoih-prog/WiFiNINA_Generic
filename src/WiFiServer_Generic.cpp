/**********************************************************************************************************************************
  WiFiServer_Generic.cpp - Library for Arduino WiFiNINA module/shield.

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

#include <string.h>
#include "utility/server_drv.h"

#define _WIFININA_LOGLEVEL_         1

////////////////////////////////////////

extern "C"
{
#include "utility/debug.h"
}

#include "WiFi_Generic.h"
#include "WiFiClient_Generic.h"
#include "WiFiServer_Generic.h"

////////////////////////////////////////

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

////////////////////////////////////////

void WiFiServer::begin()
{
  _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startServer(_port, _sock);
  }
}

////////////////////////////////////////

// From https://github.com/arduino-libraries/WiFiNINA/pull/204
WiFiClient WiFiServer::accept()
{
  int sock = ServerDrv::availServer(_sock, true);

  return WiFiClient(sock);
}

////////////////////////////////////////

void WiFiServer::begin(uint16_t port)
{
  _port = port;
  begin();
}

////////////////////////////////////////

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

      if (client.connected() && client.available())
      {
        sock = _lastSock;
      }
    }

    if (sock == NO_SOCKET_AVAIL)
    {
      // check for new client socket
      sock = ServerDrv::availServer(_sock);
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

    return client;
  }

  return WiFiClient(255);
}

////////////////////////////////////////

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

////////////////////////////////////////

size_t WiFiServer::write(uint8_t b)
{
  return write(&b, 1);
}

////////////////////////////////////////

#define WIFI_SERVER_MAX_WRITE_RETRY       100

// Don't use larger size or hang
#define WIFI_SERVER_SEND_MAX_SIZE         4032

size_t WiFiServer::write(const uint8_t *buf, size_t size)
{
  int written = 0;
  int retry = WIFI_SERVER_SEND_MAX_SIZE;

  size_t totalBytesSent = 0;
  size_t bytesRemaining = size;

  NN_LOGDEBUG1("WiFiServer::write: To write, size = ", size);

  if (_sock == NO_SOCKET_AVAIL)
  {
    setWriteError();

    NN_LOGERROR("WiFiServer::write: NO_SOCKET_AVAIL");

    return 0;
  }

  if (size == 0)
  {
    setWriteError();

    NN_LOGDEBUG("WiFiServer::write: size = 0");

    return 0;
  }

  while (retry)
  {
    written = ServerDrv::sendData(_sock, buf, min(bytesRemaining, WIFI_SERVER_SEND_MAX_SIZE) );

    if (written > 0)
    {
      totalBytesSent += written;

      NN_LOGDEBUG3("WiFiServer::write: written = ", written, ", totalBytesSent =", totalBytesSent);

      if (totalBytesSent >= size)
      {
        NN_LOGDEBUG3("WiFiServer::write: Done, written = ", written, ", totalBytesSent =", totalBytesSent);

        //completed successfully
        retry = 0;
      }
      else
      {
        buf += written;
        bytesRemaining -= written;
        retry = WIFI_SERVER_MAX_WRITE_RETRY;

        // Don't use too short delay so that NINA has some time to recover
        // The fix is considered as kludge, and the correct place to fix is in ServerDrv::sendData()
        //delay(100);

        NN_LOGDEBUG3("WiFiServer::write: Partially Done, written = ", written, ", bytesRemaining =", bytesRemaining);
      }
    }
    else if (written < 0)
    {
      NN_LOGERROR("WiFiServer::write: written error");

      // close socket
      ServerDrv::stopClient(_sock);

      written = 0;
      retry = 0;
    }

    // Looping
  }

  if (!ServerDrv::checkDataSent(_sock))
  {
    setWriteError();

    NN_LOGDEBUG("WiFiServer::write: error !checkDataSent");

    return 0;
  }

  if (totalBytesSent >= size)
  {
    NN_LOGDEBUG1("WiFiServer::write: OK, totalBytesSent = ", totalBytesSent);
  }
  else
  {
    NN_LOGERROR3("WiFiServer::write: Not OK, size = ", size, ", totalBytesSent = ", totalBytesSent);
  }

  return totalBytesSent;
}

////////////////////////////////////////

