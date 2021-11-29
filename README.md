![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# GyverWDT
Библиотека для управления WDT на AVR ATmega328p/32U4/2560 & ATtiny85/84/167
- Настройка режима работы WDT
- Настройка прерываний

### Совместимость
AVR ATmega328p/32U4/2560 & ATtiny85/84/167

### Документация
К библиотеке есть [расширенная документация](https://alexgyver.ru/GyverWDT/)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverWDT** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverWDT/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
Нет

<a id="usage"></a>
## Использование
```cpp
void reset(void);                               // сброс
void disable(void);                             // отключить WDT
void enable(uint8_t mode, uint8_t prescaler);   // включить WDT с настройками
// mode:
// RESET_MODE - сброс при зависании (при тайм-ауте WDT)
// INTERRUPT_MODE - прерывание при зависании (при тайм-ауте WDT)
// INTERRUPT_RESET_MODE - первый таймаут - прерывание, второй - сброс
// prescaler:
// WDT_PRESCALER_2, WDT_PRESCALER_4... WDT_PRESCALER_1024
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
#include <GyverWDT.h>
#include <avr/sleep.h>

/*
   Пример использования watchdog в "будильника"
   Зависимость таймаутов от делителей см. в GyverWDT.h
*/

void setup() {
  pinMode(13, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Выбираем нужный режим сна
}

void loop() {

  /* Мигаем светодиодом , а в паузах спим */
  digitalWrite(13, HIGH);

  Watchdog.enable(INTERRUPT_MODE, WDT_PRESCALER_128); // Режим прерываний , таймаут ~1c
  sleep_enable();                                     // Разрешаем сон
  sleep_cpu();                                        // Уходим в сон

  digitalWrite(13, LOW);

  Watchdog.enable(INTERRUPT_MODE, WDT_PRESCALER_128); // Режим прерываний , таймаут ~1c
  sleep_enable();                                     // Разрешаем сон
  sleep_cpu();                                        // Уходим в сон

}

/* Прерывание watchdog , в нем мы просыпаемся */
ISR(WATCHDOG) {
  sleep_disable();     // Запрещаем сон
  Watchdog.disable();  // Выключаем watchdog
}
```

<a id="versions"></a>
## Версии
- v2.1
- v2.2 - оптимизация и мелкие исправления

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!