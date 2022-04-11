#include <Arduino.h>

void prekinitev(void);

void setup() {
  TIM_TypeDef *moj_tim = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(moj_tim);
  casovnik->setOverflow(2, HERTZ_FORMAT);
  casovnik->attachInterrupt(prekinitev);
  casovnik->resume();
  pinMode(10, OUTPUT);
}

void loop() {
  delay(3000);
}

void prekinitev(void){
  digitalWrite(10, !digitalRead(10));
}