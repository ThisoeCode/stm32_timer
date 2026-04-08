#ifndef THISOE_LIB
#define THISOE_LIB

#define bool _Bool

// imports & defines //
#include "stm32f1xx_hal.h"
#include "main.h"
#include "tm1637.h"

#define BTN GPIOA
#define Bmulti BTN_MULTI_Pin
#define Bmin BTN_MIN_Pin
#define Bsec BTN_SEC_Pin


// ======= MCU ======= //
void delay(uint32_t);
void led(bool);


// ======= BUZZER ======= //
void buz(bool);

void alarm_sound(void);


// ======= BUTTON ======= //
GPIO_PinState rmulti(void);
GPIO_PinState rmin(void);
GPIO_PinState rsec(void);

// void debounce(void);
// void ondown(void);
// void onup(void);


// ======= TM1637 ======= //
bool settime(bool colonstat);
/**
 * @brief If time is up, return `0xf`.
 */
uint8_t countdown(void);
bool countup(void);


// ======= TIMER CORE ======= //




#endif
