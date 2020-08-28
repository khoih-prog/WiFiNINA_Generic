/****************************************************************************************************************************
  ESP32BootROM.h - part of the Firmware Updater for the 
  Arduino Nano-33 IoT, MKR WiFi 1010, Arduino MKR Vidor 4000, and Arduino UNO WiFi Rev.2., Adafruit's nRF52 boards
  
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

#include <Arduino.h>

class ESP32BootROMClass 
{
  public:
    ESP32BootROMClass(HardwareSerial& hwSerial, int gpio0Pin, int resetnPin);

    int begin(unsigned long baudrate);
    void end();

    int beginFlash(uint32_t offset, uint32_t size, uint32_t chunkSize);
    int dataFlash(const void* data, uint32_t length);
    int endFlash(uint32_t reboot);

    int md5Flash(uint32_t offset, uint32_t size, uint8_t* result);

  private:
    int sync();
    int changeBaudrate(unsigned long baudrate);
    int spiAttach();

    void command(int opcode, const void* data, uint16_t length);
    int response(int opcode, unsigned long timeout, void* body = NULL);

    void writeEscapedBytes(const uint8_t* data, uint16_t length);

  private:
    HardwareSerial* _serial;
    int _gpio0Pin;
    int _resetnPin;

    uint32_t _flashSequenceNumber;
    uint32_t _chunkSize;
};

extern ESP32BootROMClass ESP32BootROM;
