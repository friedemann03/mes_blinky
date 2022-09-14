//
// Created by Friedemann Drepper on 14.09.22.
//

#ifndef YS_EXERCISE_WEEK3_TIM_SUBSYSTEM_H
#define YS_EXERCISE_WEEK3_TIM_SUBSYSTEM_H
/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"

/* Exported macro ------------------------------------------------------------*/
//#define TIMER_1              1
//#define TIMER_2              2
//#define TIMER_3              3
//#define TIMER_4              4
//#define TIMER_5              5
//#define TIMER_6              6
//#define TIMER_7              7
//#define TIMER_8              8
//#define TIMER_9              9
#define TIMER_10             10
//#define TIMER_11             11


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Tim_Subsystem_Init(void);

void Tim_Enable(bool status, uint32_t index);

void Tim_EnableIRQ(bool status, uint32_t timerIRQn);

__attribute__((weak)) void Tim_10_Callback(void);
#endif //YS_EXERCISE_WEEK3_TIM_SUBSYSTEM_H
