#include "thisoe.h"

void buz(_Bool stat){
  HAL_GPIO_WritePin(GPIOA, BUZ_Pin, stat);
}


void alarm_sound(void){
  for(int i = 0; i < 4; i++)
  {
    buz(1);
    led(1);
    delay(70);
    buz(0);
    led(0);
    delay(70);
  }
  HAL_Delay(700);
}
