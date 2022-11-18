/**********************************************************************************************************************************
  WiFiClient_Generic.cpp - Library for Arduino WiFiNINA module/shield.

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

#define _WIFININA_LOGLEVEL_         1

extern "C"
{
#include "utility/wl_definitions.h"
#include "utility/wl_types.h"
#include "string.h"
#include "utility/debug.h"
}

#include "utility/server_drv.h"
#include "utility/wifi_drv.h"
#include "utility/WiFiSocketBuffer.h"

#include "WiFi_Generic.h"
#include "WiFiClient_Generic.h"

////////////////////////////////////////

uint16_t WiFiClient::_srcport = 1024;

////////////////////////////////////////

WiFiClient::WiFiClient() : _sock(NO_SOCKET_AVAIL), _retrySend(true)
{
}

////////////////////////////////////////

WiFiClient::WiFiClient(uint8_t sock) : _sock(sock), _retrySend(true)
{
}

////////////////////////////////////////

int WiFiClient::connect(const char* host, uint16_t port)
{
  IPAddress remote_addr;

  if (WiFi.hostByName(host, remote_addr))
  {
    return connect(remote_addr, port);
  }

  return 0;
}

////////////////////////////////////////

int WiFiClient::connect(IPAddress ip, uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startClient(uint32_t(ip), port, _sock);

    unsigned long start = millis();

    // wait 10 second for the connection to close
    while (!connected() && millis() - start < 10000)
    {
      delay(1);
      WiFi.feedWatchdog();
    }

    if (!connected())
    {
      return 0;
    }
  }
  else
  {
    // KH
    NN_LOGDEBUG(F("No Socket available"));

    return 0;
  }

  return 1;
}

////////////////////////////////////////

int WiFiClient::connectSSL(IPAddress ip, uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startClient(uint32_t(ip), port, _sock, TLS_MODE);

    unsigned long start = millis();

    // wait 10 second for the connection to close
    while (!connected() && millis() - start < 10000)
    {
      delay(1);
      WiFi.feedWatchdog();
    }

    if (!connected())
    {
      return 0;
    }
  }
  else
  {
    // KH
    NN_LOGDEBUG(F("No Socket available"));

    return 0;
  }

  return 1;
}

////////////////////////////////////////

int WiFiClient::connectSSL(const char *host, uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startClient(host, strlen(host), uint32_t(0), port, _sock, TLS_MODE);

    unsigned long start = millis();

    // wait 10 second for the connection to close
    while (!connected() && millis() - start < 10000)
    {
      delay(1);
      WiFi.feedWatchdog();
    }

    if (!connected())
    {
      return 0;
    }
  }
  else
  {
    // KH
    NN_LOGDEBUG(F("No Socket available"));

    return 0;
  }

  return 1;
}

////////////////////////////////////////

int WiFiClient::connectBearSSL(IPAddress ip, uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startClient(uint32_t(ip), port, _sock, TLS_BEARSSL_MODE);

    unsigned long start = millis();

    // wait 10 second for the connection to close
    while (!connected() && millis() - start < 10000)
    {
      delay(1);
      WiFi.feedWatchdog();
    }

    if (!connected())
    {
      return 0;
    }
  }
  else
  {
    // KH
    NN_LOGDEBUG(F("No Socket available"));

    return 0;
  }

  return 1;
}

////////////////////////////////////////

int WiFiClient::connectBearSSL(const char *host, uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startClient(host, strlen(host), uint32_t(0), port, _sock, TLS_BEARSSL_MODE);

    unsigned long start = millis();

    // wait 10 second for the connection to close
    while (!connected() && millis() - start < 10000)
    {
      delay(1);
      WiFi.feedWatchdog();
    }

    if (!connected())
    {
      return 0;
    }
  }
  else
  {
    // KH
    NN_LOGDEBUG(F("No Socket available"));

    return 0;
  }

  return 1;
}

////////////////////////////////////////

size_t WiFiClient::write(uint8_t b)
{
  return write(&b, 1);
}

///////////////////////////////////////////////////////////////////////////
// KH rewrite to enable chunk-sending for large file

#define WIFI_CLIENT_MAX_WRITE_RETRY       100

// Don't use larger size or hang
#define WIFI_CLIENT_SEND_MAX_SIZE         4032

////////////////////////////////////////

size_t WiFiClient::write(const uint8_t *buf, size_t size)
{
  int written = 0;
  int retry = WIFI_CLIENT_MAX_WRITE_RETRY;

  size_t totalBytesSent = 0;
  size_t bytesRemaining = size;

  NN_LOGDEBUG1("WiFiClient::write: To write, size = ", size);

  if (_sock == NO_SOCKET_AVAIL)
  {
    setWriteError();

    NN_LOGERROR("WiFiClient::write: NO_SOCKET_AVAIL");

    return 0;
  }

  if (size == 0)
  {
    setWriteError();

    NN_LOGDEBUG("WiFiClient::write: size = 0");

    return 0;
  }

  while (retry)
  {
    written = ServerDrv::sendData(_sock, buf, min(bytesRemaining, WIFI_CLIENT_SEND_MAX_SIZE) );

    if (written > 0)
    {
      totalBytesSent += written;

      NN_LOGDEBUG3("WiFiClient::write: written = ", written, ", totalBytesSent =", totalBytesSent);

      if (totalBytesSent >= size)
      {
        NN_LOGDEBUG3("WiFiClient::write: Done, written = ", written, ", totalBytesSent =", totalBytesSent);

        //completed successfully
        retry = 0;
      }
      else
      {
        buf += written;
        bytesRemaining -= written;
        retry = WIFI_CLIENT_MAX_WRITE_RETRY;

        NN_LOGDEBUG3("WiFiClient::write: Partially Done, written = ", written, ", bytesRemaining =", bytesRemaining);
      }
    }
    else if (written < 0)
    {
      NN_LOGERROR("WiFiClient::write: written error");

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

    NN_LOGDEBUG("WiFiClient::write: error !checkDataSent");

    return 0;
  }

  if (totalBytesSent >= size)
  {
    NN_LOGDEBUG1("WiFiClient::write: OK, totalBytesSent = ", totalBytesSent);
  }
  else
  {
    NN_LOGERROR3("WiFiClient::write: Not OK, size = ", size, ", totalBytesSent = ", totalBytesSent);
  }

  return totalBytesSent;
}

////////////////////////////////////////

size_t WiFiClient::retry(const uint8_t *buf, size_t size, bool write)
{
  size_t rec_bytes = 0;

  if (write)
  {
    //RETRY WRITE
    for (int i = 0; i < 5; i++)
    {
      rec_bytes = ServerDrv::sendData(_sock, buf, size);

      if (rec_bytes)
      {
        break;
      }
    }

    return rec_bytes;
  }
  else
  {
    //RETRY READ
    // To be implemented, if needed
    return rec_bytes;
  }
}

////////////////////////////////////////

int WiFiClient::available()
{
  if (_sock != 255)
  {
    return WiFiSocketBuffer.available(_sock);
  }

  return 0;
}

////////////////////////////////////////

int WiFiClient::read()
{
  if (!available())
  {
    return -1;
  }

  uint8_t b;

  WiFiSocketBuffer.read(_sock, &b, sizeof(b));

  return b;
}

////////////////////////////////////////

int WiFiClient::read(uint8_t* buf, size_t size)
{
  return  WiFiSocketBuffer.read(_sock, buf, size);
}

////////////////////////////////////////

int WiFiClient::peek()
{
  return WiFiSocketBuffer.peek(_sock);
}

////////////////////////////////////////

void WiFiClient::setRetry(bool retry)
{
  _retrySend = retry;
}

////////////////////////////////////////

void WiFiClient::flush()
{
  // TODO: a real check to ensure transmission has been completed
}

////////////////////////////////////////

void WiFiClient::stop()
{
  if (_sock == 255)
    return;

  ServerDrv::stopClient(_sock);

  int count = 0;

  // wait maximum 5 secs for the connection to close
  while (status() != CLOSED && ++count < 50)
  {
    delay(100);
    WiFi.feedWatchdog();
  }

  WiFiSocketBuffer.close(_sock);
  _sock = 255;
}

////////////////////////////////////////

uint8_t WiFiClient::connected()
{
  if (_sock == 255)
  {
    return 0;
  }
  else if (available())
  {
    return 1;
  }
  else
  {
    uint8_t s = status();

    uint8_t result =  !(s == LISTEN || s == CLOSED || s == FIN_WAIT_1 ||
                        s == FIN_WAIT_2 || s == TIME_WAIT ||
                        s == SYN_SENT || s == SYN_RCVD ||
                        s == CLOSE_WAIT);

    if (result == 0)
    {
      WiFiSocketBuffer.close(_sock);
      _sock = 255;
    }

    return result;
    // KH Debug
    //return 0;
  }
}

////////////////////////////////////////

uint8_t WiFiClient::status()
{
  if (_sock == 255)
  {
    return CLOSED;
  }
  else
  {
    return ServerDrv::getClientState(_sock);
  }
}

////////////////////////////////////////

WiFiClient::operator bool()
{
  return _sock != 255;
}

////////////////////////////////////////

IPAddress  WiFiClient::remoteIP()
{
  uint8_t _remoteIp[4]    = {0};
  uint8_t _remotePort[2]  = {0};

  WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
  IPAddress ip(_remoteIp);

  return ip;
}

////////////////////////////////////////

uint16_t  WiFiClient::remotePort()
{
  uint8_t _remoteIp[4]    = {0};
  uint8_t _remotePort[2]  = {0};

  WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
  uint16_t port = (_remotePort[0] << 8) + _remotePort[1];

  return port;
}
