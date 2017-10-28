#ifndef __UART_CONF_H
#define __UART_CONF_H

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

/* UART status declaration */
volatile ITStatus Uart2TxReady, Uart6TxReady, Uart2RxReady, Uart6RxReady;

/* UART handler declaration */
UART_HandleTypeDef UartHandle2, UartHandle6;	//Declare a UART_HandleTypeDef handle structures.


GPIO_InitTypeDef GPIO_InitStruct2, GPIO_InitStruct6;

void Uart_Clk_enable(int urt);
void Uart_Gpio_Init(int urt);
void Uart_Handler_Init(int urt);
void Error_Handler(void);

#endif
