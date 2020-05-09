## WiFiNINA_Generic ( Library for WiFiNINA modules/shields to support many more boards )

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiNINA_Generic.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiNINA_Generic.svg)](http://github.com/khoih-prog/WiFiNINA_Generic/issues)

#### New in v1.5.2

1. Port FirmwareUpdater to permit nRF52 boards to update W102 firmware and SSL certificates using ***Arduino IDE WiFi101/WiFiNINA Firmware Updater.*** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### New in v1.5.1-final
1. Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc. Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to ***NINA_B302_ublox running as nRF52840***. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.

## Features

With this library you can instantiate Servers, Clients and send/receive UDP packets through WiFiNINA. The board can connect either to open or encrypted networks (WEP, WPA). The IP address can be assigned statically or through a DHCP. The library can also manage DNS.


## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Teensy core 1.51 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 7. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 8. [`Adafruit nRF52 v0.20.1 or later`](www.adafruit.com) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, etc.
 

## Quick Start

### Manual Install

To install:

1. Navigate to [WiFiNINA_Generic](https://github.com/khoih-prog/WiFiNINA_Generic) page.
2. Download the latest release `WiFiNINA_Generic-master.zip`.
3. Extract the zip file to `WiFiNINA_Generic-master` directory 
4. Copy whole `WiFiNINA_Generic-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### Using

See examples : 
 1. [AP_SimpleWebServer](examples/AP_SimpleWebServer)
 2. [ConnectNoEncryption](examples/ConnectNoEncryption)
 3. [ConnectWithWEP](examples/ConnectWithWEP)
 4. [ConnectWithWPA](examples/ConnectWithWPA)
 5. [ConnectWithWPA2Enterprise](examples/ConnectWithWPA2Enterprise)
 6. [ScanNetworks](examples/ScanNetworks)
 7. [ScanNetworksAdvanced](examples/ScanNetworksAdvanced)
 8. [SimpleWebServerWiFi](examples/SimpleWebServerWiFi)
 9. [WiFiChatServer](examples/WiFiChatServer)
10. [WiFiPing](examples/WiFiPing)
11. [WiFiSSLClient](examples/WiFiSSLClient)
12. [WiFiUdpNtpClient](examples/WiFiUdpNtpClient)
13. [WiFiUdpSendReceiveString](examples/WiFiUdpSendReceiveString)
14. [WiFiWebClient](examples/WiFiWebClient)
15. [WiFiWebClientRepeating](examples/WiFiWebClientRepeating)
16. [WiFiWebServer](examples/WiFiWebServer)
17. [WiFiNINA_SSL_Test](examples/WiFiNINA_SSL_Test)

#### Important notes

1. To add NINA_B302_ublox boards running as nRF52840, you have to copy the whole nRF52 directory into Adafruit nRF52 directory. Supposing the Adafruit nRF52 version is 0.20.1
These files must be copied into the directory:
- `nRF52/0.20.1/board.txt`
- `nRF52/0.20.1/variants/variant.h`
- `nRF52/0.20.1/variants/variant.cpp`
Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:
- `nRF52/x.yy.z/board.txt`
- `nRF52/x.yy.z/variants/variant.h`
- `nRF52/x.yy.z/variants/variant.cpp`

2. Please change the ***pin-to-pin connection*** in `WiFiNINA_Pinout_Generic.h` to match actual connection. The section for NINA_B302_ublox has been tested and working OK.
For example

```
#elif  ( defined(NINA_B302_ublox) )

  #warning You have to modify pin usage according to actual connection for NRF528XX
  // To define pin out for WiFiNINA here
  // The following is for NINA_B302_ublox as nRF52 and W102 WiFiNINA module
  // Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip). 
  // See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0          (22u)                         // 22, IO4,  P0.16
  
  #define NINA_RESETN         (2u)                          //  2, IO21, P0.12
  #define NINA_ACK            (10u)                         // 10, IO2,  P0.14

  #define SPIWIFI_SS           4            //PIN_SPI1_SS   //  4, IO1,  P0.13
  #define SPIWIFI_ACK          10           //NINA_ACK      // 10, IO2,  P0.14
  #define SPIWIFI_RESET        2            //NINA_RESETN   //  2, IO21, P0.12
  
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) )

  #warning You have to modify pin usage according to actual connection for NRF528XX
  // To define pin out for WiFiNINA here
  // The following is for NINA_B302_ublox as nRF52 and W102 WiFiNINA module
  // Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip). 
  // See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0          (12u)                         // 12, IO8,  P1.00
  
  #define NINA_RESETN         (2u)                          //  2, IO21, P0.12
  #define NINA_ACK            (10u)                         // 10, IO2,  P0.14

  #define SPIWIFI_SS           4            //PIN_SPI1_SS   //  4, IO1,  P0.13
  #define SPIWIFI_ACK          10           //NINA_ACK      // 10, IO2,  P0.14
  #define SPIWIFI_RESET        2            //NINA_RESETN   //  2, IO21, P0.12
```


#### How to update WiFiNINA Firmware and SSL certificates

Please see the [Arduino Tutorial](https://www.arduino.cc/en/Tutorial/WiFiNINAFirmwareUpdater)

`With the same procedure, you may load root certificates on the WiFi module to access securely specific websites. Your board must be running the FirmwareUpdater sketch to work .The root certificates are issued by a limited number of certification authorities, but it is difficult to know which site is using which authority. To ease your life, we allow you to specify directly the URL to which you need to connect securely, leaving to us the task to download the root certificate.`

`The list you are building is not saved from one session to the next one. It might happen that a few websites share the same root certificate. You don't have to worry about this as we take care of it. The space available on your WiFi module to store the certificates is limited to around 10 certificates that, being issued by a limited number of authorities, should be more than enough for the average projects.`

This is the screen to demonstrate the SSL certificates have been loaded successfully onto a nRF52-based NINA_B302_ublox board running with ublox WiFiNINA W102 .

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/SSL_certs.png">
</p>


#### Sample Code [WiFiWebServer example](examples/WiFiWebServer)

```cpp
#include <SPI.h>
#include <WiFiNINA_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "****";        // your network SSID (name)
char pass[] = "********";    // your network password (use for WPA, or use as key for WEP), length must be 8+
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() 
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    //delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop()
{
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
```

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield firmware 1.3.0+` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

### TO DO

1. Add support to many more boards still not working

#### New in v1.5.2

1. Port FirmwareUpdater to permit nRF52 boards to update W102 firmware and SSL certificate using ***Arduino IDE WiFi101/WiFiNINA Firmware Updater.*** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### New in v1.5.1

1. Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc. Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to ***NINA_B302_ublox running as nRF52840***. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.

### Contributions and thanks

1. Forked from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA)
2. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially ***U-Box B302 running as nRF52840***, has never been started and finished. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright

1. Copyright (c) 2018 Arduino SA. All rights reserved.
2. Copyright (c) 2011-2014 Arduino LLC. All right reserved.
3. Copyright 2020- Khoi Hoang


