/****************************************************************************************************************************
  Endianess.ino - Network byte order conversion functions - part of the Firmware Updater for the 
  Arduino Nano-33 IoT, MKR WiFi 1010, Arduino MKR Vidor 4000, and Arduino UNO WiFi Rev.2., Adafruit's nRF52 boards
  
  Based on and modified from WiFiNINA libarary https://www.arduino.cc/en/Reference/WiFiNINA
  to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, Adafruit's nRF52 boards, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
  Licensed under MIT license
  Version: 1.5.2
   
  Copyright (c) 2015 Arduino LLC.  All right reserved.
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

bool isBigEndian() 
{
  uint32_t test = 0x11223344;
  uint8_t *pTest = reinterpret_cast<uint8_t *>(&test);
  return pTest[0] == 0x11;
}

uint32_t fromNetwork32(uint32_t from) 
{
  static const bool be = isBigEndian();
  
  if (be) 
  {
    return from;
  } 
  else 
  {
    uint8_t *pFrom = reinterpret_cast<uint8_t *>(&from);
    uint32_t to;
    
    to = pFrom[0]; to <<= 8;
    to |= pFrom[1]; to <<= 8;
    to |= pFrom[2]; to <<= 8;
    to |= pFrom[3];
    return to;
  }
}

uint16_t fromNetwork16(uint16_t from) 
{
  static bool be = isBigEndian();
  
  if (be) 
  {
    return from;
  } 
  else 
  {
    uint8_t *pFrom = reinterpret_cast<uint8_t *>(&from);
    uint16_t to;
    
    to = pFrom[0]; to <<= 8;
    to |= pFrom[1];
    return to;
  }
}

uint32_t toNetwork32(uint32_t to) 
{
  return fromNetwork32(to);
}

uint16_t toNetwork16(uint16_t to) 
{
  return fromNetwork16(to);
}
