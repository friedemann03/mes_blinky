//
// Created by Friedemann Drepper on 14.09.22.
//

#include "module_led.h"
#include "stdbool.h"
#include "main.h"

static volatile bool enabled = false;
static volatile uint8_t loop = 0;
static uint32_t led_pins[] = {LED3_Pin, LED5_Pin, LED6_Pin, LED4_Pin};
static uint32_t led_ports[] = {LED3_GPIO_Port, LED5_GPIO_Port, LED6_GPIO_Port, LED4_GPIO_Port};

void Led_Module_Init(void) {
    Tim_EnableIRQ(true, TIMER_10);
    Tim_Enable(true, TIMER_10);
}

void Led_Module_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
}

void Exti_0_Callback(void) {
    if (enabled) {
        enabled = false;
    } else {
        enabled = true;
    }
    Tim_Enable(enabled, TIMER_10);
}

void Tim_10_Callback(void) {
    Gpio_Set_Output_Pin(led_ports[loop], led_pins[loop]);
    LL_mDelay(70);
    Gpio_Reset_Output_Pin(led_ports[loop], led_pins[loop]);
    loop = (loop + 1) % 4;
}