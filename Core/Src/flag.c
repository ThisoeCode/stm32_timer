#include "flag.h"

Flag gFlag = {
    .isCountingDown = false,
};

State GS = {0};

void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec){
  GS.TM = seg;
  GS.m = &min;
  GS.s = &sec;
}
