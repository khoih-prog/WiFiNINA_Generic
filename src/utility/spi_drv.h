/**********************************************************************************************************************************
  spi_drv.h - Library for Arduino WiFiNINA module/shield.

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

#pragma once

#include <inttypes.h>
#include "utility/wifi_spi.h"

////////////////////////////////////////

#define SPI_START_CMD_DELAY   10

#define NO_LAST_PARAM   0
#define LAST_PARAM      1

#define DUMMY_DATA  0xFF

////////////////////////////////////////

#define WAIT_FOR_SLAVE_SELECT() \
  if (!SpiDrv::initialized)     \
  {                             \
    SpiDrv::begin();            \
  }                             \
  SpiDrv::waitForSlaveReady();  \
  SpiDrv::spiSlaveSelect();

////////////////////////////////////////

class SpiDrv
{
  private:
    //static bool waitSlaveReady();
    static void waitForSlaveSign();
    static void getParam(uint8_t* param);

  public:
    static bool initialized;

    static void begin();

    static void end();

    static void spiDriverInit();

    static void spiSlaveSelect();

    static void spiSlaveDeselect();

    static char spiTransfer(volatile char data);

    //static void waitForSlaveReady(bool const feed_watchdog = false);    /* feed_watchdog in TLS_BEARSSL_MODE, etc. */
    static void waitForSlaveReady();    /* feed_watchdog in TLS_BEARSSL_MODE, etc. */

    //static int waitSpiChar(char waitChar, char* readChar);

    static int waitSpiChar(unsigned char waitChar);

    static int readAndCheckChar(char checkChar, char* readChar);

    static char readChar();

    static int waitResponseParams(uint8_t cmd, uint8_t numParam, tParam* params);

    static int waitResponseCmd(uint8_t cmd, uint8_t numParam, uint8_t* param, uint8_t* param_len);

    static int waitResponseData8(uint8_t cmd, uint8_t* param, uint8_t* param_len);

    static int waitResponseData16(uint8_t cmd, uint8_t* param, uint16_t* param_len);

    //static int waitResponse(uint8_t cmd, tParam* params, uint8_t* numParamRead, uint8_t maxNumParams);

    //static int waitResponse(uint8_t cmd, uint8_t numParam, uint8_t* param, uint16_t* param_len);

    static int waitResponse(uint8_t cmd, uint8_t* numParamRead, uint8_t** params, uint8_t maxNumParams);

    static void sendParam(uint8_t* param, uint8_t param_len, uint8_t lastParam = NO_LAST_PARAM);

    // New from v1.6.0
    static void sendParamNoLen(uint8_t* param, size_t param_len, uint8_t lastParam = NO_LAST_PARAM);

    static void sendParamLen8(uint8_t param_len);

    static void sendParamLen16(uint16_t param_len);

    static uint8_t readParamLen8(uint8_t* param_len = NULL);

    static uint16_t readParamLen16(uint16_t* param_len = NULL);

    static void sendBuffer(uint8_t* param, uint16_t param_len, uint8_t lastParam = NO_LAST_PARAM);

    static void sendParam(uint16_t param, uint8_t lastParam = NO_LAST_PARAM);

    static void sendCmd(uint8_t cmd, uint8_t numParam);

    static int available();
};

////////////////////////////////////////

extern SpiDrv spiDrv;

