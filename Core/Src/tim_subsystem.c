//
// Created by Friedemann Drepper on 14.09.22.
//

/* Includes ------------------------------------------------------------------*/
#include "tim_subsystem.h"
#include "stdbool.h"
#include "tim.h"
#include "gpio_subsystem.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const uint32_t *timerMap[12] = {0, (uint32_t *) TIM1, (uint32_t *) TIM2,
                                (uint32_t *) TIM3, (uint32_t *) TIM4, (uint32_t *) TIM5,
                                0,0,0,
                                (uint32_t *) TIM9, (uint32_t *) TIM10, (uint32_t *) TIM11};

/* Private function prototypes -----------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void Tim_Subsystem_Init(void) {
    MX_TIM10_Init();
    MX_TIM11_Init();
}


void Tim_Enable(bool status, const uint32_t index) {
    if(status) {
        LL_TIM_EnableCounter((TIM_TypeDef *) timerMap[index]);
    } else {
        LL_TIM_DisableCounter((TIM_TypeDef *) timerMap[index]);
    }
}

void Tim_EnableIRQ(bool status, uint32_t index) {
    if(status) {
        LL_TIM_EnableIT_UPDATE((TIM_TypeDef *) timerMap[index]);
    } else {
        LL_TIM_DisableIT_UPDATE((TIM_TypeDef *) timerMap[index]);
    }
}



#include "tim_subsystem.h"
