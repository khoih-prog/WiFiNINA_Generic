/**********************************************************************************************************************************
  WiFiNINA_Pinout_Generic.h - Library for Arduino WiFiNINA module/shield.

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

  Version: 1.8.15-1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0      K Hoang    27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                   such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  ...
  1.8.13     K Hoang    03/08/2021 Sync with WiFiNINA v1.8.13 : new FW v1.4.8. Add support to ADAFRUIT_MATRIXPORTAL_M4_EXPRESS
  1.8.14-1   K Hoang    25/11/2021 Fix examples to support ATmega4809 such as UNO_WIFI_REV2 and NANO_EVERY
  1.8.14-2   K Hoang    31/12/2021 Add support to Nano_RP2040_Connect using arduino-pico core
  1.8.14-3   K Hoang    31/12/2021 Fix issue with UDP for Nano_RP2040_Connect using arduino-pico core
  1.8.14-4   K Hoang    01/05/2022 Fix bugs by using some PRs from original WiFiNINA. Add WiFiMulti-related examples
  1.8.14-5   K Hoang    23/05/2022 Fix bug causing data lost when sending large files
  1.8.14-6   K Hoang    17/08/2022 Add support to Teensy 4.x using WiFiNINA AirLift. Fix minor bug
  1.8.14-7   K Hoang    11/11/2022 Modify WiFiWebServer example to avoid crash in arduino-pico core
  1.8.15-0   K Hoang    14/11/2022 Fix severe limitation to permit sending much larger data than total 4K
  1.8.15-1   K Hoang    18/11/2022 Using new WiFi101_Generic library to permit sending larger data than total 4K
 ***********************************************************************************************************************************/

#pragma once

////////////////////////////////////////


/* For Nano-33-IoT, from hardware/samd/1.8.5/variants/nano33iot/variant.h/cpp
  +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
  | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
  |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
  |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  |            |SPI (Legacy ICSP) |        |                 |        |     |     |     |     |         |         |        |        |          |          |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
  | 22         | 1                |  PA12  | NINA_MOSI       |   12   |     |     |     |     |  *2/00  |   4/00  | TCC2/0 | TCC0/6 |          | AC/CMP0  |
  | 23         | 2                |  PA13  | NINA_MISO       |   13   |     |     |     |     |  *2/01  |   4/01  | TCC2/1 | TCC0/7 |          | AC/CMP1  |
  | 24         | 4                |  PA14  | NINA_CS         |   14   |     |     |     |     |   2/02  |   4/02  |  TC3/0 | TCC0/4 |          | GCLK_IO0 |
  | 25         | 3                |  PA15  | NINA_SCK        |   15   |     |     |     |     |  *2/03  |   4/03  |  TC3/1 | TCC0/5 |          | GCLK_IO1 |
  | 26         |                  |  PA27  | NINA_GPIO0      |  *15   |     |     |     |     |         |         |        |        |          | GCLK_IO0 |
  | 27         |                  |  PA08  | NINA_RESETN     |   NMI  |  16 |     | X00 |     |   0/00  |   2/00  | TCC0/0 | TCC1/2 | I2S/SD1  |          |
  | 28         |                  |  PA28  | NINA_ACK        |   08   |     |     |     |     |         |         |        |        |          | GCLK_IO0 |
  +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
*/

#if 0     // Example for Nano-33 IoT
  #define PINS_COUNT           (PINCOUNT_fn())
  #define NUM_DIGITAL_PINS     (31u)
  #define NUM_ANALOG_INPUTS    (8u)
  #define NUM_ANALOG_OUTPUTS   (1u)

  //NINA
  #define NINA_GPIO0  (26u)                     //26
  #define NINA_RESETN (27u)
  #define NINA_ACK    (28u)

  // SPI1
  #define PIN_SPI1_MISO    (23u)
  #define PIN_SPI1_MOSI    (22u)
  #define PIN_SPI1_SCK     (25u)
  #define PIN_SPI1_SS      (24u)
  #define PERIPH_SPI1   sercom2
  #define PAD_SPI1_TX   SPI_PAD_0_SCK_3
  #define PAD_SPI1_RX   SERCOM_RX_PAD_1

  #define SPIWIFI_SS       PIN_SPI1_SS            //24
  #define SPIWIFI_ACK      NINA_ACK               //28
  #define SPIWIFI_RESET    NINA_RESETN            //27

#endif

////////////WARNING////////////////
// To modify according to actual connection


////////////////////////////////////////

