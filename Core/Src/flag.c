#include "flag.h"

Flag GF = {0};
State GS = {0};
ButtonState B_MULTI = {.id=1u};
ButtonState B_MIN = {.id=2u};
ButtonState B_SEC = {.id=3u};

void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec){
  GS.TM = seg;
  GS.m = min;
  GS.s = sec;

  // init flags
  GF.led = 0;
  GF.tim2 = 0;
  GF.colon = 1u;
  GF.countingDown = 0;
  GF.countingUp = 0;
  GF.countupMode = 0;
  GF.timeUp = 0;
  GF.timeupTick = 0;
  GF.pinned[0] = 0;
  GF.pinned[1] = 0;
  GF.beepOffTick = 0;
  GF.longpress = 0;
}

void bind_btn(ButtonState *BS){
  BS->exti = 0;
  BS->useTick = 0;
}
