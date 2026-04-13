#include "thisoe.h"
#include "flag.h"



// ======= TIMER ======= //
static void timeup(){
  GF.countingDown = 0;
  GF.timeUp = 1;
}

static void next_tick(){
  if(GF.countingUp){
    GF.tim2 = 0;
    if(GF.colon)
      countup();
    GF.colon ^= 1;
    settime(GF.colon);
  }
  if(GF.countingDown){
    GF.tim2 = 0;
    if(GF.colon)
      countdown() || (timeup(),0);
    GF.colon ^= 1;
    settime(GF.colon);
  }
}



// ======= BUTTONS ======= //
#define DEBOUNCE_MS 39

static void btn(ButtonState *BS){
  // debounce
  if(HAL_GetTick() - BS->useTick < DEBOUNCE_MS) return;
  BS->exti = 0;

  // TODO delete test:
  GF.led ^= 1;
  led(GF.led);

  // switch(BS.id){
  // case 1u:
  //   BS.
  //   break;

  // case 2u:
  //   /* code */
  //   break;

  // case 3u:
  //   /* code */
  //   break;
    
  // default:
  //   break;
  // }
}

//static void combo(){
//  GS.m = 0;
//  GS.s = 0;
//}

/**
 * @brief External Interrupt Service Routine
 */
static void eisr(ButtonState *BS){
  if(!BS->exti){
    BS->useTick = HAL_GetTick();
    BS->exti = 1;
  }
}



// ======= MAIN ======= //

void thisoe_timer(){
  // TIM
  if(GF.tim2) next_tick();

  // EXTI
  if(B_MULTI.exti) btn(&B_MULTI);
  if(B_MIN.exti) btn(&B_MIN);
  if(B_SEC.exti) btn(&B_SEC);
}

void thisoe_toggle(){
  eisr(&B_MULTI);
}

void thisoe_addtime(bool isMin){
  eisr(isMin ? &B_MIN : &B_SEC);
}
