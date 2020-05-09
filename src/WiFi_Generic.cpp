/****************************************************************************************************************************
  WiFi_Generic.cpp - Library for Arduino WifiNINA module/shield.
  
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

#include "utility/wifi_drv.h"
#include "WiFi_Generic.h"

extern "C" {
  #include "utility/wl_definitions.h"
  #include "utility/wl_types.h"
  #include "utility/debug.h"
}

WiFiClass::WiFiClass() : _timeout(50000)
{
}

void WiFiClass::init()
{
    WiFiDrv::wifiDriverInit();
}

const char* WiFiClass::firmwareVersion()
{
	return WiFiDrv::getFwVersion();
}

int WiFiClass::begin(const char* ssid)
{
	uint8_t status = WL_IDLE_STATUS;

   if (WiFiDrv::wifiSetNetwork(ssid, strlen(ssid)) != WL_FAILURE)
   {
	   for (unsigned long start = millis(); (millis() - start) < _timeout;)
	   {
		   delay(WL_DELAY_START_CONNECTION);
		   status = WiFiDrv::getConnectionStatus();
		   if ((status != WL_IDLE_STATUS) && (status != WL_NO_SSID_AVAIL) && (status != WL_SCAN_COMPLETED)) {
		     break;
		   }
	   }
   }else
   {
	   status = WL_CONNECT_FAILED;
   }
   return status;
}

int WiFiClass::begin(const char* ssid, uint8_t key_idx, const char *key)
{
	uint8_t status = WL_IDLE_STATUS;

	// set encryption key
   if (WiFiDrv::wifiSetKey(ssid, strlen(ssid), key_idx, key, strlen(key)) != WL_FAILURE)
   {
	   for (unsigned long start = millis(); (millis() - start) < _timeout;)
	   {
		   delay(WL_DELAY_START_CONNECTION);
		   status = WiFiDrv::getConnectionStatus();
		   if ((status != WL_IDLE_STATUS) && (status != WL_NO_SSID_AVAIL) && (status != WL_SCAN_COMPLETED)) {
		     break;
		   }
	   }
   }else{
	   status = WL_CONNECT_FAILED;
   }
   return status;
}

int WiFiClass::begin(const char* ssid, const char *passphrase)
{
	uint8_t status = WL_IDLE_STATUS;

    // set passphrase
    if (WiFiDrv::wifiSetPassphrase(ssid, strlen(ssid), passphrase, strlen(passphrase))!= WL_FAILURE)
    {
	   for (unsigned long start = millis(); (millis() - start) < _timeout;)
 	   {
 		   delay(WL_DELAY_START_CONNECTION);
 		   status = WiFiDrv::getConnectionStatus();
		   if ((status != WL_IDLE_STATUS) && (status != WL_NO_SSID_AVAIL) && (status != WL_SCAN_COMPLETED)) 	    
		   {
		     //KH
		     #if (KH_WIFININA_DEBUG > 2)
         Serial.print("WiFi-begin: return1 = ");
         Serial.println(status);
         #endif
		     break;
		   }
 	   }
    }else{
    	status = WL_CONNECT_FAILED;
    }
    
    //KH
    #if (KH_WIFININA_DEBUG > 2)
    Serial.print("WiFi-begin: return2 = ");
    Serial.println(status);
    #endif
    
    return status;
}

uint8_t WiFiClass::beginAP(const char *ssid)
{
	return beginAP(ssid, 1);
}

uint8_t WiFiClass::beginAP(const char *ssid, uint8_t channel)
{
	uint8_t status = WL_IDLE_STATUS;

   if (WiFiDrv::wifiSetApNetwork(ssid, strlen(ssid), channel) != WL_FAILURE)
   {
	   for (unsigned long start = millis(); (millis() - start) < _timeout;)
	   {
		   delay(WL_DELAY_START_CONNECTION);
		   status = WiFiDrv::getConnectionStatus();
		   if ((status != WL_IDLE_STATUS) && (status != WL_NO_SSID_AVAIL) && (status != WL_SCAN_COMPLETED)) 
		   {
		     //KH
		     #if (KH_WIFININA_DEBUG > 2)
         Serial.print("WiFi-beginAP2: return1 = ");
         Serial.println(status);
         #endif
         
		     break;
		   }
	   }
   }
   else
   {
	   status = WL_AP_FAILED;
   }
   
   //KH
   #if (KH_WIFININA_DEBUG > 2)
   Serial.print("WiFi-beginAP2: return2 = ");
   Serial.println(status);
   #endif
   
   
   return status;
}

uint8_t WiFiClass::beginAP(const char *ssid, const char* passphrase)
{
	return beginAP(ssid, passphrase, 1);
}

uint8_t WiFiClass::beginAP(const char *ssid, const char* passphrase, uint8_t channel)
{
	uint8_t status = WL_IDLE_STATUS;

    // set passphrase
    if (WiFiDrv::wifiSetApPassphrase(ssid, strlen(ssid), passphrase, strlen(passphrase), channel)!= WL_FAILURE)
    {
	   for (unsigned long start = millis(); (millis() - start) < _timeout;)
	   {
 		   delay(WL_DELAY_START_CONNECTION);

 		   status = WiFiDrv::getConnectionStatus();

		   if ((status != WL_IDLE_STATUS) && (status != WL_NO_SSID_AVAIL) && (status != WL_SCAN_COMPLETED)) 
		   {
		     //KH
		     #if (KH_WIFININA_DEBUG > 2)
         Serial.print("WiFi-beginAP3: return1 = ");
         Serial.println(status);
         #endif
         
		     break;
		   }
 	   }
    }
    else
    {
    	status = WL_AP_FAILED;
    }
    
    //KH
    #if (KH_WIFININA_DEBUG > 2)
    Serial.print("WiFi-beginAP3: return2 = ");
    Serial.println(status);
    #endif
    
    return status;
}

uint8_t WiFiClass::beginEnterprise(const char* ssid, const char* username, const char* password)
{
	return beginEnterprise(ssid, username, password, "");
}

uint8_t WiFiClass::beginEnterprise(const char* ssid, const char* username, const char* password, const char* identity)
{
	return beginEnterprise(ssid, username, password, identity, "");
}

uint8_t WiFiClass::beginEnterprise(const char* ssid, const char* username, const char* password, const char* identity, const char* ca)
{
	uint8_t status = WL_IDLE_STATUS;

	// set passphrase
	if (WiFiDrv::wifiSetEnterprise(0 /*PEAP/MSCHAPv2*/, ssid, strlen(ssid), username, strlen(username), password, strlen(password), identity, strlen(identity), ca, strlen(ca) + 1)!= WL_FAILURE)
	{
		for (unsigned long start = millis(); (millis() - start) < _timeout;)
		{
			delay(WL_DELAY_START_CONNECTION);
			status = WiFiDrv::getConnectionStatus();
			if ((status != WL_IDLE_STATUS) && (status != WL_NO_SSID_AVAIL) && (status != WL_SCAN_COMPLETED)) {
				break;
			}
		}
	} else {
		status = WL_CONNECT_FAILED;
	}
	return status;
}

