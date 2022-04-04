#include <Arduino.h>

#define clk 8
#define sclk 7
#define lclk 4

void fill_shift_reg(byte left, byte right);
void t_clk(void);
void t_sclk(void);
void t_lclk(void);

void setup() {
  pinMode(clk, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(lclk, OUTPUT);
  digitalWrite(clk, LOW);
  digitalWrite(sclk, LOW);
  digitalWrite(lclk, LOW);
}

void loop() {
  fill_shift_reg(0xf0, 0x00);
  t_lclk();
  delay(2000);
}

void t_clk(void){
  digitalWrite(clk, HIGH);
  digitalWrite(clk, LOW);
}

void t_sclk(void){
  digitalWrite(sclk, HIGH);
  digitalWrite(sclk, LOW);
}

void t_lclk(void){
  digitalWrite(lclk, HIGH);
  digitalWrite(lclk, LOW);
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