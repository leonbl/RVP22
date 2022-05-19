#include <Arduino.h>
#include "QuickPID.h"

#define pinAA 4
#define pinAB 5
#define encA  7
#define encB  6

void motor(int8_t hitrost);
void encoder(void);
void prekinitev_pid(void);

float Setpoint, Input, Output, u;
float Kp = 2, Ki = 5, Kd = 1;
int8_t u_map;

static int32_t counter = 0;

QuickPID myPID(&Input, &Output, &Setpoint);

TIM_TypeDef *Instance1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pinAA), PinMap_PWM);
uint32_t channel1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pinAA), PinMap_PWM));
HardwareTimer *MyTim1 = new HardwareTimer(Instance1);

TIM_TypeDef *Instance2 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pinAB), PinMap_PWM);
uint32_t channel2 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pinAB), PinMap_PWM));
HardwareTimer *MyTim2 = new HardwareTimer(Instance2);

void setup() {
  pinMode(pinAA, OUTPUT);
  pinMode(pinAB, OUTPUT);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);

  TIM_TypeDef *moj_tim = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(moj_tim);
  casovnik->setOverflow(1000, HERTZ_FORMAT);
  casovnik->attachInterrupt(prekinitev_pid);
  casovnik->resume();

  MyTim1->setMode(channel1, TIMER_OUTPUT_COMPARE_PWM1, pinAA);
  MyTim1->setOverflow(500, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim1->resume();

  MyTim2->setMode(channel2, TIMER_OUTPUT_COMPARE_PWM1, pinAB);
  MyTim2->setOverflow(500, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim2->resume();

  MyTim1->setCaptureCompare(channel1, 0, PERCENT_COMPARE_FORMAT);
  MyTim2->setCaptureCompare(channel2, 0, PERCENT_COMPARE_FORMAT);

  attachInterrupt(digitalPinToInterrupt(encA), encoder, RISING);
  Serial.begin(9600);

  //apply PID gains
  myPID.SetTunings(Kp, Ki, Kd);
  //turn the PID on
  myPID.SetMode(myPID.Control::automatic);

  Setpoint = 5000;
  myPID.SetOutputLimits(-100, 100);
}

void loop() {
  Serial.print(u_map);
  Serial.print(" ");
  Serial.println(counter);
  delay(10);
}

void motor(int8_t hitrost){
  if(hitrost == 0){
    MyTim1->setCaptureCompare(channel1, 0, PERCENT_COMPARE_FORMAT);
    MyTim2->setCaptureCompare(channel2, 0, PERCENT_COMPARE_FORMAT);
  }
  else{
    if(hitrost < 0){
      digitalWrite(pinAB, LOW);
      MyTim1->setCaptureCompare(channel1, abs(hitrost), PERCENT_COMPARE_FORMAT);
    }
    else{
      digitalWrite(pinAA, LOW);
      MyTim2->setCaptureCompare(channel2, hitrost, PERCENT_COMPARE_FORMAT);
    }
  }
}

void encoder(void){
  if(digitalRead(encB)==0)
    counter++;
  else 
    counter--;
}

void prekinitev_pid(void){
    Input = counter;
    myPID.Compute();
    u = Output;
    if(u>0) u_map = map(u, 0, 100, 27, 100 );
    if(u<0) u_map = map(u, 0, -100, -50, -100 );
    motor((int8_t)u_map);
}