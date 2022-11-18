/****************************************************************************************************************************
  WiFiAdvancedChatServer.ino

  Advanced WiFi Chat Server

  A more advanced server that distributes any incoming messages
  to all connected clients but the client the message comes from.
  To use, telnet to your device's IP address and type.
  You can see the client's input in the serial monitor as well.

  Circuit:
    Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

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
#include <WiFiNINA_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

#define TELNET_PORT             23

// telnet defaults to port 23
WiFiServer server(TELNET_PORT);

#define MAX_NUMBER_CLIENTS      8

WiFiClient clients[MAX_NUMBER_CLIENTS];

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print(F("\nStart WiFiAdvancedChatServer on "));
  Serial.println(BOARD_NAME);
  Serial.println(WIFININA_GENERIC_VERSION);
  
  if (WiFi.status() == WL_NO_MODULE)
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

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED)
  {
    Serial.print(F("Attempting to connect to Network named: "));
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    //delay(10000);
  }

  // start the server:
  server.begin();

  Serial.print("Chat server address:");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // check for any new client connecting, and say hello (before any incoming data)
  WiFiClient newClient = server.accept();

  if (newClient)
  {
    for (byte i = 0; i < MAX_NUMBER_CLIENTS; i++)
    {
      if (!clients[i])
      {
        Serial.print("We have a new client #");
        Serial.println(i);

        newClient.print("Hello, client number: ");
        newClient.println(i);

        // Once we "accept", the client is no longer tracked by WiFiServer
        // so we must store it into our list of clients
        clients[i] = newClient;
        break;
      }
    }
  }

  // check for incoming data from all clients
  for (byte i = 0; i < MAX_NUMBER_CLIENTS; i++)
  {
    if (clients[i] && clients[i].available() > 0)
    {
#define BUFFER_SIZE     80

      // read bytes from a client
      byte buffer[BUFFER_SIZE];
      int count = clients[i].read(buffer, BUFFER_SIZE);

      // write the bytes to all other connected clients
      for (byte j = 0; j < MAX_NUMBER_CLIENTS; j++)
      {
        if (j != i && clients[j].connected())
        {
          clients[j].write(buffer, count);
        }
      }
    }
  }

  // stop any clients which disconnect
  for (byte i = 0; i < MAX_NUMBER_CLIENTS; i++)
  {
    if (clients[i] && !clients[i].connected())
    {
      Serial.print("disconnect client #");
      Serial.println(i);
      clients[i].stop();
    }
  }
}
