/****************************************************************************************************************************
  spi_drv.h - Library for Arduino WifiNINA module/shield.
  
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

#ifndef SPI_Drv_h
#define SPI_Drv_h

#include <inttypes.h>
#include "wifi_spi.h"

#define SPI_START_CMD_DELAY 	10

#define NO_LAST_PARAM   0
#define LAST_PARAM      1

#define DUMMY_DATA  0xFF

#define WAIT_FOR_SLAVE_SELECT()	      \
	if (!SpiDrv::initialized) {           \
		SpiDrv::begin();      \
	}                             \
	SpiDrv::waitForSlaveReady();  \
	SpiDrv::spiSlaveSelect();

class SpiDrv
{
private:
	//static bool waitSlaveReady();
	static void waitForSlaveSign();
	static void getParam(uint8_t* param);
public:
    static bool initialized;

    static void begin();

    static void end();
    
    static void spiDriverInit();
        
    static void spiSlaveSelect();
    
    static void spiSlaveDeselect();
    
    static char spiTransfer(volatile char data);

    static void waitForSlaveReady();

    //static int waitSpiChar(char waitChar, char* readChar);

    static int waitSpiChar(unsigned char waitChar);
    
    static int readAndCheckChar(char checkChar, char* readChar);

    static char readChar();

    static int waitResponseParams(uint8_t cmd, uint8_t numParam, tParam* params);
    
    static int waitResponseCmd(uint8_t cmd, uint8_t numParam, uint8_t* param, uint8_t* param_len);

    static int waitResponseData8(uint8_t cmd, uint8_t* param, uint8_t* param_len);
     
    static int waitResponseData16(uint8_t cmd, uint8_t* param, uint16_t* param_len);
 /*
    static int waitResponse(uint8_t cmd, tParam* params, uint8_t* numParamRead, uint8_t maxNumParams);
    
    static int waitResponse(uint8_t cmd, uint8_t numParam, uint8_t* param, uint16_t* param_len);
*/
    static int waitResponse(uint8_t cmd, uint8_t* numParamRead, uint8_t** params, uint8_t maxNumParams);

    static void sendParam(uint8_t* param, uint8_t param_len, uint8_t lastParam = NO_LAST_PARAM);

    static void sendParamLen8(uint8_t param_len);

    static void sendParamLen16(uint16_t param_len);

    static uint8_t readParamLen8(uint8_t* param_len = NULL);

    static uint16_t readParamLen16(uint16_t* param_len = NULL);

    static void sendBuffer(uint8_t* param, uint16_t param_len, uint8_t lastParam = NO_LAST_PARAM);

    static void sendParam(uint16_t param, uint8_t lastParam = NO_LAST_PARAM);
    
    static void sendCmd(uint8_t cmd, uint8_t numParam);

    static int available();
};                                                                 

extern SpiDrv spiDrv;

#endif