#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRWIFI1010) || \
      defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT))

#if defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT)
  // Fix UDP issue for arduino-pico core
  #define NINA_GPIOIRQ    (D20)   // actual 2, NINA_GPIO0
  #define NINA_RESETN     (D24)   // actual 3, NINA_RESETN
#endif

#if (_WIFININA_LOGLEVEL_>2)
  #warning Using default WiFiNINA settings
#endif

////////////////////////////////////////

#elif  ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
      || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
      || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
      || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
      || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )

#if !( defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )

#if defined(SEEED_WIO_TERMINAL)

  #warning You have to modify pin usage according to actual connection for SAMD SEEED_WIO_TERMINAL
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(SEEED_FEMTO_M0)

  #warning You have to modify pin usage according to actual connection for SAMD SEEED_FEMTO_M0
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(SEEED_XIAO_M0)

  #warning You have to modify pin usage according to actual connection for SAMD SEEED_XIAO_M0
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(Wio_Lite_MG126)

  #warning You have to modify pin usage according to actual connection for SAMD Wio_Lite_MG126
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(WIO_GPS_BOARD)

  #warning You have to modify pin usage according to actual connection for SAMD WIO_GPS_BOARD
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(SEEEDUINO_ZERO)

  #warning You have to modify pin usage according to actual connection for SAMD SEEEDUINO_ZERO
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(SEEEDUINO_LORAWAN)

  #warning You have to modify pin usage according to actual connection for SAMD SEEEDUINO_LORAWAN
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif defined(SEEED_GROVE_UI_WIRELESS)

  #warning You have to modify pin usage according to actual connection for SAMD SEEED_GROVE_UI_WIRELESS
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  ( 0u)                             //0
  #define NINA_RESETN ( 1u)
  #define NINA_ACK    ( 2u)

  #define SPIWIFI_SS        3   //PIN_SPI1_SS            //3
  #define SPIWIFI_ACK       2   //NINA_ACK               //2
  #define SPIWIFI_RESET     1   //NINA_RESETN            //1

#elif ( defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) || defined(ADAFRUIT_PYBADGE_AIRLIFT_M4) )

  #if (_WIFININA_LOGLEVEL_>2)
    #warning ADAFRUIT_METRO_M4_AIRLIFT_LITE or ADAFRUIT_PYBADGE_AIRLIFT_M4 are OK to use
  #endif

#elif ( defined(ADAFRUIT_MATRIXPORTAL_M4_EXPRESS)  )

  #warning You have to modify pin usage according to actual connection for SAMD51 ADAFRUIT_MATRIXPORTAL_M4_EXPRESS
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0      ESP32_GPIO0
  #define NINA_RESETN     ESP32_RESETN
  #define NINA_ACK        SPIWIFI_ACK

  #define SPIWIFI_SS      33
  #define SPIWIFI_ACK     31
  #define SPIWIFI_RESET   ESP32_RESETN

#else
  #warning You have to modify pin usage according to actual connection for SAMD
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (26u)                             //26
  #define NINA_RESETN (27u)
  #define NINA_ACK    (28u)

  #define SPIWIFI_SS       24   //PIN_SPI1_SS            //24
  #define SPIWIFI_ACK      28   //NINA_ACK               //28
  #define SPIWIFI_RESET    27   //NINA_RESETN            //27

#endif
#endif

////////////////////////////////////////

#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )

#if  ( defined(NINA_B302_ublox) )

  #warning You have to modify pin usage according to actual connection for NINA_B302_ublox running as NRF52840
  // To define pin out for WiFiNINA here. This is just an example and tested working OK.
  // The following is for NINA_B302_ublox as nRF52840 and W102 WiFiNINA module
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

#elif  ( defined(NINA_B112_ublox) )

  #warning You have to modify pin usage according to actual connection for NINA_B112_ublox running as NRF52832
  // To define pin out for WiFiNINA here. This is just an example and tested working OK.
  // The following is for NINA_B112_ublox as nRF52832 and W102 WiFiNINA module
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

#else

  #warning You have to modify pin usage according to actual connection for NRF528XX board
  // To define pin out for WiFiNINA here. This is just an example
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

#endif

////////////////////////////////////////

#elif ( defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) || defined(AVR_ADK) )

#warning You have to modify pin usage according to actual connection for Mega 2560/1280
// To define pin out for WiFiNINA here
//#define PIN_SPI_SS    (53)
//#define PIN_SPI_MOSI  (51)
//#define PIN_SPI_MISO  (50)
//#define PIN_SPI_SCK   (52)

