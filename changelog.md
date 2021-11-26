## WiFiNINA_Generic ( Library for WiFiNINA modules/shields to support many more boards )

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiNINA_Generic.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiNINA_Generic.svg)](http://github.com/khoih-prog/WiFiNINA_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.8.14-1](#releases-v1814-1)
  * [Releases v1.8.13](#releases-v1813)
  * [Releases v1.8.12](#releases-v1812)
  * [Releases v1.8.11](#releases-v1811)
  * [Releases v1.8.10-1](#releases-v1810-1)
  * [Releases v1.8.10](#releases-v1810)
  * [Releases v1.8.5](#releases-v185)
  * [Releases v1.8.2](#releases-v182)
  * [Releases v1.8.0](#releases-v180)
  * [Releases v1.7.2](#releases-v172)
  * [Releases v1.7.1](#releases-v171)
  * [Releases v1.7.0](#releases-v170)
  * [Releases v1.6.2](#releases-v162)
  * [Releases v1.6.1](#releases-v161)
  * [Releases v1.6.0](#releases-v160)
  * [Releases v1.5.3](#releases-v153)
  * [Releases v1.5.2](#releases-v152)
  * [Releases v1.5.1](#releases-v151)
  * [Releases v1.5.0](#releases-v150)
 
---
---

## Changelog

### Releases v1.8.14-1

1. Fix examples to support ATmega4809 such as UNO_WIFI_REV2 and NANO_EVERY
2. Add support to generic `__SAMD21E1xA__`, `__SAMD21G1xA__` and `__SAMD21J1xA__`
3. Add `headers` in `library.json` for PIO
4. Update `platform.io`
5. Remove debug leftovers. Check [Debug text comes out of the serial port when listening for UDP connections #15](https://github.com/khoih-prog/WiFiNINA_Generic/issues/15)


### Releases v1.8.13

1. Sync with [Arduino WiFiNINA Library v1.8.13](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.13). 
  - Update latest available nina-fw to v1.4.8

2. Add support to SAMD51 ADAFRUIT_MATRIXPORTAL_M4_EXPRESS

### Releases v1.8.12

1. Sync with [Arduino WiFiNINA Library v1.8.12](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.12). 
  - Update latest available nina-fw to v1.4.7

2. Add support to many AVR (328P, 32U4, 16U4, etc.) boards. Check [Add support to Arduino UNO board #9](https://github.com/khoih-prog/WiFiNINA_Generic/pull/9)


### Releases v1.8.11

1. Sync with [Arduino WiFiNINA Library v1.8.11](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.11). 
  - RP2040 - adapt NinaPins to be used as class
  - Provide clean API for passing watchdog function
  - Update latest available nina-fw to v1.4.6

2. Permit nina-fw version overridden to use whenever WiFi101-FirmwareUpdater-Plugin is not sync'ed with nina-fw version

### Releases v1.8.10-1

1. Fix PinStatus-related compile error for some platforms

### Releases v1.8.10

1. Sync with [Arduino WiFiNINA Library v1.8.10](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.10). 
  - Add support to **Arduino Nano RP2040 Connect** using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).
  - Update latest available nina-fw to v1.4.5
  - Bug fixes.
2. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** v1.5.1+ core](https://github.com/earlephilhower/arduino-pico).
3. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** v2.1.0+ core](https://github.com/arduino/ArduinoCore-mbed).
4. Update `Packages' Patches`

### Releases v1.8.5

1. Sync with [Arduino WiFiNINA Library v1.8.5](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.5). Bugfix: Feed watchdog within busy-wait-loop within connectBearSSL to prevent a premature reset.
2. Update `Packages' Patches`

### Releases v1.8.2

1. Sync with [Arduino WiFiNINA Library v1.8.2](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.2). Using the latest WiFiNINA FW v1.4.3 in [WiFi101-FirmwareUpdater-Plugin v0.10.13](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.13)
2. Add possibility to resend data if lwip_send fails.

### Releases v1.8.0

1. Sync with [Arduino WiFiNINA Library v1.8.0](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.0). Using the latest WiFiNINA FW v1.4.2 in [WiFi101-FirmwareUpdater-Plugin v0.10.13](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.13)
2. Limit the maximum length of the download URL for the OTA binary since the receive buffer on the nina firmware can't hold more than 128 bytes.
3. Introduce **WiFiBearSSLClient (offloaded to Nina)**

### Releases v1.7.2

1. Add support to **Adafruit Airlift M4 boards: METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4.** Thanks to [Gerard Moorcroft](https://github.com/gmstuff) to report issue [**WiFi Hangs when attempting to start WiFi (Adafruit M4 Express Airlift Lite board)**](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/2) leading to this new version.
2. Add WIFININA_GENERIC_VERSION

#### Releases v1.7.1

1. Sync with [Arduino WiFiNINA Library v1.7.1](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.7.1). Using the latest WiFiNINA FW v1.4.1 in [WiFi101-FirmwareUpdater-Plugin v0.10.12](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.12)

#### Releases v1.7.0

1. Sync with [Arduino WiFiNINA Library v1.7.0](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.7.0). See [Add 'downloadOTA' command to download OTA file and verify length/CRC](https://github.com/arduino-libraries/WiFiNINA/pull/124)
2. Add Arduino SAMD Packages_Patches to fix Arduino SAMD compiler error when using STL. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)

#### Releases v1.6.2

1. Fix WiFiStorage bug introduced from v1.6.0 resulting compile error.
2. Add example for WiFiStorage.

#### Releases v1.6.1

1. Add support to all **STM32F/L/H/G/WB/MP1**
2. Add support to **Seeeduino SAMD21/SAMD51 boards **
3. Fix bug introduced to v1.6.0 resulting nRF52 compile error.

#### Releases v1.6.0

1. Sync'ed with latest WiFiNINA Library v1.6.0. 
2. New features include **WiFiStorage** and update to **NINA Firmware v1.4.0** from v1.3.0

#### Releases v1.5.3

1. Add function to support new WebSockets2_Generic Library
2. Update default pin-outs for nRF52 boards, especially NINA_112_ublox.

#### Releases v1.5.2

1. Port FirmwareUpdater to permit **nRF52, Teensy, SAMD21, SAMD51, etc.** boards to update WiFiNINA W101/W102 firmware and SSL certificates using **Arduino IDE WiFi101/WiFiNINA Firmware Updater.** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### Releases v1.5.1

1. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc.** Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to **NINA_B302_ublox running as nRF52840**. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### Releases v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as **SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.**


