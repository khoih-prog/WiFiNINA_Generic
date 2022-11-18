## WiFiNINA_Generic ( Library for WiFiNINA modules/shields to support many more boards )

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiNINA_Generic.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiNINA_Generic.svg)](http://github.com/khoih-prog/WiFiNINA_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-WiFiNINA_Generic/count.svg" title="WiFiNINA_Generic Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-WiFiNINA_Generic/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Important Notes](#Important-Notes)
* [Why do we need this WiFiNINA_Generic library](#why-do-we-need-this-wifinina_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [HOWTO Change pin definitions for WiFiNINA](#howto-change-pin-definitions-for-wifinina) 
* [HOWTO Update WiFiNINA Firmware (latest version is v1.4.8 as of August 2021)](#howto-update-wifinina-firmware-latest-version-is-v148-as-of-august-2021)
  * [1) Update the WiFi101 / WiFiNINA FirmwareUpdater-Plugin](#1-update-the-wifi101--wifinina-firmwareupdater-plugin) 
  * [2) Upload the WiFiNINA_Generic library's FirmwareUpdater sketch](#2-upload-the-wifinina_generic-librarys-firmwareupdater-sketch) 
  * [3) Update WiFiNINA Firmware](#3-update-wifinina-firmware) 
  * [4) Verify by uploading the WiFiNINA_Generic library's CheckFirmwareVersion sketch](#4-verify-by-uploading-the-wifinina_generic-librarys-checkfirmwareversion-sketch) 
* [How to update SSL certificates](#how-to-update-ssl-certificates) 
* [Examples](#examples)
  * [General](#General)
    * [ 1. AP_SimpleWebServer](examples/AP_SimpleWebServer)
    * [ 2. ConnectNoEncryption](examples/ConnectNoEncryption)
    * [ 3. ConnectWithWEP](examples/ConnectWithWEP)
    * [ 4. ConnectWithWPA](examples/ConnectWithWPA)
    * [ 5. ConnectWithWPA2Enterprise](examples/ConnectWithWPA2Enterprise)
    * [ 6. MultiServers](examples/MultiServers)
    * [ 7. ScanNetworks](examples/ScanNetworks)
    * [ 8. ScanNetworksAdvanced](examples/ScanNetworksAdvanced)
    * [ 9. ScanNetworksAdvanced](examples/ScanNetworksAdvanced)
    * [10. WiFiChatServer](examples/WiFiChatServer)
    * [11. WiFiPing](examples/WiFiPing)
    * [12. WiFiSSLClient](examples/WiFiSSLClient)
    * [13. WiFiUdpNtpClient](examples/WiFiUdpNtpClient)
    * [14. WiFiUdpSendReceiveString](examples/WiFiUdpSendReceiveString)
    * [15. WiFiWebClient](examples/WiFiWebClient)
    * [16. WiFiWebClientRepeating](examples/WiFiWebClientRepeating)
    * [17. WiFiWebClientRepeating](examples/WiFiWebClientRepeating)
    * [18. WiFiNINA_SSL_Test](examples/WiFiNINA_SSL_Test)
    * [19. WiFiStorage](examples/WiFiStorage)
    * [20. WiFiAdvancedChatServer](examples/WiFiAdvancedChatServer)
    * [21. WiFiWebServer_BigData](examples/WiFiWebServer_BigData) **New**
  * [Tools](#tools)
    * [ 1. CheckFirmwareVersion](examples/Tools/CheckFirmwareVersion)
    * [ 2. FirmwareUpdater](examples/Tools/FirmwareUpdater)
    * [ 3. SerialNINAPassthrough](examples/Tools/SerialNINAPassthrough)
  * [WiFiMulti Examples](#WiFiMulti-examples) **New**
    * [ 1. WiFiAdvancedChatServer_WiFiMulti](examples/WiFiMulti/WiFiAdvancedChatServer_WiFiMulti)
    * [ 2. WiFiUdpNtpClient_WiFiMulti](examples/WiFiMulti/WiFiUdpNtpClient_WiFiMulti)
    * [ 3. WiFiWebClientRepeating_WiFiMulti](examples/WiFiMulti/WiFiWebClientRepeating_WiFiMulti)
    * [ 4. WiFiWebClient_WiFiMulti](examples/WiFiMulti/WiFiWebClient_WiFiMulti)
* [Example WiFiWebServer](#example-wifiwebserver)
  * [1. File WiFiWebServer.ino](#1-file-wifiwebserverino)
  * [2. File defines.h](#2-file-definesh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. AdvancedWebServer on Nano_33_IoT](#1-advancedwebserver-on-nano_33_iot)
  * [2. WiFiWebClientRepeating on MBED NANO_RP2040_CONNECT](#2-wifiwebclientrepeating-on-mbed-nano_rp2040_connect)
  * [3. WiFiWebClientRepeating on ARDUINO_NANO_RP2040_CONNECT](#3-wifiwebclientrepeating-on-arduino_nano_rp2040_connect)
  * [4. WiFiUdpNtpClient on MBED NANO_RP2040_CONNECT](#4-wifiudpntpclient-on-arduino_nano_rp2040_connect)
  * [5. WiFiUdpNtpClient on ARDUINO_NANO_RP2040_CONNECT](#5-wifiudpntpclient-on-mbed-nano_rp2040_connect)
  * [6. WiFiWebServer_BigData on SAMD_NANO_33_IOT](#6-WiFiWebServer_BigData-on-SAMD_NANO_33_IOT)
  * [7. WiFiWebServer_BigData on NANO_RP2040_CONNECT](#7-WiFiWebServer_BigData-on-NANO_RP2040_CONNECT)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [TO DO](#to-do)
* [DONE](#done)
* [Issues](#issues)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [Copyright](#copyright)

---
---

### Important Notes

The new [WiFiNINA_Generic v1.8.15-1+](https://github.com/khoih-prog/WiFiNINA_Generic/releases/tag/v1.8.15-1) is using new [WiFi101_Generic](https://github.com/khoih-prog/WiFi101_Generic) library to permit sending larger data than total 4K when using `MKR1000` or `MKRWiFi1010` with `ATMEL WINC1500 WiFi`

The new [WiFiNINA_Generic v1.8.15-0+](https://github.com/khoih-prog/WiFiNINA_Generic/releases/tag/v1.8.15-0) fixes severe limitation to permit sending much larger data than total 4K.

The new [WiFiNINA_Generic v1.8.14-5+](https://github.com/khoih-prog/WiFiNINA_Generic/releases/tag/v1.8.14-5) fixes bug causing data lost when sending large files, such as FTP Client uploading files.

Please use the new firmware `NINA_W102.zip`, modified by [Juraj Andrássy](https://github.com/JAndrassy), from [Using WIFI-NINA with FtpServer; no accept() #31](https://forum.arduino.cc/t/using-wifi-nina-with-ftpserver-no-accept/933690/31) to use with new version [WiFiNINA_Generic v1.8.14-4+](https://github.com/khoih-prog/WiFiNINA_Generic/releases/tag/v1.8.14-4) to fix some issues, such as FTPServer port 23, etc.

---
---

### Why do we need this [WiFiNINA_Generic library](https://github.com/khoih-prog/WiFiNINA_Generic)

#### Features

The original [Arduino WiFiNINA library](https://github.com/arduino-libraries/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000, Nano-33-IoT and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as **nRF52, SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32F/L/H/G/WB/MP1, RP2040-based, etc.**

With this library you can instantiate Servers, Clients and send/receive UDP packets through WiFiNINA. The board can connect either to open or encrypted networks (WEP, WPA). The IP address can be assigned statically or through a DHCP. The library can also manage DNS.

#### Currently Supported Boards

This [**WiFiNINA_Generic library**](https://github.com/khoih-prog/WiFiNINA_Generic) currently supports these following boards:


 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 2. **SAM DUE**
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 6. **All STM32F/L/H/G/WB/MP1 with more than 32KB flash memory.**
 7. **AVR Mega1280, 2560, ADK.**
 
 8. RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

 9. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** v2.1.0+ core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core v1.5.1+](https://github.com/earlephilhower/arduino-pico).
 
10. Add support to **Arduino ATMega-16U4, ATMega-32U4**-based boards
11. Add support to **Adafruit ATMega-32U4**-based boards
12. Add support to **Arduino, Adafruit ATMega-328(P)**-based boards
13. Add support to **Generic or Sparkfun AVR ATmega_32U4** such as **AVR_MAKEYMAKEY, AVR_PROMICRO, etc.**
14. Add support to **Generic or Sparkfun AVR ATmega_328(P)** such as **ARDUINO_REDBOT, ARDUINO_AVR_DIGITAL_SANDBOX, etc.**
15. Add support to **Generic or Sparkfun AVR ATmega128RFA1** such as **ATMEGA128RFA1_DEV_BOARD, etc.**

 
---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+`](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino AVR core 1.8.6+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core 1.57+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.13+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.11+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.3+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`Arduino Core for STM32 v2.3.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
10. [`Arduino mbed_rp2040 core 3.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) RP2040-based boards, such as **Arduino Nano RP2040 Connect, RASPBERRY_PI_PICO, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
11. [`Earle Philhower's arduino-pico core v2.6.3+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
12. [`Arduino AVR core 1.8.6+`](https://github.com/arduino/ArduinoCore-avr) for Arduino AVR boards. Use Arduino Board Manager to install. [![Latest release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest/)
13. [`Adafruit AVR core 1.4.14+`](https://github.com/adafruit/Adafruit_Arduino_Boards) for Adafruit AVR boards. Use Arduino Board Manager to install. 
14. [`Sparkfun AVR core 1.1.13+`](https://github.com/sparkfun/Arduino_Boards) for Sparkfun AVR boards. Use Arduino Board Manager to install. 
15. [`WiFiMulti_Generic library v1.2.2+`](https://github.com/khoih-prog/WiFiMulti_Generic) to use WiFiMulti function in some examples. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiMulti_Generic.svg?)](https://www.ardu-badge.com/WiFiMulti_Generic). **New**
16. [`WiFi101_Generic library v1.0.0+`](https://github.com/khoih-prog/WiFi101_Generic) to use WiFi101 for `MKR1000` or `MKRWiFi1010` with `ATMEL WINC1500 WiFi`. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFi101_Generic.svg?)](https://www.ardu-badge.com/WiFi101_Generic). **New**


---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**WiFiNINA_Generic**](https://github.com/khoih-prog/WiFiNINA_Generic), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) for more detailed instructions.


### Manual Install

To install:

1. Navigate to [**WiFiNINA_Generic**](https://github.com/khoih-prog/WiFiNINA_Generic) page.
2. Download the latest release `WiFiNINA_Generic-master.zip`.
3. Extract the zip file to `WiFiNINA_Generic-master` directory 
4. Copy whole `WiFiNINA_Generic-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**WiFiNINA_Generic** library](https://registry.platformio.org/libraries/khoih-prog/WiFiNINA_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/WiFiNINA_Generic/installation). Search for **WiFiNINA_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.11) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.11). 

Supposing the Adafruit SAMD core version is 1.7.11. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.3) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3). 

Supposing the Seeeduino SAMD core version is 1.8.3. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.4. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/ambd/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.9.0. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---
---

### HOWTO Change pin definitions for WiFiNINA

 Please change the **pin-to-pin connection** in [`WiFiNINA_Pinout_Generic.h`](src/WiFiNINA_Pinout_Generic.h) to match actual connection. The section for **NINA_B302_ublox and NINA_B112_ublox** has been tested and working OK.

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

### HOWTO Update WiFiNINA Firmware (latest version is v1.4.8 as of August 2021)

#### 1) Update the WiFi101 / WiFiNINA FirmwareUpdater-Plugin

- Download latest release from [WiFi101-FirmwareUpdater-Plugin](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases). As of August 2021, the latest WiFiNINA FW is v1.4.8, use [WiFi101-FirmwareUpdater-Plugin version v0.12.0+](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases).
- Unzip the downloaded file into WiFi101 folder (WiFi101/tool/firmwares folder and WiFi101/tool/WiFi101.jar file)
- Copy the whole WiFi101 folder to ./arduino-1.8.yy/tools to overwrite the old WiFi101 folder.
- Restart the Arduino IDE if running.

#### 2) Upload the WiFiNINA_Generic library's FirmwareUpdater sketch

**Upload the WiFiNINA_Generic library's [FirmwareUpdater sketch](examples/Tools/FirmwareUpdater) to your board (Nano-33-IoT, nRF52, etc.) according to these following steps:**

- Select FirmwareUpdater sketch  from File > Examples > WiFiNINA_Generic > tools > FirmwareUpdater
- Upload the sketch, then close the terminal, if opened.

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/raw/master/pics/FirmwareUpdaterSketch.png">
</p>

#### 3) Update WiFiNINA Firmware

- Select Tools > WiFi101 / WiFiNINA Firmware Updater.

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/raw/master/pics/FirmwareUpdater.png">
</p>

- Select the port of your board from the list under "1. Select port of the WiFi module".

- Select the latest firmware,  e.g. "WiFiNINA firmware (1.4.8)(Arduino MKR WiFi1010, Arduino NANO 33 IoT, Arduino NANO RP2040 Connect) under "2. Update firmware".

- Click "Update Firmware"

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/raw/master/pics/FirmwareUpdating.png">
</p>

- When done successfully, a window with message "The firmware has been updated"

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/raw/master/pics/FirmwareUpdated.png">
</p>

#### 4) Verify by uploading the WiFiNINA_Generic library's CheckFirmwareVersion sketch

**Verify by uploading the WiFiNINA_Generic library's [CheckFirmwareVersion sketch](examples/Tools/CheckFirmwareVersion) to your board (Nano 33 IoT, nRF52, etc.) according to these following steps:**

- Select CheckFirmwareVersion sketch  from File > Examples > WiFiNINA_Generic > tools > CheckFirmwareVersion
- Upload the sketch.
- If OK, terminal will show PASSED as follows:

```cpp
Start WiFiNINA CheckFirmwareVersion on SAMD_NANO_33_IOT
WiFiNINA_Generic v1.8.15-1
Firmware version installed: aaa.bbb.ccc
Latest firmware version available : aaa.bbb.ccc

Check result: PASSED

```
---

### How to update SSL certificates

Please check the [Arduino Tutorial](https://www.arduino.cc/en/Tutorial/WiFiNINAFirmwareUpdater) if more info is required.

`With the same procedure, you may load root certificates on the WiFi module to access securely specific websites. Your board must be running the FirmwareUpdater sketch to work .The root certificates are issued by a limited number of certification authorities, but it is difficult to know which site is using which authority. To ease your life, we allow you to specify directly the URL to which you need to connect securely, leaving to us the task to download the root certificate.`

`The list you are building is not saved from one session to the next one. It might happen that a few websites share the same root certificate. You don't have to worry about this as we take care of it. The space available on your WiFi module to store the certificates is limited to around 10 certificates that, being issued by a limited number of authorities, should be more than enough for the average projects.`

This is the screen to demonstrate the SSL certificates have been loaded successfully onto a nRF52-based NINA_B302_ublox board running with ublox WiFiNINA W102 .

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/raw/master/pics/SSL_certs.png">
</p>

---
---

### Examples

#### General

 1. [AP_SimpleWebServer](examples/AP_SimpleWebServer)
 2. [ConnectNoEncryption](examples/ConnectNoEncryption)
 3. [ConnectWithWEP](examples/ConnectWithWEP)
 4. [ConnectWithWPA](examples/ConnectWithWPA)
 5. [ConnectWithWPA2Enterprise](examples/ConnectWithWPA2Enterprise)
 6. [MultiServers](examples/MultiServers), credit of [**Oscar den Uijl**](https://github.com/ocrdu)
 7. [ScanNetworks](examples/ScanNetworks)
 8. [ScanNetworksAdvanced](examples/ScanNetworksAdvanced)
 9. [SimpleWebServerWiFi](examples/SimpleWebServerWiFi)
10. [WiFiChatServer](examples/WiFiChatServer)
11. [WiFiPing](examples/WiFiPing)
12. [WiFiSSLClient](examples/WiFiSSLClient)
13. [WiFiUdpNtpClient](examples/WiFiUdpNtpClient)
14. [WiFiUdpSendReceiveString](examples/WiFiUdpSendReceiveString)
15. [WiFiWebClient](examples/WiFiWebClient)
16. [WiFiWebClientRepeating](examples/WiFiWebClientRepeating)
17. [WiFiWebServer](examples/WiFiWebServer)
18. [WiFiNINA_SSL_Test](examples/WiFiNINA_SSL_Test)
19. [WiFiStorage](examples/WiFiStorage)
20. [WiFiAdvancedChatServer](examples/WiFiAdvancedChatServer) **New**
21. [WiFiWebServer_BigData](examples/WiFiWebServer_BigData) **New**

#### Tools

 1. [CheckFirmwareVersion](examples/Tools/CheckFirmwareVersion)
 2. [FirmwareUpdater](examples/Tools/FirmwareUpdater)
 3. [SerialNINAPassthrough](examples/Tools/SerialNINAPassthrough)

#### WiFiMulti Examples

 1. [WiFiAdvancedChatServer_WiFiMulti](examples/WiFiMulti/WiFiAdvancedChatServer_WiFiMulti) **New**
 2. [WiFiUdpNtpClient_WiFiMulti](examples/WiFiMulti/WiFiUdpNtpClient_WiFiMulti) **New**
 3. [WiFiWebClientRepeating_WiFiMulti](examples/WiFiMulti/WiFiWebClientRepeating_WiFiMulti) **New**
 4. [WiFiWebClient_WiFiMulti](examples/WiFiMulti/WiFiWebClient_WiFiMulti) **New**

---

## Example [WiFiWebServer](examples/WiFiWebServer)

### 1. File [WiFiWebServer.ino](examples/WiFiWebServer/WiFiWebServer.ino)

https://github.com/khoih-prog/WiFiNINA_Generic/blob/d628009bd6d8e3a48c71f62971dbe04f12309411/examples/WiFiWebServer/WiFiWebServer.ino#L41-L207


### 2. File [defines.h](examples/WiFiWebServer/defines.h)

https://github.com/khoih-prog/WiFiNINA_Generic/blob/d628009bd6d8e3a48c71f62971dbe04f12309411/examples/WiFiWebServer/defines.h#L29-L400


---
---

### Debug Terminal Output Samples

#### 1. [AdvancedWebServer](https://github.com/khoih-prog/WiFiWebServer/tree/master/examples/AdvancedWebServer) on Nano_33_IoT

The following are screen shot and debug terminal output when running example [AdvancedWebServer](https://github.com/khoih-prog/WiFiWebServer/tree/master/examples/AdvancedWebServer) on Arduino SAMD21 `Nano-33-IoT` board using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/raw/master/pics/AdvancedWebServer.png">
</p>


```
Starting AdvancedServer on SAMD_NANO_33_IOT
WiFiNINA_Generic v1.8.15-1
[NN] ===============================
[NN] 
Used/default SPI pinout: 
[NN] MOSI:  11
[NN] MISO:  12
[NN] SCK:  13
[NN] SS:  10
[NN] ===============================
[NN] 
Used/default NINA pinout: 
[NN] NINA_GPIO0:  26
[NN] NINA_RESETN/SPIWIFI_RESET:  27
[NN] NINA_ACK:  28
[NN] SS:  10
[NN] ===============================
[NN] 
Actual final pinout to used: 
[NN] SPIWIFI_SS:  24
[NN] SLAVESELECT/SPIWIFI_SS:  24
[NN] SLAVEREADY/SPIWIFI_ACK/NINA_ACK:  28
[NN] SLAVERESET/SPIWIFI_RESET/NINA_RESETN:  27
[NN] ===============================

Connecting to WPA SSID: HueNet1
HTTP server started @ 192.168.2.118
WiFiWebServer::handleClient: New Client
method:  GET
url:  /
search:
headerName: Host
headerValue: 192.168.2.118
headerName: Connection
headerValue: keep-alive
headerName: Cache-Control
headerValue: max-age=0
headerName: DNT
headerValue: 1
headerName: Upgrade-Insecure-Requests
headerValue: 1
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: Accept
headerValue: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
headerName: Cookie
headerValue: NINASESSIONID=0
args:
args count:  0
args:
args count:  0
Request: /
Arguments: 
Final list of key/value pairs:
WiFiWebServer::_handleRequest handle
WiFiWebServer::send1: len =  330
content =  <html><head><meta http-equiv='refresh' content='5'/><title>WiFiNINA SAMD_NANO_33_IOT</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h1>Hello from WiFiNINA</h1><h2>on SAMD_NANO_33_IOT</h2><p>Uptime: 00:00:20</p><img src="/test.svg" /></body></html>
WiFiWebServer::_prepareHeader sendHeader Conn close
WiFiWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 330
Connection: close


WiFiWebServer::sendContent: Client.write content:  <html><head><meta http-equiv='refresh' content='5'/><title>WiFiNINA SAMD_NANO_33_IOT</title><style>body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><h1>Hello from WiFiNINA</h1><h2>on SAMD_NANO_33_IOT</h2><p>Uptime: 00:00:20</p><img src="/test.svg" /></body></html>
WiFiWebServer::_handleRequest OK
WiFiWebServer::handleClient: Client disconnected
WiFiWebServer::handleClient: Don't keepCurrentClient
WiFiWebServer::handleClient: Client disconnected
WiFiWebServer::handleClient: New Client
method:  GET
url:  /test.svg
search:
headerName: Host
headerValue: 192.168.2.118
headerName: Connection
headerValue: keep-alive
headerName: User-Agent
headerValue: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36
headerName: DNT
headerValue: 1
headerName: Accept
headerValue: image/webp,image/apng,image/*,*/*;q=0.8
headerName: Referer
headerValue: http://192.168.2.118/
headerName: Accept-Encoding
headerValue: gzip, deflate
headerName: Accept-Language
headerValue: en-GB,en-US;q=0.9,en;q=0.8
headerName: Cookie
headerValue: NINASESSIONID=0
args:
args count:  0
args:
args count:  0
Request: /test.svg
Arguments: 
Final list of key/value pairs:
WiFiWebServer::_handleRequest handle
WiFiWebServer::send1: len =  1946
content =  <svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="310" height="150">
<rect width="310" height="150" fill="rgb(250, 230, 210)" stroke-width="1" stroke="rgb(0, 0, 0)" />
<g stroke="black">
<line x1="10" y1="77" x2="20" y2="67" stroke-width="1" />
<line x1="20" y1="67" x2="30" y2="98" stroke-width="1" />
<line x1="30" y1="98" x2="40" y2="111" stroke-width="1" />
<line x1="40" y1="111" x2="50" y2="90" stroke-width="1" />
<line x1="50" y1="90" x2="60" y2="22" stroke-width="1" />
<line x1="60" y1="22" x2="70" y2="98" stroke-width="1" />
<line x1="70" y1="98" x2="80" y2="64" stroke-width="1" />
<line x1="80" y1="64" x2="90" y2="104" stroke-width="1" />
<line x1="90" y1="104" x2="100" y2="31" stroke-width="1" />
<line x1="100" y1="31" x2="110" y2="59" stroke-width="1" />
<line x1="110" y1="59" x2="120" y2="139" stroke-width="1" />
<line x1="120" y1="139" x2="130" y2="117" stroke-width="1" />
<line x1="130" y1="117" x2="140" y2="75" stroke-width="1" />
<line x1="140" y1="75" x2="150" y2="72" stroke-width="1" />
<line x1="150" y1="72" x2="160" y2="137" stroke-width="1" />
<line x1="160" y1="137" x2="170" y2="20" stroke-width="1" />
<line x1="170" y1="20" x2="180" y2="94" stroke-width="1" />
<line x1="180" y1="94" x2="190" y2="81" stroke-width="1" />
<line x1="190" y1="81" x2="200" y2="38" stroke-width="1" />
<line x1="200" y1="38" x2="210" y2="33" stroke-width="1" />
<line x1="210" y1="33" x2="220" y2="53" stroke-width="1" />
<line x1="220" y1="53" x2="230" y2="88" stroke-width="1" />
<line x1="230" y1="88" x2="240" y2="32" stroke-width="1" />
<line x1="240" y1="32" x2="250" y2="110" stroke-width="1" />
<line x1="250" y1="110" x2="260" y2="87" stroke-width="1" />
<line x1="260" y1="87" x2="270" y2="11" stroke-width="1" />
<line x1="270" y1="11" x2="280" y2="98" stroke-width="1" />
<line x1="280" y1="98" x2="290" y2="76" stroke-width="1" />
<line x1="290" y1="76" x2="300" y2="121" stroke-width="1" />
</g>
</svg>

WiFiWebServer::_prepareHeader sendHeader Conn close
WiFiWebServer::send1: write header =  HTTP/1.1 200 OK
Content-Type: image/svg+xml
Content-Length: 1946
Connection: close
```

---

#### 2. [WiFiWebClientRepeating](examples/WiFiWebClientRepeating) on MBED NANO_RP2040_CONNECT

The following is debug terminal output when running example [WiFiWebClientRepeating](examples/WiFiWebClientRepeating) on `NANO_RP2040_CONNECT` board with [ArduinoCore-mbed core](https://github.com/arduino/ArduinoCore-mbed), using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)

```
Start WiFiWebClientRepeating on MBED NANO_RP2040_CONNECT
WiFiNINA_Generic v1.8.15-1
Attempting to connect to SSID: HueNet1
SSID: HueNet1
IP Address: 192.168.2.86
Signal strength (RSSI):-16 dBm
Connecting...
HTTP/1.1 200 OK
Age: 387215
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Fri, 31 Dec 2021 15:04:14 GMT
Etag: "3147526947+gzip+ident"
Expires: Fri, 07 Jan 2022 15:04:14 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Server: ECS (chb/02E4)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1256
Connection: close

<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
        
    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>    
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>
Connecting...
HTTP/1.1 200 OK
Age: 342142
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Fri, 31 Dec 2021 15:04:24 GMT
Etag: "3147526947+ident"
Expires: Fri, 07 Jan 2022 15:04:24 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Server: ECS (chb/0286)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1256
Connection: close

```

---


#### 3. [WiFiWebClientRepeating](examples/WiFiWebClientRepeating) on ARDUINO_NANO_RP2040_CONNECT

The following is debug terminal output when running example [WiFiWebClientRepeating](examples/WiFiWebClientRepeating) on `NANO_RP2040_CONNECT` board with [arduino-pico core](https://github.com/earlephilhower/arduino-pico), using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)


```
Start WiFiWebClientRepeating on ARDUINO_NANO_RP2040_CONNECT
WiFiNINA_Generic v1.8.15-1
Attempting to connect to SSID: HueNet1
SSID: HueNet1
IP Address: 192.168.2.86
Signal strength (RSSI):-18 dBm
Connecting...
HTTP/1.1 200 OK
Age: 343649
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Fri, 31 Dec 2021 15:29:31 GMT
Etag: "3147526947+ident"
Expires: Fri, 07 Jan 2022 15:29:31 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Server: ECS (chb/0286)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1256
Connection: close

<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
        
    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>    
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>

```

---

#### 4. [WiFiUdpNtpClient](examples/WiFiUdpNtpClient) on ARDUINO_NANO_RP2040_CONNECT

The following is debug terminal output when running example [WiFiUdpNtpClient](examples/WiFiUdpNtpClient) on `NANO_RP2040_CONNECT` board with [arduino-pico core](https://github.com/earlephilhower/arduino-pico), using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)

```
Start WiFiUdpNtpClient on ARDUINO_NANO_RP2040_CONNECT
WiFiNINA_Generic v1.8.15-1
Attempting to connect to SSID: HueNet1
Connected to WiFi
SSID: HueNet1
IP Address: 192.168.2.86
Signal strength (RSSI):-16 dBm

Starting connection to server...
Packet received
Seconds since Jan 1 1900 = 3849967470
Unix time = 1640978670
The UTC time is 19:24:30
Packet received
Seconds since Jan 1 1900 = 3849967481
Unix time = 1640978681
The UTC time is 19:24:41
Packet received
Seconds since Jan 1 1900 = 3849967492
Unix time = 1640978692
The UTC time is 19:24:52
```

---

#### 5. [WiFiUdpNtpClient](examples/WiFiUdpNtpClient) on MBED NANO_RP2040_CONNECT

The following is debug terminal output when running example [WiFiUdpNtpClient](examples/WiFiUdpNtpClient) on NANO_RP2040_CONNECT board with [ArduinoCore-mbed core](https://github.com/arduino/ArduinoCore-mbed), using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)

```
Start WiFiUdpNtpClient on MBED NANO_RP2040_CONNECT
WiFiNINA_Generic v1.8.15-1
Attempting to connect to SSID: HueNet1
Connected to WiFi
SSID: HueNet1
IP Address: 192.168.2.86
Signal strength (RSSI):-19 dBm

Starting connection to server...
Packet received
Seconds since Jan 1 1900 = 3849967854
Unix time = 1640979054
The UTC time is 19:30:54
Packet received
Seconds since Jan 1 1900 = 3849967865
Unix time = 1640979065
The UTC time is 19:31:05
```


---

#### 6. [WiFiWebServer_BigData](examples/WiFiWebServer_BigData) on SAMD_NANO_33_IOT

The following is debug terminal output when running example [WiFiWebServer_BigData](examples/WiFiWebServer_BigData) on `SAMD_NANO_33_IOT` board, using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic), to demo how to send much larger data than total 4K

##### MULTIPLY_FACTOR = 1.0f

```
Start WiFiWebServer_BigData on SAMD_NANO_33_IOT
WiFiNINA_Generic v1.8.15-1
WiFiWebServer v1.10.0
Attempting to connect to SSID: HueNet
Attempting to connect to SSID: HueNet
SSID: HueNet
IP Address: 192.168.2.107
Signal strength (RSSI):-15 dBm
String Len = 8103
String Len = 8103
String Len = 8103
String Len = 8103
String Len = 8103
String Len = 8103
```

##### MULTIPLY_FACTOR = 2.0f

```
Start WiFiWebServer_BigData on SAMD_NANO_33_IOT
WiFiNINA_Generic v1.8.15-1
WiFiWebServer v1.10.0
Attempting to connect to SSID: HueNet
Attempting to connect to SSID: HueNet
SSID: HueNet
IP Address: 192.168.2.107
Signal strength (RSSI):-15 dBm
String Len = 15903
String Len = 15903
String Len = 15903
String Len = 15903
String Len = 15903
```

##### MULTIPLY_FACTOR = 2.5f

```
Start WiFiWebServer_BigData on SAMD_NANO_33_IOT
WiFiNINA_Generic v1.8.15-1
WiFiWebServer v1.10.0
Attempting to connect to SSID: HueNet
Attempting to connect to SSID: HueNet
SSID: HueNet
IP Address: 192.168.2.107
Signal strength (RSSI):-17 dBm
String Len = 19803
String Len = 19803
String Len = 19803
String Len = 19803
String Len = 19803
String Len = 19803
```

---

#### 7. [WiFiWebServer_BigData](examples/WiFiWebServer_BigData) on NANO_RP2040_CONNECT

The following is debug terminal output when running example [WiFiWebServer_BigData](examples/WiFiWebServer_BigData) on `NANO_RP2040_CONNECT` board, using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic), to demo how to send much larger data than total 4K

##### MULTIPLY_FACTOR = 3.0f

```
Start WiFiWebServer_BigData on NANO_RP2040_CONNECT
WiFiNINA_Generic v1.8.15-1
WiFiWebServer v1.10.0
Attempting to connect to SSID: HueNet
Attempting to connect to SSID: HueNet
SSID: HueNet
IP Address: 192.168.2.117
Signal strength (RSSI):-24 dBm
String Len = 27609
String Len = 27609
```

---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _WEBSOCKETS_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_WIFININA_PORT       Serial
// Use this to disable all output debug msgs
// Debug Level from 0 to 4
#define _WIFININA_LOGLEVEL_       0
```


---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield firmware 1.4.8+` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

---
---

### TO DO
1. Bug Searching and Killing
2. Support more types of boards using WiFiNINA and other WiFi shields.

---

### DONE

 1. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 2. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4, etc.)**.
 3. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)**.
 4. Add support to SAM DUE.
 5. Add support to Teensy.
 6. Add support to all **STM32F/L/H/G/WB/MP1 having 64K+** Flash program memory.
 7. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
 8. Add function to support new WebSockets2_Generic Library
 9. Update default pin-outs for nRF52 boards, especially NINA_112_ublox.
10. Add support to **Arduino Nano RP2040 Connect** using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).
11. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
12. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
13. Add support to **Arduino ATMega-16U4, ATMega-32U4**-based boards
14. Add support to **Adafruit ATMega-32U4**-based boards
15. Add support to **Arduino, Adafruit ATMega-328(P)**-based boards
16. Add support to **Generic or Sparkfun AVR ATmega_32U4** such as **AVR_MAKEYMAKEY, AVR_PROMICRO, etc.**
17. Add support to **Generic or Sparkfun AVR ATmega_328(P)** such as **ARDUINO_REDBOT, ARDUINO_AVR_DIGITAL_SANDBOX, etc.**
18. Add support to **Generic or Sparkfun AVR ATmega128RFA1** such as **ATMEGA128RFA1_DEV_BOARD, etc.**
19. Add support to **ADAFRUIT_MATRIXPORTAL_M4_EXPRESS**
20. Add support to generic `__SAMD21E1xA__`, `__SAMD21G1xA__` and `__SAMD21J1xA__`
21. Add support to **Nano_RP2040_Connect** using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
22. Fix bugs by using some PRs from original WiFiNINA, such as:

 - [WiFi.config - setting defaults as the Ethernet library #219](https://github.com/arduino-libraries/WiFiNINA/pull/219)
 - [Fix WiFiClient watchdog usage #211](https://github.com/arduino-libraries/WiFiNINA/pull/211)
 - [Watchdog trigger changes #208](https://github.com/arduino-libraries/WiFiNINA/pull/208)
 - [added server.accept() #204](https://github.com/arduino-libraries/WiFiNINA/pull/204)
 - [Fix PinStatus error on some platforms #185](https://github.com/arduino-libraries/WiFiNINA/pull/185)
23. Fix bug causing data lost when sending large files. This is just a kludge for temporary use, waiting for better and final fix, dealing with SPI driver, from Arduino.
24. Add support to Teensy 4.x using `Adafruit Airlift Featherwing Co-Processor`
25. Modify [WiFiWebServer](https://github.com/khoih-prog/WiFiNINA_Generic/tree/master/examples/WiFiWebServer) example to avoid `analogRead()` crash in `arduino-pico` core. Check [WiFi.localIP() hangs in Nano RP2040 Connect with Arduino-Pico core (EarlePhilhower) #24](https://github.com/khoih-prog/WiFiNINA_Generic/discussions/24)
26. Use `allman astyle` and add `utils`
27. Fix severe limitation to permit sending much larger data than total 4K. Check [server.send buffer size limited to 4k #23](https://github.com/khoih-prog/WiFiWebServer/issues/23)
28. Add examples [WiFiWebServer_BigData](https://github.com/khoih-prog/WiFiNINA_Generic/tree/master/examples/WiFiWebServer_BigData) to demo how to send much larger data than total 4K
29. Using new [WiFi101_Generic](https://github.com/khoih-prog/WiFi101_Generic) library to permit sending larger data than total 4K when using `MKR1000` or `MKRWiFi1010` with `ATMEL WINC1500 WiFi`


---

### Issues ###

Submit issues to: [WiFiNINA_Generic issues](https://github.com/khoih-prog/WiFiNINA_Generic/issues)

---
---

### Contributions and Thanks

 1. Based on and modified from from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA).Thanks to the great works of these [WiFiNINA Library's Contributors](https://github.com/arduino-libraries/WiFiNINA/graphs/contributors)
 2. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially **NINA_B302_ublox running as nRF52840 and NINA_B112_ublox running as nRF52832**, has never been started and finished. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)
 3. Thanks to [AppsByDavideV](https://github.com/AppsByDavideV) to report [WiFiStorage Bug](https://github.com/khoih-prog/WiFiNINA_Generic/issues/4)
 4. Thanks to [Oscar den Uijl](https://github.com/ocrdu) for : 
  - the fix, reported in [Version 1.4.0 can break code that uses more than one WiFiServer and socket](https://github.com/arduino-libraries/WiFiNINA/issues/87) and has been included.
  - the newly-added example [MultiServers](examples/MultiServers)
 5. Thanks to [Gerard Moorcroft](https://github.com/gmstuff) to report issue [**WiFi Hangs when attempting to start WiFi (Adafruit M4 Express Airlift Lite board)**](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/2) leading to version v1.7.2 to add support to Adafruit METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4.
 6. Thanks to [mouradelbellili](https://github.com/mouradelbellili) to create PR [**Add support to Arduino UNO board** #9](https://github.com/khoih-prog/WiFiNINA_Generic/pull/9) leading to version v1.8.12 to add support to Arduino, Adafruit, Sparkfun AVR 328P, 32u4, 16u4, etc. boards
 7. Thanks to [Juraj Andrássy](https://github.com/JAndrassy) to create these following PRs, used in v1.8.14-4
 - [WiFi.config - setting defaults as the Ethernet library #219](https://github.com/arduino-libraries/WiFiNINA/pull/219)
 - [added server.accept() #204](https://github.com/arduino-libraries/WiFiNINA/pull/204)
 8. Thanks to [Tamás Mélykuti](https://github.com/BlooD2oo1) to create the following PR, used in v1.8.14-4
 - [Fix WiFiClient watchdog usage #211](https://github.com/arduino-libraries/WiFiNINA/pull/211)
 9. Thanks to [Mattia Pennasilico](https://github.com/pennam) to create the following PR, used in v1.8.14-4
 - [Watchdog trigger changes #208](https://github.com/arduino-libraries/WiFiNINA/pull/208)
10. Thanks to [NachtRave](https://github.com/NachtRaveVL) to report issue [**Flush method not implemented #22**](https://github.com/khoih-prog/WiFiNINA_Generic/issues/22) leading to version v1.8.14-6
11. Thanks to [Stefano](https://github.com/stefat) to report issue [**WiFi.localIP() hangs in Nano RP2040 Connect with Arduino-Pico core (EarlePhilhower) #24**](https://github.com/khoih-prog/WiFiNINA_Generic/issues/24) leading to version v1.8.14-7
12. Thanks to [jlemieux55](https://github.com/jlemieux55) to report issue [**server.send buffer size limited to 4k #23**](https://github.com/khoih-prog/WiFiWebServer/issues/23) leading to version v1.8.15-0



---

<table>
  <tr>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/AppsByDavideV"><img src="https://github.com/AppsByDavideV.png" width="100px;" alt="AppsByDavideV"/><br /><sub><b>AppsByDavideV</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/ocrdu"><img src="https://github.com/ocrdu.png" width="100px;" alt="ocrdu"/><br /><sub><b>Oscar den Uijl</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/gmstuff"><img src="https://github.com/gmstuff.png" width="100px;" alt="gmstuff"/><br /><sub><b>Gerard Moorcroft</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/mouradelbellili"><img src="https://github.com/mouradelbellili.png" width="100px;" alt="mouradelbellili"/><br /><sub><b>mouradelbellili</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/JAndrassy"><img src="https://github.com/JAndrassy.png" width="100px;" alt="JAndrassy"/><br /><sub><b>Juraj Andrássy</b></sub></a><br /></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/BlooD2oo1"><img src="https://github.com/BlooD2oo1.png" width="100px;" alt="BlooD2oo1"/><br /><sub><b>Tamás Mélykuti</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/pennam"><img src="https://github.com/pennam.png" width="100px;" alt="pennam"/><br /><sub><b>Mattia Pennasilico</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/NachtRaveVL"><img src="https://github.com/NachtRaveVL.png" width="100px;" alt="NachtRaveVL"/><br /><sub><b>NachtRave</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/stefat"><img src="https://github.com/stefat.png" width="100px;" alt="stefat"/><br /><sub><b>Stefano</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/jlemieux55"><img src="https://github.com/jlemieux55.png" width="100px;" alt="jlemieux55"/><br /><sub><b>jlemieux55</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---
---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)

---

### Copyright

1. Copyright (c) 2018 Arduino SA. All rights reserved.
2. Copyright (c) 2011-2014 Arduino LLC. All right reserved.
3. Copyright (c) 2020- Khoi Hoang


