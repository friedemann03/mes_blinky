//
// Created by Friedemann Drepper on 15.09.22.
//

#include "log_module.h"

#include "stdio.h"
#include "stdarg.h"
#include "retarget.h"

void Log_Module_Init(void) {
    MX_USART2_UART_Init();
    RetargetInit(&huart2);
}

void Log_Message(uint8_t logLevel, const char *sFormat, ...) {
    if(logLevel >= DEBUG_LOG_LEVEL) {
        char prefix[512] = {0};
        char msg[1024] = {0};
        switch (logLevel) {
            case LOG_LVL_DEBUG:
                sprintf(prefix ,"DEBUG   - ");
                break;
            case LOG_LVL_INFO:
                sprintf(prefix, "%sINFO    - %s", RTT_CTRL_TEXT_BRIGHT_GREEN, RTT_CTRL_RESET);
                break;
            case LOG_LVL_WARNING:
                sprintf(prefix, "%sWARNING - %s", RTT_CTRL_TEXT_BRIGHT_YELLOW, RTT_CTRL_RESET);
                break;
            case LOG_LVL_ERROR:
                sprintf(prefix, "%sERROR   - %s", RTT_CTRL_TEXT_BRIGHT_RED, RTT_CTRL_RESET);
                break;
            case LOG_LVL_SYSTEM:
                sprintf(prefix, "%sSYSTEM  - %s", RTT_CTRL_TEXT_BRIGHT_BLUE, RTT_CTRL_RESET);
                break;
            default:
                break;
        }
        va_list ParamList;
        va_start(ParamList, sFormat);
        vsprintf(msg, sFormat, ParamList);
        va_end(ParamList);
        printf("%s%s",prefix, msg);
    }
}