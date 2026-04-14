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

static GPIO_PinState read_btn(const ButtonState *BS){
  switch (BS->id){
    case 1u: return HAL_GPIO_ReadPin(BTN_MULTI_GPIO_Port, BTN_MULTI_Pin);
    case 2u: return HAL_GPIO_ReadPin(BTN_MIN_GPIO_Port,   BTN_MIN_Pin);
    case 3u: return HAL_GPIO_ReadPin(BTN_SEC_GPIO_Port,   BTN_SEC_Pin);
    default: return GPIO_PIN_SET; // safe default
  }
}

static void handle_btn(ButtonState *BS){
  if(!BS->exti) return;

  // debounce
  if((HAL_GetTick() - BS->useTick) < DEBOUNCE_MS) return;
  BS->exti = 0;
  // bool nowActive = (read_btn(BS) == GPIO_PIN_RESET);
  // bool wasActive = BS->isActive;
  // BS->isActive = nowActive;
  // bool debounced = wasActive && !nowActive;

  bool debounced_optmz = (read_btn(BS) == GPIO_PIN_SET);
  if(debounced_optmz){
    GF.led ^= 1;
    led(GF.led);
    countup();
    settime(1);
  }

  // BS->isActive = !debounced;


  // switch(BS.id){
  // case 1u:
  //   /* code */
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
  // TODO
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
