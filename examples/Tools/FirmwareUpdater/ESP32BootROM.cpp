/****************************************************************************************************************************
  ESP32BootROM.cpp - part of the Firmware Updater for the
  Arduino Nano-33 IoT, MKR WiFi 1010, Arduino MKR Vidor 4000, and Arduino UNO WiFi Rev.2., Adafruit's nRF52 boards

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
 *****************************************************************************************************************************/
#ifdef ARDUINO_SAMD_MKRVIDOR4000
  #include <VidorPeripherals.h>

  #define NINA_GPIO0 FPGA_NINA_GPIO0
  #define NINA_RESETN FPGA_SPIWIFI_RESET

#endif

#include <WiFiNINA_Pinout_Generic.h>

#include "ESP32BootROM.h"

ESP32BootROMClass::ESP32BootROMClass(HardwareSerial& serial, int gpio0Pin, int resetnPin) :
  _serial(&serial),
  _gpio0Pin(gpio0Pin),
  _resetnPin(resetnPin)
{

}

int ESP32BootROMClass::begin(unsigned long baudrate)
{
#ifdef ARDUINO_SAMD_MKRVIDOR4000
  FPGA.begin();

  _serial->begin(119400);

  FPGA.pinMode(_gpio0Pin, OUTPUT);
  FPGA.pinMode(_resetnPin, OUTPUT);

  FPGA.digitalWrite(_gpio0Pin, LOW);

  FPGA.digitalWrite(_resetnPin, LOW);
  delay(10);
  FPGA.digitalWrite(_resetnPin, HIGH);
  delay(100);

#elif defined(ARDUINO_AVR_UNO_WIFI_REV2)
  _serial->begin(119400);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, LOW);
  delay(100);
  digitalWrite(_resetnPin, HIGH);
  delay(100);
  digitalWrite(_resetnPin, LOW);

#elif defined(NINA_B302_ublox)
  // For NINA_B302_ublox boards. OK now
  _serial->begin(115200);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, LOW);
  delay(100);
  digitalWrite(_resetnPin, HIGH);
  delay(100);
  // check if we need this
  digitalWrite(_gpio0Pin, HIGH);
  delay(100);

#elif defined(NRF52_SERIES)
  // For NRF52_SERIES boards. To change accordingly
  _serial->begin(115200);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, LOW);
  delay(100);
  digitalWrite(_resetnPin, HIGH);
  delay(100);
  // check if we need this
  digitalWrite(_gpio0Pin, HIGH);
  delay(100);

#elif ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )

  // For SAMD21 and SAMD51 boards.  To change accordingly
  _serial->begin(115200);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, HIGH);
  delay(10);
  digitalWrite(_resetnPin, LOW);
  delay(100);
#if ( defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_NANO_RP2040_CONNECT) )
  digitalWrite(_resetnPin, HIGH);
  delay(100);
#endif

#elif ( defined(CORE_TEENSY) || defined(__IMXRT1062__) || defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__)\
     || defined(__MK20DX128__) )

  // For Teensy boards.  To change accordingly
  _serial->begin(115200);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, HIGH);
  delay(10);
  digitalWrite(_resetnPin, LOW);
  delay(100);

  // To check if you need to do this
  digitalWrite(_resetnPin, HIGH);
  delay(100);

#elif defined(ARDUINO_NANO_RP2040_CONNECT) || ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )

  // For RP2040-based boards.  To change accordingly
  _serial->begin(115200);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, HIGH);
  delay(10);
  digitalWrite(_resetnPin, LOW);
  delay(100);
#if defined(ARDUINO_NANO_RP2040_CONNECT)
  digitalWrite(_resetnPin, HIGH);
  delay(100);
#endif

#else

  // For remaining boards.  To change accordingly
  _serial->begin(115200);

  pinMode(_gpio0Pin, OUTPUT);
  pinMode(_resetnPin, OUTPUT);

  digitalWrite(_gpio0Pin, LOW);

  digitalWrite(_resetnPin, HIGH);
  delay(10);
  digitalWrite(_resetnPin, LOW);
  delay(100);
  // To check if you need to do this
  digitalWrite(_resetnPin, HIGH);
  delay(100);

