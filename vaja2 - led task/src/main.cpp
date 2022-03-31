#include <Arduino.h>
#include <TaskScheduler.h>

void u2Hz(void);
void u3Hz(void);
void u5Hz(void);
void print(void);  

Scheduler runner;
Task utripaj2Hz(250, TASK_FOREVER, &u2Hz);
Task utripaj3Hz(166, TASK_FOREVER, &u3Hz);
Task utripaj5Hz(100, TASK_FOREVER, &u5Hz);
Task izpis(1000, TASK_FOREVER, &print);

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  runner.addTask(utripaj2Hz);
  runner.addTask(utripaj3Hz);
  runner.addTask(utripaj5Hz);
  runner.addTask(izpis);
  utripaj2Hz.enable();
  utripaj3Hz.enable();
  utripaj5Hz.enable();
  izpis.enable();
}

void loop() {
  runner.execute();
}

void u2Hz(void){
  digitalWrite(10, !digitalRead(10));
}

void u3Hz(void){
  digitalWrite(11, !digitalRead(11));
}

void u5Hz(void){
  digitalWrite(12, !digitalRead(12));
}

void print(void){
  Serial.println("Izpis vsako sekundo");
}