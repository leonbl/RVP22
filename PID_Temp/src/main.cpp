#include <Arduino.h>

uint32_t cas;
int32_t u;
uint32_t dt = 100;
float t = (float)dt/1000.0;
float r = 40.0, e, up, ui, ud, sumE=0.0, epr=0.0;
float Kp=100.0, Kd=10.0, Ki=1.0;

uint32_t Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(115200);
}

void loop() {
  while((millis() - cas) < dt);
  cas = millis();
  //digitalWrite(6, !digitalRead(6));

  Vo = analogRead(A1);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  e = r - T;
  up = Kp * e; 

  sumE += e * t;
  ui = Ki * sumE;

  ud = Kd * (e - epr)/t;

  u = up + ui + ud;

  if(u>255) u=255;
  else if(u<0) u = 0;

  analogWrite(5, (int)u);

  Serial.print(T);
  Serial.print('\t');
  Serial.println(u);

  epr = e;


}