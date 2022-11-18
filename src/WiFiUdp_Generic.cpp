/**********************************************************************************************************************************
  WiFiUdp_Generic.cpp - Library for Arduino WiFiNINA module/shield.

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

#ifdef KH_WIFININA_UDP_DEBUG
  #undef KH_WIFININA_UDP_DEBUG
#endif
#define KH_WIFININA_UDP_DEBUG   0

////////////////////////////////////////

extern "C"
{
#include "utility/debug.h"
#include "utility/wifi_spi.h"
}

#include "utility/server_drv.h"
#include "utility/wifi_drv.h"
#include "utility/WiFiSocketBuffer.h"

#include "WiFi_Generic.h"
#include "WiFiUdp_Generic.h"
#include "WiFiClient_Generic.h"
#include "WiFiServer_Generic.h"

////////////////////////////////////////

/* Constructor */
WiFiUDP::WiFiUDP() : _sock(NO_SOCKET_AVAIL), _parsed(0) {}

////////////////////////////////////////

/* Start WiFiUDP socket, listening at local port PORT */
uint8_t WiFiUDP::begin(uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  uint8_t sock = ServerDrv::getSocket();

  if (sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startServer(port, sock, UDP_MODE);
    _sock = sock;
    _port = port;
    _parsed = 0;
    return 1;
  }

  return 0;
}

////////////////////////////////////////

uint8_t WiFiUDP::beginMulticast(IPAddress ip, uint16_t port)
{
  if (_sock != NO_SOCKET_AVAIL)
  {
    stop();
  }

  uint8_t sock = ServerDrv::getSocket();

  if (sock != NO_SOCKET_AVAIL)
  {
    // KH,  Debug test. Original is ServerDrv::startServer(ip, port, sock, UDP_MULTICAST_MODE);
    ServerDrv::startServer(ip, port, sock, UDP_MULTICAST_MODE);
    //ServerDrv::startServer(port, sock, UDP_MULTICAST_MODE);
    //ServerDrv::startClient(ip, port, sock, UDP_MULTICAST_MODE);

#if (KH_WIFININA_UDP_DEBUG > 1)
    Serial.print("WiFiUDP::beginMulticast: Start Client(Server) on port ");
    Serial.println(port);
#endif

    _sock = sock;
    _port = port;
    _parsed = 0;

    // KH
#if (KH_WIFININA_UDP_DEBUG > 1)
    Serial.println("WiFiUDP::beginMulticast: Start Client(Server) OK");
#endif

    return 1;
  }

  return 0;
}

////////////////////////////////////////

/* return number of bytes available in the current packet,
   will return zero if parsePacket hasn't been called yet */
int WiFiUDP::available()
{
  return _parsed;
}

////////////////////////////////////////

/* Release any resources being used by this WiFiUDP instance */
void WiFiUDP::stop()
{
  if (_sock == NO_SOCKET_AVAIL)
    return;

  ServerDrv::stopClient(_sock);

  WiFiSocketBuffer.close(_sock);
  _sock = NO_SOCKET_AVAIL;
}

////////////////////////////////////////

int WiFiUDP::beginPacket(const char *host, uint16_t port)
{
  // Look up the host first
  int ret = 0;
  IPAddress remote_addr;

  if (WiFi.hostByName(host, remote_addr))
  {
    return beginPacket(remote_addr, port);
  }

  return ret;
}

////////////////////////////////////////

int WiFiUDP::beginPacket(IPAddress ip, uint16_t port)
{
  if (_sock == NO_SOCKET_AVAIL)
    _sock = ServerDrv::getSocket();

  if (_sock != NO_SOCKET_AVAIL)
  {
    ServerDrv::startClient(uint32_t(ip), port, _sock, UDP_MODE);

#if (KH_WIFININA_UDP_DEBUG > 1)
    Serial.print("WiFiUDP::beginPacket: startClient, ip=");
    Serial.print(ip);
    Serial.print(", port=");
    Serial.println(port);
#endif

    return 1;
  }

  return 0;
}

////////////////////////////////////////

int WiFiUDP::endPacket()
{
  return ServerDrv::sendUdpData(_sock);
}

////////////////////////////////////////

size_t WiFiUDP::write(uint8_t byte)
{
  return write(&byte, 1);
}

////////////////////////////////////////

size_t WiFiUDP::write(const uint8_t *buffer, size_t size)
{
#if (KH_WIFININA_UDP_DEBUG > 3)
  Serial.print("\nWiFiUDP::write: buffer=");

  for (int i = 0; i < size; i++)
  {
    Serial.print(String(buffer[i], HEX));
    Serial.print(", ");

    if (( i > 0 ) && ( i % 20 == 0 ))
      Serial.println("");

  }

  Serial.println("");
#endif

  ServerDrv::insertDataBuf(_sock, buffer, size);
  return size;
}

////////////////////////////////////////

int WiFiUDP::parsePacket()
{
#if 0

  while (_parsed--)
  {
    // discard previously parsed packet data
    uint8_t b;

    WiFiSocketBuffer.read(_sock, &b, sizeof(b));
  }

#endif

  _parsed = ServerDrv::availData(_sock);

#if (KH_WIFININA_UDP_DEBUG > 3)

  Serial.print("WiFiUDP::parsePacket: len=");
  Serial.print(_parsed);
  Serial.print(", _sock =");
  Serial.println(_sock);
#endif

  return _parsed;
}

////////////////////////////////////////

int WiFiUDP::read()
{
  if (_parsed < 1)
  {
    return -1;
  }

  uint8_t b;

  WiFiSocketBuffer.read(_sock, &b, sizeof(b));
  _parsed--;

  return b;
}

////////////////////////////////////////

int WiFiUDP::read(unsigned char* buffer, size_t len)
{
  if (_parsed < 1)
  {
    return 0;
  }

  int result = WiFiSocketBuffer.read(_sock, buffer, len);

  if (result > 0)
  {
    _parsed -= result;
  }

#if (KH_WIFININA_UDP_DEBUG > 3)
  Serial.print("WiFiUDP::read: buffer=");

  for (int i = 0; i < result; i++)
  {
    Serial.print(String(buffer[i], HEX));
    Serial.print(", ");

    if (( i > 0 ) && ( i % 20 == 0 ))
      Serial.println("");

  }

  Serial.println("");
#endif

  return result;
}

////////////////////////////////////////

int WiFiUDP::peek()
{
  if (_parsed < 1)
  {
    return -1;
  }

  return WiFiSocketBuffer.peek(_sock);
}

////////////////////////////////////////

void WiFiUDP::flush()
{
  // TODO: a real check to ensure transmission has been completed
}

////////////////////////////////////////

IPAddress  WiFiUDP::remoteIP()
{
  uint8_t _remoteIp[4]    = {0};
  uint8_t _remotePort[2]  = {0};

  WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
  IPAddress ip(_remoteIp);

  return ip;
}

////////////////////////////////////////

uint16_t  WiFiUDP::remotePort()
{
  uint8_t _remoteIp[4]    = {0};
  uint8_t _remotePort[2]  = {0};

  WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
  uint16_t port = (_remotePort[0] << 8) + _remotePort[1];

  return port;
}

////////////////////////////////////////

