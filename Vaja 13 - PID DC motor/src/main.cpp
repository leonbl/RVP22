#include <Arduino.h>

#define pinAA 4
#define pinAB 5
#define encA  7
#define encB  6

void motor(int8_t hitrost);
void encoder(void);
void prekinitev_pid(void);

float error=0, eSum=0;
float y, u, up=0, ui=0, ud=0;
float r, Period;
float Kp=10, Ki=10;
int8_t u_map;

static int32_t counter = 0;
volatile bool calcPID = false;

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

  uint32_t peri = 1000;
  TIM_TypeDef *moj_tim = TIM3;
  HardwareTimer *casovnik = new HardwareTimer(moj_tim);
  casovnik->setOverflow(peri, MICROSEC_FORMAT);
  casovnik->attachInterrupt(prekinitev_pid);
  casovnik->resume();
  Period = peri/1000000.0;

  MyTim1->setMode(channel1, TIMER_OUTPUT_COMPARE_PWM1, pinAA);
  MyTim1->setOverflow(10000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim1->resume();

  MyTim2->setMode(channel2, TIMER_OUTPUT_COMPARE_PWM1, pinAB);
  MyTim2->setOverflow(10000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  MyTim2->resume();

  MyTim1->setCaptureCompare(channel1, 0, PERCENT_COMPARE_FORMAT);
  MyTim2->setCaptureCompare(channel2, 0, PERCENT_COMPARE_FORMAT);

  attachInterrupt(digitalPinToInterrupt(encA), encoder, RISING);
  Serial.begin(9600);
  motor(27);
  r=1000.0;
}

void loop() {
  if(calcPID == true){  
    y = counter;

    // P
    error = r - y;
    up = Kp * error;
    // I
    eSum += error;
    ui = eSum * Ki * Period;

    u = up + ui + ud;
    if(u>100) u=100;
    if(u<-100) u=-100;
    if(u>0) u_map = map(u, 0, 100, 20, 100 );
    if(u<0) u_map = map(u, 0, -100, -20, -100 );
    motor((int8_t)u_map);
    Serial.print(u_map);
    Serial.print(" ");
    Serial.println(counter);
    calcPID = false;
  }
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
  calcPID = true;
} 