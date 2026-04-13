#ifndef FLAG_H
#define FLAG_H

#include "thisoe.h"


typedef struct{
  volatile bool led;
  volatile bool tim2;
  volatile bool colon;
  volatile bool countingUp;
  volatile bool countingDown;
  volatile bool timeUp;
} Flag;

typedef struct{
  tm1637_t *TM;
  volatile uint8_t m;
  volatile uint8_t s;
} State;

typedef struct{
  const uint8_t id;
  volatile uint32_t useTick;
  volatile bool exti;
  // volatile bool isActive;
  // volatile bool isBouncing;
} ButtonState;


/**
 * @brief Global Flags
 */
extern Flag GF;

/**
 * @brief Global State
 */
extern State GS;

/**
 * @brief Global State
 */
extern ButtonState B_MULTI;
extern ButtonState B_MIN;
extern ButtonState B_SEC;


void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec);


#endif
