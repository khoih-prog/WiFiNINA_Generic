/****************************************************************************************************************************
  WiFiSocketBuffer.cpp - Library for Arduino WifiNINA module/shield.
  
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

#include <stdlib.h>
#include <string.h>

#include "utility/server_drv.h"

#include "WiFiSocketBuffer.h"

#define WIFI_SOCKET_NUM_BUFFERS (sizeof(_buffers) / sizeof(_buffers[0]))

#ifdef __AVR__
#define WIFI_SOCKET_BUFFER_SIZE 64
#else
#define WIFI_SOCKET_BUFFER_SIZE 1500
#endif

WiFiSocketBufferClass::WiFiSocketBufferClass()
{
  memset(&_buffers, 0x00, sizeof(_buffers));
}

WiFiSocketBufferClass::~WiFiSocketBufferClass()
{
  for (unsigned int i = 0; i < WIFI_SOCKET_NUM_BUFFERS; i++) {
    close(i);
  }
}

void WiFiSocketBufferClass::close(int socket)
{
  if (_buffers[socket].data) {
    free(_buffers[socket].data);
    _buffers[socket].data = _buffers[socket].head = NULL;
    _buffers[socket].length = 0;
  }
}

int WiFiSocketBufferClass::available(int socket)
{
  if (_buffers[socket].length == 0) {
    if (_buffers[socket].data == NULL) {
      _buffers[socket].data = _buffers[socket].head = (uint8_t*)malloc(WIFI_SOCKET_BUFFER_SIZE);
      _buffers[socket].length = 0;
    }

    // sizeof(size_t) is architecture dependent
    // but we need a 16 bit data type here
    uint16_t size = WIFI_SOCKET_BUFFER_SIZE;
    if (ServerDrv::getDataBuf(socket, _buffers[socket].data, &size)) {
      _buffers[socket].head = _buffers[socket].data;
      _buffers[socket].length = size;
    }
  }

  return _buffers[socket].length;
}

int WiFiSocketBufferClass::peek(int socket)
{
  if (!available(socket)) {
    return -1;
  }

  return *_buffers[socket].head;
}

int WiFiSocketBufferClass::read(int socket, uint8_t* data, size_t length)
{
  int avail = available(socket);

  if (!avail) {
    return 0;
  }

  if (avail < (int)length) {
    length = avail;
  }

  memcpy(data, _buffers[socket].head, length);
  _buffers[socket].head += length;
  _buffers[socket].length -= length;

  return length;
}

WiFiSocketBufferClass WiFiSocketBuffer;
