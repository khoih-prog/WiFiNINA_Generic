/****************************************************************************************************************************
  FirmwareUpdater.ino - Firmware Updater for the
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

#include "ESP32BootROM.h"

typedef struct __attribute__((__packed__))
{
  uint8_t command;
  uint32_t address;
  uint32_t arg1;
  uint16_t payloadLength;

  // payloadLenght bytes of data follows...
}
UartPacket;

static const int MAX_PAYLOAD_SIZE = 1024;

#define CMD_READ_FLASH        0x01
#define CMD_WRITE_FLASH       0x02
#define CMD_ERASE_FLASH       0x03
#define CMD_MD5_FLASH         0x04
#define CMD_MAX_PAYLOAD_SIZE  0x50
#define CMD_HELLO             0x99

void setup()
{
#if defined(NINA_B302_ublox) ||  defined(NRF52_SERIES)
#warning Serial speed currently set to 921,600 for nRF52 and NINA_B302_ublox
  Serial.begin(921600);
#elif   ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
      || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
      || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
      || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
      || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )
  // Change according to the speed your board can support
  // 1000000 is default and working for Nano 33 IoT, ARDUINO_SAMD_MKRWIFI1010, ARDUINO_SAMD_MKRVIDOR4000
#warning Serial speed currently set to 1,000,000 for SAMD21 and SAMD51
  Serial.begin(1000000);
#elif ( defined(CORE_TEENSY) || defined(__IMXRT1062__) || defined(__MK66FX1M0__) || defined(__MK64FX512__) || defined(__MK20DX256__)\
     || defined(__MK20DX128__) )
#if ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )
#error Teensy LC and 2.0 not supported
#endif
  // Change according to the speed your board can support
#warning Serial speed currently set to 921,600 for Teensy boards
  Serial.begin(921600);
#else
  // Change according to the speed your board can support
  Serial.begin(921600);
#endif

  if (!ESP32BootROM.begin(921600))
  {
    Serial.println(F("Unable to communicate with ESP32 boot ROM!"));

    while (1);
  }

  Serial.println(F("Communicate OK with ESP32 boot ROM!"));
}

void receivePacket(UartPacket *pkt, uint8_t *payload)
{
  // Read command
  uint8_t *p = reinterpret_cast<uint8_t *>(pkt);
  uint16_t l = sizeof(UartPacket);

  while (l > 0)
  {
    int c = Serial.read();

    if (c == -1)
      continue;

    *p++ = c;
    l--;
  }

  // Convert parameters from network byte order to cpu byte order
  pkt->address = fromNetwork32(pkt->address);
  pkt->arg1 = fromNetwork32(pkt->arg1);
  pkt->payloadLength = fromNetwork16(pkt->payloadLength);

  // Read payload
  l = pkt->payloadLength;

  while (l > 0)
  {
    int c = Serial.read();

    if (c == -1)
      continue;

    *payload++ = c;
    l--;
  }
}

// Allocated statically so the compiler can tell us
// about the amount of used RAM
static UartPacket pkt;
static uint8_t payload[MAX_PAYLOAD_SIZE];

void loop()
{
  receivePacket(&pkt, payload);

  if (pkt.command == CMD_HELLO)
  {
    if (pkt.address == 0x11223344 && pkt.arg1 == 0x55667788)
      Serial.print(F("v10000"));
  }

  if (pkt.command == CMD_MAX_PAYLOAD_SIZE)
  {
    uint16_t res = toNetwork16(MAX_PAYLOAD_SIZE);
    Serial.write(reinterpret_cast<uint8_t *>(&res), sizeof(res));
  }

  if (pkt.command == CMD_READ_FLASH)
  {
    // not supported!
    Serial.println(F("ER"));
  }

  if (pkt.command == CMD_WRITE_FLASH)
  {
    uint32_t len = pkt.payloadLength;

    if (!ESP32BootROM.dataFlash(payload, len))
    {
      Serial.print(F("ER"));
    }
    else
    {
      Serial.print(F("OK"));
    }
  }

  if (pkt.command == CMD_ERASE_FLASH)
  {
    uint32_t address = pkt.address;
    uint32_t len = pkt.arg1;

    if (!ESP32BootROM.beginFlash(address, len, MAX_PAYLOAD_SIZE))
    {
      Serial.print(F("ER"));
    }
    else
    {
      Serial.print(F("OK"));
    }
  }

  if (pkt.command == CMD_MD5_FLASH)
  {
    uint32_t address = pkt.address;
    uint32_t len = pkt.arg1;

    if (!ESP32BootROM.endFlash(1))
    {
      Serial.print(F("ER"));
    }
    else
    {
      ESP32BootROM.end();

      uint8_t md5[16];

      if (!ESP32BootROM.begin(921600))
      {
        Serial.print(F("ER"));
      }
      else if (!ESP32BootROM.md5Flash(address, len, md5))
      {
        Serial.print(F("ER"));
      }
      else
      {
        Serial.print(F("OK"));
        Serial.write(md5, sizeof(md5));
      }
    }
  }
}
