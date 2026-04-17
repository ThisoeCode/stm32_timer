#include "thisoe.h"
#include "flag.h"



// ======= TEST (unusable for EXTI buttons) ======= //

GPIO_PinState r_multi(void){
  return HAL_GPIO_ReadPin(BTN,Bmulti);
}
GPIO_PinState r_min(void){
  return HAL_GPIO_ReadPin(BTN,Bmin);
}
GPIO_PinState r_sec(void){
  return HAL_GPIO_ReadPin(BTN,Bsec);
}



// ======= HANDLE BUTTON ======= //

void h_multi(){
  if(GF.countingDown)
    GF.countingDown = 0;
  else if(GF.countingUp)
    GF.countingUp = 0;
  else if(GF.countupMode)
    GF.countingUp = 1u;
  else if(GS.m==0 && GS.s==0){
    GF.countupMode = 1u;
    GF.countingUp = 1u;
  }else
    GF.countingDown = 1u;

  /*** TEST ***/
  // GF.led ^= 1;
  // led(GF.led);
  // countup();
  // settime(1);
}

static bool h_undone(){
  bool undone = 0;
  if(GF.countingDown)
    GF.countingDown = 0;
  else if(GF.countingUp)
    GF.countingUp = 0;
  else{
    GF.countupMode = 0;
    undone = 1u;
  }
  return undone;
}

void h_min(){
  if(h_undone()){
    GS.m = GS.m>=99 ? 0 : GS.m+1;
    memo();
  }
}

void h_sec(){
  if(h_undone()){
    countup();
    memo();
  }
}
