# Thisoe Timer

As a C-lang driven MCU beginner, I think this project is a good starter. <br>




## Hardware Preparation
- An `STM32F103C8T6`
- An `ST-LINK/V2` ICD (in-circuit debugger)
- A `TM1637` 4-digits 7-seg number display with a colon
- A `TMB12A05` buzzer
- Some un-debounced buttons
- Some breadboards and wires



## Component Connections & GPIO Settings

### Connections to MCU

| Component | Signal | STM32 Pin | Notes |
|-----------|--------|-----------|-------|
| TM1637    | CLK    | PB6       | Output (bit-bang) |
| TM1637    | DIO    | PB7       | Output (open-drain) |
| BTN_MULTI | OUT    | PA1       | `GPIO_EXTI` Rising-edge (`GPIO_Input` when test),<br>pull-down, active LOW |
| BTN_MIN   | OUT    | PA2       | `GPIO_EXTI` Rising-edge (`GPIO_Input` when test),<br>pull-down, active LOW |
| BTN_SEC   | OUT    | PA3       | `GPIO_EXTI` Rising-edge (`GPIO_Input` when test),<br>pull-down, active LOW |
| TMB12A05  | S      | PA8       | Output (active HIGH) |

### Debugging pins within MCU:

> `.ioc` GUI > `Pinout & Config` > `System Core` > `SYS` > Debug:
> Select `Serial Wire`

| Component  | STM32 Pin | Notes |
|------------|-----------|-------|
| `SYS` auto | `PA13`    | for debugging |
| `SYS` auto | `PA14`    | for debugging |
| BTN_S2     | `PA0`     | Input, pull-up, active LOW |
| LED_D2     | `PC13`    | Output, no pull |

### Power

| Device |  3V3  |  GND  |
|--------|-------|-------|
| TM1637 | `VCC` | `GND` |
| BTNs   | `VCC` | `GND` |
| TMB12A05 | (mid pin) | `-` |



## Hardware tests

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

I had to make `BTN_MIN` and `BTN_SEC` Pull-down,
so that when floating they won't output any signals.


### Try out a `TM1637` driver lib

