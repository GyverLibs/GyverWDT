/*
    Библиотека для управления watchdog таймером, список поддерживаемых МК ниже.
	ВНИМАНИЕ! Использование watchdog с Arduino-загрузчиком версии 'OLD' НЕДОСТУПНО
    Документация: https://alexgyver.ru/gyverwdt/
    GitHub: https://github.com/GyverLibs/GyverWDT
	
    Возможности:
    - Настройка режима работы watchdog
    - Настройка прерываний
    Поддержка МК:
	> AVR ATmega48p/88p/168p/328p (Arduino UNO/NANO/MINI/PRO MINI)
	> AVR ATmega32u4			  (Arduino LEONARDO/PRO MICRO)
	> AVR ATmega1280/2560		  (Arduino MEGA)
	> AVR ATtiny87/167			  (Naked chip)
	> AVR ATtiny45/85			  (Naked chip)
	> AVR ATtiny44/84			  (Naked chip)
	> AVR ATtiny13				  (Naked chip)
	Доступные режимы:
	> RST_MODE (RESET_MODE) 				- Сброс МК при тайм-ауте
	> ISR_MODE (INTERRUPT_MODE) 		 	- Прерывание при тайм-ауте
	> ISR_RST_MODE (INTERRUPT_RESET_MODE) 	- Прерывание при тайм-ауте и переключение в RST_MODE (RESET_MODE)	
		
    Egor 'Nich1con' Zaharov for AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v2.2 ~ 08.11.2021
*/

#ifndef GyverWDT_h
#define GyverWDT_h
#include <Arduino.h>

/************************
* Режим работы watchdog *
************************/
/* Краткие - определения */
#define RST_MODE	  (RESET_MODE)			 // - Сброс МК при тайм-ауте	
#define ISR_MODE	  (INTERRUPT_MODE)		 // - Прерывание при тайм-ауте
#define ISR_RST_MODE  (INTERRUPT_RESET_MODE) // - Прерывание при тайм-ауте и переключение в RST_MODE (RESET_MODE)

/* Legacy - определения */
#define RESET_MODE			  (1 << WDE)	
#define INTERRUPT_MODE		  (1 << WDIE)	
#define INTERRUPT_RESET_MODE  (1 << WDE | 1 << WDIE)
	
/* Вектор прерывания watchdog */
#define	WATCHDOG WDT_vect
/*
  ISR(WATCHDOG){
    ...	 	 
  }
*/


/****************************************************
* Предделители watchdog и приблизительные тайм-ауты *
****************************************************/
/* Выбор по тайм-ауту, примерный разброс ~ 10% */
#define WDT_TIMEOUT_16MS 	(WDT_PRESCALER_2)	 // (16 ± 1.6) ms
#define WDT_TIMEOUT_32MS 	(WDT_PRESCALER_4)    // (32 ± 3.2) ms
#define WDT_TIMEOUT_64MS  	(WDT_PRESCALER_8)    // (64 ± 6.4) ms
#define WDT_TIMEOUT_128MS 	(WDT_PRESCALER_16)   // (128 ± 12.8) ms
#define WDT_TIMEOUT_256MS 	(WDT_PRESCALER_32)   // (256 ± 25.6) ms
#define WDT_TIMEOUT_512MS 	(WDT_PRESCALER_64)   // (512 ± 51.2) ms
#define WDT_TIMEOUT_1S 		(WDT_PRESCALER_128)  // (1024 ± 102.4) ms
#define WDT_TIMEOUT_2S 		(WDT_PRESCALER_256)  // (2048 ± 204.8) ms
#define WDT_TIMEOUT_4S 		(WDT_PRESCALER_512)  // (4096 ± 409.6) ms
#define WDT_TIMEOUT_8S 		(WDT_PRESCALER_1024) // (8192 ± 819.2) ms

/* Выбор по предделителю */
#define WDT_PRESCALER_2		0x00	// (16 ± 1.6) ms
#define WDT_PRESCALER_4		0x01	// (32 ± 3.2) ms
#define WDT_PRESCALER_8		0x02	// (64 ± 6.4) ms
#define WDT_PRESCALER_16	0x03	// (128 ± 12.8) ms
#define WDT_PRESCALER_32	0x04	// (256 ± 25.6) ms
#define WDT_PRESCALER_64	0x05	// (512 ± 51.2) ms
#define WDT_PRESCALER_128	0x06	// (1024 ± 102.4) ms
#define WDT_PRESCALER_256	0x07	// (2048 ± 204.8) ms
#define WDT_PRESCALER_512	0x08	// (4096 ± 409.6) ms
#define WDT_PRESCALER_1024	0x09	// (8192 ± 819.2) ms


