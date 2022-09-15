# Week 3 Exercise

## Exercise:
On your final project board, make blinky for yourself. Then add a button to turn the LED on and
off. Bonus points for making the button cause an interrupt. Triple bonus points for debouncing
the button signal.

Investigate further, using the processor manual:
1. What are the hardware registers that cause the LED to turn on and off? (From the
processor manual, don’t worry about initialization.)
2. What are the registers that you read in order to find out the state of the button?
3. Can you read the register directly and see the button change in a debugger or by
4. printing out these value of the memory at the register’s address?

## Information
I am using the Nucleo-F446RE board from STM. 
My program lets the one LED on the Board blink with a Timer. 
The LED can be turnt off by pressing the user button. 
The Button also gets debounced in software by using another Timer.

Files I added or edited (all found in _Core/Inc_ or _Core/Src_):
- all subsystems
- all controllers
- pinout header
- retargeting files to use printf
- logging module
- stm32f4xx_it interrupt handler file (i added IRQ handling and calls to callback functions)
- i added calls to the subsystem and controller Init-Functions in the main function

All other files are generated with STM32CubeMX, choosing the Nucleo-F446RE board with all default peripherals initialized.

## Todos
- [x] Make simple blinking LED program
- [x] Make slightly more complex LED program with Button in Interrupt Mode
- [x] Implement subsystem for GPIO and change program accordingly
- [x] Use Timer to drive LEDs
- [x] Implement subsystem for Timers and change program accordingly
- [x] Create LED Controller and move program into it so main loop does nothing
- [x] Add IO Retargeting
- [x] Add Logging Module
- [x] Add Logging to LED controller and subsystems
- [x] Answer questions from the exercise
- [x] Add software debouncing to button
- [ ] Add Console Module to have a terminal connection to the MCU (_maybe_)

## Answers to questions from the exercise

### 1. Question: Registers for the LED
On the Nucleo-F446 the LED (LD2) is connected to PA5 (Pin 5 on Port A). 
For Initialization of PA5 as Output you need to set the according bits in the _MODER_ (MODE Register).
```
GPIOA->MODER |= (0x01 << 10);        // setting mode bits of pin 5 to 01 => Output mode
```
To actually set the output of PA5 you need to set the according bit in the _ODR_ (Output Data Register).
```
GPIOA->ODR |= (1 << 5);              // setting bit
GPIOA->ODR &= ~(1 << 5);             // resetting bit
```
Because that is not possible to do as an atomic operation, there is the _BSRR_ (Bit Set Reset Register) which allow setting a Pin with an atomic instruction.
```
GPIOA->BSRR |= (1 << 5);             // setting bit
GPIOA->BSRR |= ((1 << 5) << 16);     // resetting bit
```

### 2. Question: Registers for the Button
The button is connected to PC13 (Pin 13 on Port C).
To configure PC13 to be in interrupt Mode we need to set the pin mask in the _SYSCFG_EXTICR1_ 
(System Config External Interrupt Control Register 1 (CR1 contains the fields for EXTI0 - EXITI3)).
```
SYSCFG->EXTICR[3] &= ~(0xf << 4);    // clearing all four bits for EXTI13
SYSCFG->EXTICR[3] |= (0x2 << 4);     // setting EXTI13 Bits to 0b0010 => Port C
```
Next, you need to unmask the pin in the _EXTI_IMRx_ (EXTI Interrupt Mask Register).
```
EXTI->IMR |= (1 << 13);              // setting bit 13 to 1 => unmasking Interrupt
```
I configured PC13 to fire an interrupt at falling edge, which is done inside the _EXTI_FTSRx_ 
(EXIT Falling Trigger Selection Register). Then you need to clear the opposite bit in the RTSR (Rising Trigger Selection Register)
else the pin is configured to both, firing two interrupts per button press.
```
EXTI->FTSR |= (1 << 13);             // enable Rising Edge Trigger
EXTI->RTSR &= ~(1 << 13);            // disable Falling Edge Trigger
```
You also have to enable the interrupt in the NVIC (but I do not want to get into the NVIC registers).

When an interrupt occurs you have to clear the pending bit in the _EXTI_PRx_ (EXTI Pending Register) from where you also get the 
information on which pin on the line caused the interrupt.
```
EXTI->PR |= (1 << 13);               // clear the interrupt flag by writing a 1 
```

If the button is used in polling mode, the pin needs to be configured as input in the MODE Register. 
```
GPIOC->MODER |= (0x10 << 26);        // setting mode bits for pin 13 to 10 => Input mode
```
To poll the pin then, you need to get the _IDR_ (Input Data Register) and use bitwise operation to get the information on PC13.
```
uint8_t pinState = GPIOC->IDR & (1 << 13);     // getting value of bit 13 in input register
```

### 3. and 4. Question: Logging / Debugging Registers
I used IO retargeting to use printf to be able to print over the USART 2 Peripheral and then used it to build an Log Module which allows me to print out information about the system (like register contents).
Using the STM32CubeIDE and the connected ST-LINK on the Nucleo board, it's really easy to look at the registers inside the debugger.

## Documents
- [STM32F446 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00135183-stm32f446xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
- [STM32 Cortex-M4 Programming Manual](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
- [Nucleo-F446RE Schematic](file:///Users/friedemann/Downloads/en.MB1136-DEFAULT-C05_Schematic.pdf)
- [Nucleo-F446RE Pinout](https://os.mbed.com/platforms/ST-Nucleo-F446RE/#nucleo-pinout)