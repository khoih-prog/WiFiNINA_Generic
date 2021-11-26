/**********************************************************************************************************************************
  wifi_drv.cpp - Library for Arduino WiFiNINA module/shield.
  
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
  
  Version: 1.8.14-1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0      K Hoang    27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                   such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  1.5.1      K Hoang    22/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense,
                                   Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, etc.
  1.5.2      K Hoang    09/05/2020 Port FirmwareUpdater to permit nRF52, Teensy, SAMD21, SAMD51, etc. boards to update WiFiNINA
                                   W101/W102 firmware and SSL certs on IDE. Update default pin-outs.
  1.5.3      K Hoang    14/07/2020 Add function to support new WebSockets2_Generic Library
  1.6.0      K Hoang    19/07/2020 Sync with Arduino WiFiNINA Library v1.6.0 (new Firmware 1.4.0 and WiFiStorage)
  1.6.1      K Hoang    24/07/2020 Add support to all STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards 
  1.6.2      K Hoang    28/07/2020 Fix WiFiStorage bug from v1.6.0  
  1.7.0      K Hoang    06/08/2020 Sync with Arduino WiFiNINA Library v1.7.0 : Add downloadOTA() and verify length/CRC
  1.7.1      K Hoang    27/08/2020 Sync with Arduino WiFiNINA Library v1.7.1 : new Firmware 1.4.1
  1.7.2      K Hoang    05/11/2020 Add support to Adafruit Airlift M4 boards: METRO_M4_AIRLIFT_LITE, PYBADGE_AIRLIFT_M4
  1.8.0      K Hoang    19/11/2020 Sync with Arduino WiFiNINA Library v1.8.0 : new Firmware 1.4.2. Add WiFiBearSSLClient.
  1.8.2      K Hoang    02/02/2021 Sync with WiFiNINA v1.8.2 : new Firmware 1.4.3. Add possibility to resend data if lwip_send fails
  1.8.5      K Hoang    20/03/2021 Sync with WiFiNINA v1.8.5 : Feed watchdog within busy-wait-loop within connectBearSSL
  1.8.10     K Hoang    25/05/2021 Sync with WiFiNINA v1.8.10 : Support RP2040, new FW v1.4.5
  1.8.10-1   K Hoang    29/05/2021 Fix PinStatus compile error for some platforms
  1.8.11     K Hoang    14/06/2021 Sync with WiFiNINA v1.8.11 : Support RP2040, new FW v1.4.6
  1.8.12     K Hoang    30/06/2021 Sync with WiFiNINA v1.8.12 : new FW v1.4.7. Add support to most AVR boards.
  1.8.13     K Hoang    03/08/2021 Sync with WiFiNINA v1.8.13 : new FW v1.4.8. Add support to ADAFRUIT_MATRIXPORTAL_M4_EXPRESS
  1.8.14-1   K Hoang    25/11/2021 Fix examples to support ATmega4809 such as UNO_WIFI_REV2 and NANO_EVERY
 ***********************************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "Arduino.h"
#include "spi_drv.h"
#include "wifi_drv.h"

#define _DEBUG_

#if defined(KH_WIFININA_DRV_DEBUG)
  #undef KH_WIFININA_DRV_DEBUG
#endif
#define KH_WIFININA_DRV_DEBUG   0

// From v1.5.1, For nRF52x
#include "wifi_spi.h"
#include "wl_types.h"
#include "debug.h"

// Array of data to cache the information related to the networks discovered
char   WiFiDrv::_networkSsid[][WL_SSID_MAX_LENGTH] = 
{
  {"1"}, 
  {"2"}, 
  {"3"}, 
  {"4"}, 
  {"5"}
};

// Cached values of retrieved data
char  WiFiDrv::_ssid[]          = {0};
uint8_t WiFiDrv::_bssid[]       = {0};
uint8_t WiFiDrv::_mac[]         = {0};
uint8_t WiFiDrv::_localIp[]     = {0};
uint8_t WiFiDrv::_subnetMask[]  = {0};
uint8_t WiFiDrv::_gatewayIp[]   = {0};
// Firmware version
char    WiFiDrv::fwVersion[]    = {0};


// Private Methods

void WiFiDrv::getNetworkData(uint8_t *ip, uint8_t *mask, uint8_t *gwip)
{
  tParam params[PARAM_NUMS_3] = { {0, (char*)ip}, {0, (char*)mask}, {0, (char*)gwip}};

  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_IPADDR_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, sizeof(_dummy), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  SpiDrv::waitResponseParams(GET_IPADDR_CMD, PARAM_NUMS_3, params);

  SpiDrv::spiSlaveDeselect();
}

void WiFiDrv::getRemoteData(uint8_t sock, uint8_t *ip, uint8_t *port)
{
  tParam params[PARAM_NUMS_2] = 
  { 
    {0, (char*)ip}, 
    {0, (char*)port} 
  };

  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_REMOTE_DATA_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam(&sock, sizeof(sock), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  SpiDrv::waitResponseParams(GET_REMOTE_DATA_CMD, PARAM_NUMS_2, params);

  SpiDrv::spiSlaveDeselect();
}


// Public Methods


void WiFiDrv::wifiDriverInit()
{
  SpiDrv::begin();
}

void WiFiDrv::wifiDriverDeinit()
{
  SpiDrv::end();
}

int8_t WiFiDrv::wifiSetNetwork(const char* ssid, uint8_t ssid_len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_NET_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam((uint8_t*)ssid, ssid_len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 5 + ssid_len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_NET_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();

  return (_data == WIFI_SPI_ACK) ? WL_SUCCESS : WL_FAILURE;
}

int8_t WiFiDrv::wifiSetPassphrase(const char* ssid, uint8_t ssid_len, const char *passphrase, const uint8_t len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_PASSPHRASE_CMD, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)ssid, ssid_len, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)passphrase, len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 6 + ssid_len + len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_PASSPHRASE_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");

    _data = WL_FAILURE;

    //KH
#if (KH_WIFININA_DRV_DEBUG > 0)
    Serial.println("WiFiDrv-wifiSetPassphrase: waitResponseCmd = WL_FAILURE");
#endif
  }
  
  SpiDrv::spiSlaveDeselect();

  //KH
#if (KH_WIFININA_DRV_DEBUG > 0)
  Serial.print("WiFiDrv-wifiSetPassphrase: return = ");
  Serial.println(_data);
#endif

  return _data;
}


int8_t WiFiDrv::wifiSetKey(const char* ssid, uint8_t ssid_len, uint8_t key_idx, const void *key, const uint8_t len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_KEY_CMD, PARAM_NUMS_3);
  SpiDrv::sendParam((uint8_t*)ssid, ssid_len, NO_LAST_PARAM);
  SpiDrv::sendParam(&key_idx, KEY_IDX_LEN, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)key, len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 8 + ssid_len + len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  if (!SpiDrv::waitResponseCmd(SET_KEY_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

void WiFiDrv::config(uint8_t validParams, uint32_t local_ip, uint32_t gateway, uint32_t subnet)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_IP_CONFIG_CMD, PARAM_NUMS_4);
  SpiDrv::sendParam((uint8_t*)&validParams, 1, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&local_ip, 4, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&gateway, 4, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&subnet, 4, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_IP_CONFIG_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
}

void WiFiDrv::setDNS(uint8_t validParams, uint32_t dns_server1, uint32_t dns_server2)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_DNS_CONFIG_CMD, PARAM_NUMS_3);
  SpiDrv::sendParam((uint8_t*)&validParams, 1, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&dns_server1, 4, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&dns_server2, 4, LAST_PARAM);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_DNS_CONFIG_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
}

void WiFiDrv::setHostname(const char* hostname)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_HOSTNAME_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam((uint8_t*)hostname, strlen(hostname), LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 5 + strlen(hostname);
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_HOSTNAME_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
}

int8_t WiFiDrv::disconnect()
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(DISCONNECT_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  int8_t result = SpiDrv::waitResponseCmd(DISCONNECT_CMD, PARAM_NUMS_1, &_data, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return result;
}

uint8_t WiFiDrv::getReasonCode()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_REASON_CODE_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 1;
  uint8_t _dataLen = 0;
  SpiDrv::waitResponseCmd(GET_REASON_CODE_CMD, PARAM_NUMS_1, &_data, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return _data;
}

uint8_t WiFiDrv::getConnectionStatus()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_CONN_STATUS_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = -1;
  uint8_t _dataLen = 0;
  
  //KH
#if (KH_WIFININA_DRV_DEBUG > 0)
  Serial.println("WiFiDrv-getConnectionStatus");
#endif

  SpiDrv::waitResponseCmd(GET_CONN_STATUS_CMD, PARAM_NUMS_1, &_data, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  //KH
#if (KH_WIFININA_DRV_DEBUG > 0)
  Serial.print("WiFiDrv-getConnectionStatus: _data = ");
  Serial.println(_data);
#endif

  return _data;
}

uint8_t* WiFiDrv::getMacAddress()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_MACADDR_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  SpiDrv::waitResponseCmd(GET_MACADDR_CMD, PARAM_NUMS_1, _mac, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return _mac;
}

void WiFiDrv::getIpAddress(IPAddress& ip)
{
  getNetworkData(_localIp, _subnetMask, _gatewayIp);
  ip = _localIp;
}

void WiFiDrv::getSubnetMask(IPAddress& mask)
{
  getNetworkData(_localIp, _subnetMask, _gatewayIp);
  mask = _subnetMask;
}

void WiFiDrv::getGatewayIP(IPAddress& ip)
{
  getNetworkData(_localIp, _subnetMask, _gatewayIp);
  ip = _gatewayIp;
}

const char* WiFiDrv::getCurrentSSID()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_CURR_SSID_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  memset(_ssid, 0x00, sizeof(_ssid));

  // Wait for reply
  uint8_t _dataLen = 0;
  SpiDrv::waitResponseCmd(GET_CURR_SSID_CMD, PARAM_NUMS_1, (uint8_t*)_ssid, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return _ssid;
}

uint8_t* WiFiDrv::getCurrentBSSID()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_CURR_BSSID_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  SpiDrv::waitResponseCmd(GET_CURR_BSSID_CMD, PARAM_NUMS_1, _bssid, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return _bssid;
}

int32_t WiFiDrv::getCurrentRSSI()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_CURR_RSSI_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  int32_t rssi = 0;
  SpiDrv::waitResponseCmd(GET_CURR_RSSI_CMD, PARAM_NUMS_1, (uint8_t*)&rssi, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  return rssi;
}

uint8_t WiFiDrv::getCurrentEncryptionType()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_CURR_ENCT_CMD, PARAM_NUMS_1);

  uint8_t _dummy = DUMMY_DATA;
  SpiDrv::sendParam(&_dummy, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  uint8_t encType = 0;
  
  SpiDrv::waitResponseCmd(GET_CURR_ENCT_CMD, PARAM_NUMS_1, (uint8_t*)&encType, &dataLen);

  SpiDrv::spiSlaveDeselect();

  return encType;
}

int8_t WiFiDrv::startScanNetworks()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(START_SCAN_NETWORKS, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(START_SCAN_NETWORKS, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }

  SpiDrv::spiSlaveDeselect();

  return ((int8_t)_data == WL_FAILURE) ? _data : (int8_t)WL_SUCCESS;
}


uint8_t WiFiDrv::getScanNetworks()
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(SCAN_NETWORKS, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t ssidListNum = 0;
  SpiDrv::waitResponse(SCAN_NETWORKS, &ssidListNum, (uint8_t**)_networkSsid, WL_NETWORKS_LIST_MAXNUM);

  SpiDrv::spiSlaveDeselect();

  return ssidListNum;
}

const char* WiFiDrv::getSSIDNetoworks(uint8_t networkItem)
{
  if (networkItem >= WL_NETWORKS_LIST_MAXNUM)
    return (char*)NULL;

  return _networkSsid[networkItem];
}

uint8_t WiFiDrv::getEncTypeNetowrks(uint8_t networkItem)
{
  if (networkItem >= WL_NETWORKS_LIST_MAXNUM)
    return ENC_TYPE_UNKNOWN;

  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_IDX_ENCT_CMD, PARAM_NUMS_1);

  SpiDrv::sendParam(&networkItem, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  uint8_t encType = 0;
  
  SpiDrv::waitResponseCmd(GET_IDX_ENCT_CMD, PARAM_NUMS_1, (uint8_t*)&encType, &dataLen);

  SpiDrv::spiSlaveDeselect();

  return encType;
}

uint8_t* WiFiDrv::getBSSIDNetowrks(uint8_t networkItem, uint8_t* bssid)
{
  if (networkItem >= WL_NETWORKS_LIST_MAXNUM)
    return NULL;

  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_IDX_BSSID, PARAM_NUMS_1);

  SpiDrv::sendParam(&networkItem, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  
  SpiDrv::waitResponseCmd(GET_IDX_BSSID, PARAM_NUMS_1, (uint8_t*)bssid, &dataLen);

  SpiDrv::spiSlaveDeselect();

  return bssid;
}

uint8_t WiFiDrv::getChannelNetowrks(uint8_t networkItem)
{
  if (networkItem >= WL_NETWORKS_LIST_MAXNUM)
    return 0;

  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_IDX_CHANNEL_CMD, PARAM_NUMS_1);

  SpiDrv::sendParam(&networkItem, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  uint8_t channel = 0;
  
  SpiDrv::waitResponseCmd(GET_IDX_CHANNEL_CMD, PARAM_NUMS_1, (uint8_t*)&channel, &dataLen);

  SpiDrv::spiSlaveDeselect();

  return channel;
}

int32_t WiFiDrv::getRSSINetoworks(uint8_t networkItem)
{
  if (networkItem >= WL_NETWORKS_LIST_MAXNUM)
    return 0;
    
  int32_t networkRssi = 0;

  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(GET_IDX_RSSI_CMD, PARAM_NUMS_1);

  SpiDrv::sendParam(&networkItem, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  
  SpiDrv::waitResponseCmd(GET_IDX_RSSI_CMD, PARAM_NUMS_1, (uint8_t*)&networkRssi, &dataLen);

  SpiDrv::spiSlaveDeselect();

  return networkRssi;
}

uint8_t WiFiDrv::reqHostByName(const char* aHostname)
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(REQ_HOST_BY_NAME_CMD, PARAM_NUMS_1);
  SpiDrv::sendParam((uint8_t*)aHostname, strlen(aHostname), LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 5 + strlen(aHostname);
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  uint8_t result = SpiDrv::waitResponseCmd(REQ_HOST_BY_NAME_CMD, PARAM_NUMS_1, &_data, &_dataLen);

  SpiDrv::spiSlaveDeselect();

  if (result) 
  {
    result = (_data == 1);
  }

  return result;
}

int WiFiDrv::getHostByName(IPAddress& aResult)
{
  uint8_t  _ipAddr[WL_IPV4_LENGTH];
  IPAddress dummy(0xFF, 0xFF, 0xFF, 0xFF);
  int result = 0;

  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_HOST_BY_NAME_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(GET_HOST_BY_NAME_CMD, PARAM_NUMS_1, _ipAddr, &_dataLen))
  {
    WARN("error waitResponse");
  } 
  else 
  {
    aResult = _ipAddr;
    result = (aResult != dummy);
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return result;
}

int WiFiDrv::getHostByName(const char* aHostname, IPAddress& aResult)
{
  if (reqHostByName(aHostname))
  {
    return getHostByName(aResult);
  } 
  else 
  {
    return 0;
  }
}

const char*  WiFiDrv::getFwVersion()
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_FW_VERSION_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(GET_FW_VERSION_CMD, PARAM_NUMS_1, (uint8_t*)fwVersion, &_dataLen))
  {
    WARN("error waitResponse");
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return fwVersion;
}

uint32_t WiFiDrv::getTime()
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_TIME_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  uint32_t _data = 0;
  
  if (!SpiDrv::waitResponseCmd(GET_TIME_CMD, PARAM_NUMS_1, (uint8_t*)&_data, &_dataLen))
  {
    WARN("error waitResponse");
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

void WiFiDrv::setPowerMode(uint8_t mode)
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(SET_POWER_MODE_CMD, PARAM_NUMS_1);

  SpiDrv::sendParam(&mode, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  uint8_t data = 0;
  
  SpiDrv::waitResponseCmd(SET_POWER_MODE_CMD, PARAM_NUMS_1, &data, &dataLen);

  SpiDrv::spiSlaveDeselect();
}

int8_t WiFiDrv::wifiSetApNetwork(const char* ssid, uint8_t ssid_len, uint8_t channel)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_AP_NET_CMD, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)ssid, ssid_len);
  SpiDrv::sendParam(&channel, 1, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 3 + ssid_len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_AP_NET_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");

//KH
#if (KH_WIFININA_DRV_DEBUG > 0)
    Serial.println("WiFiDrv-wifiSetApNetwork: waitResponseCmd = WL_FAILURE");
#endif

    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();

//KH
#if (KH_WIFININA_DRV_DEBUG > 0)
  Serial.print("WiFiDrv-wifiSetApNetwork: _data = ");
  Serial.println(_data);
#endif

  return (_data == WIFI_SPI_ACK) ? WL_SUCCESS : WL_FAILURE;
}

int8_t WiFiDrv::wifiSetApPassphrase(const char* ssid, uint8_t ssid_len, const char *passphrase, const uint8_t len, uint8_t channel)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_AP_PASSPHRASE_CMD, PARAM_NUMS_3);
  SpiDrv::sendParam((uint8_t*)ssid, ssid_len, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)passphrase, len, NO_LAST_PARAM);
  SpiDrv::sendParam(&channel, 1, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 4 + ssid_len + len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_AP_PASSPHRASE_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

int8_t WiFiDrv::wifiSetEnterprise(uint8_t eapType, const char* ssid, uint8_t ssid_len, const char *username, const uint8_t username_len, const char *password, const uint8_t password_len, const char *identity, const uint8_t identity_len, const char* ca_cert, uint16_t ca_cert_len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_ENT_CMD, PARAM_NUMS_6);
  SpiDrv::sendBuffer(&eapType, sizeof(eapType));
  SpiDrv::sendBuffer((uint8_t*)ssid, ssid_len);
  SpiDrv::sendBuffer((uint8_t*)username, username_len);
  SpiDrv::sendBuffer((uint8_t*)password, password_len);
  SpiDrv::sendBuffer((uint8_t*)identity, identity_len);
  SpiDrv::sendBuffer((uint8_t*)ca_cert, ca_cert_len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 15 + sizeof(eapType) + ssid_len + username_len + password_len + identity_len + ca_cert_len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_ENT_CMD, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

int16_t WiFiDrv::ping(uint32_t ipAddress, uint8_t ttl)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(PING_CMD, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)&ipAddress, sizeof(ipAddress), NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&ttl, sizeof(ttl), LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint16_t _data;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(PING_CMD, PARAM_NUMS_1, (uint8_t*)&_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_PING_ERROR;
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

void WiFiDrv::debug(uint8_t on)
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(SET_DEBUG_CMD, PARAM_NUMS_1);

  SpiDrv::sendParam(&on, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t dataLen = 0;
  uint8_t data = 0;
  
  SpiDrv::waitResponseCmd(SET_DEBUG_CMD, PARAM_NUMS_1, &data, &dataLen);

  SpiDrv::spiSlaveDeselect();
}

float WiFiDrv::getTemperature()
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(GET_TEMPERATURE_CMD, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _dataLen = 0;
  float _data = 0;
  
  if (!SpiDrv::waitResponseCmd(GET_TEMPERATURE_CMD, PARAM_NUMS_1, (uint8_t*)&_data, &_dataLen))
  {
    WARN("error waitResponse");
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

void WiFiDrv::pinMode(uint8_t pin, uint8_t mode)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_PIN_MODE, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)&pin, 1, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&mode, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_PIN_MODE, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
}

// KH, for compatibility with other platforms
//#if defined(ARDUINO_ARCH_MBED)
#if defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARDUINO_NANO_RP2040_CONNECT)
PinStatus WiFiDrv::digitalRead(uint8_t pin)
#else
int WiFiDrv::digitalRead(uint8_t pin)
#endif
{
    WAIT_FOR_SLAVE_SELECT();
    // Send Command
    SpiDrv::sendCmd(GET_DIGITAL_READ, PARAM_NUMS_1);
    SpiDrv::sendParam((uint8_t*)&pin, 1, LAST_PARAM);

    // pad to multiple of 4
    SpiDrv::readChar();
    SpiDrv::readChar();

    SpiDrv::spiSlaveDeselect();
    //Wait the reply elaboration
    SpiDrv::waitForSlaveReady();
    SpiDrv::spiSlaveSelect();

    // Wait for reply
    uint8_t _data = 0;
    uint8_t _dataLen = 0;
    if (!SpiDrv::waitResponseCmd(GET_DIGITAL_READ, PARAM_NUMS_1, &_data, &_dataLen))
    {
        WARN("error waitResponse");
        _data = WL_FAILURE;
    }
    SpiDrv::spiSlaveDeselect();

    if (_data == 1)
        return HIGH;
    else
        return LOW;
}

void WiFiDrv::digitalWrite(uint8_t pin, uint8_t value)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_DIGITAL_WRITE, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)&pin, 1, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&value, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_DIGITAL_WRITE, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
}

uint16_t WiFiDrv::analogRead(uint8_t adc_channel)
{
    WAIT_FOR_SLAVE_SELECT();
    // Send Command
    SpiDrv::sendCmd(GET_ANALOG_READ, PARAM_NUMS_1);
    SpiDrv::sendParam((uint8_t*)&adc_channel, 1, LAST_PARAM);

    // pad to multiple of 4
    SpiDrv::readChar();
    SpiDrv::readChar();

    SpiDrv::spiSlaveDeselect();
    //Wait the reply elaboration
    SpiDrv::waitForSlaveReady();
    SpiDrv::spiSlaveSelect();

    // Wait for reply
    uint16_t adc_raw = 0;
    uint8_t adc_raw_len = 0;
    if (!SpiDrv::waitResponseCmd(GET_ANALOG_READ, PARAM_NUMS_1, (uint8_t*)&adc_raw, &adc_raw_len))
    {
        WARN("error waitResponse");
    }
    SpiDrv::spiSlaveDeselect();

    return adc_raw;
}

void WiFiDrv::analogWrite(uint8_t pin, uint8_t value)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(SET_ANALOG_WRITE, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)&pin, 1, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&value, 1, LAST_PARAM);

  // pad to multiple of 4
  SpiDrv::readChar();

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(SET_ANALOG_WRITE, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
}

int8_t WiFiDrv::downloadFile(const char* url, uint8_t url_len, const char *filename, uint8_t filename_len)
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(DOWNLOAD_FILE, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)url, url_len, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)filename, filename_len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 6 + url_len + filename_len;

  while (commandSize % 4)
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;

  if (!SpiDrv::waitResponseCmd(DOWNLOAD_FILE, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }

  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

// New from v1.7.0
int8_t WiFiDrv::downloadOTA(const char* url, uint8_t url_len)
{
  WAIT_FOR_SLAVE_SELECT();
  // Send Command
  SpiDrv::sendCmd(DOWNLOAD_OTA, PARAM_NUMS_1);
  SpiDrv::sendParam((uint8_t*)url, url_len, LAST_PARAM);

  // pad to multiple of 4
  int commandSize = 5 + url_len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  if (!SpiDrv::waitResponseCmd(DOWNLOAD_OTA, PARAM_NUMS_1, &_data, &_dataLen))
  {
    WARN("error waitResponse");
    _data = WL_FAILURE;
  }
  
  SpiDrv::spiSlaveDeselect();
  
  return _data;
}

//////

int8_t WiFiDrv::renameFile(const char * old_file_name, uint8_t const old_file_name_len, const char * new_file_name, uint8_t const new_file_name_len)
{
  WAIT_FOR_SLAVE_SELECT();
  
  /* Send Command */
  SpiDrv::sendCmd(RENAME_FILE, PARAM_NUMS_2);
  SpiDrv::sendParam((uint8_t*)old_file_name, old_file_name_len, NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)new_file_name, new_file_name_len, LAST_PARAM);

  /* pad to multiple of 4 */
  int commandSize = 6 + old_file_name_len + new_file_name_len;

  while (commandSize % 4)
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  /* Wait the reply elaboration */
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  /* Wait for reply */
  uint8_t data = 0;
  uint8_t dataLen = 0;

  if (!SpiDrv::waitResponseCmd(RENAME_FILE, PARAM_NUMS_1, &data, &dataLen))
  {
    WARN("error waitResponse");
    data = WL_FAILURE;
  }

  SpiDrv::spiSlaveDeselect();

  return data;
}

