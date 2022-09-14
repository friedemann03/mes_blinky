//
// Created by Friedemann Drepper on 14.09.22.
//

#include "controller_led.h"
#include "stdbool.h"

#define NR_OF_LEDS 4
#define DEBOUNCE_LOOPS 30



static volatile uint8_t loop = 0;

static uint32_t led_pins[] = {LED3_Pin, LED5_Pin, LED6_Pin, LED4_Pin};
static uint32_t led_ports[] = {LED3_GPIO_Port, LED5_GPIO_Port, LED6_GPIO_Port, LED4_GPIO_Port};

void Led_Module_Init(void) {
    Tim_EnableIRQ(true, TIMER_10);
    Tim_EnableIRQ(true, TIMER_11);
    Tim_Enable(true, TIMER_10);
}

void Led_Module_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
}

void Exti_0_Callback(void) {
    Tim_Enable(true, TIMER_11);
}

void Tim_10_Callback(void) {
    Gpio_Reset_Output_Pin(led_ports[loop], led_pins[loop]);
    loop = (loop + 1) % NR_OF_LEDS;
    Gpio_Set_Output_Pin(led_ports[loop], led_pins[loop]);
}

void Tim_11_Callback(void) {
    static volatile bool ledEnabled = false;
    static volatile uint8_t debounceCounter = 0;
    volatile bool debounceEnabled = true;

    if (debounceCounter < DEBOUNCE_LOOPS) { // still debouncing
        if (!Gpio_Is_Input_Pin_Set(USER_BTN_GPIO_Port, USER_BTN_Pin)) {
            debounceCounter++;
        } else {
            debounceEnabled = false;
        }
    } else { // signal clear after debouncing
        if (ledEnabled) {
            ledEnabled = false;
            Gpio_Reset_Output_Pin(led_ports[loop], led_pins[loop]); // turn off currently active LED
        } else {
            ledEnabled = true;
        }
        Tim_Enable(ledEnabled, TIMER_10);
        debounceEnabled = false;
    }
    Tim_Enable(debounceEnabled, TIMER_11);
}