void WiFiClass::config(IPAddress local_ip)
{
	WiFiDrv::config(1, (uint32_t)local_ip, 0, 0);
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server)
{
	WiFiDrv::config(1, (uint32_t)local_ip, 0, 0);
	WiFiDrv::setDNS(1, (uint32_t)dns_server, 0);
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway)
{
	WiFiDrv::config(2, (uint32_t)local_ip, (uint32_t)gateway, 0);
	WiFiDrv::setDNS(1, (uint32_t)dns_server, 0);
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet)
{
	WiFiDrv::config(3, (uint32_t)local_ip, (uint32_t)gateway, (uint32_t)subnet);
	WiFiDrv::setDNS(1, (uint32_t)dns_server, 0);
}

void WiFiClass::setDNS(IPAddress dns_server1)
{
	WiFiDrv::setDNS(1, (uint32_t)dns_server1, 0);
}

void WiFiClass::setDNS(IPAddress dns_server1, IPAddress dns_server2)
{
	WiFiDrv::setDNS(2, (uint32_t)dns_server1, (uint32_t)dns_server2);
}

void WiFiClass::setHostname(const char* name)
{
	WiFiDrv::setHostname(name);
}

int WiFiClass::disconnect()
{
    return WiFiDrv::disconnect();
}

void WiFiClass::end(void)
{
	WiFiDrv::wifiDriverDeinit();
}

