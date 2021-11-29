#include <GyverWDT.h>

/*
   Пример использования watchdog в качестве генератора прерываний
   Зависимость таймаутов от делителей см. в GyverWDT.h
*/

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Watchdog.enable(ISR_MODE, WDT_TIMEOUT_1S); // Режим генерации прерываний , таймаут ~1с
}

void loop() {
  /* Загруженный цикл */
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
  delay(5000);
}

/* Прерывание watchdog */
ISR(WATCHDOG) {
  Serial.println("Hello from interrupt");
}
