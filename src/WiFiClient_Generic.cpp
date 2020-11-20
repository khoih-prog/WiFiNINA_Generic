/****************************************************************************************************************************
  WiFiClient_Generic.cpp - Library for Arduino WifiNINA module/shield.

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

uint16_t WiFiClient::_srcport = 1024;

WiFiClient::WiFiClient() : _sock(NO_SOCKET_AVAIL)
{
}

WiFiClient::WiFiClient(uint8_t sock) : _sock(sock)
{
}

int WiFiClient::connect(const char* host, uint16_t port)
{
  IPAddress remote_addr;

  if (WiFi.hostByName(host, remote_addr))
  {
    return connect(remote_addr, port);
  }

  return 0;
}

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

    // wait 4 second for the connection to close
    while (!connected() && millis() - start < 10000)
      delay(1);

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

    // wait 4 second for the connection to close
    while (!connected() && millis() - start < 10000)
      delay(1);

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

    // wait 4 second for the connection to close
    while (!connected() && millis() - start < 10000)
      delay(1);

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

// From v1.8.0
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

    // wait 4 second for the connection to close
    while (!connected() && millis() - start < 10000)
      delay(1);

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

    // wait 4 second for the connection to close
    while (!connected() && millis() - start < 10000)
      delay(1);

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
//////

size_t WiFiClient::write(uint8_t b)
{
  return write(&b, 1);
}

size_t WiFiClient::write(const uint8_t *buf, size_t size)
{
  if (_sock == NO_SOCKET_AVAIL)
  {
    setWriteError();
    return 0;
  }

  if (size == 0)
  {
    setWriteError();
    return 0;
  }

  size_t written = ServerDrv::sendData(_sock, buf, size);

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

int WiFiClient::available()
{
  if (_sock != 255)
  {
    return WiFiSocketBuffer.available(_sock);
  }

  return 0;
}

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


int WiFiClient::read(uint8_t* buf, size_t size)
{
  return  WiFiSocketBuffer.read(_sock, buf, size);
}

int WiFiClient::peek()
{
  return WiFiSocketBuffer.peek(_sock);
}

void WiFiClient::flush()
{
  // TODO: a real check to ensure transmission has been completed
}

void WiFiClient::stop()
{

  if (_sock == 255)
    return;

  ServerDrv::stopClient(_sock);

  int count = 0;

  // wait maximum 5 secs for the connection to close
  while (status() != CLOSED && ++count < 50)
    delay(100);

  WiFiSocketBuffer.close(_sock);
  _sock = 255;
}

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
                        (s == CLOSE_WAIT));

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

WiFiClient::operator bool()
{
  return _sock != 255;
}

IPAddress  WiFiClient::remoteIP()
{
  uint8_t _remoteIp[4]    = {0};
  uint8_t _remotePort[2]  = {0};

  WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
  IPAddress ip(_remoteIp);

  return ip;
}

uint16_t  WiFiClient::remotePort()
{
  uint8_t _remoteIp[4]    = {0};
  uint8_t _remotePort[2]  = {0};

  WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
  uint16_t port = (_remotePort[0] << 8) + _remotePort[1];

  return port;
}
