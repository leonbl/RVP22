#include <Arduino.h>

void setup(){
    Serial.begin(9600);
}

void loop(){
    float t = millis()/1000.0;
    uint32_t napetost = analogRead(A2);
    Serial.print(t); 
    Serial.print("\t");
    Serial.println(napetost);
}