#endif

  int synced = 0;

  for (int retries = 0; !synced && (retries < 5); retries++)
  {
    synced = sync();
  }

  if (!synced)
  {
    return 0;
  }

#if defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_NANO_RP2040_CONNECT)
  (void)baudrate;
#else

  if (baudrate != 115200)
  {
    if (!changeBaudrate(baudrate))
    {
      return 0;
    }

    delay(100);

    _serial->end();
    _serial->begin(baudrate);
  }

#endif

  if (!spiAttach())
  {
    return 0;
  }

  return 1;
}

void ESP32BootROMClass::end()
{
  _serial->end();
}

int ESP32BootROMClass::sync()
{
  const uint8_t data[] =
  {
    0x07, 0x07, 0x12, 0x20,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55
  };

  command(0x08, data, sizeof(data));

  int results[8];

  for (int i = 0; i < 8; i++)
  {
    results[i] = response(0x08, 100);
  }

  return (results[0] == 0);
}

int ESP32BootROMClass::changeBaudrate(unsigned long baudrate)
{
  const uint32_t data[2] =
  {
    baudrate,
    0
  };

  command(0x0f, data, sizeof(data));

  return (response(0x0f, 3000) == 0);
}

int ESP32BootROMClass::spiAttach()
{
  const uint8_t data[] =
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

  command(0x0d, data, sizeof(data));

  return (response(0x0d, 3000) == 0);
}

int ESP32BootROMClass::beginFlash(uint32_t offset, uint32_t size, uint32_t chunkSize)
{
  const uint32_t data[4] =
  {
    size,
    size / chunkSize,
    chunkSize,
    offset
  };

  command(0x02, data, sizeof(data));

  _flashSequenceNumber = 0;
  _chunkSize = chunkSize;

  return (response(0x02, 120000) == 0);
}

int ESP32BootROMClass::dataFlash(const void* data, uint32_t length)
{
  uint32_t cmdData[4 + (_chunkSize / 4)];

  cmdData[0] = length;
  cmdData[1] = _flashSequenceNumber++;
  cmdData[2] = 0;
  cmdData[3] = 0;

  memcpy(&cmdData[4], data, length);

  if (length < _chunkSize)
  {
    memset(&cmdData[4 + (length / 4)], 0xff, _chunkSize - length);
  }

  command(0x03, cmdData, sizeof(cmdData));

  return (response(0x03, 3000) == 0);
}

int ESP32BootROMClass::endFlash(uint32_t reboot)
{
  const uint32_t data[1] =
  {
    reboot
  };

  command(0x04, data, sizeof(data));

  return (response(0x04, 3000) == 0);
}

int ESP32BootROMClass::md5Flash(uint32_t offset, uint32_t size, uint8_t* result)
{
  const uint32_t data[4] =
  {
    offset,
    size,
    0,
    0
  };

  command(0x13, data, sizeof(data));

  uint8_t asciiResult[32];

  if (response(0x13, 3000, asciiResult) != 0)
  {
    return 0;
  }

  char temp[3] = { 0, 0, 0 };

  for (int i = 0; i < 16; i++)
  {
    temp[0] = asciiResult[i * 2];
    temp[1] = asciiResult[i * 2 + 1];

    result[i] = strtoul(temp, NULL, 16);
  }

  return 1;
}

void ESP32BootROMClass::command(int opcode, const void* data, uint16_t length)
{
  uint32_t checksum = 0;

  if (opcode == 0x03)
  {
    checksum = 0xef; // seed

    for (uint16_t i = 16; i < length; i++)
    {
      checksum ^= ((const uint8_t*)data)[i];
    }
  }

  _serial->write(0xc0);
  _serial->write((uint8_t)0x00); // direction
  _serial->write(opcode);
  _serial->write((uint8_t*)&length, sizeof(length));
  writeEscapedBytes((uint8_t*)&checksum, sizeof(checksum));
  writeEscapedBytes((uint8_t*)data, length);
  _serial->write(0xc0);

#ifdef ARDUINO_SAMD_MKRVIDOR4000
  // _serial->flush(); // doesn't work!
#else
  _serial->flush();
#endif
}

