#include "flag.h"

Flag GF = {0};
State GS = {0};

void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec){
  GS.TM = seg;
  GS.m = min;
  GS.s = sec;

  // init flags
  GF.tim2 = 0;
  GF.colon = 1u;
  GF.countingDown = 0;
  GF.countingUp = 0;
  GF.listeningCombo = 0;
}
