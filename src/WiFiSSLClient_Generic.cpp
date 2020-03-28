/****************************************************************************************************************************
  WiFiSSLClient_Generic.cpp - Library for Arduino WifiNINA module/shield.
  
  Forked and modified from WiFiNINA libarary https://www.arduino.cc/en/Reference/WiFiNINA
  to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
  Licensed under MIT license
  Version: 1.5.0
   
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
 *****************************************************************************************************************************/

#include "WiFiSSLClient_Generic.h"

WiFiSSLClient::WiFiSSLClient() : 
	WiFiClient()
{
}

WiFiSSLClient::WiFiSSLClient(uint8_t sock) :
	WiFiClient(sock)
{  
}

int WiFiSSLClient::connect(IPAddress ip, uint16_t port)
{
	return WiFiClient::connectSSL(ip, port);
}

int WiFiSSLClient::connect(const char* host, uint16_t port)
{
	return WiFiClient::connectSSL(host, port);
}
