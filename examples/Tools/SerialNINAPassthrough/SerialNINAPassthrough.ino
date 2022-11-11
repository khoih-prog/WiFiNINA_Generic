/****************************************************************************************************************************
  SerialNINAPassthrough - Use esptool to flash the u-blox NINA (ESP32) module
  Arduino MKR WiFi 1010, Arduino MKR Vidor 4000, and Arduino UNO WiFi Rev.2.

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

  unsigned long baud = 119400;
#else
  unsigned long baud = 115200;
#endif

int rts = -1;
int dtr = -1;

#if   ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
      || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
      || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
      || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
      || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )

#define USE_RTS_CTS      false

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

#define USE_RTS_CTS      false

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
#warning To change the pin definitions to match actual assignment for your board

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

#define USE_RTS_CTS      false

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

#ifndef USE_RTS_CTS
  #define  USE_RTS_CTS      true
#endif


void setup()
{
  Serial.begin(baud);

#ifdef ARDUINO_SAMD_MKRVIDOR4000
  FPGA.begin();
#endif

  SerialNina.begin(baud);

#ifdef ARDUINO_SAMD_MKRVIDOR4000
  FPGA.pinMode(FPGA_NINA_GPIO0, OUTPUT);
  FPGA.pinMode(FPGA_SPIWIFI_RESET, OUTPUT);
#else
  pinMode(NINA_GPIO0, OUTPUT);
  pinMode(NINA_RESETN, OUTPUT);
#endif

#ifdef ARDUINO_AVR_UNO_WIFI_REV2
  // manually put the NINA in upload mode
  digitalWrite(NINA_GPIO0, LOW);

  digitalWrite(NINA_RESETN, LOW);
  delay(100);
  digitalWrite(NINA_RESETN, HIGH);
  delay(100);
  digitalWrite(NINA_RESETN, LOW);
#endif
}

void loop()
{

#if USE_RTS_CTS

#ifndef ARDUINO_AVR_UNO_WIFI_REV2

  if (rts != Serial.rts())
  {
#ifdef ARDUINO_SAMD_MKRVIDOR4000
    FPGA.digitalWrite(FPGA_SPIWIFI_RESET, (Serial.rts() == 1) ? LOW : HIGH);
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
    digitalWrite(NINA_RESETN, Serial.rts() ? LOW : HIGH);
#else
    digitalWrite(NINA_RESETN, Serial.rts());
#endif
    rts = Serial.rts();
  }

  if (dtr != Serial.dtr())
  {
#ifdef ARDUINO_SAMD_MKRVIDOR4000
    FPGA.digitalWrite(FPGA_NINA_GPIO0, (Serial.dtr() == 1) ? HIGH : LOW);
#else
    digitalWrite(NINA_GPIO0, (Serial.dtr() == 0) ? HIGH : LOW);
#endif
    dtr = Serial.dtr();
  }

#endif

#endif      // USE_RTS_CTS

  if (Serial.available())
  {
    SerialNina.write(Serial.read());
  }

  if (SerialNina.available())
  {
    Serial.write(SerialNina.read());
  }

#if USE_RTS_CTS

#ifndef ARDUINO_AVR_UNO_WIFI_REV2

  // check if the USB virtual serial wants a new baud rate
  if (Serial.baud() != baud)
  {
    rts = -1;
    dtr = -1;

    baud = Serial.baud();
#ifndef ARDUINO_SAMD_MKRVIDOR4000
    SerialNina.begin(baud);
#endif
  }

#endif

#endif    // #if USE_RTS_CTS
}
