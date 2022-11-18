/**********************************************************************************************************************************
  server_drv.cpp - Library for Arduino WiFiNINA module/shield.

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

#define _DEBUG_

#define KH_WIFININA_SERVER_DRV_DEBUG   0

#include "server_drv.h"

#include "Arduino.h"
#include "spi_drv.h"

// From v1.5.1, For nRF52x
#include "wl_types.h"
#include "debug.h"

////////////////////////////////////////

// Start server TCP on port specified
void ServerDrv::startServer(uint16_t port, uint8_t sock, uint8_t protMode)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(START_SERVER_TCP_CMD, PARAM_NUMS_3);
  SpiDrv::sendParam(port);
  SpiDrv::sendParam(&sock, 1);
  SpiDrv::sendParam(&protMode, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(START_SERVER_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();
}

////////////////////////////////////////

void ServerDrv::startServer(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(START_SERVER_TCP_CMD, PARAM_NUMS_4);
  SpiDrv::sendParam((uint8_t*)&ipAddress, sizeof(ipAddress));
  SpiDrv::sendParam(port);
  SpiDrv::sendParam(&sock, 1);
  SpiDrv::sendParam(&protMode, 1, LAST_PARAM);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(START_SERVER_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();
}

////////////////////////////////////////

// Start server TCP on port specified
void ServerDrv::startClient(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_4);
  SpiDrv::sendParam((uint8_t*)&ipAddress, sizeof(ipAddress));
  SpiDrv::sendParam(port);
  SpiDrv::sendParam(&sock, 1);
  SpiDrv::sendParam(&protMode, 1, LAST_PARAM);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();
}

////////////////////////////////////////

void ServerDrv::startClient(const char* host, uint8_t host_len, uint32_t ipAddress, uint16_t port, uint8_t sock,
                            uint8_t protMode)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_5);
  SpiDrv::sendParam((uint8_t*)host, host_len);
  SpiDrv::sendParam((uint8_t*)&ipAddress, sizeof(ipAddress));
  SpiDrv::sendParam(port);
  SpiDrv::sendParam(&sock, 1);
  SpiDrv::sendParam(&protMode, 1, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 17 + host_len;

  while (commandSize % 4)
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  //SpiDrv::waitForSlaveReady((protMode == TLS_BEARSSL_MODE));    /* feed_watchdog in TLS_BEARSSL_MODE */
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();
}

////////////////////////////////////////

