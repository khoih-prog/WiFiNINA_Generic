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

//#ifdef ARDUINO_NANO_RP2040_CONNECT

#if defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT)

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include "nina_pins.h" /* variants/NANO_RP2040_CONNECT/ninaPins.h */
#include "wifi_drv.h"

/******************************************************************************
 * FUNCTION DEFINITION
 ******************************************************************************/

#ifdef NINA_PINS_AS_CLASS
  #define VAL(x)      x.get()
#else
  #define VAL(x)      static_cast<uint8_t>(x)
#endif

uint8_t toAnalogPin(NinaPin pin)
{
  if      (pin == A4) return 6; /* ADC1 - CH6 */
  else if (pin == A5) return 3; /* ADC1 - CH3 */
  
#if defined(ARDUINO_NANO_RP2040_CONNECT)  
  else if (pin == A6) return 0; /* ADC1 - CH0 */
  else if (pin == A7) return 7; /* ADC1 - CH7 */
#endif
  
  else                return 0xFF;
}

void pinMode(NinaPin pin, PinMode mode)
{
  WiFiDrv::pinMode(VAL(pin), static_cast<uint8_t>(mode));
}

PinStatus digitalRead(NinaPin pin)
{
  return WiFiDrv::digitalRead(VAL(pin));
}

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

void analogWrite(NinaPin pin, int value)
{
  WiFiDrv::analogWrite(VAL(pin), static_cast<uint8_t>(value));
}

#endif /* ARDUINO_NANO_RP2040_CONNECT */
