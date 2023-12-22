This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverwdt
Library for managing WDT on AVR Atmega328P/32U4/2560 & Attiny85/84/167
- Setting the operating mode WDT
- Setting up interruptions

## compatibility
AVR Atmega328P/32U4/2560 & Attiny85/84/167

### Documentation
There is [extended documentation] to the library (https://alexgyver.ru/gyverwdt/)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyverwdt ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverwdt/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
No

<a id="usage"> </a>
## Usage
`` `CPP
VOID Reset (VOID);// Reset
VOID DISABLE (VOID);// Disable WDT
VOID Enable (Uint8_t Mode, Uint8_t PressCaler);// Turn on WDT with settings
// Mode:
// reset_mode - reset during freezing (at a time -out WDT)
// Interrupt_Mode - interruption when freezing (at a time -out WDT)
// Interrupt_Reset_Mode - first timout - interruption, second - reset
// PressCaler:
// wdt_prescaler_2, wdt_prescaler_4 ... wdt_prescaler_1024
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
#include <gyverwdt.h>
#include <avr/sleep.h>

/*
   An example of using Watchdog in the "alarm clock"
   Dependence of Tymauts on dividers, see gyverwdt.h
*/

VOID setup () {
  Pinmode (13, output);
  set_sleep_mode (Sleep_mode_pwr_down);// Select the desired sleep mode
}

VOID loop () {

  / * We blink a LED, and we sleep in pauses */
  DigitalWrite (13, High);

  Watchdog.enable (Interrupt_mode, WDT_PRESCALER_128);// interruption mode, timaut ~ 1c
  Sleep_enable ();// We allow a dream
  Sleep_cpu ();// We go to sleep

  digitalWrite (13, LOW);

  Watchdog.enable (Interrupt_mode, WDT_PRESCALER_128);// interruption mode, timaut ~ 1c
  Sleep_enable ();// We allow sleep
  Sleep_cpu ();// We go to sleep

}

/ * Interruption Watchdog, in it we wake up */
ISR (Watchdog) {
  Sleep_disable ();// We prohibit sleep
  Watchdog.disable ();// Turn off Watchdog
}
`` `

<a id="versions"> </a>
## versions
- V2.1
- v2.2 - optimization and small corrections

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code