// Start server TCP on port specified
void ServerDrv::stopClient(uint8_t sock)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(STOP_CLIENT_TCP_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam(&sock, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(STOP_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();
}

////////////////////////////////////////

uint8_t ServerDrv::getServerState(uint8_t sock)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_STATE_TCP_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam(&sock, sizeof(sock), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(GET_STATE_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  return _data;
}

////////////////////////////////////////

uint8_t ServerDrv::getClientState(uint8_t sock)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_CLIENT_STATE_TCP_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam(&sock, sizeof(sock), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(GET_CLIENT_STATE_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  return _data;
}

////////////////////////////////////////

uint16_t ServerDrv::availData(uint8_t sock)
{
  if  (!SpiDrv::available())
  {
    // KH
#if (KH_WIFININA_SERVER_DRV_DEBUG > 2)
    Serial.println("ServerDrv::availData: SpiDrv not available");
#endif
    return 0;
  }

  // KH
#if (KH_WIFININA_SERVER_DRV_DEBUG > 2)
  Serial.println("ServerDrv::availData: SpiDrv OK");
#endif

  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam(&sock, sizeof(sock), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  uint16_t len = 0;

  SpiDrv::waitResponseCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1, (uint8_t*)&len,  &_dataLen);

  SpiDrv::spiSlaveDeselect();

  // KH
#if (KH_WIFININA_SERVER_DRV_DEBUG > 2)
  Serial.print("ServerDrv::availData: len =");
  Serial.println(len);
#endif

  return len;
}

////////////////////////////////////////

uint8_t ServerDrv::availServer(uint8_t sock, uint8_t accept)
{
  if (!SpiDrv::available())
  {
    return 255;
  }

  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  // From https://github.com/arduino-libraries/WiFiNINA/pull/204
  SpiDrv::sendCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_2);
  SpiDrv::sendParam(&sock, sizeof(sock));
  SpiDrv::sendParam(&accept, sizeof(accept), LAST_PARAM);
  //////

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  uint16_t socket = 0;

  SpiDrv::waitResponseCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1, (uint8_t*)&socket,  &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return socket;
}

////////////////////////////////////////

bool ServerDrv::getData(uint8_t sock, uint8_t *data, uint8_t peek)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_DATA_TCP_CMD, PARAM_NUMS_2);
  SpiDrv::sendParam(&sock, sizeof(sock));
  SpiDrv::sendParam(peek, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseData8(GET_DATA_TCP_CMD, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  if (_dataLen != 0)
  {
    *data = _data;
    return true;
  }

  return false;
}

////////////////////////////////////////

bool ServerDrv::getDataBuf(uint8_t sock, uint8_t *_data, uint16_t *_dataLen)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_DATABUF_TCP_CMD, PARAM_NUMS_2);
  SpiDrv::sendBuffer(&sock, sizeof(sock));
  SpiDrv::sendBuffer((uint8_t *)_dataLen, sizeof(*_dataLen), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  if (!SpiDrv::waitResponseData16(GET_DATABUF_TCP_CMD, _data, _dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  if (*_dataLen != 0)
  {
    return true;
  }

  return false;
}

////////////////////////////////////////

bool ServerDrv::insertDataBuf(uint8_t sock, const uint8_t *data, uint16_t _len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(INSERT_DATABUF_CMD, PARAM_NUMS_2);
  SpiDrv::sendBuffer(&sock, sizeof(sock));
  SpiDrv::sendBuffer((uint8_t *)data, _len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 9 + _len;

  while (commandSize % 4)
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseData8(INSERT_DATABUF_CMD, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  if (_dataLen != 0)
  {
    return (_data == 1);
  }

  return false;
}

////////////////////////////////////////

bool ServerDrv::sendUdpData(uint8_t sock)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SEND_DATA_UDP_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam(&sock, sizeof(sock), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseData8(SEND_DATA_UDP_CMD, &_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  if (_dataLen != 0)
  {
    return (_data == 1);
  }

  return false;
}

////////////////////////////////////////

uint16_t ServerDrv::sendData(uint8_t sock, const uint8_t *data, uint16_t len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SEND_DATA_TCP_CMD, PARAM_NUMS_2);
  SpiDrv::sendBuffer(&sock, sizeof(sock));
  SpiDrv::sendBuffer((uint8_t *)data, len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 9 + len;

  while (commandSize % 4)
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint16_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseData8(SEND_DATA_TCP_CMD, (uint8_t*)&_data, &_dataLen))
  {
    WARN("error waitResponse");
  }

  SpiDrv::spiSlaveDeselect();

  return _data;
}

////////////////////////////////////////

uint8_t ServerDrv::checkDataSent(uint8_t sock)
{
  const uint16_t TIMEOUT_DATA_SENT = 25;
  uint16_t timeout = 0;
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  do
  {
    WAIT_FOR_SLAVE_SELECT();
    // Send Command
    SpiDrv::sendCmd(DATA_SENT_TCP_CMD, PARAM_NUMS_1);
    SpiDrv::sendParam(&sock, sizeof(sock), LAST_PARAM);

    // pad to multiple of 4
    SpiDrv::readChar();
    SpiDrv::readChar();

    SpiDrv::spiSlaveDeselect();
    //Wait the reply elaboration
    SpiDrv::waitForSlaveReady();
    SpiDrv::spiSlaveSelect();

    // Wait for reply
    if (!SpiDrv::waitResponseCmd(DATA_SENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
      WARN("error waitResponse isDataSent");
    }

    SpiDrv::spiSlaveDeselect();

    if (_data)
      timeout = 0;
    else
    {
      ++timeout;
      delay(100);
    }

  } while ((_data == 0) && (timeout < TIMEOUT_DATA_SENT));

  return (timeout == TIMEOUT_DATA_SENT) ? 0 : 1;
}

////////////////////////////////////////

uint8_t ServerDrv::getSocket()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_SOCKET_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = -1;
  uint8_t _dataLen = 0;
  SpiDrv::waitResponseCmd(GET_SOCKET_CMD, PARAM_NUMS_1, &_data, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return _data;
}

////////////////////////////////////////

ServerDrv serverDrv;
