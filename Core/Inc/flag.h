#ifndef FLAG_H
#define FLAG_H

#include "thisoe.h"


typedef struct{
  volatile bool tim2;
  volatile bool colon;
  volatile bool countingDown;
  volatile bool countingUp;
  volatile bool listeningCombo;
} Flag;

typedef struct{
  tm1637_t *TM;
  volatile uint8_t m;
  volatile uint8_t s;
} State;


/**
 * @brief Global Flags
 */
extern Flag GF;

/**
 * @brief Global State
 */
extern State GS;


void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec);


#endif
