#include <Arduino.h>

void sample_time(void);
void calculate_PID(void);

uint32_t last_t = 0;
float error, last_error, error_sum;
float Kp=50.0, Ki=0.0, Kd=0.0;
float up = 0.0, ui = 0.0, ud = 0.0, u;
float r, y;

TIM_TypeDef *Instance1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(6), PinMap_PWM);
uint32_t channel1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(6), PinMap_PWM));
HardwareTimer *MyTim1 = new HardwareTimer(Instance1);

void setup() {
  MyTim1->setMode(channel1, TIMER_OUTPUT_COMPARE_PWM1, 6);
  MyTim1->setOverflow(1, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim1->resume();

  TIM_TypeDef *moj_tim = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(moj_tim);
  casovnik->setOverflow(100, HERTZ_FORMAT);
  casovnik->attachInterrupt(sample_time);
  casovnik->resume();
  Serial.begin(115200);
  r = 1000;
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
  y = analogRead(A0);
  error = r - y;
  up = error * Kp;


  u = up + ui + ud;

  if(u>100) u=100;
  else if (u<0) u=0;
  u=500;
  MyTim1->setCaptureCompare(channel1, u, PERCENT_COMPARE_FORMAT);

  Serial.print(t); 
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(r);
  Serial.print("\t");
  Serial.println(u);
}