#include "thisoe.h"


GPIO_PinState rmulti(void){
  return HAL_GPIO_ReadPin(BTN,Bmulti);
}

GPIO_PinState rmin(void){
  return HAL_GPIO_ReadPin(BTN,Bmin);
}

GPIO_PinState rsec(void){
  return HAL_GPIO_ReadPin(BTN,Bsec);
}

void debounce(void){

}

void ondown(){

}

void onup(){

}
