/**********************************************************************************************************************************
  spi_drv.cpp - Library for Arduino WiFiNINA module/shield.
  
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
  
  Version: 1.8.14-3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0      K Hoang    27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                   such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  1.5.1      K Hoang    22/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense,
                                   Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, etc.
  1.5.2      K Hoang    09/05/2020 Port FirmwareUpdater to permit nRF52, Teensy, SAMD21, SAMD51, etc. boards to update WiFiNINA
                                   W101/W102 firmware and SSL certs on IDE. Update default pin-outs.
  1.5.3      K Hoang    14/07/2020 Add function to support new WebSockets2_Generic Library
  1.6.0      K Hoang    19/07/2020 Sync with Arduino WiFiNINA Library v1.6.0 (new Firmware 1.4.0 and WiFiStorage)
  1.6.1      K Hoang    24/07/2020 Add support to all STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards 
  1.6.2      K Hoang    28/07/2020 Fix WiFiStorage bug from v1.6.0  
  1.7.0      K Hoang    06/08/2020 Sync with Arduino WiFiNINA Library v1.7.0 : Add downloadOTA() and verify length/CRC
  1.7.1      K Hoang    27/08/2020 Sync with Arduino WiFiNINA Library v1.7.1 : new Firmware 1.4.1
  1.7.2      K Hoang    05/11/2020 Add support to Adafruit Airlift M4 boards: METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4
  1.8.0      K Hoang    19/11/2020 Sync with Arduino WiFiNINA Library v1.8.0 : new Firmware 1.4.2. Add WiFiBearSSLClient.
  1.8.2      K Hoang    02/02/2021 Sync with WiFiNINA v1.8.2 : new Firmware 1.4.3. Add possibility to resend data if lwip_send fails
  1.8.5      K Hoang    20/03/2021 Sync with WiFiNINA v1.8.5 : Feed watchdog within busy-wait-loop within connectBearSSL
  1.8.10     K Hoang    25/05/2021 Sync with WiFiNINA v1.8.10 : Support RP2040, new FW v1.4.5
  1.8.10-1   K Hoang    29/05/2021 Fix PinStatus compile error for some platforms
  1.8.11     K Hoang    14/06/2021 Sync with WiFiNINA v1.8.11 : Support RP2040, new FW v1.4.6
  1.8.12     K Hoang    30/06/2021 Sync with WiFiNINA v1.8.12 : new FW v1.4.7. Add support to most AVR boards.
  1.8.13     K Hoang    03/08/2021 Sync with WiFiNINA v1.8.13 : new FW v1.4.8. Add support to ADAFRUIT_MATRIXPORTAL_M4_EXPRESS
  1.8.14-1   K Hoang    25/11/2021 Fix examples to support ATmega4809 such as UNO_WIFI_REV2 and NANO_EVERY
  1.8.14-2   K Hoang    31/12/2021 Add support to Nano_RP2040_Connect using arduino-pico core
  1.8.14-3   K Hoang    31/12/2021 Fix issue with UDP for Nano_RP2040_Connect using arduino-pico core
 ***********************************************************************************************************************************/

#include "Arduino.h"
#include <SPI.h>
#include "spi_drv.h"
#include "pins_arduino.h"
#include "WiFi_Generic.h"

//KH
#include "WiFiNINA_Pinout_Generic.h"

#if defined(KH_WIFININA_SPI_DEBUG)
  #undef KH_WIFININA_SPI_DEBUG
#endif
#define KH_WIFININA_SPI_DEBUG   0

#ifdef ARDUINO_SAMD_MKRVIDOR4000

// check if a bitstream is already included
#if __has_include(<VidorFPGA.h>)
// yes, so use the existing VidorFPGA include
#include <VidorFPGA.h>
#else
// otherwise, fallback to VidorPeripherals and it's bitstream
#include <VidorPeripherals.h>
#endif

#define NINA_GPIO0    FPGA_NINA_GPIO0
#define SPIWIFI_SS    FPGA_SPIWIFI_SS
#define SPIWIFI_ACK   FPGA_SPIWIFI_ACK
#define SPIWIFI_RESET FPGA_SPIWIFI_RESET

