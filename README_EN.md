This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverWDT.svg?color=brightgreen)](https://github.com/GyverLibs/GyverWDT/releases/latest/download/GyverWDT.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverWDT.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverWDT)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverWDT?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverWDT
WDT management library on AVR ATmega328p/32U4/2560 & ATtiny85/84/167
- Setting up the WDT mode
- Customization of interruptions

### Compatibility
AVR ATmega328p/32U4/2560 & ATtiny85/84/167

### Documentation.
There's a library[extended documentation](https://alexgyver.ru/GyverWDT/)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverWDT** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverWDT/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
No.

<a id="usage"></a>
## Use of use
```cpp
void reset(void);                               // discharge
void disable(void);                             // switch off WDT
void enable(uint8_t mode, uint8_t prescaler);   // switch on WDT with settings
// mode:
// RESET MODE - reset when hovering (during WDT timeout)
// INTERRUPT MODE - interruption when hovering (WDT timeout)
// INTERRUPT RESET MODE - first timeout - interruption, second - reset
// prescaler:
// WDT_PRESCALER_2, WDT_PRESCALER_4... WDT_PRESCALER_1024
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
#include <GyverWDT.h>
#include <avr/sleep.h>

/*
   Пример использования watchdog в "будильника"
   Зависимость таймаутов от делителей см. в GyverWDT.h
*/

void setup() {
  pinMode(13, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Choosing the right sleep mode
}

void loop() {

  /* Мигаем светодиодом , а в паузах спим */
  digitalWrite(13, HIGH);

  Watchdog.enable(INTERRUPT_MODE, WDT_PRESCALER_128); // Interruption mode , timeout ~1c
  sleep_enable();                                     // Allow sleep.
  sleep_cpu();                                        // We sleep.

  digitalWrite(13, LOW);

  Watchdog.enable(INTERRUPT_MODE, WDT_PRESCALER_128); // Interruption mode , timeout ~1c
  sleep_enable();                                     // Allow sleep.
  sleep_cpu();                                        // We sleep.

}

/* Прерывание watchdog , в нем мы просыпаемся */
ISR(WATCHDOG) {
  sleep_disable();     // No sleep.
  Watchdog.disable();  // Turn off watchdog.
}
```

<a id="versions"></a>
## Versions
- v2.1
- v2.2 - Optimization and minor corrections
- v2.3 - Tinni compilation error corrected

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