int8_t WiFiDrv::fileOperation(uint8_t operation, const char *filename, uint8_t filename_len, uint32_t offset, uint8_t* buffer, uint32_t len)
{
  WAIT_FOR_SLAVE_SELECT();
  
  // Send Command
  uint8_t numParams = PARAM_NUMS_3;

  if (operation == WRITE_FILE)
  {
    numParams = PARAM_NUMS_4;
  }

  SpiDrv::sendCmd(operation, numParams);
  SpiDrv::sendParam((uint8_t*)&offset, sizeof(offset), NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)&len, sizeof(len), NO_LAST_PARAM);
  SpiDrv::sendParam((uint8_t*)filename, filename_len, (operation == WRITE_FILE) ? NO_LAST_PARAM : LAST_PARAM);
  
  if (operation == WRITE_FILE) 
  {
    SpiDrv::sendParamNoLen((uint8_t*)buffer, len, LAST_PARAM);
  }

  // pad to multiple of 4
  int commandSize = 4 + numParams + sizeof(offset) + sizeof(len) + filename_len;
  
  while (commandSize % 4) 
  {
    SpiDrv::readChar();
    commandSize++;
  }

  SpiDrv::spiSlaveDeselect();
  //Wait the reply elaboration
  SpiDrv::waitForSlaveReady();
  SpiDrv::spiSlaveSelect();

  // Wait for reply
  uint8_t _data = 0;
  uint8_t _dataLen = 0;
  
  SpiDrv::waitResponseCmd(operation, PARAM_NUMS_1, (operation == WRITE_FILE) ? &_data : buffer, &_dataLen);

  SpiDrv::spiSlaveDeselect();
  
  return _dataLen;
}

void WiFiDrv::applyOTA() 
{
  WAIT_FOR_SLAVE_SELECT();

  // Send Command
  SpiDrv::sendCmd(APPLY_OTA_COMMAND, PARAM_NUMS_0);

  SpiDrv::spiSlaveDeselect();

  // don't wait for return; OTA operation should be fire and forget :)
}

WiFiDrv wiFiDrv;
