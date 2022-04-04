#include <Arduino.h>

int stara_t = 0, stanje_led = 0;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(A1, INPUT);
}

void loop() {
  int test = digitalRead(A1);
  if(test == 0 && stara_t == 1){
    stanje_led = !stanje_led;
    digitalWrite(10, stanje_led);
  }
  stara_t = test;
  delay(50);
}