#define pinMode(pin, mode)       FPGA.pinMode(pin, mode)
#define digitalRead(pin)         FPGA.digitalRead(pin)
#define digitalWrite(pin, value) FPGA.digitalWrite(pin, value)
#endif    //ARDUINO_SAMD_MKRVIDOR4000

#define _DEBUG_

// From v1.5.1, For nRF52x
#include "debug.h"

static uint8_t SLAVESELECT = 10; // ss
static uint8_t SLAVEREADY  = 7;  // handshake pin
static uint8_t SLAVERESET  = 5;  // reset pin

static bool inverted_reset = false;

#define DELAY_TRANSFER()

#ifndef SPIWIFI
  #define SPIWIFI SPI
#endif

#ifndef NINA_GPIOIRQ
  #define NINA_GPIOIRQ    NINA_GPIO0
#endif

bool SpiDrv::initialized = false;

extern WiFiClass WiFi;

void SpiDrv::begin()
{
#ifdef ARDUINO_SAMD_MKRVIDOR4000
  FPGA.begin();
#endif

#ifdef SPIWIFI_SS
  SLAVESELECT = SPIWIFI_SS;
#endif

#ifdef SPIWIFI_ACK
  SLAVEREADY = SPIWIFI_ACK;
#endif

#ifdef SPIWIFI_RESET
  SLAVERESET = (uint8_t)SPIWIFI_RESET;
#endif

#ifdef ARDUINO_SAMD_MKRVIDOR4000
  inverted_reset = false;
#else
  if (SLAVERESET > PINS_COUNT) {
    inverted_reset = true;
    SLAVERESET = ~SLAVERESET;
  }
#endif

#if (KH_WIFININA_SPI_DEBUG >1)
  Serial.println("===============================");
  Serial.println("\nUsed/default SPI pinout: ");
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);
  Serial.println("===============================");
  Serial.println("\nUsed/default NINA pinout: ");
  Serial.print("NINA_GPIO0: ");
  Serial.println(NINA_GPIO0);
  Serial.print("NINA_RESETN/SPIWIFI_RESET: ");
  Serial.println(NINA_RESETN);

#if defined(ARDUINO_SAMD_NANO_33_IOT)
  Serial.print("NINA_ACK: ");
  Serial.println(NINA_ACK);
#endif
  
  Serial.println("===============================");
  Serial.println("\nActual final pinout to used: ");
  Serial.print("SPIWIFI_SS: ");
  Serial.println(SPIWIFI_SS);
  Serial.print("SLAVESELECT/SPIWIFI_SS: ");
  Serial.println(SLAVESELECT);
  Serial.print("SLAVEREADY/SPIWIFI_ACK/NINA_ACK: ");
  Serial.println(SLAVEREADY);
  Serial.print("SLAVERESET/SPIWIFI_RESET/NINA_RESETN: ");
  Serial.println(SLAVERESET);
  Serial.println("===============================\n");
#endif

  //SPIWIFI.begin();
  pinMode(SLAVESELECT, OUTPUT);
  pinMode(SLAVEREADY, INPUT);
  pinMode(SLAVERESET, OUTPUT);
  pinMode(NINA_GPIO0, OUTPUT);

  digitalWrite(NINA_GPIO0, HIGH);
  digitalWrite(SLAVESELECT, HIGH);
  digitalWrite(SLAVERESET, inverted_reset ? HIGH : LOW);
  delay(10);
  digitalWrite(SLAVERESET, inverted_reset ? LOW : HIGH);
  delay(750);

  digitalWrite(NINA_GPIO0, LOW);
  pinMode(NINA_GPIOIRQ, INPUT);
  
  SPIWIFI.begin();

#ifdef _DEBUG_
  INIT_TRIGGER()
#endif

  initialized = true;
}

void SpiDrv::end()
{
  digitalWrite(SLAVERESET, inverted_reset ? HIGH : LOW);

  pinMode(SLAVESELECT, INPUT);

  SPIWIFI.end();

  initialized = false;
}

void SpiDrv::spiSlaveSelect()
{
  SPIWIFI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(SLAVESELECT, LOW);

  // wait for up to 5 ms for the NINA to indicate it is not ready for transfer
  // the timeout is only needed for the case when the shield or module is not present
  for (unsigned long start = millis(); (digitalRead(SLAVEREADY) != HIGH) && (millis() - start) < 5;);
}


