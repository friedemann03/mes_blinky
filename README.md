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

Files I added or edited:
- all subsystems
- all controllers
- pinout header
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
- [ ] Add Logging Module
- [ ] Add Logging to LED module and subsystems
- [ ] Answer questions from the exercise
- [x] Add software debouncing to button
- [ ] Add Console Module to have a terminal connection to the MCU

## Answers to questions from the exercise
not done yet
