/**********************************************************************************************************************************
  debug.h - Library for Arduino WiFiNINA module/shield.

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

#include <stdio.h>
#include <string.h>

////////////////////////////////////////

// KH Add, v1.6.0
#ifdef DEBUG_WIFININA_PORT
  #define DBG_PORT_NN      DEBUG_WIFININA_PORT
#else
  #define DBG_PORT_NN     Serial
#endif

////////////////////////////////////////

// Change _WIFININA_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

////////////////////////////////////////

#ifndef _WIFININA_LOGLEVEL_
  #define _WIFININA_LOGLEVEL_       0
#endif

///////////////////////////////////////

const char NN_MARK[]  = "[NN] ";
const char NN_SP[]    = " ";

#define NN_PRINT          DBG_PORT_NN.print
#define NN_PRINTLN        DBG_PORT_NN.println
#define NN_FLUSH          DBG_PORT_NN.flush

#define NN_PRINT_MARK     NN_PRINT(NN_MARK)
#define NN_PRINT_SP       NN_PRINT(NN_SP)

///////////////////////////////////////

// Error waitResponse message
#define ERROR_RESPONSE  ":Error waitResponse"

#define NN_LOGERROR0(x)     if(_WIFININA_LOGLEVEL_>0) { NN_PRINT(x); }
#define NN_LOGERROR(x)      if(_WIFININA_LOGLEVEL_>0) { NN_PRINT_MARK; NN_PRINTLN(x); }
#define NN_LOGERROR1(x,y)   if(_WIFININA_LOGLEVEL_>0) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINTLN(y); }
#define NN_LOGERROR2(x,y,z) if(_WIFININA_LOGLEVEL_>0) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINTLN(z); }
#define NN_LOGERROR3(x,y,z,w) if(_WIFININA_LOGLEVEL_>0) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINT(z); NN_PRINT_SP; NN_PRINTLN(w); }

///////////////////////////////////////

#define NN_LOGWARN0(x)     if(_WIFININA_LOGLEVEL_>1) { NN_PRINT(x); }
#define NN_LOGWARN(x)      if(_WIFININA_LOGLEVEL_>1) { NN_PRINT_MARK; NN_PRINTLN(x); }
#define NN_LOGWARN1(x,y)   if(_WIFININA_LOGLEVEL_>1) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINTLN(y); }
#define NN_LOGWARN2(x,y,z) if(_WIFININA_LOGLEVEL_>1) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINTLN(z); }
#define NN_LOGWARN3(x,y,z,w) if(_WIFININA_LOGLEVEL_>1) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINT(z); NN_PRINT_SP; NN_PRINTLN(w); }

///////////////////////////////////////

#define NN_LOGINFO0(x)     if(_WIFININA_LOGLEVEL_>2) { NN_PRINT(x); }
#define NN_LOGINFO(x)      if(_WIFININA_LOGLEVEL_>2) { NN_PRINT_MARK; NN_PRINTLN(x); }
#define NN_LOGINFO1(x,y)   if(_WIFININA_LOGLEVEL_>2) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINTLN(y); }
#define NN_LOGINFO2(x,y,z) if(_WIFININA_LOGLEVEL_>3) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINTLN(z); }
#define NN_LOGINFO3(x,y,z,w) if(_WIFININA_LOGLEVEL_>3) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINT(z); NN_PRINT_SP; NN_PRINTLN(w); }

///////////////////////////////////////

#define NN_LOGDEBUG0(x)     if(_WIFININA_LOGLEVEL_>3) { NN_PRINT(x); }
#define NN_LOGDEBUG(x)      if(_WIFININA_LOGLEVEL_>3) { NN_PRINT_MARK; NN_PRINTLN(x); }
#define NN_LOGDEBUG1(x,y)   if(_WIFININA_LOGLEVEL_>3) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINTLN(y); }
#define NN_LOGDEBUG2(x,y,z) if(_WIFININA_LOGLEVEL_>3) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINTLN(z); }
#define NN_LOGDEBUG3(x,y,z,w) if(_WIFININA_LOGLEVEL_>3) { NN_PRINT_MARK; NN_PRINT(x); NN_PRINT_SP; NN_PRINT(y); NN_PRINT_SP; NN_PRINT(z); NN_PRINT_SP; NN_PRINTLN(w); }

///////////////////////////////////////

#define PRINT_FILE_LINE() do {            \
    Serial.print("[");Serial.print(__FILE__);   \
    Serial.print("::");Serial.print(__LINE__);Serial.print("]");\
} while (0);

//KH
//#define _DEBUG_

#ifdef _DEBUG_

#define INFO(format, args...) do { \
    char buf[250];  \
    sprintf(buf, format, args); \
    Serial.println(buf); \
  } while(0);

#define INFO1(x) do { PRINT_FILE_LINE() Serial.print("-I-");\
      Serial.println(x);          \
  } while (0);

#define INFO2(x,y) do { PRINT_FILE_LINE() Serial.print("-I-");\
      Serial.print(x,16);Serial.print(",");Serial.println(y,16); \
  } while (0);


#else
#define INFO1(x) do {} while(0);
#define INFO2(x,y) do {} while(0);
#define INFO(format, args...) do {} while(0);
#endif

#define WARN(args) do {} while (0);

//KH
#define _DEBUG_SPI_     false

#if _DEBUG_SPI_
#define DBG_PIN2 5
#define DBG_PIN 4

#define START()         digitalWrite(DBG_PIN2, HIGH);
#define END()           digitalWrite(DBG_PIN2, LOW);
#define SET_TRIGGER()   digitalWrite(DBG_PIN, HIGH);
#define RST_TRIGGER()   digitalWrite(DBG_PIN, LOW);

#define INIT_TRIGGER()  pinMode(DBG_PIN, OUTPUT); \
                          pinMode(DBG_PIN2, OUTPUT); \
                          RST_TRIGGER()
#define TOGGLE_TRIGGER() SET_TRIGGER() \
                             delayMicroseconds(2);    \
                                 RST_TRIGGER()
#else
#define START()
#define END()
#define SET_TRIGGER()
#define RST_TRIGGER()
#define INIT_TRIGGER()
#define TOGGLE_TRIGGER()
#endif



