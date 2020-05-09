/****************************************************************************************************************************
  WiFiUdp_Generic.h - Library for Arduino WifiNINA module/shield.
  
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

#ifndef WiFiUDP_Generic_h
#define WiFiUDP_Generic_h

#include <Udp.h>

#define UDP_TX_PACKET_MAX_SIZE 24

class WiFiUDP : public UDP {
private:
  uint8_t _sock;  // socket ID for Wiz5100
  uint16_t _port; // local port to listen on
  int _parsed;

public:
  WiFiUDP();  // Constructor
  virtual uint8_t begin(uint16_t);	// initialize, start listening on specified port. Returns 1 if successful, 0 if there are no sockets available to use
  virtual uint8_t beginMulticast(IPAddress, uint16_t);  // initialize, start listening on specified multicast IP address and port. Returns 1 if successful, 0 if there are no sockets available to use
  virtual void stop();  // Finish with the UDP socket

  // Sending UDP packets
  
  // Start building up a packet to send to the remote host specific in ip and port
  // Returns 1 if successful, 0 if there was a problem with the supplied IP address or port
  virtual int beginPacket(IPAddress ip, uint16_t port);
  // Start building up a packet to send to the remote host specific in host and port
  // Returns 1 if successful, 0 if there was a problem resolving the hostname or port
  virtual int beginPacket(const char *host, uint16_t port);
  // Finish off this packet and send it
  // Returns 1 if the packet was sent successfully, 0 if there was an error
  virtual int endPacket();
  // Write a single byte into the packet
  virtual size_t write(uint8_t);
  // Write size bytes from buffer into the packet
  virtual size_t write(const uint8_t *buffer, size_t size);
  
  using Print::write;

  // Start processing the next available incoming packet
  // Returns the size of the packet in bytes, or 0 if no packets are available
  virtual int parsePacket();
  // Number of bytes remaining in the current packet
  virtual int available();
  // Read a single byte from the current packet
  virtual int read();
  // Read up to len bytes from the current packet and place them into buffer
  // Returns the number of bytes read, or 0 if none are available
  virtual int read(unsigned char* buffer, size_t len);
  // Read up to len characters from the current packet and place them into buffer
  // Returns the number of characters read, or 0 if none are available
  virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };
  // Return the next byte from the current packet without moving on to the next byte
  virtual int peek();
  virtual void flush();	// Finish reading the current packet

  // Return the IP address of the host who sent the current incoming packet
  virtual IPAddress remoteIP();
  // Return the port of the host who sent the current incoming packet
  virtual uint16_t remotePort();

  friend class WiFiDrv;
};

#endif    //WiFiUDP_Generic_h
