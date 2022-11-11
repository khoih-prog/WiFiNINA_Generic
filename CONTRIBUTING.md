## Contributing to WiFiNINA_Generic

### Reporting Bugs

Please report bugs in WiFiNINA_Generic if you find them.

However, before reporting a bug please check through the following:

* [Existing Open Issues](https://github.com/khoih-prog/WiFiNINA_Generic/issues) - someone might have already encountered this.

If you don't find anything, please [open a new issue](https://github.com/khoih-prog/WiFiNINA_Generic/issues/new).

### How to submit a bug report

Please ensure to specify the following:

* Arduino IDE version (e.g. 1.8.19) or Platform.io version
* Core Version (e.g. Arduino SAMD core v1.8.13, Adafruit SAMD core v1.7.11, Arduino-mbed RP2040 v3.4.1)
* Board type (e.g. NANO_RP2040_CONNECT, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc.)
* Contextual information (e.g. what you were trying to achieve)
* Simplest possible steps to reproduce
* Anything that might be relevant in your opinion, such as:
  * Operating system (Windows, Ubuntu, etc.) and the output of `uname -a`
  * Network configuration


### Example

```
Arduino IDE version: 1.8.19
Arduino-mbed RP2040 v3.4.1
NANO_RP2040_CONNECT Module
OS: Ubuntu 20.04 LTS
Linux xy-Inspiron-3593 5.15.0-52-generic #58~20.04.1-Ubuntu SMP Thu Oct 13 13:09:46 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux

Context:
I encountered a crash while using this library
Steps to reproduce:
1. ...
2. ...
3. ...
4. ...
```

### Additional context

Add any other context about the problem here.

---

### Sending Feature Requests

Feel free to post feature requests. It's helpful if you can explain exactly why the feature would be useful.

There are usually some outstanding feature requests in the [existing issues list](https://github.com/khoih-prog/WiFiNINA_Generic/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement), feel free to add comments to them.

---

### Sending Pull Requests

Pull Requests with changes and fixes are also welcome!

Please use the `astyle` to reformat the updated library code as follows (demo for Ubuntu Linux)

1. Change directory to the library GitHub

```
xy@xy-Inspiron-3593:~$ cd Arduino/xy/WiFiNINA_Generic_GitHub/
xy@xy-Inspiron-3593:~/Arduino/xy/WiFiNINA_Generic_GitHub$
```

2. Issue astyle command

```
xy@xy-Inspiron-3593:~/Arduino/xy/WiFiNINA_Generic_GitHub$ bash utils/restyle.sh
```

