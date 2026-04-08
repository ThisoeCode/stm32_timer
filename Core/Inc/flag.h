#ifndef FLAG_H
#define FLAG_H

#include "thisoe.h"


typedef struct{
  bool isCountingDown;
} Flag;

extern Flag gFlag;


typedef struct{
  tm1637_t *TM;
  uint8_t *m;
  uint8_t *s;
} State;

/**
 * @brief Global State
 */
extern State GS;

void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec);


#endif
