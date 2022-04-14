#include <Arduino.h>

#if !defined(STM32_CORE_VERSION) || (STM32_CORE_VERSION  < 0x01090000)
#error "Due to API change, this sketch is compatible with STM32_CORE_VERSION  >= 0x01090000"
#endif

// void Update_IT_callback(void)
// { // Update event correspond to Rising edge of PWM when configured in PWM1 mode
//   digitalWrite(13, LOW); // pin2 will be complementary to pin
// }

// void Compare_IT_callback(void)
// { // Compare match event correspond to falling edge of PWM when configured in PWM1 mode
//   digitalWrite(13, HIGH);
// }
  // Automatically retrieve TIM instance and channel associated to pin
  // This is used to be compatible with all STM32 series automatically.
  TIM_TypeDef *Instance1 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(11), PinMap_PWM);
  uint32_t channel1 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(11), PinMap_PWM));
  TIM_TypeDef *Instance2 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(10), PinMap_PWM);
  uint32_t channel2 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(10), PinMap_PWM));
  TIM_TypeDef *Instance3 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(9), PinMap_PWM);
  uint32_t channel3 = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(9), PinMap_PWM));

  // Instantiate HardwareTimer object. 
  // Thanks to 'new' instantiation, HardwareTimer is not destructed when setup function is finished.
  HardwareTimer *MyTim1 = new HardwareTimer(Instance1);
  HardwareTimer *MyTim2 = new HardwareTimer(Instance2);
  HardwareTimer *MyTim3 = new HardwareTimer(Instance3);

void setup()
{
  MyTim1->setMode(channel1, TIMER_OUTPUT_COMPARE_PWM1, 11);
  // MyTim->setPrescaleFactor(8); // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  MyTim1->setOverflow(10000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  //MyTim1->setCaptureCompare(channel1, 80, PERCENT_COMPARE_FORMAT); // 50%
  //MyTim->attachInterrupt(Update_IT_callback);
  //MyTim->attachInterrupt(channel, Compare_IT_callback);
  MyTim1->resume();

  MyTim2->setMode(channel2, TIMER_OUTPUT_COMPARE_PWM1, 10);
  // MyTim->setPrescaleFactor(8); // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  MyTim2->setOverflow(10000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  //MyTim2->setCaptureCompare(channel2, 80, PERCENT_COMPARE_FORMAT); // 50%
  //MyTim->attachInterrupt(Update_IT_callback);
  //MyTim->attachInterrupt(channel, Compare_IT_callback);
  MyTim2->resume();

  MyTim3->setMode(channel3, TIMER_OUTPUT_COMPARE_PWM1, 9);
  // MyTim->setPrescaleFactor(8); // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  MyTim3->setOverflow(10000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  //MyTim3->setCaptureCompare(channel3, 80, PERCENT_COMPARE_FORMAT); // 50%
  //MyTim->attachInterrupt(Update_IT_callback);
  //MyTim->attachInterrupt(channel, Compare_IT_callback);
  MyTim3->resume();
}


void loop()
{
  for(int n=0; n<100; n++){
    MyTim1->setCaptureCompare(channel1, n, PERCENT_COMPARE_FORMAT);
    // MyTim2->setCaptureCompare(channel2, 100-n, PERCENT_COMPARE_FORMAT);
    // MyTim3->setCaptureCompare(channel3, 50, PERCENT_COMPARE_FORMAT);
    delay(50);
  }
}