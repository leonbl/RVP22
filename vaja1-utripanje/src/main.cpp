#include <Arduino.h>
uint32_t cnt = 0;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  if(cnt%100 == 0)
    digitalWrite(10, !digitalRead(10));
  if(cnt%250 == 0)
    digitalWrite(11, !digitalRead(11));
  if(cnt%166 == 0)
    digitalWrite(12, !digitalRead(12));
  delay(1);
  cnt++;
}