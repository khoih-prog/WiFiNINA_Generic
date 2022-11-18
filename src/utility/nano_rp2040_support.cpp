/**********************************************************************************************************************************
  nano_rp2040_support.cpp - Library for Arduino WiFiNINA module/shield.

  Based on and modified from WiFiNINA library https://www.arduino.cc/en/Reference/WiFiNINA
  to support nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, etc. boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR400, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiNINA_Generic
  Licensed under MIT license

  This file is part of the WiFiNINA library.
  Copyright (c) 2021 Arduino SA. All rights reserved.

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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

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

//#ifdef ARDUINO_NANO_RP2040_CONNECT

#if defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT)

/******************************************************************************
   INCLUDE
 ******************************************************************************/

#include "nina_pins.h" /* variants/NANO_RP2040_CONNECT/ninaPins.h */
#include "wifi_drv.h"

/******************************************************************************
   FUNCTION DEFINITION
 ******************************************************************************/

#ifdef NINA_PINS_AS_CLASS
  #define VAL(x)      x.get()
#else
  #define VAL(x)      static_cast<uint8_t>(x)
#endif

////////////////////////////////////////

uint8_t toAnalogPin(NinaPin pin)
{
  if      (pin == A4)
    return 6; /* ADC1 - CH6 */
  else if (pin == A5)
    return 3; /* ADC1 - CH3 */

#if defined(ARDUINO_NANO_RP2040_CONNECT)
  else if (pin == A6)
    return 0; /* ADC1 - CH0 */
  else if (pin == A7)
    return 7; /* ADC1 - CH7 */

#endif

  else
    return 0xFF;
}

////////////////////////////////////////

void pinMode(NinaPin pin, PinMode mode)
{
  WiFiDrv::pinMode(VAL(pin), static_cast<uint8_t>(mode));
}

////////////////////////////////////////

PinStatus digitalRead(NinaPin pin)
{
  return WiFiDrv::digitalRead(VAL(pin));
}

////////////////////////////////////////

void digitalWrite(NinaPin pin, PinStatus value)
{
  if (value == LOW)
  {
    WiFiDrv::digitalWrite(VAL(pin), 1);
  }
  else
  {
    WiFiDrv::digitalWrite(VAL(pin), 0);
  }
}

////////////////////////////////////////

int analogRead(NinaPin pin)
{
  uint8_t const adc_channel = toAnalogPin(pin);

  if (adc_channel == 0xFF)
    return 0;
  else
#ifdef NINA_PINS_AS_CLASS
    return WiFiDrv::analogRead(adc_channel) >> (12 - pin.analogReadResolution());

#else
    return WiFiDrv::analogRead(adc_channel);
#endif
}

////////////////////////////////////////

void analogWrite(NinaPin pin, int value)
{
  WiFiDrv::analogWrite(VAL(pin), static_cast<uint8_t>(value));
}

////////////////////////////////////////

#endif /* ARDUINO_NANO_RP2040_CONNECT */