[`nimaltd/tm1637`](https://github.com/nimaltd/tm1637)

> ChatGPT provided me the `seg_map` as follow:
> ```c
> static const uint8_t seg_map[11] = {
>   0x3F,//0
>   0x06,//1
>   0x5B,//2
>   0x4F,//3
>   0x66,//4
>   0x6D,//5
>   0x7D,//6
>   0x07,//7
>   0x7F,//8
>   0x6F,//9
> };
> ```
> so that I can control the board seg-precisely,
> with `tm1637_raw()`from nimaltd's driver.

I added a `flag.c` to share the current `min` and `sec` state across files.
Also prepared a place for flags in future coding of the core logic.



## Prepare for `__WFI()`

I want a pure interrupt-driven firmware.

To do this,
**add `__WFI();` inside the main while loop**.

Now the `HAL_Delay()` will ruin the timer's normal functionality,
so get rid of them all with their related logics from now on.



### Clock configuration

Since there is a 8 MHz crystal on board, let's use it.

- Setup HSE

In `.ioc` > `Pinout Config` > `System Core` > `RCC`, find `High Speed Clock` and select `Crystal/Ceramic Resonator`.

Then in `Clock Config`:

| Setting    | Value  |
| ---------- | ------ |
| HSE Input  | 8 MHz  |
| PLL Source | HSE    |
| PLLMul     | x9     |
| System Clock Mux | PLLCLK  |
| SYSCLK     | 72 MHz |
| HCLK       | 72 MHz |
| APB1       | / 2 (resulting 36 MHz) |

- Setup `TIM2`

In `Pinout Config` > `Timers` > `TIM2` > `Mode`
find `Clock Source` and select `Internal Clock`.

`Configuration` contents will appear.
Under `NVIC Settings`, enable `TIM2 global interrupt`.

Then in `Parameter Settings`:
| Param                | Value  |
| -------------------- | ------ |
| Prescaler (PSC)      | 7200-1 |
| Counter Period (ARR) | 5000-1 |
| Counter Mode         | Up     |

> **Explain of the value:**
> 
> The goal is to interrupt every 0.5 seconds.<br>
> The formula:
> ```c
> f_update = TIM_CLK / ((PSC + 1) * (ARR + 1))
> ```
> For TIM2, `TIM_CLK` is 72 MHz;<br>
> - Prescaler = `7200 - 1`
> - Period = `5000 - 1`
> Result:
> - 72 MHz / 7200 = 10 kHz
> - 10 kHz / 5000 = 2 Hz

Save `.ioc` and generate code.

- Test TIM ISR (Interrupt Service Routine)

Now test the timer interrupt.<br>
In `/* USER CODE BEGIN 4 */`:
```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if(htim->Instance==TIM2){
    // Callback when interrupt triggered every 0.5 sec
  }
}
```
> ChatGPT warns that we should keep ISR logic short.
> 
> So we better only set a flag in the ISR callback,
> and move heavy work into the main while loop.
> ```c
> while(1){
>   if(flag){
>     flag = 0;
>     // handling logic...
>   }
> 
>   __WFI();
> }
> ```



### Setup EXTI: button interruption

EXTI (External Interrupt) is an ISR from a GPIO input.

1. Re-configure Pins

    In `.ioc` > `Pinout & Config` > `Pinout view`,
    set the 3 button's pins as `GPIO_EXTIn`.

    Then go to `Pinout & Config` > `System Core` > `GPIO` and set:
    | Setting | Value |
    | ------- | ----- |
    | GPIO mode | External Interrupt Mode with Rising edge trigger |
    | GPIO Pull | Pull-up |
    | User Label     | `BTN_MULTI_Pin_Pin`/`BTN_MIN_Pin_Pin`/`BTN_SEC_Pin_Pin` |

2. Enable NVIC (Nested Vectored Interrupt Controller)

    In `Pinout & Config` > `System Core` > `NVIC`,
    check the interrupt of EXTI 1, 2, and 3.

    Save `.ioc`.

3. ISR callback function

    In `/* USER CODE BEGIN 4 */`:
    ```c
    void HAL_GPIO_EXTI_Callback(uint16_t Pin){
      if(pin==BTN_MULTI_Pin){
        B_MULTI.exti = 1u;
      }
      // ...
    }
    ```

    Then in main while loop, make a test that toggles led on button press:
    ```c
    // test
    if(B_MULTI.exti){
      handle();
    }

    void handle(){
      // debounce
      if(HAL_GetTick() - BS->useTick < DEBOUNCE_MS) return;

      BS->exti = 0;

      GF.led ^= 1;
      led(GF.led);

    }
    ```


# Button debouncing

Buttons, physically, are often 2 pieces of thin metal touching.
The pressing of the button usually creates one or several bounces of those metals under few milliseconds,
which may trigger the EXTI Rising-edge event more than twice with only one button press.

We can fix this just with a few lines of code.

- Begin a 39 ms timer (`DEBOUNCE_MS`) at the first Rising-edge.

    Inside `HAL_GPIO_EXTI_Callback`:
    ```c
    // exti (External Interrupt) Service Routine
    static void eisr(ButtonState *BS){
      if(!BS->exti){
        BS->useTick = HAL_GetTick();
        BS->exti = 1u;
      }
    }
    ```
    > The `BS->exti` is a "pending" flag, 
    > leaving heavy mission to the main while loop.

- In the main loop's `handle_btn()`:
    - Take a break during debouncing. 
      ```c
        if((HAL_GetTick() - BS->useTick) < DEBOUNCE_MS) return;
        BS->exti = 0;
      ```
    - When button still pressed after 39 ms, proceed working the button ought to.
      ```c
        bool debounced_optmz = (read_btn(BS) == GPIO_PIN_SET);
        if(debounced_optmz){
          GF.led ^= 1;
          led(GF.led);
          countup();
          settime(1u);
        }
      ```