uint8_t* WiFiClass::macAddress(uint8_t* mac)
{
	uint8_t* _mac = WiFiDrv::getMacAddress();
	memcpy(mac, _mac, WL_MAC_ADDR_LENGTH);
    return mac;
}
   
IPAddress WiFiClass::localIP()
{
	IPAddress ret;
	WiFiDrv::getIpAddress(ret);
	return ret;
}

IPAddress WiFiClass::subnetMask()
{
	IPAddress ret;
	WiFiDrv::getSubnetMask(ret);
	return ret;
}

IPAddress WiFiClass::gatewayIP()
{
	IPAddress ret;
	WiFiDrv::getGatewayIP(ret);
	return ret;
}

const char* WiFiClass::SSID()
{
    return WiFiDrv::getCurrentSSID();
}

uint8_t* WiFiClass::BSSID(uint8_t* bssid)
{
	uint8_t* _bssid = WiFiDrv::getCurrentBSSID();
	memcpy(bssid, _bssid, WL_MAC_ADDR_LENGTH);
    return bssid;
}

int32_t WiFiClass::RSSI()
{
    return WiFiDrv::getCurrentRSSI();
}

uint8_t WiFiClass::encryptionType()
{
    return WiFiDrv::getCurrentEncryptionType();
}


int8_t WiFiClass::scanNetworks()
{
	uint8_t attempts = 10;
	uint8_t numOfNetworks = 0;

	if (WiFiDrv::startScanNetworks() == WL_FAILURE)
		return WL_FAILURE;
 	do
 	{
 		delay(2000);
 		numOfNetworks = WiFiDrv::getScanNetworks();
 	}
	while (( numOfNetworks == 0)&&(--attempts>0));
	return numOfNetworks;
}

const char* WiFiClass::SSID(uint8_t networkItem)
{
	return WiFiDrv::getSSIDNetoworks(networkItem);
}

int32_t WiFiClass::RSSI(uint8_t networkItem)
{
	return WiFiDrv::getRSSINetoworks(networkItem);
}

uint8_t WiFiClass::encryptionType(uint8_t networkItem)
{
    return WiFiDrv::getEncTypeNetowrks(networkItem);
}

uint8_t* WiFiClass::BSSID(uint8_t networkItem, uint8_t* bssid)
{
	return WiFiDrv::getBSSIDNetowrks(networkItem, bssid);
}

uint8_t WiFiClass::channel(uint8_t networkItem)
{
	return WiFiDrv::getChannelNetowrks(networkItem);
}

uint8_t WiFiClass::status()
{
    return WiFiDrv::getConnectionStatus();
}

uint8_t WiFiClass::reasonCode()
{
	return WiFiDrv::getReasonCode();
}

int WiFiClass::hostByName(const char* aHostname, IPAddress& aResult)
{
	return WiFiDrv::getHostByName(aHostname, aResult);
}

unsigned long WiFiClass::getTime()
{
	return WiFiDrv::getTime();
}

void WiFiClass::lowPowerMode()
{
	WiFiDrv::setPowerMode(1);
}

void WiFiClass::noLowPowerMode()
{
	WiFiDrv::setPowerMode(0);
}

int WiFiClass::ping(const char* hostname, uint8_t ttl)
{
	IPAddress ip;

	if (!hostByName(hostname, ip)) {
		return WL_PING_UNKNOWN_HOST;
	}

	return ping(ip, ttl);
}

int WiFiClass::ping(const String &hostname, uint8_t ttl)
{
	return ping(hostname.c_str(), ttl);
}

int WiFiClass::ping(IPAddress host, uint8_t ttl)
{
	return WiFiDrv::ping(host, ttl);
}

void WiFiClass::setTimeout(unsigned long timeout)
{
	_timeout = timeout;
}
WiFiClass WiFi;