int ESP32BootROMClass::response(int opcode, unsigned long timeout, void* body)
{
  uint8_t data[10 + 256];
  uint16_t index = 0;

  uint8_t responseLength = 4;

  for (unsigned long start = millis(); (index < (uint16_t)(10 + responseLength)) && (millis() - start) < timeout;)
  {
    if (_serial->available())
    {
      data[index] = _serial->read();

      if (index == 3)
      {
        responseLength = data[index];
      }

      index++;
    }
  }

#ifdef DEBUG

  if (index)
  {
    for (int i = 0; i < index; i++)
    {
      byte b = data[i];

      if (b < 0x10)
      {
        Serial.print('0');
      }

      Serial.print(b, HEX);
      Serial.print(' ');
    }

    Serial.println();
  }

#endif

  if (index != (uint16_t)(10 + responseLength))
  {
    return -1;
  }

  if (data[0] != 0xc0 || data[1] != 0x01 || data[2] != opcode || data[responseLength + 5] != 0x00
      || data[responseLength + 6] != 0x00 || data[responseLength + 9] != 0xc0)
  {
    return -1;
  }

  if (body)
  {
    memcpy(body, &data[9], responseLength - 4);
  }

  return data[responseLength + 5];
}

void ESP32BootROMClass::writeEscapedBytes(const uint8_t* data, uint16_t length)
{
  uint16_t written = 0;

  while (written < length)
  {
    uint8_t b = data[written++];

    if (b == 0xdb)
    {
      _serial->write(0xdb);
      _serial->write(0xdd);
    }
    else if (b == 0xc0)
    {
      _serial->write(0xdb);
      _serial->write(0xdc);
    }
    else
    {
      _serial->write(b);
    }
  }
}

/*
  #define NINA_GPIO0          (12u)                         // 12, IO8,  P1.00

  #define NINA_RESETN         (2u)                          //  2, IO21, P0.12
  #define NINA_ACK            (10u)                         // 10, IO2,  P0.14

  #define SPIWIFI_SS           4            //PIN_SPI1_SS   //  4, IO1,  P0.13
  #define SPIWIFI_ACK          10           //NINA_ACK      // 10, IO2,  P0.14
  #define SPIWIFI_RESET        2            //NINA_RESETN   //  2, IO21, P0.12

*/

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )

// For SAMD21 and SAMD51  boards. To be changed and added as necessary
#warning To change the pin defintions to match actual assignment for your board

#ifndef SerialNina
  // Just need to do something such as
  #define SerialNina  Serial1   //Serial2, etc.
#endif

#ifndef NINA_GPIO0
  // Just need assign some pin, such as
  #define NINA_GPIO0  (26u)                         //
#endif

#ifndef NINA_RESETN
  // Just need assign some pin, such as
  #define NINA_RESETN (27u)                          //
#endif

#ifndef NINA_ACK
  // Just need assign some pin, such as
  #define NINA_ACK    (28u)                         //
#endif

#elif defined(NINA_B302_ublox) ||  defined(NRF52_SERIES)

#if defined(NINA_B302_ublox)

  // For  NINA_B302_ublox boards. To be changed and added as necessary
  #warning To change the pin defintions to match actual assignment for NINA_B302_ublox

  #ifndef SerialNina
    // Just need to do something such as
    #define SerialNina  Serial1   //Serial2, etc.
  #endif

  #ifndef NINA_GPIO0
    // Just need assign some pin, such as
    #define NINA_GPIO0  (22u)                         // 12, IO8,  P1.00
  #endif

  #ifndef NINA_RESETN
    // Just need assign some pin, such as
    #define NINA_RESETN (2u)                          //  2, IO21, P0.12
  #endif

  #ifndef NINA_ACK
    // Just need assign some pin, such as
    #define NINA_ACK    (10u)                         // 10, IO2,  P0.14
  #endif

