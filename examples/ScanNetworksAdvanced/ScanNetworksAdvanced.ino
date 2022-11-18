/****************************************************************************************************************************
  ScanNetworksAdvanced.ino

  This example  prints the board's MAC address, and
  scans for available WiFi networks using the NINA module.
  Every ten seconds, it scans again. It doesn't actually
  connect to any network, so no encryption scheme is specified.
  BSSID and WiFi channel are printed

  Circuit:
    Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  This example is based on ScanNetworks

  created 1 Mar 2017
  by Arturo Guadalupi

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

#include "defines.h"
#include "arduino_secrets.h"

// To eliminate FW warning when using not latest nina-fw version
// To use whenever WiFi101-FirmwareUpdater-Plugin is not sync'ed with nina-fw version
#define WIFI_FIRMWARE_LATEST_VERSION        "1.4.8"

#include <SPI.h>

#if USING_WIFI101
  #include <WiFi101_Generic.h>
#else
  #include <WiFiNINA_Generic.h>
#endif

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print(F("\nStart ScanNetworksAdvanced on "));
  Serial.println(BOARD_NAME);

// check for the WiFi module:
#if USING_WIFI101
  if (WiFi.status() == WL_NO_SHIELD)
#else
  Serial.println(WIFININA_GENERIC_VERSION);
  
  if (WiFi.status() == WL_NO_MODULE)
#endif
  {
    Serial.println(F("Communication with WiFi module failed!"));

    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.print(F("Your current firmware NINA FW v"));
    Serial.println(fv);
    Serial.print(F("Please upgrade the firmware to NINA FW v"));
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
  }

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print(F("MAC: "));
  printMacAddress(mac);

  // scan for existing networks:
  Serial.println(F("\nScanning available networks..."));
  listNetworks();
}

void loop()
{
  delay(10000);
  // scan for existing networks:
  Serial.println(F("Scanning available networks..."));
  listNetworks();
}

void listNetworks()
{
  // scan for nearby networks:
  Serial.println(F("** Scan Networks **"));
  int numSsid = WiFi.scanNetworks();

  if (numSsid == -1)
  {
    Serial.println(F("Couldn't get a WiFi connection"));

    while (true);
  }

  // print the list of networks seen:
  Serial.print(F("Number of available networks: "));
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++)
  {
    Serial.print(thisNet + 1);
    Serial.print(F(") "));
    Serial.print(F("Signal: "));
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(F(" dBm"));
    Serial.print(F("\tChannel: "));
    Serial.print(WiFi.channel(thisNet));
    byte bssid[6];
    Serial.print(F("\t\tBSSID: "));
    printMacAddress(WiFi.BSSID(thisNet, bssid));
    Serial.print(F("\tEncryption: "));
    printEncryptionType(WiFi.encryptionType(thisNet));
    Serial.print(F("\t\tSSID: "));
    Serial.println(WiFi.SSID(thisNet));
    Serial.flush();
  }

  Serial.println();
}

void printEncryptionType(int thisType)
{
  // read the encryption type and print out the name:
  switch (thisType)
  {
    case ENC_TYPE_WEP:
      Serial.print(F("WEP"));
      break;

    case ENC_TYPE_TKIP:
      Serial.print(F("WPA"));
      break;

    case ENC_TYPE_CCMP:
      Serial.print(F("WPA2"));
      break;

    case ENC_TYPE_NONE:
      Serial.print(F("None"));
      break;

    case ENC_TYPE_AUTO:
      Serial.print(F("Auto"));
      break;

#if !USING_WIFI101
     case ENC_TYPE_UNKNOWN:
#endif    
    default:
      Serial.print(F("Unknown"));
      break;
  }
}

void print2Digits(byte thisByte)
{
  if (thisByte < 0xF)
  {
    Serial.print(F("0"));
  }

  Serial.print(thisByte, HEX);
}

void printMacAddress(byte mac[])
{
  for (int i = 5; i >= 0; i--)
  {
    if (mac[i] < 16)
    {
      Serial.print(F("0"));
    }

    Serial.print(mac[i], HEX);

    if (i > 0)
    {
      Serial.print(F(":"));
    }
  }

  Serial.println();
}
