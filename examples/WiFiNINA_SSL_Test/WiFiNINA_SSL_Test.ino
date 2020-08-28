/****************************************************************************************************************************
  WiFiNINA_SSL_Test.ino

  This example creates a client object that connects and transfers
  data using always SSL.

  It is compatible with the methods normally related to plain
  connections, like client.connect(host, port).

  Written by Arturo Guadalupi
  last revision November 2015

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

  Version: 1.7.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0   K Hoang      27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                  such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  1.5.1   K Hoang      22/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense,
                                  Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, etc.
  1.5.2   K Hoang      09/05/2020 Port FirmwareUpdater to permit nRF52, Teensy, SAMD21, SAMD51, etc. boards to update WiFiNINA
                                  W101/W102 firmware and SSL certs on IDE. Update default pin-outs.
  1.5.3   K Hoang      14/07/2020 Add function to support new WebSockets2_Generic Library
  1.6.0   K Hoang      19/07/2020 Sync with Arduino WiFiNINA Library v1.6.0 (new Firmware 1.4.0 and WiFiStorage)
  1.6.1   K Hoang      24/07/2020 Add support to all STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards 
  1.6.2   K Hoang      28/07/2020 Fix WiFiStorage bug from v1.6.0  
  1.7.0   K Hoang      06/08/2020 Sync with Arduino WiFiNINA Library v1.7.0 : Add downloadOTA() and verify length/CRC
  1.7.1   K Hoang      27/08/2020 Sync with Arduino WiFiNINA Library v1.7.1 : new Firmware 1.4.1
*****************************************************************************************************************************/

#include "defines.h"
#include "arduino_secrets.h"

#include <SPI.h>
#include <WiFiNINA_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8+

int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
char server[] = "arduino.cc";    // name address for Arduino (using DNS)

// Initialize the Wifi client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) ;

  Serial.println("\nStart WiFiNINA_SSL_Test on " + String(BOARD_NAME));

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(1000);
  }

  Serial.print("Connected to wifi SSID: ");
  Serial.println(ssid);

  Serial.println("\nStarting connection to server...");

  // if you get a connection, report back via serial:
  if (client.connectSSL(server, 443))
  {
    Serial.print("Connected to server: ");
    Serial.println(server);

    // Make a HTTP request:
    client.println("GET /asciilogo.txt HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("Connection: close");
    client.println();
    Serial.println("Request sent");
  }
  else
  {
    Serial.print("Can't connected to server: ");
    Serial.println(server);
  }
}

void loop() 
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected())
  {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}
