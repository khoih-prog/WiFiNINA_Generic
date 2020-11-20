## WiFiNINA_Generic ( Library for WiFiNINA modules/shields to support many more boards )

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiNINA_Generic.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiNINA_Generic.svg)](http://github.com/khoih-prog/WiFiNINA_Generic/issues)

---
---

### Why do we need this [WiFiNINA_Generic library](https://github.com/khoih-prog/WiFiNINA_Generic)

The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000, Nano-33-IoT and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as **nRF52, SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32F/L/H/G/WB/MP1, etc.**

With this library you can instantiate Servers, Clients and send/receive UDP packets through WiFiNINA. The board can connect either to open or encrypted networks (WEP, WPA). The IP address can be assigned statically or through a DHCP. The library can also manage DNS.

---

### New in v1.8.0

1. Sync with [Arduino WiFiNINA Library v1.8.0](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.0). Using the latest WiFiNINA FW v1.4.2 in [WiFi101-FirmwareUpdater-Plugin v0.10.13](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.13)
2. Limit the maximum length of the download URL for the OTA binary since the receive buffer on the nina firmware can't hold more than 128 bytes.
3. Introduce **WiFiBearSSLClient (offloaded to Nina)**

### New in v1.7.2

1. Add support to **Adafruit Airlift M4 boards: METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4.** Thanks to [Gerard Moorcroft](https://github.com/gmstuff) to report issue [**WiFi Hangs when attempting to start WiFi (Adafruit M4 Express Airlift Lite board)**](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/2) leading to this new version.
2. Add WIFININA_GENERIC_VERSION

#### New in v1.7.1

1. Sync with [Arduino WiFiNINA Library v1.7.1](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.7.1). Using the latest WiFiNINA FW v1.4.1 in [WiFi101-FirmwareUpdater-Plugin v0.10.12](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.12)

#### New in v1.7.0

1. Sync with [Arduino WiFiNINA Library v1.7.0](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.7.0). See [Add 'downloadOTA' command to download OTA file and verify length/CRC](https://github.com/arduino-libraries/WiFiNINA/pull/124)
2. Add Arduino SAMD Packages_Patches to fix Arduino SAMD compiler error when using STL. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)

#### New in v1.6.2

1. Fix WiFiStorage bug introduced from v1.6.0 resulting compile error.
2. Add example for WiFiStorage.

#### New in v1.6.1

1. Add support to all **STM32F/L/H/G/WB/MP1**
2. Add support to **Seeeduino SAMD21/SAMD51 boards **
3. Fix bug introduced to v1.6.0 resulting nRF52 compile error.

#### New in v1.6.0

1. Sync'ed with latest WiFiNINA Library v1.6.0. 
2. New features include **WiFiStorage** and update to **NINA Firmware v1.4.0** from v1.3.0


#### New in v1.5.3

1. Add function to support new WebSockets2_Generic Library
2. Update default pin-outs for nRF52 boards, especially NINA_112_ublox.

#### New in v1.5.2

1. Port FirmwareUpdater to permit **nRF52, Teensy, SAMD21, SAMD51, etc.** boards to update WiFiNINA W101/W102 firmware and SSL certificates using **Arduino IDE WiFi101/WiFiNINA Firmware Updater.** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### New in v1.5.1

1. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc.** Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to **NINA_B302_ublox running as nRF52840**. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as **SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.**

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+`](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino AVR core 1.8.3+`](https://github.com/arduino/ArduinoCore-avr) for Arduino AVR boards. Use Arduino Board Manager to install.
 3. [`Teensy core v1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.9+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards  (Nano 33 IoT, etc.).
 6. [`Adafruit SAMD core 1.6.4+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Itsy-Bitsy M4, etc.)
 7. [`Seeeduino SAMD core 1.8.1+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.) 
 8. [`Adafruit nRF52 v0.21.0+`](https://www.adafruit.com/) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.
 9. [`Arduino Core for STM32 v1.9.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards 
 
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
3. Install [**WiFiNINA_Generic** library](https://platformio.org/lib/show/11284/WiFiNINA_Generic) by using [Library Manager](https://platformio.org/lib/show/11284/WiFiNINA_Generic/installation). Search for **WiFiNINA_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

 1. **To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

 2. **To be able to compile and run on Teensy boards**, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

 3. **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

 4. ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.9](Packages_Patches/arduino/hardware/samd/1.8.9) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.9).
 
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

 5. ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.4) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.4). 

