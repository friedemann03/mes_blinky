//
// Created by Friedemann Drepper on 14.09.22.
//

#ifndef YS_EXERCISE_WEEK3_UART_SUBSYSTEM_H
#define YS_EXERCISE_WEEK3_UART_SUBSYSTEM_H

#include "usart.h"


__attribute__((weak)) void Uart_2_Callback(UART_HandleTypeDef *huart);

#endif //YS_EXERCISE_WEEK3_UART_SUBSYSTEM_H