void SpiDrv::spiSlaveDeselect()
{
  digitalWrite(SLAVESELECT, HIGH);
  SPIWIFI.endTransaction();
}


char SpiDrv::spiTransfer(volatile char data)
{
  char result = SPIWIFI.transfer(data);
  DELAY_TRANSFER();

  return result;                    // return the received byte
}

int SpiDrv::waitSpiChar(unsigned char waitChar)
{
  int timeout = TIMEOUT_CHAR;
  unsigned char _readChar = 0;

  do
  {
    _readChar = readChar(); //get data byte

    if (_readChar == ERR_CMD)
    {
      WARN("Err cmd received\n");
      return -1;
    }
  } while ((timeout-- > 0) && (_readChar != waitChar));

  return  (_readChar == waitChar);
}

int SpiDrv::readAndCheckChar(char checkChar, char* readChar)
{
  getParam((uint8_t*)readChar);

  return  (*readChar == checkChar);
}

char SpiDrv::readChar()
{
  uint8_t readChar = 0;
  getParam(&readChar);
  return readChar;
}

#define WAIT_START_CMD(x) waitSpiChar(START_CMD)


#define IF_CHECK_START_CMD(x)             \
  if (!WAIT_START_CMD(_data))             \
  {                                       \
    TOGGLE_TRIGGER()                      \
    WARN("Error waiting START_CMD");      \
    return 0;                             \
  } else                                  \

#define CHECK_DATA(check, x)              \
  if (!readAndCheckChar(check, &x))       \
  {                                       \
    TOGGLE_TRIGGER()                      \
    WARN("Reply error");                  \
    INFO2(check, (uint8_t)x);             \
    return 0;                             \
  }else                                   \


#define waitSlaveReady() (digitalRead(SLAVEREADY) == LOW)
#define waitSlaveSign() (digitalRead(SLAVEREADY) == HIGH)
#define waitSlaveSignalH() while(digitalRead(SLAVEREADY) != HIGH){}
#define waitSlaveSignalL() while(digitalRead(SLAVEREADY) != LOW){}

void SpiDrv::waitForSlaveSign()
{
  while (!waitSlaveSign());
}

void SpiDrv::waitForSlaveReady(bool const feed_watchdog)
{
  unsigned long const start = millis();
  
  while (!waitSlaveReady())
  {
    if (feed_watchdog) 
    {
      if ((millis() - start) < 10000) 
      {
        WiFi.feedWatchdog();
      }
    }
  }
}

void SpiDrv::getParam(uint8_t* param)
{
  // Get Params data
  *param = spiTransfer(DUMMY_DATA);
  DELAY_TRANSFER();
}

int SpiDrv::waitResponseCmd(uint8_t cmd, uint8_t numParam, uint8_t* param, uint8_t* param_len)
{
  char _data = 0;
  int ii = 0;

  IF_CHECK_START_CMD(_data)
  {
    CHECK_DATA(cmd | REPLY_FLAG, _data) {};

    CHECK_DATA(numParam, _data)
    {
      readParamLen8(param_len);
      
      for (ii = 0; ii < (*param_len); ++ii)
      {
        // Get Params data
        //param[ii] = spiTransfer(DUMMY_DATA);
        getParam(&param[ii]);

        //KH
#if (KH_WIFININA_SPI_DEBUG > 3)
        Serial.print("spi_drv-waitResponseCmd: *param_len = ");
        Serial.println(*param_len);
        Serial.print("spi_drv-waitResponseCmd: *param[ ");
        Serial.print(ii);
        Serial.print(" ] = ");
        Serial.println(param[ii]);
#endif
      }
    }

    readAndCheckChar(END_CMD, &_data);
  }

  return 1;
}
/*
  int SpiDrv::waitResponse(uint8_t cmd, uint8_t numParam, uint8_t* param, uint16_t* param_len)
  {
    char _data = 0;
    int i =0, ii = 0;

    IF_CHECK_START_CMD(_data)
    {
        CHECK_DATA(cmd | REPLY_FLAG, _data){};

        CHECK_DATA(numParam, _data);
        {
            readParamLen16(param_len);
            for (ii=0; ii<(*param_len); ++ii)
            {
                // Get Params data
                param[ii] = spiTransfer(DUMMY_DATA);
            }
        }

        readAndCheckChar(END_CMD, &_data);
    }

    return 1;
  }
*/

