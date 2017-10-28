/**
 ******************************************************************************
 * @file    main.c
 * @author  Nazim SAIBI
 * @version V1.0
 * @date    01-September-2017
 * @brief   LEDs handler with UART and Qt application in non blocking mode (IT)
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "uart_conf.h"

/* Buffer used for Tx and Rx */
static uint8_t aRxBuffer[50];
static volatile ind = 5;

static const char *sendArray[] = {
		"AT\r\n",
		"AT+CWMODE=1\r\n",
		"AT+CWJAP=\"Master_SE\",\"U8d_4fW@\"\r\n",
		"AT+CIPSTART=\"UDP\",\"192.168.1.32\",49441\r\n",
		"AT+CIPSEND=13\r\n",
		"ESTEI/STM32F4"
};

int main(void) {

	/* Configure LED3, LED4, LED5 and LED6 */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch, instruction and Data caches
	 - Configure the Systick to generate an interrupt each 1 msec
	 - Set NVIC Group Priority to 4
	 - Global MSP (MCU Support Package) initialization
	 */
	HAL_Init();
	HAL_Delay(1000);  //Avoid ESP boot sequence

	/* Reset transmission flag */
	Uart2TxReady = Uart6TxReady = Uart2RxReady = Uart6RxReady = RESET;

	Uart_Clk_enable(6);
	Uart_Gpio_Init(6);
	Uart_Handler_Init(6);

	BSP_LED_On(LED4);

	/* Infinite loop */
	while (1)
	{
		for (int i=0; i<4; ++i)
		{
			if (HAL_UART_Transmit_IT(&UartHandle6, (uint8_t *)sendArray[i], strlen(sendArray[i])) != HAL_OK) {
				Error_Handler();
			}
			while (Uart6TxReady != SET);
			Uart6TxReady = RESET;

			BSP_LED_On(LED4);
			HAL_Delay(i==2?15000:500);
		}

		for(;;){
			ind=ind==5?4:5;

			if (HAL_UART_Transmit_IT(&UartHandle6, (uint8_t *)sendArray[ind], strlen(sendArray[ind])) != HAL_OK) {
				Error_Handler();
			}
			while (Uart6TxReady != SET);
			Uart6TxReady = RESET;
			HAL_Delay(100);

			BSP_LED_On(LED4);
			HAL_Delay(ind==5?500:50);
			BSP_LED_Off(LED4);
			HAL_Delay(ind==5?500:50);
		}
	}
}
