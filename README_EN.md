This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverWDT
Library for WDT control on AVR ATmega328p/32U4/2560 & ATtiny85/84/167
- Setting the WDT operation mode
- Setting interrupts

### Compatibility
AVR ATmega328p/32U4/2560 & ATtiny85/84/167

### Documentation
The library has [extended documentation](https://alexgyver.ru/GyverWDT/)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GyverWDT** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/GyverWDT/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
Not

<a id="usage"></a>
## Usage
```cpp
void reset(void); // reset
void disable(void); // disable WDT
void enable(uint8_t mode, uint8_t prescaler); // enable WDT with settings
// mode:
// RESET_MODE - reset on hangup (on WDT timeout)
// INTERRUPT_MODE - interrupt on hangup (on WDT timeout)
// INTERRUPT_RESET_MODE - first timeout - interrupt, second - reset
// prescaler:
// WDT_PRESCALER_2, WDT_PRESCALER_4... WDT_PRESCALER_1024
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include <GyverWDT.h>
#include <avr/sleep.h>

/*
   An example of using watchdog in "alarm clock"
   See GyverWDT.h for timeouts versus divisors
*/

void setup() {
  pinMode(13, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Select the desired sleep mode
}

void loop() {

  /* Blink the LED, and sleep in pauses */
  digitalWrite(13, HIGH);

  Watchdog.enable(INTERRUPT_MODE, WDT_PRESCALER_128); // Interrupt mode, timeout ~1s
  sleep_enable(); // Allow sleep
  sleep_cpu(); // Go to sleep

  digitalWrite(13, LOW);

  Watchdog.enable(INTERRUPT_MODE, WDT_PRESCALER_128); // Interrupt mode, timeout ~1s
  sleep_enable(); // Allow sleep
  sleep_cpu(); // Go to sleep

}

/* Watchdog interrupt, we wake up in it */
ISR(WATCHDOG) {
  sleep_disable(); // disable sleep
  watchdog.disable(); // Turn off watchdog
}
```

<a id="versions"></a>
## Versions
- v2.1
- v2.2 - optimization and minor fixes

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!