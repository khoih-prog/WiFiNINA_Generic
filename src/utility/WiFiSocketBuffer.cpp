/**********************************************************************************************************************************
  WiFiSocketBuffer.cpp - Library for Arduino WiFiNINA module/shield.

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

#include <stdlib.h>
#include <string.h>

#include "utility/server_drv.h"

#include "WiFiSocketBuffer.h"

////////////////////////////////////////

#define WIFI_SOCKET_NUM_BUFFERS (sizeof(_buffers) / sizeof(_buffers[0]))

////////////////////////////////////////

#ifdef __AVR__
  #define WIFI_SOCKET_BUFFER_SIZE 64
#else
  #define WIFI_SOCKET_BUFFER_SIZE 1500
#endif

////////////////////////////////////////

WiFiSocketBufferClass::WiFiSocketBufferClass()
{
  memset(&_buffers, 0x00, sizeof(_buffers));
}

////////////////////////////////////////

WiFiSocketBufferClass::~WiFiSocketBufferClass()
{
  for (unsigned int i = 0; i < WIFI_SOCKET_NUM_BUFFERS; i++)
  {
    close(i);
  }
}

////////////////////////////////////////

void WiFiSocketBufferClass::close(int socket)
{
  if (_buffers[socket].data)
  {
    free(_buffers[socket].data);
    _buffers[socket].data = _buffers[socket].head = NULL;
    _buffers[socket].length = 0;
  }
}

////////////////////////////////////////

int WiFiSocketBufferClass::available(int socket)
{
  if (_buffers[socket].length == 0)
  {
    if (_buffers[socket].data == NULL)
    {
      _buffers[socket].data = _buffers[socket].head = (uint8_t*)malloc(WIFI_SOCKET_BUFFER_SIZE);
      _buffers[socket].length = 0;
    }

    // sizeof(size_t) is architecture dependent
    // but we need a 16 bit data type here
    uint16_t size = WIFI_SOCKET_BUFFER_SIZE;

    if (ServerDrv::getDataBuf(socket, _buffers[socket].data, &size))
    {
      _buffers[socket].head = _buffers[socket].data;
      _buffers[socket].length = size;
    }
  }

  return _buffers[socket].length;
}

////////////////////////////////////////

int WiFiSocketBufferClass::peek(int socket)
{
  if (!available(socket))
  {
    return -1;
  }

  return *_buffers[socket].head;
}

////////////////////////////////////////

int WiFiSocketBufferClass::read(int socket, uint8_t* data, size_t length)
{
  int avail = available(socket);

  if (!avail)
  {
    return 0;
  }

  if (avail < (int)length)
  {
    length = avail;
  }

  memcpy(data, _buffers[socket].head, length);
  _buffers[socket].head += length;
  _buffers[socket].length -= length;

  return length;
}

////////////////////////////////////////

WiFiSocketBufferClass WiFiSocketBuffer;
