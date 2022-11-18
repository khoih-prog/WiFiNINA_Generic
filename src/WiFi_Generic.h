/**********************************************************************************************************************************
  WiFi_Generic.h - Library for Arduino WiFiNINA module/shield.

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

// To eliminate FW warning when using not latest nina-fw version
// To use whenever WiFi101-FirmwareUpdater-Plugin is not sync'ed with nina-fw version
#if !defined(WIFI_FIRMWARE_LATEST_VERSION)
  //#define WIFI_FIRMWARE_LATEST_VERSION        "1.5.0"
  #define WIFI_FIRMWARE_LATEST_VERSION        "1.4.8"
#endif

#define WIFI_HAS_FEED_WATCHDOG_FUNC

#define WIFININA_GENERIC_VERSION                "WiFiNINA_Generic v1.8.15-1"

#define WIFININA_GENERIC_VERSION_MAJOR          1
#define WIFININA_GENERIC_VERSION_MINOR          8
#define WIFININA_GENERIC_VERSION_PATCH          15
#define WIFININA_GENERIC_VERSION_PATCH_MINOR    1

#define WIFININA_GENERIC_VERSION_INT            1008015001

#include <inttypes.h>

extern "C"
{
#include "utility/wl_definitions.h"
#include "utility/wl_types.h"
}

#include "IPAddress.h"

#include "WiFiClient_Generic.h"
#include "WiFiSSLClient_Generic.h"
#include "WiFiServer_Generic.h"
#include "WiFiStorage_Generic.h"

typedef void(*FeedHostProcessorWatchdogFuncPointer)();

////////////////////////////////////////

class WiFiClass
{
  private:

    static void     init();
    unsigned long   _timeout;
    FeedHostProcessorWatchdogFuncPointer _feed_watchdog_func;

  public:
    WiFiClass();

    /*
       Get firmware version
    */
    static const char* firmwareVersion();


    /* Start WiFi connection for OPEN networks

       param ssid: Pointer to the SSID string.
    */
    int begin(const char* ssid);

    /* Start WiFi connection with WEP encryption.
       Configure a key into the device. The key type (WEP-40, WEP-104)
       is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).

       param ssid: Pointer to the SSID string.
       param key_idx: The key index to set. Valid values are 0-3.
       param key: Key input buffer.
    */
    int begin(const char* ssid, uint8_t key_idx, const char* key);

    /* Start WiFi connection with passphrase
       the most secure supported mode will be automatically selected

       param ssid: Pointer to the SSID string.
       param passphrase: Passphrase. Valid characters in a passphrase
              must be between ASCII 32-126 (decimal).
    */
    int begin(const char* ssid, const char *passphrase);

    uint8_t beginAP(const char *ssid);
    uint8_t beginAP(const char *ssid, uint8_t channel);
    uint8_t beginAP(const char *ssid, const char* passphrase);
    uint8_t beginAP(const char *ssid, const char* passphrase, uint8_t channel);

    uint8_t beginEnterprise(const char* ssid, const char* username, const char* password);
    uint8_t beginEnterprise(const char* ssid, const char* username, const char* password, const char* identity);
    uint8_t beginEnterprise(const char* ssid, const char* username, const char* password, const char* identity,
                            const char* ca);

    /* Change Ip configuration settings disabling the dhcp client

          param local_ip:   Static ip configuration
    */
    void config(IPAddress & local_ip);

    /* Change Ip configuration settings disabling the dhcp client

          param local_ip:   Static ip configuration
      param dns_server:     IP configuration for DNS server 1
    */
    void config(IPAddress & local_ip, IPAddress & dns_server);

    /* Change Ip configuration settings disabling the dhcp client

          param local_ip:   Static ip configuration
      param dns_server:     IP configuration for DNS server 1
          param gateway :   Static gateway configuration
    */
    void config(IPAddress & local_ip, IPAddress & dns_server, IPAddress & gateway);

    /* Change Ip configuration settings disabling the dhcp client

          param local_ip:   Static ip configuration
      param dns_server:     IP configuration for DNS server 1
          param gateway:  Static gateway configuration
          param subnet:   Static Subnet mask
    */
    void config(IPAddress & local_ip, IPAddress & dns_server, IPAddress & gateway, IPAddress & subnet);

    /* Change DNS Ip configuration

       param dns_server1: ip configuration for DNS server 1
    */
    void setDNS(IPAddress & dns_server1);

    /* Change DNS Ip configuration

       param dns_server1: ip configuration for DNS server 1
       param dns_server2: ip configuration for DNS server 2

    */
    void setDNS(IPAddress & dns_server1, IPAddress & dns_server2);


    /* Set the hostname used for DHCP requests

       param name: hostname to set

    */
    void setHostname(const char* name);

    /*
       Disconnect from the network

       return: one value of wl_status_t enum
    */
    int disconnect();

    void end();

    /*
       Get the interface MAC address.

       return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
    */
    uint8_t* macAddress(uint8_t* mac);

    /*
       Get the interface IP address.

       return: Ip address value
    */
    IPAddress localIP();

    /*
       Get the interface subnet mask address.

       return: subnet mask address value
    */
    IPAddress subnetMask();

    /*
       Get the gateway ip address.

       return: gateway ip address value
    */
    IPAddress gatewayIP();

    /*
       Return the current SSID associated with the network

       return: ssid string
    */
    const char* SSID();

    /*
        Return the current BSSID associated with the network.
        It is the MAC address of the Access Point

        return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
    */
    uint8_t* BSSID(uint8_t* bssid);

    /*
        Return the current RSSI /Received Signal Strength in dBm)
        associated with the network

        return: signed value
    */
    int32_t RSSI();

    /*
        Return the Encryption Type associated with the network

        return: one value of wl_enc_type enum
    */
    uint8_t encryptionType();

    /*
       Start scan WiFi networks available

       return: Number of discovered networks
    */
    int8_t scanNetworks();

    /*
       Return the SSID discovered during the network scan.

       param networkItem: specify from which network item want to get the information

       return: ssid string of the specified item on the networks scanned list
    */
    const char* SSID(uint8_t networkItem);

    /*
       Return the encryption type of the networks discovered during the scanNetworks

       param networkItem: specify from which network item want to get the information

       return: encryption type (enum wl_enc_type) of the specified item on the networks scanned list
    */
    uint8_t encryptionType(uint8_t networkItem);

    uint8_t* BSSID(uint8_t networkItem, uint8_t* bssid);
    uint8_t channel(uint8_t networkItem);

    /*
       Return the RSSI of the networks discovered during the scanNetworks

       param networkItem: specify from which network item want to get the information

       return: signed value of RSSI of the specified item on the networks scanned list
    */
    int32_t RSSI(uint8_t networkItem);

    /*
       Return Connection status.

       return: one of the value defined in wl_status_t
    */
    uint8_t status();

    /*
       Return The deauthentication reason code.

       return: the deauthentication reason code
    */
    uint8_t reasonCode();

    /*
       Resolve the given hostname to an IP address.
       param aHostname: Name to be resolved
       param aResult: IPAddress structure to store the returned IP address
       result: 1 if aIPAddrString was successfully converted to an IP address,
                else error code
    */
    int hostByName(const char* aHostname, IPAddress& aResult);

    unsigned long getTime();

    void lowPowerMode();
    void noLowPowerMode();

    int ping(const char* hostname, uint8_t ttl = 128);
    int ping(const String &hostname, uint8_t ttl = 128);
    int ping(IPAddress & host, uint8_t ttl = 128);

    void setTimeout(unsigned long timeout);

    void setFeedWatchdogFunc(FeedHostProcessorWatchdogFuncPointer func);
    void feedWatchdog();
};

////////////////////////////////////////

extern WiFiClass WiFi;
