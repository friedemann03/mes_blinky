//
// Created by Friedemann Drepper on 19.09.22.
//

#include "unity.h"
#include "cmock.h"
#include "stdbool.h"
#include "controller_led.h"
#include "mock_subsystem_tim.h"
#include "mock_subsystem_gpio.h"
#include "mock_log_module.h"


extern volatile bool ledEnabled;
extern volatile bool buttonPressed;

void setUp(void) {

}

void tearDown(void) {

}

void test_Update_should_setEnabledToTrue(void) {
    ledEnabled = false;
    buttonPressed = true;

    Tim_EnableIRQ_Ignore();
    Tim_Enable_Ignore();

    Led_Controller_Update();

    TEST_ASSERT_EQUAL(true, ledEnabled);
}



