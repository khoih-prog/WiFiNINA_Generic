/****************************************************************************************************************************
  defines.h 
  For boards with WiFiNINA module/shield.
  
  Based on and modified from WiFiNINA libarary https://www.arduino.cc/en/Reference/WiFiNINA
  to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiNINA_Generic
  Licensed under MIT license
  Version: 1.6.0

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
  1.5.2   K Hoang      09/05/2020 Port FirmwareUpdater to permit nRF52, Teensy, SAMD21, SAMD51, etc. boards to update WiFiNINA
                                  W101/W102 firmware and SSL certs on IDE. Update default pin-outs.
  1.5.3   K Hoang      14/07/2020 Add function to support new WebSockets2_Generic Library
  1.6.0   K Hoang      19/07/2020 Sync with Aruino WiFiNINA Library v1.6.0 (new Firmware 1.4.0 and WiFiStorage)
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFININA_USE_SAMD)
    #undef WIFININA_USE_SAMD
  #endif
  #define WIFININA_USE_SAMD      true
#endif

#if defined(WIFININA_USE_SAMD)

  #if defined(ARDUINO_SAMD_ZERO)
  #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
  #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
  #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
  #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
  #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
  #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
  #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
  #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(__SAMD21E18A__)
  #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
  #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
  #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
  #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
  #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
  #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
  #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
  #define BOARD_TYPE      "SAMD51"
  #else
  #define BOARD_TYPE      "SAMD Unknown"
  #endif

#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(WIFININA_USE_NRF52)
    #undef WIFININA_USE_NRF52
  #endif
  #define WIFININA_USE_NRF52     true
#endif

#if defined(WIFININA_USE_NRF52)

  #if defined(NRF52840_FEATHER)
  #define BOARD_TYPE      "NRF52840_FEATHER_EXPRESS"
  #elif defined(NRF52832_FEATHER)
  #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
  #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
  #define BOARD_TYPE      "NRF52840_ITSYBITSY_EXPRESS"
  #elif defined(NRF52840_CIRCUITPLAY)
  #define BOARD_TYPE      "NRF52840_CIRCUIT_PLAYGROUND"
  #elif defined(NRF52840_CLUE)
  #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
  #define BOARD_TYPE      "NRF52840_METRO_EXPRESS"
  #elif defined(NRF52840_PCA10056)
  #define BOARD_TYPE      "NORDIC_NRF52840DK"
  #elif defined(NINA_B302_ublox)
  #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
  #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
  #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(MDBT50Q_RX)
  #define BOARD_TYPE      "RAYTAC_MDBT50Q_RX"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
  #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
  #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFININA_USE_SAMDUE)
    #undef WIFININA_USE_SAMDUE
  #endif
  #define WIFININA_USE_SAMDUE      true
  #endif
#endif

#if defined(WIFININA_USE_SAMDUE)

// For SAM DUE
#if defined(ARDUINO_SAM_DUE)
#define BOARD_TYPE      "SAM DUE"
#elif defined(__SAM3X8E__)
#define BOARD_TYPE      "SAM SAM3X8E"
#else
#define BOARD_TYPE      "SAM Unknown"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#define DEBUG_WIFININA_PORT     Serial
// Debug Level from 0 to 4
#define _WIFININA_LOGLEVEL_     1

#endif      //defines_h
