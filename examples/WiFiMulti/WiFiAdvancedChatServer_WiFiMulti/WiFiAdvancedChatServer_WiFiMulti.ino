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

#define USE_WIFI_NINA         true
#define USE_WIFI101           false
#define USE_WIFI_CUSTOM       false

#include <SPI.h>
#include <WiFiMulti_Generic.h>
#include <WiFiNINA_Generic.h>

int status = WL_IDLE_STATUS;

#define TELNET_PORT             23

// telnet defaults to port 23
WiFiServer server(TELNET_PORT);

#define MAX_NUMBER_CLIENTS      8

WiFiClient clients[MAX_NUMBER_CLIENTS];

WiFiMulti_Generic wifiMulti;

void heartBeatPrint()
{
  static int num = 1;

  //WFM_LOGDEBUG1("\nWiFi connected, RSSI:", WiFi.RSSI());

  if (WiFi.status() == WL_CONNECTED)
    Serial.print(F("H"));        // H means connected to WiFi
  else
    Serial.print(F("F"));        // F means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

uint8_t connectMultiWiFi()
{
  // For general board, this better be 1000 to enable connect the 1st time
#define WIFI_MULTI_1ST_CONNECT_WAITING_MS             1000L
#define WIFI_MULTI_CONNECT_WAITING_MS                 500L

  Serial.println("WiFi lost. Trying to scan and reconnect");

  WiFi.disconnect();

  int i = 0;

  uint8_t status = wifiMulti.run();

  delay(WIFI_MULTI_1ST_CONNECT_WAITING_MS);

  while ( ( i++ < 20 ) && ( status != WL_CONNECTED ) )
  {
    status = WiFi.status();

    if ( status == WL_CONNECTED )
      break;
    else
      delay(WIFI_MULTI_CONNECT_WAITING_MS);
  }

  if ( status == WL_CONNECTED )
  {
    WFM_LOGERROR1(F("WiFi connected after time: "), i);
    WFM_LOGERROR3(F("SSID:"), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
    WFM_LOGERROR1(F("IP address:"), WiFi.localIP() );
  }
  else
  {
    WFM_LOGERROR(F("WiFi not connected"));

    if (wifiMulti.run() != WL_CONNECTED)
    {
      Serial.println("WiFi not connected!");
      delay(1000);
    }
  }

  return status;
}

void check_WiFi()
{
  if ( (WiFi.status() != WL_CONNECTED) )
  {
    Serial.println(F("\nWiFi lost. Call connectMultiWiFi in loop"));
    connectMultiWiFi();
  }
}

void check_status()
{
  static uint32_t checkstatus_timeout  = 0;
  static uint32_t checkwifi_timeout    = 0;

  static uint32_t current_millis;

#define WIFICHECK_INTERVAL    1000L
#define HEARTBEAT_INTERVAL    10000L

  current_millis = millis();

  // Check WiFi every WIFICHECK_INTERVAL (1) seconds.
  if ((current_millis > checkwifi_timeout) || (checkwifi_timeout == 0))
  {
    check_WiFi();
    checkwifi_timeout = current_millis + WIFICHECK_INTERVAL;
  }

  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((current_millis > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = current_millis + HEARTBEAT_INTERVAL;
  }
}

void printWiFiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print(F("Signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print(F("\nStart WiFiAdvancedChatServer on "));
  Serial.println(BOARD_NAME);
  Serial.println(WIFIMULTI_GENERIC_VERSION);
  Serial.println(WIFININA_GENERIC_VERSION);

  // check for the WiFi module:
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

  wifiMulti.addAP(SECRET_SSID1, SECRET_PASS1);
  wifiMulti.addAP(SECRET_SSID2, SECRET_PASS2);
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
  wifiMulti.addAP("ssid_from_AP_4", "your_password_for_AP_4");

  Serial.println("Connecting WiFi...");

  if (wifiMulti.run() == WL_CONNECTED)
  {
    Serial.print("\nWiFi connected, IP address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.println(F("Connected to WiFi"));
  printWiFiStatus();

  // start the server:
  server.begin();

  Serial.print("Chat server address:");
  Serial.println(WiFi.localIP());
}

void loop()
{
  check_status();

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
