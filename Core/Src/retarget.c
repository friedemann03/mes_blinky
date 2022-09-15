//
// Created by Friedemann Drepper on 15.09.22.
//

#include "retarget.h"

#include "stdio.h"
#include "sys/unistd.h"
#include "sys/errno.h"


UART_HandleTypeDef *gHuart;


void RetargetInit(UART_HandleTypeDef*huart){
    gHuart = huart;
    /* Disable I/O buffering for STDOUT stream, so that
     * chars are sent out as soon as they are printed. */
    setvbuf(stdout, NULL, _IONBF, 0);
}

int _write(int fd,char *ptr,int len) {
    HAL_StatusTypeDef hstatus;
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        hstatus = HAL_UART_Transmit(gHuart, (uint8_t *) ptr, len, 100);
        if (hstatus == HAL_OK)
            return len;
        else
            return EIO;
    }
    errno = EBADF;
    return -1;
}

