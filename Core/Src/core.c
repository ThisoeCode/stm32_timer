#include "thisoe.h"
#include "flag.h"



// ======= TIMER ======= //
static void timeup(){
  settime(1u);
  GF.countingDown = 0;
  GF.timeUp = 1u;
}

static void next_tick(){
  if(GF.countingUp){
    GF.tim2 = 0;
    if(GF.colon)
      countup();
    GF.colon ^= 1;
    settime(!GF.colon);
  }
  if(GF.countingDown){
    GF.tim2 = 0;
    if(GF.colon)
      countdown() || (timeup(),0);
    GF.colon ^= 1;
    settime(!GF.colon);
  }
}



// ======= BUTTONS ======= //

static void handle_btn(ButtonState *BS){
  if(!BS->exti) return;

  /*** debounce ***/
  if((HAL_GetTick() - BS->useTick) < DEBOUNCE_MS) return;
  // bool nowActive = (read_btn(BS) == GPIO_PIN_RESET);
  // bool wasActive = BS->isActive;
  // BS->isActive = nowActive;
  // bool debounced = wasActive && !nowActive;

  bool level = (read_btn(BS) == GPIO_PIN_SET);
  if(!level) return;
  BS->exti = 0;

  /*** MAIN HANDLE ***/
  // 1. Timeup confirmation
  if(GF.timeUp){
    GF.timeUp = 0;
    GS.m = GF.pinned[0];
    GS.s = GF.pinned[1];
    settime(1u);
    return;
  }
  // 2. Handle combo
  if(h_combo(BS->id)){
    reset();
    return;
  }
  // 3. Others
  switch(BS->id){
  case 1u:
    h_multi();
    break;
  case 2u:
    h_min();
    break;
  case 3u:
    h_sec();
    break;
  // default:
  //   break;
  }
  settime(1u);

  // BS->isActive = !debounced;

}

//static void combo(){
  // TODO
//}

/**
 * @brief External Interrupt Service Routine
 */
static void eisr(ButtonState *BS){
  if(!BS->exti){
    BS->useTick = HAL_GetTick();
    BS->exti = 1u;
  }
}



// ======= MAIN ======= //

/** 
 * @brief main while loop
 */
void thisoe_timer(){
  // TIM
  if(GF.tim2) next_tick();

  // EXTI
  if(B_MULTI.exti) handle_btn(&B_MULTI);
  if(B_MIN.exti) handle_btn(&B_MIN);
  if(B_SEC.exti) handle_btn(&B_SEC);
}

void thisoe_startstop(){
  eisr(&B_MULTI);
}

void thisoe_addtime(bool isMin){
  eisr(isMin ? &B_MIN : &B_SEC);
}
