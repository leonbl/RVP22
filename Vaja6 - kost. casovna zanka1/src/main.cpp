#include <Arduino.h>
uint32_t starCas = 0, n=0;

void setup() {
  Serial.begin(115200);
  pinMode(9, OUTPUT);
}

void loop() {
  uint32_t cas = millis();
  while((millis() - starCas) < 500);
  Serial.println(millis() - starCas);
  starCas = cas;

  digitalWrite(9, !digitalRead(9));
  Serial.println("To je en dolg niz, ki sem ga sem napisal kar tako malo brezveze !");
  n++;
  if(n%3==0)
    delay(250);

}