Supposing the Adafruit SAMD core version is 1.6.4. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.4/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

 6. ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

7. **To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`


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

### HOWTO Update WiFiNINA Firmware (latest version is v1.4.1 as of August 2020)

#### 1) Update the WiFi101 / WiFiNINA FirmwareUpdater-Plugin

- Download latest release from [WiFi101-FirmwareUpdater-Plugin](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases). As of August 2020, the latest WiFiNINA FW is v1.4.1, use [WiFi101-FirmwareUpdater-Plugin version v0.10.12](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.12).
- Unzip the downloaded file into WiFi101 folder (WiFi101/tool/firmwares folder and WiFi101/tool/WiFi101.jar file)
- Copy the whole WiFi101 folder to ./arduino-1.8.yy/tools to overwrite the old WiFi101 folder.
- Restart the Arduino IDE if running.

#### 2) Upload the WiFiNINA_Generic library's [FirmwareUpdater sketch](examples/Tools/FirmwareUpdater) to your board (Nano-33-IoT, nRF52, etc.) according to these following steps:

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

- Select the latest firmware,  e.g. "WiFiNINA firmware (1.4.1)(Arduino MKR WiFi1010, Arduino NANO 33 IoT) under "2. Update firmware".

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

Firmware version installed: 1.4.1
Latest firmware version available : 1.4.1

Check result: PASSED
```
---

### How to update SSL certificates

