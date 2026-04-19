#ifndef FLAG_H
#define FLAG_H

#include "thisoe.h"


typedef struct{
  /** @brief Is D2 led on */
  volatile bool led;
  /** @brief TIM2 pending */
  volatile bool tim2;
  /** @brief Is TM1637 "colon" on */
  volatile bool colon;
  /** @brief Is counting up */
  volatile bool countingUp;
  /** @brief Was conting up before pause */
  volatile bool countupMode;
  /** @brief Is counting down */
  volatile bool countingDown;
  /** @brief Is timeup alarm ringing */
  volatile bool timeUp;
  /** @brief Timeup alarm starting timestamp */
  volatile uint32_t timeupTick;
  /** @brief Last used timestamp `[min,sec]` */
  volatile uint8_t pinned[2];
  /** @brief Ending timestamp of beeping on button press */
  volatile uint32_t beepOffTick;
  /** @brief Is longpress enabled */
  volatile bool longpress;
} Flag;

typedef struct{
  tm1637_t *TM;
  volatile uint8_t m;
  volatile uint8_t s;
} State;

typedef struct{
  /** @brief 1:MULTI 2:MIN 3:SEC */
  const uint8_t id;
  /** @brief HAL timestamp at rise */
  volatile uint32_t useTick;
  /** @brief EXTI pending */
  volatile bool exti;
} ButtonState;


/**
 * @brief Global Flags
 */
extern Flag GF;

/**
 * @brief Global State
 */
extern State GS;

extern ButtonState B_MULTI;
extern ButtonState B_MIN;
extern ButtonState B_SEC;

void bind_state(tm1637_t *seg, uint8_t min, uint8_t sec);
void bind_btn(ButtonState *BS);

/**
 * @brief Read GPIO pin (HAL)
 */
GPIO_PinState read_btn(ButtonState *BS);

#endif
