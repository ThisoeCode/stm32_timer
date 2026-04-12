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
GPIO_PinState r_multi(void);
GPIO_PinState r_min(void);
GPIO_PinState r_sec(void);

// void debounce(void);
// void ondown(void);
// void onup(void);


// ======= TM1637 ======= //
void settime(bool colonstat);
/**
 * @returns - Returns `1` when time is up.
 */
bool countdown(void);
void countup(void);


// ======= TIMER WFI CORE ======= //

void thisoe_timer(void);


#endif
