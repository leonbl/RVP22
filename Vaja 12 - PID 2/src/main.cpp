#include <Arduino.h>

void sample_time(void);
void calculate_PID(void);

uint32_t last_t = 0;
double error, last_error, error_sum;
double Kp=0.05, Ki=0.01, Kd=0.02;
double up = 0.0, ui = 0.0, ud = 0.0, u;
double r, y;
// PID calculation frequency
uint32_t PIDf = 1000;
double PIDT = 1/(double)PIDf;

TIM_TypeDef *Instance1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(6), PinMap_PWM);
uint32_t channel1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(6), PinMap_PWM));
HardwareTimer *MyTim1 = new HardwareTimer(Instance1);

void setup() {
  MyTim1->setMode(channel1, TIMER_OUTPUT_COMPARE_PWM1, 6);
  MyTim1->setOverflow(100, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim1->resume();

  TIM_TypeDef *moj_tim = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(moj_tim);
  casovnik->setOverflow(PIDf, HERTZ_FORMAT);
  casovnik->attachInterrupt(sample_time);
  casovnik->resume();
  Serial.begin(115200);
  r = 600;
}

void loop() {
  delay(3000);
}

void sample_time(void){
  calculate_PID();
}

void calculate_PID(void){
  y = analogRead(A0);
  MyTim1->setCaptureCompare(channel1, u, PERCENT_COMPARE_FORMAT);

 

  Serial.print(t); 
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(r);
  Serial.print("\t");
  Serial.println(u);
}