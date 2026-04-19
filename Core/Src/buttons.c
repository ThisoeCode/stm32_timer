#include "thisoe.h"
#include "flag.h"



// ======= TEST (unusable for EXTI buttons) ======= //

// GPIO_PinState r_multi(void){
//   return HAL_GPIO_ReadPin(BTN,Bmulti);
// }
// GPIO_PinState r_min(void){
//   return HAL_GPIO_ReadPin(BTN,Bmin);
// }
// GPIO_PinState r_sec(void){
//   return HAL_GPIO_ReadPin(BTN,Bsec);
// }



// ======= HANDLE BUTTON ======= //

bool h_combo(uint8_t id){
  if(id==1u){
    if(
      read_btn(&B_MIN) == GPIO_PIN_SET ||
      read_btn(&B_SEC) == GPIO_PIN_SET
    ) return 1u;
  }
  if(id==2u || id==3u){
    if(read_btn(&B_MULTI) == GPIO_PIN_SET)
      return 1u;
  }
  return 0;
}

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
  // settime(1u);
}

static bool h_m_s(){
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
  if(h_m_s()){
    GS.m = GS.m>=99 ? 0 : GS.m+1;
    memo();
  }
}

void h_sec(){
  if(h_m_s()){
    countup();
    memo();
  }
}

/** handle longpress */
static void h_lp(ButtonState *BS){
  uint32_t now = HAL_GetTick();
  uint32_t start = BS->useTick + DEBOUNCE_MS + LONGPRESS_MS;
  uint32_t step = now % (ONPRESS_BEEP_PULSE_MS * 2);
  if((now > start) && (step == 0)){
    switch(BS->id){
      case 2u:
        h_min();
        break;
      case 3u:
        h_sec();
        break;
    }
    settime(1u);
    beep();
    led(1u);
  }
}

void longpress(){
  if(read_btn(&B_MIN))
    h_lp(&B_MIN);
  else if(read_btn(&B_SEC))
    h_lp(&B_SEC);
  else{
    GF.longpress = 0;
    led(0);
  }
}