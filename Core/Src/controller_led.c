//
// Created by Friedemann Drepper on 14.09.22.
//

#include "controller_led.h"
#include "stdbool.h"

#define NR_OF_LEDS 1
#define DEBOUNCE_LOOPS 25



static volatile uint8_t loop = 0;

static uint32_t led_pins[] = {LED2_Pin};
static uint32_t led_ports[] = {LED2_GPIO_Port};

void Led_Controller_Init(void) {
    Tim_EnableIRQ(true, TIMER_10);
    Tim_EnableIRQ(true, TIMER_11);
    Tim_Enable(true, TIMER_10);
}

void Led_Controller_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
}

void Exti_15_10_Callback(void) {
    Tim_Enable(true, TIMER_11);
}

void Tim_10_Callback(void) {
    Gpio_Toggle_Output_Pin(led_ports[0], led_pins[0]);
}

void Tim_11_Callback(void) {
    static volatile bool ledEnabled = false;
    static volatile uint8_t debounceCounter = 0;
    volatile bool debounceEnabled = true;

    if (debounceCounter < DEBOUNCE_LOOPS) { // still debouncing
        if (Gpio_Is_Input_Pin_Set(USER_BTN_GPIO_Port, USER_BTN_Pin)) {
            debounceCounter++;
        } else {
            debounceEnabled = false;
        }
    } else { // signal clear after debouncing
        if (ledEnabled) {
            ledEnabled = false;
            Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]); // turn off currently active LED
        } else {
            ledEnabled = true;
        }
        Tim_Enable(ledEnabled, TIMER_10);
        debounceEnabled = false;
    }
    Tim_Enable(debounceEnabled, TIMER_11);
}