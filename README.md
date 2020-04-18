## WiFiNINA_Generic ( Library for WiFiNINA modules/shields to support many more boards )

[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiNINA_Generic.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiNINA_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiNINA_Generic.svg)](http://github.com/khoih-prog/WiFiNINA_Generic/issues)

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.

## Features

With this library you can instantiate Servers, Clients and send/receive UDP packets through WiFiNINA. The board can connect either to open or encrypted networks (WEP, WPA). The IP address can be assigned statically or through a DHCP. The library can also manage DNS.


## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Teensy core 1.51 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 4. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 7. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 

## Quick Start

### Manual Install

Another way to install is to:

1. Navigate to [WiFiNINA_Generic](https://github.com/khoih-prog/WiFiNINA_Generic) page.
2. Download the latest release `WiFiNINA_Generic-master.zip`.
3. Extract the zip file to `WiFiNINA_Generic-master` directory 
4. Copy whole `WiFiNINA_Generic-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### Using

See examples : 
 1. [AP_SimpleWebServer](examples/AP_SimpleWebServer)
 2. [ConnectNoEncryption](examples/ConnectNoEncryption)
 3. [ConnectWithWEP](examples/ConnectWithWEP)
 4. [ConnectWithWPA](examples/ConnectWithWPA)
 5. [ConnectWithWPA2Enterprise](examples/ConnectWithWPA2Enterprise)
 6. [ScanNetworks](examples/ScanNetworks)
 7. [ScanNetworksAdvanced](examples/ScanNetworksAdvanced)
 8. [SimpleWebServerWiFi](examples/SimpleWebServerWiFi)
 9. [WiFiChatServer](examples/WiFiChatServer)
10. [WiFiPing](examples/WiFiPing)
11. [WiFiSSLClient](examples/WiFiSSLClient)
12. [WiFiUdpNtpClient](examples/WiFiUdpNtpClient)
13. [WiFiUdpSendReceiveString](examples/WiFiUdpSendReceiveString)
14. [WiFiWebClient](examples/WiFiWebClient)
15. [WiFiWebClientRepeating](examples/WiFiWebClientRepeating)
16. [WiFiWebServer](examples/WiFiWebServer)


#### Sample Code

[WiFiWebServer example](examples/WiFiWebServer)

```cpp
#include <SPI.h>
#include <WiFiNINA_Generic.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "****";        // your network SSID (name)
char pass[] = "********";    // your network password (use for WPA, or use as key for WEP), length must be 8+
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() 
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    //delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop()
{
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
```

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `WiFiNINA module/shield firmware 1.3.0+` or this library version.

Sometimes, the library will only work if you update the `WiFiNINA module/shield` core to the newer or older version because some function compatibility.

### TO DO

1. Add support to many more boards still not working

#### New in v1.5.0

1. The original [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) only supports very limited boards, such as: the Arduino MKR WiFi 1010, Arduino MKR VIDOR 4000 and Arduino UNO WiFi Rev.2. This library is based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA) to provide support for many more boards, such as SAM DUE, SAMD21, SAMD51, Teensy, AVR Mega, STM32, etc.

### Contributions and thanks

1. Based on and modified from [Arduino WiFiNINA library](http://www.arduino.cc/en/Reference/WiFiNINA)

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright

1. Copyright (c) 2018 Arduino SA. All rights reserved.
2. Copyright (c) 2011-2014 Arduino LLC. All right reserved.
3. Copyright 2020- Khoi Hoang


