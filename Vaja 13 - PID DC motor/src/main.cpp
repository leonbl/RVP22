#include <Arduino.h>

#define pinAA 4
#define pinAB 5
#define encA  6
#define encB  7

void motor(uint8_t hitrost, bool smer);
void encoder(void);

static int32_t counter = 0;

void setup() {
  pinMode(pinAA, OUTPUT);
  pinMode(pinAB, OUTPUT);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  attachInterrupt(digitalPinToInterrupt(encA), encoder, RISING);
  Serial.begin(9600);
  motor(100, 0);
}

void loop() {
  // motor(100, 0);
  // delay(5000);
  // motor(100, 1);
  if(counter>1000){
    motor(0, 1);
  }
  Serial.println(counter); 
}

void motor(uint8_t hitrost, bool smer){
  if(hitrost == 0){
    digitalWrite(pinAA, LOW);
    digitalWrite(pinAB, LOW);
  }
  else{
    if(smer == 0){
      digitalWrite(pinAA, HIGH);
      digitalWrite(pinAB, LOW);
    }
    else{
      digitalWrite(pinAB, HIGH);
      digitalWrite(pinAA, LOW);
    }
  }
}

void encoder(void){
  if(digitalRead(encB)==0)
    counter++;
  else 
    counter--;
}