/*****************
* Класс watchdog *
*****************/
/*
  Проверка совместимости выбранного МК с библиотекой
*/
#if not (                        \
defined (__AVR_ATmega48P__) ||   \
defined (__AVR_ATmega88P__) ||   \
defined (__AVR_ATmega168P__) ||  \
defined (__AVR_ATmega328P__) ||  \
defined (__AVR_ATmega32u4__) ||  \
defined (__AVR_ATmega1280__) ||  \
defined (__AVR_ATmega2560__) ||  \
defined (__AVR_ATtiny87__) ||    \
defined (__AVR_ATtiny167__) ||   \
defined (__AVR_ATtiny44__) ||    \
defined (__AVR_ATtiny84__) ||    \
defined (__AVR_ATtiny45__) ||    \
defined (__AVR_ATtiny85__) ||    \
defined (__AVR_ATtiny13__))                             
#error "This MCU is not supported in GyverWDT.h library"  
#endif

#if defined(WDTCSR)
#  define _WD_CONTROL_REG     WDTCSR
#elif defined(WDTCR)
#  define _WD_CONTROL_REG     WDTCR
#else
#  define _WD_CONTROL_REG     WDT
#endif

class GyverWDT {
  public:

    void reset() {			 // Сбросить watchdog таймер
      asm volatile ("WDR");	 // ASM команда 'watchdog reset'
    }
    /*
      Watchdog.reset();
      Сбросить watchdog таймер, чтобы избежать тайм-аута
      После вызова watchdog начнет считать заного
      Размещается в коде, после всех ответственных операций
      Можно размещать по своему усмотрению
    */


    void disable() {						// Сбросить watchdog таймер
      uint8_t _SREG_COPY = SREG;			// Сохраняем SREG (и настройки глобальных прерываний)
      noInterrupts();						// Запрещаем глобальные прерывания
      WDTCSR = ((1 << WDCE) | (1 << WDE));  // Разблокировка доступа к watchdog, см. документацию на МК
      WDTCSR = 0x00;						// Очищаем все настройки watchdog
      SREG = _SREG_COPY;					// Возвращаем SREG и прерывания, если они были включены до этого
    }
    /*
      Watchdog.disable();
      Остановить watchdog таймер
      После вызова все настройки watchdog сбросятся
      Размещается в начале setup или main, чтобы избежать bootloop
      Можно использовать перед выполнением долгих атомарных операций
    */


    void enable(uint8_t mode, uint8_t prescaler) {  // Настроить и запустить watchdog таймер
      uint8_t _WDT_REG = mode | ((prescaler > 7) ? ((1 << WDP3) | (prescaler - 8)) : prescaler); // Cоставляем содержимое регистра WDT
      uint8_t _SREG_COPY = SREG;				 	// Сохраняем SREG (и настройки глобальных прерываний)
      noInterrupts();				 				// Запрещаем глобальные прерывания
      WDTCSR = ((1 << WDCE) | (1 << WDE));			// Разблокировка доступа к watchdog, см. документацию на МК
      WDTCSR = _WDT_REG;				 			// Сразу же загружаем готовые настройки watchdog
      SREG = _SREG_COPY;							// Возвращаем SREG и прерывания, если они были включены до этого	
    }
    /*
      Watchdog.enable(mode, prescaler);
      Запустить watchdog таймер с новыми параметрами
      После вызова все настройки watchdog перезапишутся, но счет НЕ сбросится
      Размещается в начале setup или main, и на усмотрение программиста
      Можно использовать перед выполнением ответственных операций

      Доступные режимы (mode):
      RST_MODE (RESET_MODE)                 - Сброс МК при тайм-ауте
      ISR_MODE (INTERRUPT_MODE)             - Прерывание при тайм-ауте
      ISR_RST_MODE (INTERRUPT_RESET_MODE)   - Прерывание при тайм-ауте и переключение в RST_MODE (RESET_MODE)

      Доступные предделители (prescaler):
      WDT_PRESCALER_2    0x00   // (16 ± 1.6) ms
      WDT_PRESCALER_4    0x01   // (32 ± 3.2) ms
      ...
      WDT_PRESCALER_1024  0x09  // (8192 ± 819.2) ms

      Примеры использования:
      ЕСЛИ не вызывать Watchdog.reset();
      Watchdog.enable(RST_MODE, WDT_PRESCALER_128);        - Сбросить МК через ~1с, 
      Watchdog.enable(ISR_MODE, WDT_PRESCALER_2);          - Вызывать прерывание ISR(WATCHDOG){} каждую секунду
      Watchdog.enable(ISR_RST_MODE, WDT_PRESCALER_1024);   - Вызвать прерывание ISR(WATCHDOG){} через ~8с, переключиться в режим RST_MODE 
    */

  private:
};

extern GyverWDT Watchdog;
#endif