Please check the [Arduino Tutorial](https://www.arduino.cc/en/Tutorial/WiFiNINAFirmwareUpdater) if more info is required.

`With the same procedure, you may load root certificates on the WiFi module to access securely specific websites. Your board must be running the FirmwareUpdater sketch to work .The root certificates are issued by a limited number of certification authorities, but it is difficult to know which site is using which authority. To ease your life, we allow you to specify directly the URL to which you need to connect securely, leaving to us the task to download the root certificate.`

`The list you are building is not saved from one session to the next one. It might happen that a few websites share the same root certificate. You don't have to worry about this as we take care of it. The space available on your WiFi module to store the certificates is limited to around 10 certificates that, being issued by a limited number of authorities, should be more than enough for the average projects.`

This is the screen to demonstrate the SSL certificates have been loaded successfully onto a nRF52-based NINA_B302_ublox board running with ublox WiFiNINA W102 .

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/SSL_certs.png">
</p>

---
---

### Examples

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

### Tools

20. [CheckFirmwareVersion](examples/Tools/CheckFirmwareVersion)
21. [FirmwareUpdater](examples/Tools/FirmwareUpdater)
22. [SerialNINAPassthrough](examples/Tools/SerialNINAPassthrough)

---

## Example [WiFiWebServer](examples/WiFiWebServer)

### 1. File [WiFiWebServer.ino](examples/WiFiWebServer/WiFiWebServer.ino)

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
  Serial.println("Version " + String(WIFININA_GENERIC_VERSION));

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
    Serial.print("Your current firmware NINA FW v");
    Serial.println(fv);
    Serial.print("Please upgrade the firmware to NINA FW v");
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
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

### 2. File [defines.h](examples/WiFiWebServer/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFININA_USE_SAMD)
    #undef WIFININA_USE_SAMD
  #endif
  #define WIFININA_USE_SAMD      true
#endif

#if defined(WIFININA_USE_SAMD)

  #if defined(ARDUINO_SAMD_ZERO)
  #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
  #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
  #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
  #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
  #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
  #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
  #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
  #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
  #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
  #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
  #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
  #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
  #elif defined(Wio_Lite_MG126)
  #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
  #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
  #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
  #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
  #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
  #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
  #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
  #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
  #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51P19A__)
  #define BOARD_TYPE      "__SAMD51P19A__"
  #elif defined(__SAMD51J20A__)
  #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
  #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
  #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
  #define BOARD_TYPE      "SAMD51"
  #else
  #define BOARD_TYPE      "SAMD Unknown"
  #endif

#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(WIFININA_USE_NRF52)
    #undef WIFININA_USE_NRF52
  #endif
  #define WIFININA_USE_NRF52     true
#endif

#if defined(WIFININA_USE_NRF52)

  #if defined(NRF52840_FEATHER)
  #define BOARD_TYPE      "NRF52840_FEATHER_EXPRESS"
  #elif defined(NRF52832_FEATHER)
  #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
  #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
  #define BOARD_TYPE      "NRF52840_ITSYBITSY_EXPRESS"
  #elif defined(NRF52840_CIRCUITPLAY)
  #define BOARD_TYPE      "NRF52840_CIRCUIT_PLAYGROUND"
  #elif defined(NRF52840_CLUE)
  #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
  #define BOARD_TYPE      "NRF52840_METRO_EXPRESS"
  #elif defined(NRF52840_PCA10056)
  #define BOARD_TYPE      "NORDIC_NRF52840DK"
  #elif defined(NINA_B302_ublox)
  #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
  #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
  #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(MDBT50Q_RX)
  #define BOARD_TYPE      "RAYTAC_MDBT50Q_RX"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
  #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
  #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFININA_USE_SAMDUE)
    #undef WIFININA_USE_SAMDUE
  #endif
  #define WIFININA_USE_SAMDUE      true
#endif

#if defined(WIFININA_USE_SAMDUE)

  // For SAM DUE
  #if defined(ARDUINO_SAM_DUE)
  #define BOARD_TYPE      "SAM DUE"
  #elif defined(__SAM3X8E__)
  #define BOARD_TYPE      "SAM SAM3X8E"
  #else
  #define BOARD_TYPE      "SAM Unknown"
  #endif

#endif

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
#if defined(WIFININA_USE_STM32)
#undef WIFININA_USE_STM32
#endif
#define WIFININA_USE_STM32      true
#endif

#if defined(WIFININA_USE_STM32)
  #if defined(STM32F0)
  #warning STM32F0 board selected
  #define BOARD_TYPE  "STM32F0"
  #elif defined(STM32F1)
  #warning STM32F1 board selected
  #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
  #warning STM32F2 board selected
  #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
  #warning STM32F3 board selected
  #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
  #warning STM32F4 board selected
  #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
  #warning STM32F7 board selected
  #define BOARD_TYPE  "STM32F7"
  #elif defined(STM32L0)
  #warning STM32L0 board selected
  #define BOARD_TYPE  "STM32L0"
  #elif defined(STM32L1)
  #warning STM32L1 board selected
  #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
  #warning STM32L4 board selected
  #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32H7)
  #warning STM32H7 board selected
  #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
  #warning STM32G0 board selected
  #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
  #warning STM32G4 board selected
  #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
  #warning STM32WB board selected
  #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
  #warning STM32MP1 board selected
  #define BOARD_TYPE  "STM32MP1"
  #else
  #warning STM32 unknown board selected
  #define BOARD_TYPE  "STM32 Unknown"
  #endif

#endif

#ifdef CORE_TEENSY

  #if defined(WIFININA_USE_TEENSY)
    #undef WIFININA_USE_TEENSY
  #endif
  #define WIFININA_USE_TEENSY      true
  
  #if defined(__IMXRT1062__)
  // For Teensy 4.1/4.0
  #define BOARD_TYPE      "TEENSY 4.1/4.0"
  #elif defined(__MK66FX1M0__)
  #define BOARD_TYPE "Teensy 3.6"
  #elif defined(__MK64FX512__)
  #define BOARD_TYPE "Teensy 3.5"
  #elif defined(__MKL26Z64__)
  #define BOARD_TYPE "Teensy LC"
  #elif defined(__MK20DX256__)
  #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
  #elif defined(__MK20DX128__)
  #define BOARD_TYPE "Teensy 3.0"
  #elif defined(__AVR_AT90USB1286__)
  #error Teensy 2.0++ not supported yet
  #elif defined(__AVR_ATmega32U4__)
  #error Teensy 2.0 not supported yet
  #else
  // For Other Boards
  #define BOARD_TYPE      "Unknown Teensy Board"
  #endif

#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#define DEBUG_WIFININA_PORT     Serial
// Debug Level from 0 to 4
#define _WIFININA_LOGLEVEL_     1

#endif      //defines_h

```

---
---

### Debug Termimal Output Samples

The following are screen shot and debug terminal output when running example [AdvancedWebServer](https://github.com/khoih-prog/WiFiWebServer/tree/master/examples/AdvancedWebServer) on Arduino SAMD21 Nano-33-IoT board using this [WiFiNINA_Generic Library](https://github.com/khoih-prog/WiFiNINA_Generic)

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/pics/AdvancedWebServer.png">
</p>


```
Starting AdvancedServer on SAMD_NANO_33_IOT
Version 1.8.0
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

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield firmware 1.4.1+` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

---
---

## Releases

### New in v1.8.0

1. Sync with [Arduino WiFiNINA Library v1.8.0](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.8.0). Using the latest WiFiNINA FW v1.4.2 in [WiFi101-FirmwareUpdater-Plugin v0.10.13](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.13)
2. Limit the maximum length of the download URL for the OTA binary since the receive buffer on the nina firmware can't hold more than 128 bytes.
3. Introduce **WiFiBearSSLClient (offloaded to Nina)**

### New in v1.7.2

1. Add support to **Adafruit Airlift M4 boards: METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4.** Thanks to [Gerard Moorcroft](https://github.com/gmstuff) to report issue [**WiFi Hangs when attempting to start WiFi (Adafruit M4 Express Airlift Lite board)**](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/2) leading to this new version.
2. Add WIFININA_GENERIC_VERSION

#### New in v1.7.1

1. Sync with [Arduino WiFiNINA Library v1.7.1](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.7.1). Using the latest WiFiNINA FW v1.4.1 in [WiFi101-FirmwareUpdater-Plugin v0.10.12](https://github.com/arduino/WiFi101-FirmwareUpdater-Plugin/releases/tag/v0.10.12)

#### New in v1.7.0

1. Sync with [Arduino WiFiNINA Library v1.7.0](https://github.com/arduino-libraries/WiFiNINA/releases/tag/1.7.0). See [Add 'downloadOTA' command to download OTA file and verify length/CRC](https://github.com/arduino-libraries/WiFiNINA/pull/124)
2. Add Arduino SAMD Packages_Patches to fix Arduino SAMD compiler error when using STL. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)

#### New in v1.6.2

1. Fix WiFiStorage bug introduced from v1.6.0 resulting compile error.
2. Add example for WiFiStorage.

#### New in v1.6.1

1. Add support to all **STM32F/L/H/G/WB/MP1**
2. Add support to **Seeeduino SAMD21/SAMD51 boards **
3. Fix bug introduced to v1.6.0 resulting nRF52 compile error.

#### New in v1.6.0

1. Sync'ed with latest WiFiNINA Library v1.6.0. 
2. New features include **WiFiStorage** and update to **NINA Firmware v1.4.0** from v1.3.0


#### New in v1.5.3

1. Add function to support new WebSockets2_Generic Library
2. Update default pin-outs for nRF52 boards, especially NINA_112_ublox.

#### New in v1.5.2

1. Port FirmwareUpdater to permit **nRF52, Teensy, SAMD21, SAMD51, etc.** boards to update WiFiNINA W101/W102 firmware and SSL certificates using **Arduino IDE WiFi101/WiFiNINA Firmware Updater.** 
2. Update default pin-outs for nRF52 boards, especially NINA_B302_ublox.

Again with credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip).

#### New in v1.5.1

1. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, Clue nRF52840, Nordic nRF52840DK, Particle Xenon, etc.** Raytac MDBT50Q-RX Dongle is not supported.
2. Add support to **NINA_B302_ublox running as nRF52840**. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as **SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.**

---

### TO DO
1. Bug Searching and Killing
2. Support more types of boards using WiFiNINA and other WiFi shields.


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

<table>
  <tr>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/AppsByDavideV"><img src="https://github.com/AppsByDavideV.png" width="100px;" alt="AppsByDavideV"/><br /><sub><b>AppsByDavideV</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/ocrdu"><img src="https://github.com/ocrdu.png" width="100px;" alt="ocrdu"/><br /><sub><b>Oscar den Uijl</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/gmstuff"><img src="https://github.com/gmstuff.png" width="100px;" alt="gmstuff"/><br /><sub><b>Gerard Moorcroft</b></sub></a><br /></td>
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

### Copyright

1. Copyright (c) 2018 Arduino SA. All rights reserved.
2. Copyright (c) 2011-2014 Arduino LLC. All right reserved.
3. Copyright 2020- Khoi Hoang


