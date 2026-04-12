#include "thisoe.h"

void buz(bool stat){
  HAL_GPIO_WritePin(GPIOA, BUZ_Pin, stat);
}


void alarm_sound(void){
  // TODO alarm_sound
}
