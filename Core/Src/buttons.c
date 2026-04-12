#include "thisoe.h"



// ======= TEST ======= //

GPIO_PinState r_multi(void){
  return HAL_GPIO_ReadPin(BTN,Bmulti);
}
GPIO_PinState r_min(void){
  return HAL_GPIO_ReadPin(BTN,Bmin);
}
GPIO_PinState r_sec(void){
  return HAL_GPIO_ReadPin(BTN,Bsec);
}



// ======= BUTTONS ======= //


