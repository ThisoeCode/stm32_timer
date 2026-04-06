#ifndef THISOE_LIB
#define THISOE_LIB

// imports & defines
#include "stm32f1xx_hal.h"
#include "main.h"

#define BTN GPIOA
#define Bmulti BTN_MULTI_Pin
#define Bmin BTN_MIN_Pin
#define Bsec BTN_SEC_Pin


// ======= MCU =======
void delay(uint32_t);
void led(_Bool);


// ======= BUZZER =======
void buz(_Bool);

void alarm_sound(void);


// ======= BUTTON =======
GPIO_PinState rmulti(void);
GPIO_PinState rmin(void);
GPIO_PinState rsec(void);

void debounce(void);
void ondown();
void onup();


// ======= LIB =======
void countdown(uint8_t *min, uint8_t *sec);
void countup(uint8_t *min, uint8_t *sec);


#endif