#define PINS_COUNT           (60u)
//NINA
#define NINA_GPIO0  (26u)                             //26
#define NINA_RESETN (27u)
#define NINA_ACK    (28u)

#define SPIWIFI_SS       53   //PIN_SPI_SS             //53
#define SPIWIFI_ACK      28   //NINA_ACK               //28 
#define SPIWIFI_RESET    27   //NINA_RESETN            //27

////////////////////////////////////////

#elif ( defined(ARDUINO_AVR_UNO_WIFI_REV2) )

#if (_WIFININA_LOGLEVEL_>2)
  #warning Use WiFiNINA for UNO WiFi Rev2
#endif

////////////////////////////////////////

#elif defined(CORE_TEENSY)

#if defined(__IMXRT1062__)
  // For Teensy 4.0
  #warning You have to modify pin usage according to actual connection for Teensy 4.0/4.1
  #define PINS_COUNT           (60u)
  // T4.1 SPI pin defs for WiFiNINA AirLift.
  #define NINA_GPIO0  (255u)                           //6
  #define NINA_RESETN (6u)
  #define NINA_ACK    (9u)

  // T4.1 SPI pin defs for WiFiNINA AirLift.
  #define SPIWIFI_SS       5   //PIN_SPI1_SS           //10
  #define SPIWIFI_ACK      9   //NINA_ACK               //7
  #define SPIWIFI_RESET    6   //NINA_RESETN            //5

#elif ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )

  // For BOARD_TYPE      "TEENSY LC or 2.0"
  #warning You have to modify pin usage according to actual connection for Teensy LC or 2.0
  #define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (6u)                             //6
  #define NINA_RESETN (2u)
  #define NINA_ACK    (5u)

  #define SPIWIFI_SS       10   //PIN_SPI1_SS           //10
  #define SPIWIFI_ACK      5   //NINA_ACK               //5
  #define SPIWIFI_RESET    2   //NINA_RESETN            //7

#else

  #warning You have to modify pin usage according to actual connection for Teensy 3.x
  #define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (6u)                             //6
  #define NINA_RESETN (2u)
  #define NINA_ACK    (5u)

  #define SPIWIFI_SS       10   //PIN_SPI1_SS           //10
  #define SPIWIFI_ACK      5   //NINA_ACK               //5
  #define SPIWIFI_RESET    2   //NINA_RESETN            //7

#endif

////////////////////////////////////////

#elif ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )

#warning You have to modify pin usage according to actual connection for SAM DUE
//#define PINS_COUNT           (60u)
//NINA
#define NINA_GPIO0  (26u)                             //26
#define NINA_RESETN (27u)
#define NINA_ACK    (28u)

#define SPIWIFI_SS       24   //PIN_SPI1_SS            //24
#define SPIWIFI_ACK      28   //NINA_ACK               //28 
#define SPIWIFI_RESET    27   //NINA_RESETN            //27

////////////////////////////////////////

#elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )

#if defined(ARDUINO_NUCLEO_L053R8)
  // For Nucleo-64 NUCLEO_L053R8
  #warning You have to modify pin usage according to actual connection for NUCLEO_L053R8
  #define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (6u)                             //not used
  #define NINA_RESETN (D2)
  #define NINA_ACK    (D3)

  #define SPIWIFI_SS       D10   //PIN_SPI1_SS           //10
  #define SPIWIFI_ACK      D3   //NINA_ACK               //3
  #define SPIWIFI_RESET    D2   //NINA_RESETN            //2

#else
  #warning You have to modify pin usage according to actual connection for STM32
  #define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (26u)                             //26
  #define NINA_RESETN (27u)
  #define NINA_ACK    (28u)

  #define SPIWIFI_SS       24   //PIN_SPI1_SS            //24
  #define SPIWIFI_ACK      28   //NINA_ACK               //28
  #define SPIWIFI_RESET    27   //NINA_RESETN            //27
#endif

////////////////////////////////////////

#elif ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
        defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT) )

#if defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT)
  #if (_WIFININA_LOGLEVEL_>2)
    #warning Using Nano_RP2040_Connect with arduino-pico core
  #endif

  //NINA
  #define NINA_GPIO0  (20u)
  #define NINA_RESETN (24u)
  #define NINA_ACK    (27u)

  #define SPIWIFI_SS       (26u)
  #define SPIWIFI_ACK      (27u)
  #define SPIWIFI_RESET    (NINA_RESETN)

