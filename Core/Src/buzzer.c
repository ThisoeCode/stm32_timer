#include "thisoe.h"
#include "flag.h"


void buz(bool stat){
  HAL_GPIO_WritePin(
    GPIOA,
    BUZ_Pin,
    stat ? GPIO_PIN_SET : GPIO_PIN_RESET
  );
}


void beep(){
  buz(1u);
  GF.beepOffTick = HAL_GetTick() + ONPRESS_BEEP_PULSE_MS;
}


void beep_update(){
  if((int32_t)(HAL_GetTick() - GF.beepOffTick) >= 0){
    buz(0);
    GF.beepOffTick = 0;
  }
}


void alarm_sound(){
  uint32_t cycle[2] = {
    ALARM_TONE_STEP_MS * 7u, // BEEP BEEP phase
    ALARM_TONE_STEP_MS * 14u, // total cycle
  };
  uint32_t local = (HAL_GetTick() - GF.timeupTick) % cycle[1];

  switch(local){
    // turn ON
    case 1:
    case 2 * ALARM_TONE_STEP_MS:
    case 4 * ALARM_TONE_STEP_MS:
    case 6 * ALARM_TONE_STEP_MS:
      buz(1u);
      break;
    // turn OFF
    case 1 * ALARM_TONE_STEP_MS:
    case 3 * ALARM_TONE_STEP_MS:
    case 5 * ALARM_TONE_STEP_MS:
    case 7 * ALARM_TONE_STEP_MS:
      buz(0);
      break;
  }
  switch(local){
    case 1:
      led(1u);
      settime(1);
      break;
    case 7 * ALARM_TONE_STEP_MS:
      led(0);
      settime(0);
      break;
  }
}