int SpiDrv::waitResponseData16(uint8_t cmd, uint8_t* param, uint16_t* param_len)
{
  char _data = 0;
  uint16_t ii = 0;

  IF_CHECK_START_CMD(_data)
  {
    CHECK_DATA(cmd | REPLY_FLAG, _data) {};

    uint8_t numParam = readChar();
    
    if (numParam != 0)
    {
      readParamLen16(param_len);
      
      for (ii = 0; ii < (*param_len); ++ii)
      {
        // Get Params data
        param[ii] = spiTransfer(DUMMY_DATA);
      }
    }

    readAndCheckChar(END_CMD, &_data);
  }

  return 1;
}

int SpiDrv::waitResponseData8(uint8_t cmd, uint8_t* param, uint8_t* param_len)
{
  char _data = 0;
  int ii = 0;

  IF_CHECK_START_CMD(_data)
  {
    CHECK_DATA(cmd | REPLY_FLAG, _data) {};

    uint8_t numParam = readChar();
    
    if (numParam != 0)
    {
      readParamLen8(param_len);
      
      for (ii = 0; ii < (*param_len); ++ii)
      {
        // Get Params data
        param[ii] = spiTransfer(DUMMY_DATA);
      }
    }

    readAndCheckChar(END_CMD, &_data);
  }

  return 1;
}

int SpiDrv::waitResponseParams(uint8_t cmd, uint8_t numParam, tParam* params)
{
  char _data = 0;
  int i = 0, ii = 0;


  IF_CHECK_START_CMD(_data)
  {
    CHECK_DATA(cmd | REPLY_FLAG, _data) {};

    uint8_t _numParam = readChar();
    
    if (_numParam != 0)
    {
      for (i = 0; i < _numParam; ++i)
      {
        params[i].paramLen = readParamLen8();
        
        for (ii = 0; ii < params[i].paramLen; ++ii)
        {
          // Get Params data
          params[i].param[ii] = spiTransfer(DUMMY_DATA);
        }
      }
    } 
    else
    {
      WARN("Error numParam == 0");
      return 0;
    }

    if (numParam != _numParam)
    {
      WARN("Mismatch numParam");
      return 0;
    }

    readAndCheckChar(END_CMD, &_data);
  }
  
  return 1;
}

/*
  int SpiDrv::waitResponse(uint8_t cmd, tParam* params, uint8_t* numParamRead, uint8_t maxNumParams)
  {
    char _data = 0;
    int i =0, ii = 0;

    IF_CHECK_START_CMD(_data)
    {
        CHECK_DATA(cmd | REPLY_FLAG, _data){};

        uint8_t numParam = readChar();

        if (numParam > maxNumParams)
        {
            numParam = maxNumParams;
        }
         numParamRead = numParam;
        if (numParam != 0)
        {
            for (i=0; i<numParam; ++i)
            {
                params[i].paramLen = readParamLen8();

                for (ii=0; ii<params[i].paramLen; ++ii)
                {
                    // Get Params data
                    params[i].param[ii] = spiTransfer(DUMMY_DATA);
                }
            }
        } else
        {
            WARN("Error numParams == 0");
            Serial.println(cmd, 16);
            return 0;
        }
        readAndCheckChar(END_CMD, &_data);
    }
    return 1;
  }
*/

int SpiDrv::waitResponse(uint8_t cmd, uint8_t* numParamRead, uint8_t** params, uint8_t maxNumParams)
{
  char _data = 0;
  int i = 0, ii = 0;

  char *index[WL_SSID_MAX_LENGTH];

  for (i = 0 ; i < WL_NETWORKS_LIST_MAXNUM ; i++)
    index[i] = (char *)params + WL_SSID_MAX_LENGTH * i;

  IF_CHECK_START_CMD(_data)
  {
    CHECK_DATA(cmd | REPLY_FLAG, _data) {};

    uint8_t numParam = readChar();

    if (numParam > maxNumParams)
    {
      numParam = maxNumParams;
    }
    
    *numParamRead = numParam;
    
    if (numParam != 0)
    {
      for (i = 0; i < numParam; ++i)
      {
        uint8_t paramLen = readParamLen8();
        
        for (ii = 0; ii < paramLen; ++ii)
        {
          //ssid[ii] = spiTransfer(DUMMY_DATA);
          // Get Params data
          index[i][ii] = (uint8_t)spiTransfer(DUMMY_DATA);

        }
        
        index[i][ii] = 0;
      }
    } 
    else
    {
      WARN("Error numParams == 0");
      readAndCheckChar(END_CMD, &_data);
      return 0;
    }
    
    readAndCheckChar(END_CMD, &_data);
  }
  
  return 1;
}

