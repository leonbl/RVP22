#include <Arduino.h>

void setup() {
  pinMode(10, OUTPUT);
  pinMode(A1, INPUT);
}

void loop() {
  int tipka = digitalRead(A1);
  if(tipka == 1){
    digitalWrite(10, HIGH);
  }
  else {
    digitalWrite(10, LOW);
  }
}