#include <Arduino.h>

void sample_time(void);
void calculate_PID(void);

uint32_t last_t = 0;
float error, last_error, error_sum;
float Kp=50.0, Ki=0.0, Kd=0.0;
float up = 0.0, ui = 0.0, ud = 0.0, u;
float r, y;


void setup() {
  TIM_TypeDef *moj_tim = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(moj_tim);
  casovnik->setOverflow(10, HERTZ_FORMAT);
  casovnik->attachInterrupt(sample_time);
  casovnik->resume();
  pinMode(6, OUTPUT);
  Serial.begin(115200);
  r = 800;
}

void loop() {
  delay(3000);
}

void sample_time(void){
  // uint32_t t = micros();
  // uint32_t d = t - last_t;
  // last_t = t;
  // Serial.println(d);
  // digitalWrite(6, !digitalRead(6));
  calculate_PID();
}

void calculate_PID(void){
  float t = millis()/1000.0;
  y = analogRead(A1);
  error = r - y;
  up = error * Kp;

  u = up + ui + ud;
  analogWrite(5, u);

  Serial.print(t); 
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(r);
}