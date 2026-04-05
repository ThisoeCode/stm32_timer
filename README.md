# Thisoe Timer

As a C-lang driven MCU beginner, I think this project is a good starter. <br>




## Hardware Preparation
- An `STM32F103C8T6` board
- An `ST-LINK/V2` in-circuit debugger
- A `TM1637` 4-digits 7-seg number display
- A `TMB12A05` buzzer
- Some un-debounced buttons
- Some breadboards and wires



## Component Connections & GPIO Settings

### Connections to MCU

| Component | Signal | STM32 Pin | Notes |
|-----------|--------|-----------|-------|
| TM1637    | CLK    | PB6       | Output (bit-bang) |
| TM1637    | DIO    | PB7       | Output (open-drain) |
| BTN_MULTI | OUT    | PA1       | Input, pull-down, active LOW |
| BTN_MIN   | OUT    | PA2       | Input, pull-down, active LOW |
| BTN_SEC   | OUT    | PA3       | Input, pull-down, active LOW |
| TMB12A05  | S      | PA8       | Output (active HIGH) |

### Debugging pins within MCU:

> `.ioc` GUI > Pinout & Config > System Core > `SYS` > Debug:
> Select `Serial Wire`

| Component  | STM32 Pin | Notes |
|------------|-----------|-------|
| `SYS` auto | PA13      | for debugging |
| `SYS` auto | PA14      | for debugging |
| BTN_S2     | PA0       | Input, pull-up, active LOW |
| LED_D2     | PC13      | Output, no pull |

### Power

| Device | 3V3 | GND |
|--------|-----|-----|
| TM1637 | VCC | GND |
| BTNs   | VCC | GND |
| TMB12A05 | (mid pin) | - |

### Notes

- Buttons use **internal pull-up** → pressed = LOW
- TM1637 uses **2-wire proprietary protocol (not I²C)**



## Tests

### Buzzer test

1. Declaration

In `/* USER CODE BEGIN PFP */`:

```c
void alarm_sound(void);
```

2. Implementation

In `/* USER CODE BEGIN 4 */`:

```c
void alarm_sound(void)
{
  for(int i = 0; i < 4; i++)
  {
    HAL_GPIO_WritePin(GPIOA, BUZ_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin, 0);
    HAL_Delay(70);
    HAL_GPIO_WritePin(GPIOA, BUZ_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_D2_GPIO_Port, LED_D2_Pin, 1);
    HAL_Delay(70);
  }
  HAL_Delay(700);
}
```

3. Call in main while loop
```c
alarm_sound();
```


### Buttons debugging

I got only 2 buttons but I have a 3-pin switch (that have 2 states: A-B & B-C).

So I have to make `BTN_MIN` and `BTN_SEC` Pull-down,
so that when floating they won't output as HIGH.


### Try out a `TM1637` driver lib

[TODO](https://github.com/nimaltd/tm1637)


