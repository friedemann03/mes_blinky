//
// Created by Friedemann Drepper on 14.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "gpio_subsystem.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static const GPIO_TypeDef *portMap[6] = {GPIOA,
                                         GPIOB,
                                         GPIOC,
                                         GPIOD,
                                         GPIOE,
                                         GPIOH,
};
/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void Gpio_Subsystem_Init(void) {
    MX_GPIO_Init();
}

void Gpio_Set_Output_Pin(uint32_t port, uint32_t pinMask) {
    LL_GPIO_SetOutputPin((GPIO_TypeDef *) portMap[port], pinMask);
}

void Gpio_Reset_Output_Pin(uint32_t port, uint32_t pinMask) {
    LL_GPIO_ResetOutputPin((GPIO_TypeDef *) portMap[port], pinMask);
}

void Gpio_Toggle_Output_Pin(uint32_t port, uint32_t pinMask) {
    LL_GPIO_TogglePin((GPIO_TypeDef *) portMap[port], pinMask);
}

uint32_t Gpio_Is_Input_Pin_Set(uint32_t port, uint32_t pinMask) {
    return LL_GPIO_IsInputPinSet((GPIO_TypeDef *) portMap[port], pinMask);
}

