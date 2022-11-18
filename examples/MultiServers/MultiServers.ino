/****************************************************************************************************************************
  MultiServers.ino
  For boards with WiFiNINA module/shield.

  by Oscar den Uijl (https://github.com/ocrdu) in (https://github.com/arduino-libraries/WiFiNINA/issues/87)

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
#define _WIFININA_LOGLEVEL_       1

// To eliminate FW warning when using not latest nina-fw version
// To use whenever WiFi101-FirmwareUpdater-Plugin is not sync'ed with nina-fw version
#define WIFI_FIRMWARE_LATEST_VERSION        "1.4.8"

#include "defines.h"

#include <SPI.h>

#if USING_WIFI101
  #include <WiFi101_Generic.h>
#else
  #include <WiFiNINA_Generic.h>
#endif

// https://github.com/ocrdu/NINA-Websocket
#include <WebSocketServer.h>
//////

#include <Base64.h>

#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

#define Sprint(a)   (Serial.print(a))
#define Sprintln(a) (Serial.println(a))

const int IPLastByte  = 99;

const int webPort     = 80;
const int socketPort  = 8080;

WiFiServer      webServer(webPort);
WiFiServer      socketServer(socketPort);
WebSocketServer webSocketServer;
WiFiClient      socketClient;

boolean on = false;
char webpage_base64[] =
  "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";

void printWifiStatus()
{
  Sprint(F("SSID: "));
  Sprintln(WiFi.SSID());
  Sprint(F("Signal strength (RSSI): "));
  Sprint(WiFi.RSSI());
  Sprintln(F(" dBm"));
  Sprint(F("IP address: "));
  Sprintln(WiFi.localIP());
  Sprint(F("Gateway: "));
  Sprintln(WiFi.gatewayIP());
  Sprint(F("Netmask: "));
  Sprintln(WiFi.subnetMask());
  Sprint(F("Webpage is at http://"));
  Sprint(WiFi.localIP());
  Sprintln(F("/"));
  Sprint(F("Websocket is at http://"));
  Sprint(WiFi.localIP());
  Sprintln(":" + (String)socketPort + "/");
}

void WiFiConnect()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    Sprint(F("Connecting to "));
    Sprintln(ssid);
    WiFi.begin(ssid, pass);
    delay(5000);
  }

  IPAddress IP = WiFi.localIP();
  IP[3] = IPLastByte;

  WiFi.config(IP, WiFi.gatewayIP(), WiFi.gatewayIP(), WiFi.subnetMask());
  Sprint(F("Connected to "));
  Sprintln(ssid);


  webServer.begin();
  socketServer.begin();
  printWifiStatus();
  WiFi.lowPowerMode();
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print(F("\nStart MultiServers on "));
  Serial.println(BOARD_TYPE);

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

  pinMode(LED_BUILTIN, OUTPUT);
  WiFiConnect();
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    Sprintln(F("\n--Lost WiFi connection"));
    WiFi.end();
    WiFiConnect();
  }

  //if (!socketClient.connected()) {
  WiFiClient webClient = webServer.available();

  if (webClient.connected())
  {
    Sprint(F("\n--New client: "));
    Sprint(webClient.remoteIP());
    Sprint(F(":"));
    Sprintln(webClient.remotePort());
    String header = "";

    while (webClient.available())
    {
      char c = webClient.read();

      if (c != '\r')
      {
        header += c;
      }

      if (header.substring(header.length() - 2) == "\n\n")
      {
        Sprint(header.substring(0, header.length() - 1));

        if (header.indexOf("GET / HTTP") > -1)
        {
          const int webpage_base64_length = sizeof(webpage_base64);
          const int webpage_gz_length = base64_dec_len(webpage_base64, webpage_base64_length);
          char webpage_gz[webpage_gz_length];
          base64_decode(webpage_gz, webpage_base64, webpage_base64_length);
          int packetsize = 1024;
          int done = 0;

          webClient.println("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Encoding: gzip\n");

          while (webpage_gz_length > done)
          {
            if (webpage_gz_length - done < packetsize)
            {

              packetsize = webpage_gz_length - done;
            }

            webClient.write(webpage_gz + done, packetsize * sizeof(char));
            done = done + packetsize;
          }

          Sprintln(F("--Interface webpage sent"));
        }
        else
        {
          webClient.println("HTTP/1.1 404 Not Found\nContent-Type: text/plain; charset=utf-8\n\n404 Not Found\n");
          Sprintln(F("--Page not found"));
        }

        webClient.stop();
        Sprintln(F("--Client disconnected"));
      }
    }
  }

  //}

  if (!socketClient.connected())
  {
    socketClient = socketServer.available();

    if (socketClient.connected() && webSocketServer.handshake(socketClient))
    {
      Sprint(F("\n--Websocket connected to: "));
      Sprint(socketClient.remoteIP());
      Sprint(F(":"));
      Sprintln(socketClient.remotePort());

      if (on)
      {
        webSocketServer.sendData("sw:true");
      }
      else
      {
        webSocketServer.sendData("sw:false");
      }

      Sprintln(F("\n--Settings sent"));
    }
    else
    {
      //Sprintln(F("\n--Couldn't connect websocket"));
      socketClient.stop();
      delay(100);
    }
  }

  if (socketClient.connected())
  {
    String data = webSocketServer.getData();

    if (data.length() > 0)
    {
      String name = data.substring(0, data.indexOf(":"));
      String value = data.substring(data.indexOf(":") + 1);
      boolean goodSettings = true;

      if (name == "switch")
      {
        on = (value == "true");
      }
      else
      {
        goodSettings = false;
        webSocketServer.sendData("message:Bad data; ignored");
      }

      if (goodSettings)
      {
        webSocketServer.sendData("message:" + name + " set to " + value);
      }
    }
  }
}
