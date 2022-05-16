#include <Arduino.h>

#define pinAA 4
#define pinAB 5
#define encA  7
#define encB  6

void motor(int8_t hitrost);
void encoder(void);

static int32_t counter = 0;

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

  MyTim1->setMode(channel1, TIMER_OUTPUT_COMPARE_PWM1, pinAA);
  MyTim1->setOverflow(1000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim1->resume();

  MyTim2->setMode(channel2, TIMER_OUTPUT_COMPARE_PWM1, pinAB);
  MyTim2->setOverflow(1000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim2->resume();

  MyTim1->setCaptureCompare(channel1, 0, PERCENT_COMPARE_FORMAT);
  MyTim2->setCaptureCompare(channel2, 0, PERCENT_COMPARE_FORMAT);

  attachInterrupt(digitalPinToInterrupt(encA), encoder, RISING);
  Serial.begin(9600);
  motor(40);
}

void loop() {
  // motor(100, 0);
  // delay(5000);
  // motor(100, 1);
  if(counter>1000){
    motor(0);
  }
  Serial.println(counter); 
}

void motor(int8_t hitrost){
  if(hitrost == 0){
    MyTim1->setCaptureCompare(channel1, 0, PERCENT_COMPARE_FORMAT);
    MyTim2->setCaptureCompare(channel2, 0, PERCENT_COMPARE_FORMAT);
  }
  else{
    if(hitrost < 0){
      MyTim1->setCaptureCompare(channel1, abs(hitrost), PERCENT_COMPARE_FORMAT);
      digitalWrite(pinAB, LOW);
    }
    else{
      MyTim2->setCaptureCompare(channel2, hitrost, PERCENT_COMPARE_FORMAT);
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