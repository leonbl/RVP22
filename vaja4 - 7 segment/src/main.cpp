#include <Arduino.h>

#define clk 8
#define sclk 7
#define lclk 4

void fill_shift_reg(byte left, byte right);
void t_clk(void);
void t_sclk(void);
void t_lclk(void);
void write_num(byte disp_num, byte number);

void setup() {
  pinMode(clk, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(lclk, OUTPUT);
  digitalWrite(clk, LOW);
  digitalWrite(sclk, LOW);
  digitalWrite(lclk, LOW);
  delay(10);
}

void loop() {
  write_num(3, 5);
  t_lclk();
  delay(2000);
}

void t_clk(void){
  digitalWrite(clk, HIGH);
  delay(1);
  digitalWrite(clk, LOW);
  delay(1);
}

void t_sclk(void){
  digitalWrite(sclk, HIGH);
  delay(1);
  digitalWrite(sclk, LOW);
  delay(1);
}

void t_lclk(void){
  digitalWrite(lclk, HIGH);
  delay(1);
  digitalWrite(lclk, LOW);
  delay(1);
}

void fill_shift_reg(byte left, byte right){
  for(int n =0; n<8; n++){
    digitalWrite(clk, right & 0x01);
    right = right >> 1;
    t_sclk();
  }
  for(int n =0; n<8; n++){
    digitalWrite(clk, left & 0x01);
    left = left >> 1;
    t_sclk();
  }
}

void write_num(byte disp_num, byte number){
  byte nums[10]={0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};
  byte levi = 0x01 << (4+disp_num);
  fill_shift_reg(levi, nums[number]);
}