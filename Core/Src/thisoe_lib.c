#include "thisoe.h"

void delay(uint32_t ms){
  HAL_Delay(ms);
}

void led(_Bool stat){
  HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin, !stat);
}

void countdown(uint8_t *min, uint8_t *sec){
  if(!min || !sec) return;
  // 
  if(*sec > 0){
    (*sec)--;
  }else{
    if(*min > 0){
      (*min)--;
      *sec = 59;
    }else{
    // 00:00
      alarm_sound();
    }
  }
}

void countup(uint8_t *min, uint8_t *sec){
  if(!min || !sec)return;

  if(*min == 99 && *sec == 59){
    *min = 0;
    *sec = 0;
    return;
  }
  // carry SEC
  if(*sec < 59){
    (*sec)++;
  }else{
    *sec = 0;
    // carry MIN
    if(*min<99){
      (*min)++;
    }else{
      *min = 0;
    }
  }
}