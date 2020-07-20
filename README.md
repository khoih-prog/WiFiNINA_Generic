## WiFiNINA_Generic ( Library for WiFiNINA modules/shields to support many more boards )

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiNINA_Generic.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiNINA_Generic.svg)](http://github.com/khoih-prog/WiFiNINA_Generic/issues)

---
## Important Notes

1. Currently, the ***NINA Firmware v1.4.0 creates some not-yet-identified issue to WebServer. Please don't update yet and continue to use NINA Firmware v1.3.0***
2. Investigating now.

#### New in v1.6.0

1. Sync'ed with latest WiFiNINA Library v1.6.0. 
2. New features include ***WiFiStorage*** and update to ***NINA Firmware v1.4.0*** from v1.3.0

#### New in v1.5.3

1. Add function to support new WebSockets2_Generic Library
2. Update default pin-outs for nRF52 boards, especially NINA_112_ublox.

#### New in v1.5.2

1. Port FirmwareUpdater to permit ***nRF52, Teensy, SAMD21, SAMD51, etc.*** boards to update WiFiNINA W101/W102 firmware and SSL certificates using ***Arduino IDE WiFi101/WiFiNINA Firmware Updater.*** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.
3. Add support to ***Arduino UNO WiFi (R2)***

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### New in v1.5.1-final
1. Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc. Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to ***NINA_B302_ublox running as nRF52840***. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.

## Features

With this library you can instantiate Servers, Clients and send/receive UDP packets through WiFiNINA. The board can connect either to open or encrypted networks (WEP, WPA). The IP address can be assigned statically or through a DHCP. The library can also manage DNS.

---

## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.9.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Teensy core 1.53 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.6 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.5.14 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 8. [`Adafruit nRF52 v0.20.5 or later`](www.adafruit.com) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox etc.
 
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `WiFiNINA_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) for more detailed instructions.


### Manual Install

To install:

1. Navigate to [WiFiNINA_Generic](https://github.com/khoih-prog/WiFiNINA_Generic) page.
2. Download the latest release `WiFiNINA_Generic-master.zip`.
3. Extract the zip file to `WiFiNINA_Generic-master` directory 
4. Copy whole `WiFiNINA_Generic-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **WiFiNINA_Generic** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for WiFiNINA_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](examples/platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automaticly.

---

#### Important notes

1. To add NINA_B302_ublox and NINA_B112_ublox boards running as nRF52840/nRF52832, you have to copy the whole nRF52 directory into Adafruit nRF52 directory. The patch also enables automatically detecting and displaying BOARD_NAME in sketch.

Supposing the Adafruit nRF52 version is 0.20.5. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.cpp`

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`

2. Please change the ***pin-to-pin connection*** in `WiFiNINA_Pinout_Generic.h` to match actual connection. The section for NINA_B302_ublox and NINA_B112_ublox has been tested and working OK.

For example


```cpp
#elif  ( defined(NINA_B302_ublox) )

  #warning You have to modify pin usage according to actual connection for NRF528XX
  // To define pin out for WiFiNINA here
  // The following is for NINA_B302_ublox as nRF52 and W102 WiFiNINA module
  // Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip). 
  // See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

  //#define PINS_COUNT        (60u)
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
---

### HOWTO Update WiFiNINA Firmware (latest version is v1.4.0 as of July 2020)

#### 1) Update the WiFi101 / WiFiNINA FirmwareUpdater-Plugin

- Download latest release from [WiFi101-FirmwareUpdater-Plugin](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases). As of July 2020, the latest WiFiNINA FW is v1.4.0, use [WiFi101-FirmwareUpdater-Plugin version v0.10.11](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.11).
- Unzip the downloaded file into WiFi101 folder (WiFi101/tool/firmwares folder and WiFi101/tool/WiFi101.jar file)
- Copy the whole WiFi101 folder to ./arduino-1.8.yy/tools to overwrite the old WiFi101 folder.
- Restart the Arduino IDE if running.

#### 2) Upload the WiFiNINA_Generic library's [FirmwareUpdater sketch](examples/Tools/FirmwareUpdater) to your board (Nano 33 IoT, nRF52, etc.) according to these following steps:

- Select FirmwareUpdater sketch  from File > Examples > WiFiNINA_Generic > tools > FirmwareUpdater
- Upload the sketch, then close the terminal, if opened.

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/FirmwareUpdaterSketch.png">
</p>

#### 3) Update WiFiNINA Firmware:

- Select Tools > WiFi101 / WiFiNINA Firmware Updater.

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/FirmwareUpdater.png">
</p>

- Select the port of your board from the list under "1. Select port of the WiFi module".

- Select the latest firmware,  e.g. "WiFiNINA firmware (1.4.0)(Arduino MKR WiFi1010, Arduino NANO 33 IoT) under "2. Update firmware".

- Click "Update Firmware"

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/FirmwareUpdating.png">
</p>

- When done successfully, a window with message "The firmware has been updated"

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/FirmwareUpdated.png">
</p>

#### 4) Verify by uploading the WiFiNINA_Generic library's [CheckFirmwareVersion sketch](examples/Tools/CheckFirmwareVersion) sketch to your board (Nano 33 IoT, nRF52, etc.) according to these following steps:

- Select CheckFirmwareVersion sketch  from File > Examples > WiFiNINA_Generic > tools > CheckFirmwareVersion
- Upload the sketch.
- If OK, terminal will show PASSED as follows:

```
WiFiNINA firmware check.

Firmware version installed: 1.4.0
Latest firmware version available : 1.4.0

Check result: PASSED
```


### How to update SSL certificates

Please check the [Arduino Tutorial](https://www.arduino.cc/en/Tutorial/WiFiNINAFirmwareUpdater) if more info is required.

`With the same procedure, you may load root certificates on the WiFi module to access securely specific websites. Your board must be running the FirmwareUpdater sketch to work .The root certificates are issued by a limited number of certification authorities, but it is difficult to know which site is using which authority. To ease your life, we allow you to specify directly the URL to which you need to connect securely, leaving to us the task to download the root certificate.`

`The list you are building is not saved from one session to the next one. It might happen that a few websites share the same root certificate. You don't have to worry about this as we take care of it. The space available on your WiFi module to store the certificates is limited to around 10 certificates that, being issued by a limited number of authorities, should be more than enough for the average projects.`

This is the screen to demonstrate the SSL certificates have been loaded successfully onto a nRF52-based NINA_B302_ublox board running with ublox WiFiNINA W102 .

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/SSL_certs.png">
</p>

---

### Examples

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

---

#### Sample Code [WiFiWebServer example](examples/WiFiWebServer)

```cpp
#include "defines.h"
#include "arduino_secrets.h"

#include <SPI.h>
#include <WiFiNINA_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8+

int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart WiFiWebServer on " + String(BOARD_NAME));

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
  if (client)
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) 
          {
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
        
        if (c == '\n') 
        {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') 
        {
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


void printWifiStatus() 
{
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
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _WEBSOCKETS_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_WIFININA_PORT       Serial
// Use this to disable all output debug msgs
//#define DEBUG_WEBSOCKETS_PORT
// Debug Level from 0 to 4
#define _WIFININA_LOGLEVEL_       0
```

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield firmware 1.4.0+` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

### TO DO

1. Add support to many more boards still not working

---

#### New in v1.6.0

1. Sync'ed with latest WiFiNINA Library v1.6.0. 
2. New features include ***WiFiStorage*** and update to ***NINA Firmware v1.4.0*** from v1.3.0


#### New in v1.5.3

1. Add function to support new WebSockets2_Generic Library
2. Update default pin-outs for nRF52 boards, especially NINA_112_ublox.

#### New in v1.5.2

1. Port FirmwareUpdater to permit ***nRF52, Teensy, SAMD21, SAMD51, etc.*** boards to update WiFiNINA W101/W102 firmware and SSL certificates using ***Arduino IDE WiFi101/WiFiNINA Firmware Updater.*** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### New in v1.5.1

1. Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc. Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to ***NINA_B302_ublox running as nRF52840***. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.

---

### Contributions and thanks

1. Based on and modified from from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA)
2. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially ***U-Box B302 running as nRF52840 and U-Box B112 running as nRF52832***, has never been started and finished. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

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


