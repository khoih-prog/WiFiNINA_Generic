/****************************************************************************************************************************
  WiFiWebClientRepeating.ino

  This sketch connects to a a web server and makes a request
  using a WiFi equipped Arduino board.

  created 23 April 2012
  modified 31 May 2012
  by Tom Igoe
  modified 13 Jan 2014
  by Federico Vanzati

  http://www.arduino.cc/en/Tutorial/WifiWebClientRepeating
  This code is in the public domain.

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

#define USE_WIFI_NINA         true
#define USE_WIFI101           false
#define USE_WIFI_CUSTOM       false

#include <SPI.h>
#include <WiFiMulti_Generic.h>
#include <WiFiNINA_Generic.h>

int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// server address:
char server[] = "arduino.tips";

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

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

// this method makes a HTTP connection to the server:
void httpRequest()
{
  // close any connection before send a new request.
  // This will free the socket on the Nina module
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80))
  {
    Serial.println(F("\nConnected to server"));
    // Make a HTTP request:
    client.println(F("GET /asciilogo.txt HTTP/1.1"));
    client.println("Host: arduino.tips");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  }
  else
  {
    // if you couldn't make a connection:
    Serial.println(F("Connection failed"));
  }
}

void check_status()
{
  static uint32_t checkstatus_timeout  = 0;
  static uint32_t checkwifi_timeout    = 0;
  static uint32_t sendHTTP_timeout     = 0;

  static uint32_t current_millis;

#define WIFICHECK_INTERVAL    1000L
#define HEARTBEAT_INTERVAL    10000L
#define SEND_HTTP_INTERVAL    20000L

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

  // Send httpRequest every SEND_HTTP_INTERVAL (20) seconds.
  if ((current_millis > sendHTTP_timeout) || (sendHTTP_timeout == 0))
  {
    httpRequest();
    sendHTTP_timeout = current_millis + SEND_HTTP_INTERVAL;
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

  Serial.print(F("\nStart WiFiWebClientRepeating on "));
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
}

void loop()
{
  check_status();

  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }
}
