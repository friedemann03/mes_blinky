//
// Created by Friedemann Drepper on 19.09.22.
//

#include "unity.h"
#include "cmock.h"
#include "stdbool.h"
#include "controller_led.h"
#include "pinout.h"
#include "mock_subsystem_tim.h"
#include "mock_subsystem_gpio.h"
#include "mock_log_module.h"


extern volatile bool ledEnabled;
extern volatile bool buttonPressed;

void setUp(void) {
    Tim_EnableIRQ_Ignore();
    Tim_Enable_Ignore();
    Gpio_Reset_Output_Pin_Ignore();
}

void tearDown(void) {

}

void test_Update_should_setEnabledToTrue(void) {
    ledEnabled = false;
    buttonPressed = true;

    Led_Controller_Update();

    TEST_ASSERT_EQUAL(true, ledEnabled);
}

void test_Update_should_setButtonPressedToFalse(void) {
    buttonPressed = true;

    Led_Controller_Update();

    TEST_ASSERT_EQUAL(false, buttonPressed);
}

void test_Update_should_setEnabledToFalseAndResetLED(void) {
    ledEnabled = true;
    buttonPressed = true;

    Gpio_Reset_Output_Pin_StopIgnore();
    Gpio_Reset_Output_Pin_Expect(Gpio_Port_A, Gpio_Pin_5);

    Led_Controller_Update();

    TEST_ASSERT_EQUAL(false, ledEnabled);
}

void test_Update_should_doNothing(void) {
    buttonPressed = false;

    ledEnabled = true;

    Gpio_Reset_Output_Pin_StopIgnore();

    Led_Controller_Update();

    TEST_ASSERT_EQUAL(true, ledEnabled);

    ledEnabled = false;

    Led_Controller_Update();

    TEST_ASSERT_EQUAL(false, ledEnabled);
}



