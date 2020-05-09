/****************************************************************************************************************************
  WiFiUdp_Generic.cpp - Library for Arduino WifiNINA module/shield.
  
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

extern "C" {
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


/* Constructor */
WiFiUDP::WiFiUDP() : _sock(NO_SOCKET_AVAIL), _parsed(0) {}

/* Start WiFiUDP socket, listening at local port PORT */
uint8_t WiFiUDP::begin(uint16_t port) {
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

uint8_t WiFiUDP::beginMulticast(IPAddress ip, uint16_t port) {
    if (_sock != NO_SOCKET_AVAIL)
    {
        stop();
    }

    uint8_t sock = ServerDrv::getSocket();
    if (sock != NO_SOCKET_AVAIL)
    {
        ServerDrv::startServer(ip, port, sock, UDP_MULTICAST_MODE);
        _sock = sock;
        _port = port;
        _parsed = 0;
        return 1;
    }
    return 0;
}

/* return number of bytes available in the current packet,
   will return zero if parsePacket hasn't been called yet */
int WiFiUDP::available() {
	 return _parsed;
}

/* Release any resources being used by this WiFiUDP instance */
void WiFiUDP::stop()
{
	  if (_sock == NO_SOCKET_AVAIL)
	    return;

	  ServerDrv::stopClient(_sock);

	  WiFiSocketBuffer.close(_sock);
	  _sock = NO_SOCKET_AVAIL;
}

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

int WiFiUDP::beginPacket(IPAddress ip, uint16_t port)
{
  if (_sock == NO_SOCKET_AVAIL)
	  _sock = ServerDrv::getSocket();
  if (_sock != NO_SOCKET_AVAIL)
  {
	  ServerDrv::startClient(uint32_t(ip), port, _sock, UDP_MODE);
	  return 1;
  }
  return 0;
}

int WiFiUDP::endPacket()
{
	return ServerDrv::sendUdpData(_sock);
}

size_t WiFiUDP::write(uint8_t byte)
{
  return write(&byte, 1);
}

size_t WiFiUDP::write(const uint8_t *buffer, size_t size)
{
	ServerDrv::insertDataBuf(_sock, buffer, size);
	return size;
}

int WiFiUDP::parsePacket()
{
	while (_parsed--)
	{
	  // discard previously parsed packet data
	  uint8_t b;

	  WiFiSocketBuffer.read(_sock, &b, sizeof(b));
	}

	_parsed = ServerDrv::availData(_sock);

	return _parsed;
}

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

  return result;
}

int WiFiUDP::peek()
{
  if (_parsed < 1)
  {
    return -1;
  }

  return WiFiSocketBuffer.peek(_sock);
}

void WiFiUDP::flush()
{
  // TODO: a real check to ensure transmission has been completed
}

IPAddress  WiFiUDP::remoteIP()
{
	uint8_t _remoteIp[4] = {0};
	uint8_t _remotePort[2] = {0};

	WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
	IPAddress ip(_remoteIp);
	return ip;
}

uint16_t  WiFiUDP::remotePort()
{
	uint8_t _remoteIp[4] = {0};
	uint8_t _remotePort[2] = {0};

	WiFiDrv::getRemoteData(_sock, _remoteIp, _remotePort);
	uint16_t port = (_remotePort[0]<<8)+_remotePort[1];
	return port;
}