void SpiDrv::sendParamNoLen(uint8_t* param, size_t param_len, uint8_t lastParam)
{
  size_t i = 0;
  // Send Spi paramLen
  sendParamLen8(0);

  // Send Spi param data
  for (i = 0; i < param_len; ++i)
  {
    spiTransfer(param[i]);
  }

  // if lastParam==1 Send Spi END CMD
  if (lastParam == 1)
    spiTransfer(END_CMD);
}

void SpiDrv::sendParam(uint8_t* param, uint8_t param_len, uint8_t lastParam)
{
  int i = 0;
  // Send Spi paramLen
  sendParamLen8(param_len);

  // Send Spi param data
  for (i = 0; i < param_len; ++i)
  {
    spiTransfer(param[i]);
  }

  // if lastParam==1 Send Spi END CMD
  if (lastParam == 1)
    spiTransfer(END_CMD);
}

void SpiDrv::sendParamLen8(uint8_t param_len)
{
  // Send Spi paramLen
  spiTransfer(param_len);
}

void SpiDrv::sendParamLen16(uint16_t param_len)
{
  // Send Spi paramLen
  spiTransfer((uint8_t)((param_len & 0xff00) >> 8));
  spiTransfer((uint8_t)(param_len & 0xff));
}

uint8_t SpiDrv::readParamLen8(uint8_t* param_len)
{
  uint8_t _param_len = spiTransfer(DUMMY_DATA);
  
  if (param_len != NULL)
  {
    *param_len = _param_len;
  }
  
  return _param_len;
}

uint16_t SpiDrv::readParamLen16(uint16_t* param_len)
{
  uint16_t _param_len = spiTransfer(DUMMY_DATA) << 8 | (spiTransfer(DUMMY_DATA) & 0xff);
  
  if (param_len != NULL)
  {
    *param_len = _param_len;
  }
  
  return _param_len;
}


void SpiDrv::sendBuffer(uint8_t* param, uint16_t param_len, uint8_t lastParam)
{
  uint16_t i = 0;

  // Send Spi paramLen
  sendParamLen16(param_len);

  // Send Spi param data
  for (i = 0; i < param_len; ++i)
  {
    spiTransfer(param[i]);
  }

  // if lastParam==1 Send Spi END CMD
  if (lastParam == 1)
    spiTransfer(END_CMD);
}


void SpiDrv::sendParam(uint16_t param, uint8_t lastParam)
{
  // Send Spi paramLen
  sendParamLen8(2);

  spiTransfer((uint8_t)((param & 0xff00) >> 8));
  spiTransfer((uint8_t)(param & 0xff));

  // if lastParam==1 Send Spi END CMD
  if (lastParam == 1)
    spiTransfer(END_CMD);
}

/* Cmd Struct Message */
/* _________________________________________________________________________________  */
/*| START CMD | C/R  | CMD  |[TOT LEN]| N.PARAM | PARAM LEN | PARAM  | .. | END CMD | */
/*|___________|______|______|_________|_________|___________|________|____|_________| */
/*|   8 bit   | 1bit | 7bit |  8bit   |  8bit   |   8bit    | nbytes | .. |   8bit  | */
/*|___________|______|______|_________|_________|___________|________|____|_________| */

void SpiDrv::sendCmd(uint8_t cmd, uint8_t numParam)
{
  // Send Spi START CMD
  spiTransfer(START_CMD);

  // Send Spi C + cmd
  spiTransfer(cmd & ~(REPLY_FLAG));

  // Send Spi totLen
  //spiTransfer(totLen);

  // Send Spi numParam
  spiTransfer(numParam);

  // If numParam == 0 send END CMD
  if (numParam == 0)
    spiTransfer(END_CMD);

}

int SpiDrv::available()
{
  return (digitalRead(NINA_GPIOIRQ) != LOW);
}

SpiDrv spiDrv;
