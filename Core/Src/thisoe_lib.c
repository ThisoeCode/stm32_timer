#include "thisoe.h"
#include "flag.h"



// ======= MCU ======= //

void delay(uint32_t ms){
  HAL_Delay(ms);
}

void led(bool stat){
  HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin, !stat);
}



// ======= TM1637 ======= //

static const uint8_t seg_map[11] = {
  0x3F,//0
  0x06,//1
  0x5B,//2
  0x4F,//3
  0x66,//4
  0x6D,//5
  0x7D,//6
  0x07,//7
  0x7F,//8
  0x6F,//9
};

void settime(bool colonstat){
  uint8_t min = GS.m;
  uint8_t sec = GS.s;

  uint8_t buf[4];

  // int to digit
  uint8_t d0 = min/10;
  uint8_t d1 = min%10;
  uint8_t d2 = sec/10;
  uint8_t d3 = sec%10;

  // set each number
  buf[0] = seg_map[d0];
  buf[1] = seg_map[d1];
  buf[2] = seg_map[d2];
  buf[3] = seg_map[d3];

  // set colon
  if(colonstat) buf[1] |= 0x80;
  else buf[1] &= ~0x80;

  tm1637_raw(GS.TM,buf);
}

bool countdown(){
  if(GS.s > 0)
    (GS.s)--;
  else{
    if(GS.m > 0){
      (GS.m)--;
      GS.s = 59;
    }else{ // 00:00
      return 1;
    }
  }
  return 0;
}

void countup(){
  if(GS.m == 99 && GS.s == 59){
    GS.m = 0;
    GS.s = 0;
  }
  // carry SEC
  if(GS.s < 59)
    (GS.s)++;
  else{
    GS.s = 0;
    // carry MIN
    if(GS.m<99)
      (GS.m)++;
    else
      GS.m = 0;
  }
}
