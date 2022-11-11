/****************************************************************************************************************************
  CheckFirmwareVersion.ino
  For boards with WiFiNINA module/shield.

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

/*
   This example check if the firmware loaded on the NINA module
   is updated.

   Circuit:
   - Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

   Created 17 October 2018 by Riccardo Rosario Rizzo
   This code is in the public domain.
*/

// To eliminate FW warning when using not latest nina-fw version
// To use whenever WiFi101-FirmwareUpdater-Plugin is not sync'ed with nina-fw version
//#define WIFI_FIRMWARE_LATEST_VERSION        "1.4.8"

#include "defines.h"
#include <SPI.h>
#include <WiFiNINA_Generic.h>

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  // Print a welcome message
  Serial.print(F("\nStart WiFiNINA CheckFirmwareVersion on "));
  Serial.println(BOARD_NAME);
  Serial.println(WIFININA_GENERIC_VERSION);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println(F("Communication with WiFi module failed!"));

    // don't continue
    while (true);
  }

  // Print firmware version on the module
  String fv = WiFi.firmwareVersion();
  String latestFv;

  Serial.print("Firmware version installed: ");
  Serial.println(fv);

  latestFv = WIFI_FIRMWARE_LATEST_VERSION;

  // Print required firmware version
  Serial.print(F("Latest firmware version available : "));
  Serial.println(latestFv);

  // Check if the latest version is installed
  Serial.println();

  if (fv >= latestFv)
  {
    Serial.println(F("Check result: PASSED"));
  }
  else
  {
    Serial.println(F("Check result: NOT PASSED"));
    Serial.println(F(" - The firmware version on the module do not match the"));
    Serial.println(F("   version required by the library, you may experience"));
    Serial.println(F("   issues or failures."));
  }
}

void loop()
{
  // do nothing
}