#else
  #warning You have to modify pin usage according to actual connection for RP2040

  //NINA
  #define NINA_GPIO0  (20u)
  #define NINA_RESETN (24u)
  #define NINA_ACK    (27u)

  #define SPIWIFI_SS       (26u)
  #define SPIWIFI_ACK      (27u)
  #define SPIWIFI_RESET    (NINA_RESETN)
#endif

////////////////////////////////////////

#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__)    || \
      defined(__AVR_ATmega640__)   || defined(__AVR_ATmega641__)    || defined(__AVR_ATmega644__)  || defined(__AVR_ATmega644A__)      || \
      defined(__AVR_ATmega644P__)  || defined(__AVR_ATmega644PA__)  || defined(ARDUINO_AVR_UNO)    || defined(ARDUINO_AVR_NANO)        || \
      defined(ARDUINO_AVR_MINI)    || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO)    || defined(ARDUINO_AVR_BT)          || \
      defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO)      || defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) || \
      defined(ARDUINO_AVR_DUEMILANOVE)  || defined(ARDUINO_AVR_FEATHER328P) || defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) || \
      defined(ARDUINO_AVR_PROTRINKET3)  || defined(ARDUINO_AVR_PROTRINKET5FTDI) || defined(ARDUINO_AVR_PROTRINKET3FTDI) || \
      defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_LEONARDO_ETH) || defined(ARDUINO_AVR_YUN) || defined(ARDUINO_AVR_MICRO) || \
      defined(ARDUINO_AVR_ESPLORA)  || defined(ARDUINO_AVR_LILYPAD_USB)  || defined(ARDUINO_AVR_ROBOT_CONTROL) || \
      defined(ARDUINO_AVR_ROBOT_MOTOR) || defined(ARDUINO_AVR_CIRCUITPLAY)  || defined(ARDUINO_AVR_YUNMINI) || defined(ARDUINO_AVR_INDUSTRIAL101) || \
      defined(ARDUINO_AVR_LININO_ONE) || defined(ARDUINO_AVR_FLORA8 ) || defined(ARDUINO_AVR_FEATHER32U4) || defined(ARDUINO_AVR_CIRCUITPLAY) || \
      defined(ARDUINO_AVR_ITSYBITSY32U4_5V) || defined(ARDUINO_AVR_ITSYBITSY32U4_3V) || defined(ARDUINO_AVR_BLUEFRUITMICRO) || \
      defined(ARDUINO_AVR_ADAFRUIT32U4) || defined(__AVR_ATmega32U4__) || defined(ARDUINO_AVR_MAKEYMAKEY ) || defined(ARDUINO_AVR_PROMICRO) || \
      defined(ARDUINO_AVR_FIOV3) || defined(ARDUINO_AVR_QDUINOMINI) || defined(ARDUINO_AVR_LILYPAD_ARDUINO_USB_PLUS_BOARD ) || \
      defined(__AVR_ATmega328P__) || defined(ARDUINO_AVR_DIGITAL_SANDBOX ) || defined(ARDUINO_REDBOT) || defined(ARDUINO_AVR_SERIAL_7_SEGMENT) || \
      defined(__AVR_ATmega128RFA1__) || defined(ARDUINO_ATMEGA128RFA1_DEV_BOARD)

// To define pin out for WiFiNINA here
//#define PIN_SPI_SS    (4)
//#define PIN_SPI_MOSI  (11)
//#define PIN_SPI_MISO  (12)
//#define PIN_SPI_SCK   (13)

#define PINS_COUNT           (60u)
//NINA
#define NINA_GPIO0  (2u)
#define NINA_RESETN (7u)
#define NINA_ACK    (8u)
#define SPIWIFI_SS       4
#define SPIWIFI_ACK      8
#define SPIWIFI_RESET    7

#warning You have to modify pin usage according to actual connection for AVR (328P, 32U4, 16U4, etc.) boards

////////////////////////////////////////

#else

#warning You have to modify pin usage according to actual connection for your unknown board
#define PINS_COUNT           (60u)
//NINA
#define NINA_GPIO0  (26u)                             //26
#define NINA_RESETN (27u)
#define NINA_ACK    (28u)

#define SPIWIFI_SS       10   //PIN_SPI_SS             //10
#define SPIWIFI_ACK      28   //NINA_ACK               //28 
#define SPIWIFI_RESET    27   //NINA_RESETN            //27  

////////////////////////////////////////

#endif

