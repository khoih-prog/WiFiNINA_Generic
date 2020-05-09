/****************************************************************************************************************************
  debug.h - Library for Arduino WifiNINA module/shield.
  
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

//*********************************************/
// 
//  File:   debug.h
// 
//  Author: dlf (Metodo2 srl)
// 
//********************************************/

#ifndef Debug_H
#define Debug_H

#include <stdio.h>
#include <string.h>

#define PRINT_FILE_LINE() do { 						\
		Serial.print("[");Serial.print(__FILE__);		\
		Serial.print("::");Serial.print(__LINE__);Serial.print("]");\
}while (0);

//KH
#define _DEBUG_

#ifdef _DEBUG_

#define INFO(format, args...) do { \
	char buf[250];	\
	sprintf(buf, format, args); \
	Serial.println(buf); \
} while(0);

#define INFO1(x) do { PRINT_FILE_LINE() Serial.print("-I-");\
		Serial.println(x);    			\
}while (0);

#define INFO2(x,y) do { PRINT_FILE_LINE() Serial.print("-I-");\
		Serial.print(x,16);Serial.print(",");Serial.println(y,16); \
}while (0);


#else
#define INFO1(x) do {} while(0);
#define INFO2(x,y) do {} while(0);
#define INFO(format, args...) do {} while(0);
#endif

#if 1
#define WARN(args) do { PRINT_FILE_LINE()			\
		Serial.print("-W-"); Serial.println(args);	\
}while (0);
#else
#define WARN(args) do {} while (0);
#endif


//KH
#define _DEBUG_SPI_     false

#if _DEBUG_SPI_
#define DBG_PIN2 5
#define DBG_PIN 4

#define START()         digitalWrite(DBG_PIN2, HIGH);
#define END()           digitalWrite(DBG_PIN2, LOW);
#define SET_TRIGGER()   digitalWrite(DBG_PIN, HIGH);
#define RST_TRIGGER()   digitalWrite(DBG_PIN, LOW);

#define INIT_TRIGGER()  pinMode(DBG_PIN, OUTPUT); \
                        pinMode(DBG_PIN2, OUTPUT); \
                        RST_TRIGGER()
#define TOGGLE_TRIGGER() SET_TRIGGER() \
                           delayMicroseconds(2);    \
                               RST_TRIGGER()
#else
#define START()
#define END()
#define SET_TRIGGER()
#define RST_TRIGGER()
#define INIT_TRIGGER()
#define TOGGLE_TRIGGER()
#endif

#endif
