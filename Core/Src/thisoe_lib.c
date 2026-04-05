#include "thisoe.h"

void delay(uint32_t ms){
  HAL_Delay(ms);
}

void led(_Bool stat){
  HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin, !stat);
}
