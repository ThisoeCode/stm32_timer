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

// config
#define DEBOUNCE_MS 39U
#define ONPRESS_BEEP_PULSE_MS 63U
#define ALARM_TONE_STEP_MS 70U
#define LONGPRESS_MS 900U


// ======= MCU ======= //
void delay(uint32_t);
void led(bool);


// ======= BUZZER ======= //
void buz(bool);
void beep(void);
void beep_update(void);
void alarm_sound(void);


// ======= GPIO_INPUT BUTTONS TEST (unusable for EXTI buttons) ======= //
// GPIO_PinState r_multi(void);
// GPIO_PinState r_min(void);
// GPIO_PinState r_sec(void);


// ======= EXTI BUTTONS ======= //
void h_multi(void);
void h_min(void);
void h_sec(void);
bool h_combo(uint8_t id);

void longpress(void);


// ======= TM1637 ======= //
void settime(bool colonstat);
/**
 * @returns - Returns `1` when time is up.
 */
bool countdown(void);
void countup(void);


// ======= TIMER WFI CORE ======= //

/** 
 * @brief Core logic impl
 */
void thisoe_timer(void);
/** 
 * @brief EXTI handler of MULTI btn
 */
void thisoe_startstop(void);
/** 
 * @brief EXTI handler of MIN/SEC btn
 */
void thisoe_addtime(bool isMin);
/** 
 * @brief Memo current timestamp into `Flag.pinned`
 */
void memo(void);
/** 
 * @brief Reset timer timestamps and states
 */
void reset(void);


#endif
