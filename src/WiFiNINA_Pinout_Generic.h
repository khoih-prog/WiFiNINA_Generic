/****************************************************************************************************************************
  WiFiNINA_Pinout_Generic.h - Library for Arduino WifiNINA module/shield.
  
  Based on and modified from WiFiNINA libarary https://www.arduino.cc/en/Reference/WiFiNINA
  to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, Adafruit's nRF52 boards, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
  Licensed under MIT license
  Version: 1.5.2
   
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
  
  Version Modified By   Date      Comments
 ------- -----------  ---------- -----------
  1.5.0   K Hoang      27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                  such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  1.5.1   K Hoang      22/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, 
                                  Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, etc.         
  1.5.2   K Hoang      09/05/2020 Port FirmwareUpdater to permit nRF52 boards to update W102 firmware and SSL certs on IDE   
                                  Update default pin-outs.                                                
 *****************************************************************************************************************************/

#ifndef WiFiNINA_Pinout_Generic_h
#define WiFiNINA_Pinout_Generic_h

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

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) \
      || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500)  || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__)  )

  #if !( defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
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

#elif  ( defined(NINA_B302_ublox) )

  #warning You have to modify pin usage according to actual connection for NINA_B302_ublox running as NRF52840
  // To define pin out for WiFiNINA here. This is just an example and tested working OK.
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
  
#elif ( defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) )

  #warning You have to modify pin usage according to actual connection for Mega 2560/1280
  // To define pin out for WiFiNINA here

  #define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (26u)                             //26
  #define NINA_RESETN (27u)
  #define NINA_ACK    (28u)

  #define SPIWIFI_SS       24   //PIN_SPI1_SS            //24
  #define SPIWIFI_ACK      28   //NINA_ACK               //28 
  #define SPIWIFI_RESET    27   //NINA_RESETN            //27

#elif defined(CORE_TEENSY)

  #if defined(__IMXRT1062__)
    // For Teensy 4.0
    #warning You have to modify pin usage according to actual connection for Teensy 4.0
    #define PINS_COUNT           (60u)
    //NINA
    #define NINA_GPIO0  (6u)                             //6
    #define NINA_RESETN (2u)
    #define NINA_ACK    (5u)

    #define SPIWIFI_SS       10   //PIN_SPI1_SS           //10
    #define SPIWIFI_ACK      5   //NINA_ACK               //5
    #define SPIWIFI_RESET    2   //NINA_RESETN            //7

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

#elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )

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


#endif    //WiFiNINA_Pinout_Generic_h
