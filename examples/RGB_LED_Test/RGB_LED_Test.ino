/****************************************************************************************************************************
  RGB_LED_Test.ino

  This example tests LEDR, LEDB and LEDG, accessed via WiFiNINA module.
  Credit of https://learnembeddedsystems.co.uk/using-the-rgb-led-on-the-arduino-nano-rp2040-connect and https://github.com/jandrassy
  Check https://github.com/earlephilhower/arduino-pico/pull/404

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiNINA_Generic
  Licensed under GPLv3 license

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

#if (!defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARCH_MBED))
  #error Only for ARDUINO_NANO_RP2040_CONNECT using arduino-pico core
#endif

#include <WiFiNINA_Generic.h>

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print("RGB_LED_Test on ");
  Serial.print(BOARD_NAME);
  Serial.print(" using ");

#if __has_include("WiFiNINA.h")
  Serial.println("WiFiNINA Library");
#elif __has_include("WiFiNINA_Generic.h")
  Serial.println("WiFiNINA_Generic Library");
#else
#error Error. No WiFiNINA or WiFiNINA_Generic included
#endif

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop()
{
  digitalWrite(LEDR, HIGH);  // Turn On RED LED
  delay(250);
  digitalWrite(LEDR, LOW);   // Turn Off RED LED

  digitalWrite(LEDG, HIGH);  // Turn On GREEN LED
  delay(250);
  digitalWrite(LEDG, LOW);   // Turn Off GREEN LED

  digitalWrite(LEDB, HIGH);  // Turn On BLUE LED
  delay(250);
  digitalWrite(LEDB, LOW);   // Turn Off BLUE LED
}