#elif defined(NRF52840_ITSYBITSY)

  //Just a template for NRF52840_ITSYBITSY boards. Must be changed and added as necessary
  #warning To change the pin defintions to match actual assignment for NRF52840_ITSYBITSY
  #ifndef SerialNina
    // Just need to do something such as
    #define SerialNina  Serial1   //Serial2, etc.
  #endif

  #ifndef NINA_GPIO0
    // Just need assign some pin, such as
    #define NINA_GPIO0  (12u)                         // 12, IO8,  P1.00
  #endif

  #ifndef NINA_RESETN
    // Just need assign some pin, such as
    #define NINA_RESETN (2u)                          //  2, IO21, P0.12
  #endif

  #ifndef NINA_ACK
    // Just need assign some pin, such as
    #define NINA_ACK    (10u)                         // 10, IO2,  P0.14
  #endif

#elif defined(NRF52_SERIES)

  //Just a template for NRF52_SERIES boards. Must be changed and added as necessary
  #warning To change the pin defintions to match actual assignment for NRF52_SERIES
  #ifndef SerialNina
    // Just need to do something such as
    #define SerialNina  Serial1   //Serial2, etc.
  #endif

  #ifndef NINA_GPIO0
    // Just need assign some pin, such as
    #define NINA_GPIO0  (12u)                         // 12, IO8,  P1.00
  #endif

  #ifndef NINA_RESETN
    // Just need assign some pin, such as
    #define NINA_RESETN (2u)                          //  2, IO21, P0.12
  #endif

  #ifndef NINA_ACK
    // Just need assign some pin, such as
    #define NINA_ACK    (10u)                         // 10, IO2,  P0.14
  #endif

#else

  // For other nRF52 boards. To be changed and added as necessary
  #warning To change the pin defintions to match actual assignment for nRF52

  #ifndef SerialNina
    // Just need to do something such as
    #define SerialNina  Serial1   //Serial2, etc.
  #endif

  #ifndef NINA_GPIO0
    // Just need assign some pin, such as
    #define NINA_GPIO0  (12u)                         // 12, IO8,  P1.00
  #endif

  #ifndef NINA_RESETN
    // Just need assign some pin, such as
    #define NINA_RESETN (2u)                          //  2, IO21, P0.12
  #endif

  #ifndef NINA_ACK
    // Just need assign some pin, such as
    #define NINA_ACK    (10u)                         // 10, IO2,  P0.14
  #endif

#endif    //#if defined(NINA_B302_ublox)

#elif ( defined(CORE_TEENSY) || defined(__IMXRT1062__) || defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__)\
     || defined(__MK20DX128__) )

// For Teensy boards. To be changed and added as necessary
#warning To change the pin defintions to match actual assignment for your board

#ifndef SerialNina
  // Just need to do something such as
  #define SerialNina  Serial1   //Serial2, etc.
#endif

#ifndef NINA_GPIO0
  // Just need assign some pin, such as
  #define NINA_GPIO0  (6u)                         //
#endif

#ifndef NINA_RESETN
  // Just need assign some pin, such as
  #define NINA_RESETN (2u)                          //
#endif

#ifndef NINA_ACK
  // Just need assign some pin, such as
  #define NINA_ACK    (5u)                         //
#endif

#else

// For other boards. To be changed and added as necessary
#warning To change the pin defintions to match actual assignment for your board

#ifndef SerialNina
  // Just need to do something such as
  #define SerialNina  Serial1   //Serial2, etc.
#endif

#ifndef NINA_GPIO0
  // Just need assign some pin, such as
  #define NINA_GPIO0  (12u)                         // 12, IO8,  P1.00
#endif

#ifndef NINA_RESETN
  // Just need assign some pin, such as
  #define NINA_RESETN (2u)                          //  2, IO21, P0.12
#endif

#ifndef NINA_ACK
  // Just need assign some pin, such as
  #define NINA_ACK    (10u)                         // 10, IO2,  P0.14
#endif

#endif    //#if defined(NINA_B302_ublox) ||  defined(NRF52_SERIES)

ESP32BootROMClass ESP32BootROM(SerialNina, NINA_GPIO0, NINA_RESETN);
