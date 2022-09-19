//
// Created by Friedemann Drepper on 14.09.22.
//

#include "controller_led.h"
#include "stdbool.h"
#include "log_module.h"



//Private Variables
static volatile bool ledEnabled = true;
static volatile bool buttonPressed = false;

static uint32_t led_pins[] = {LED2_Pin};
static uint32_t led_ports[] = {LED2_GPIO_Port};

// Public Functions
void Led_Controller_Init(void) {
    Log_Message(LOG_LVL_SYSTEM, "LED Controller Starting.\n");
    Tim_EnableIRQ(true, TIMER_10);
    Tim_EnableIRQ(false, TIMER_11);
    Tim_Enable(true, TIMER_10);
    Tim_Enable(false, TIMER_11);
}

void Led_Controller_Update(void) {
    if (buttonPressed) {
        buttonPressed = false;
        if (ledEnabled) {
            ledEnabled = false;
            Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]); // turn off currently active LED
        } else {
            ledEnabled = true;
        }
        Tim_Enable(ledEnabled, TIMER_10);
    }
}

void Led_Controller_DeInit(void) {
    Tim_EnableIRQ(false, TIMER_10);
    Tim_EnableIRQ(false, TIMER_11);
    Gpio_Reset_Output_Pin(led_ports[0], led_pins[0]);
    ledEnabled = false;
    buttonPressed = false;
}


// Private Functions
void Exti_15_10_Callback(void) {
    Tim_EnableIRQ(true, TIMER_11);
    Tim_Enable(true, TIMER_11);
}

void Tim_10_Callback(void) {
    Gpio_Toggle_Output_Pin(led_ports[0], led_pins[0]);
}

void Tim_11_Callback(void) {
    Tim_EnableIRQ(false, TIMER_11);
    Tim_Enable(false, TIMER_11);

    if (Gpio_Is_Input_Pin_Set(USER_BTN_GPIO_Port, USER_BTN_Pin)) {
        buttonPressed = true;
    }
}