#include <Arduino.h>

#define data 8
#define sclk 7
#define lclk 4

void fill_shift_reg(byte left, byte right);
void t_clk(void);
void t_sclk(void);
void t_lclk(void);
void write_num(byte disp_num, byte number, byte dp);
void display(float num);

void setup() {
  pinMode(data, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(lclk, OUTPUT);
  digitalWrite(sclk, LOW);
  digitalWrite(lclk, LOW);
  delay(10);
}

void loop() {
  display(12.22);
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
    digitalWrite(data, right & 0x01);
    right = right >> 1;
    t_sclk();
  }
  for(int n =0; n<8; n++){
    digitalWrite(data, left & 0x01);
    left = left >> 1;
    t_sclk();
  }
}

void write_num(byte disp_num, byte number, byte dp){
  byte nums[11]={0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09,0xff};
  byte levi = 0x01 << (4+disp_num);
  fill_shift_reg(levi, nums[number]&(0xff^dp));
}

void display(float num){
  char str_num[10];
  /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
  dtostrf(num, 4, 3, str_num);
  //sprintf(out,"%s", str_num);
  //Serial.print(str_num);
  int strcnt=0;
  for(int n=0; n<4; n++){
    if(str_num[strcnt+1]=='.'){
      write_num(3-n, str_num[strcnt]-'0', 1);
      delay(2);
      strcnt++;
    }
    else{
      write_num(3-n, str_num[strcnt]-'0', 0);
      delay(2);
    }
    t_lclk();
    strcnt++;
  }
}