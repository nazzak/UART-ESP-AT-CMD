#include "uart_conf.h"


void Uart_Clk_enable(int urt)
{
	if(urt == 2){
		__HAL_RCC_USART2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if(urt == 6){
		__HAL_RCC_USART6_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
}

void Uart_Gpio_Init(int urt)
{
	if(urt == 2){
		/* UART TX GPIO pin configuration  */
		GPIO_InitStruct2.Pin = GPIO_PIN_2;
	GPIO_InitStruct2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct2.Pull = GPIO_PULLUP;
	GPIO_InitStruct2.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct2.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct2);

		/* UART RX GPIO pin configuration  */
		GPIO_InitStruct2.Pin = GPIO_PIN_3;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct2);
	}
	else if(urt == 6){
		/* UART TX GPIO pin configuration  */
		GPIO_InitStruct6.Pin = GPIO_PIN_6;
		GPIO_InitStruct6.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct6.Pull = GPIO_PULLUP;
		GPIO_InitStruct6.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct6.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct6);

		/* UART RX GPIO pin configuration  */
		GPIO_InitStruct6.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct6);
	}
}

void Uart_Handler_Init(int urt)
{
	if(urt == 2){
		UartHandle2.Instance = USART2;
		UartHandle2.Init.BaudRate = 9600;
		UartHandle2.Init.WordLength = UART_WORDLENGTH_8B;
		UartHandle2.Init.StopBits = UART_STOPBITS_1;
		UartHandle2.Init.Parity = UART_PARITY_NONE;
		UartHandle2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		UartHandle2.Init.Mode = UART_MODE_TX_RX;
		UartHandle2.Init.OverSampling = UART_OVERSAMPLING_16;

		if (HAL_UART_Init(&UartHandle2) != HAL_OK) {
			Error_Handler();
		}
	}
	else if(urt == 6){
		UartHandle6.Instance = USART6;
		UartHandle6.Init.BaudRate = 9600;
		UartHandle6.Init.WordLength = UART_WORDLENGTH_8B;
		UartHandle6.Init.StopBits = UART_STOPBITS_1;
		UartHandle6.Init.Parity = UART_PARITY_NONE;
		UartHandle6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		UartHandle6.Init.Mode = UART_MODE_TX_RX;
		UartHandle6.Init.OverSampling = UART_OVERSAMPLING_16;
		if (HAL_UART_Init(&UartHandle6) != HAL_OK) {
			Error_Handler();
		}
	}
}

/**
 * UART MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for UART interrupt request enable
 * huart: UART handle pointer
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

	//if (huart == &UartHandle2){
	/* NVIC for USART2 */
	//	HAL_NVIC_SetPriority(USART2_IRQn, 0, 1); //Configure the USARTx interrupt priority.
	//	HAL_NVIC_EnableIRQ(USART2_IRQn);	//Enable the NVIC USART IRQ handle
	//}
	//else
	if (huart == &UartHandle6){
		/* NVIC for USART2 */
		HAL_NVIC_SetPriority(USART6_IRQn, 0, 2); //Configure the USARTx interrupt priority.
		HAL_NVIC_EnableIRQ(USART6_IRQn);	//Enable the NVIC USART IRQ handle
	}
}

/**
 * This function is executed in case of error occurrence.
 */
void Error_Handler(void) {
	/* Turn LED4 on */
	BSP_LED_On(LED4);
	for(;;);
}

/**
 * Tx Transfer completed callback
 * UartHandle: UART handle.
 * This example shows a simple way to report end of IT Tx transfer, and
 *         you can add your own implementation.
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {
	/* Set transmission flag: transfer complete */
	if (UartHandle == &UartHandle2)
		Uart2TxReady = SET;
	else if (UartHandle == &UartHandle6)
		Uart6TxReady = SET;
}

/**
 * Rx Transfer completed callback
 * UartHandle: UART handle
 * This example shows a simple way to report end of IT Rx transfer, and
 *         you can add your own implementation.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
	/* Set transmission flag: transfer complete */
	if (UartHandle == &UartHandle2)
		Uart2RxReady = SET;
	else if (UartHandle == &UartHandle6)
		Uart6RxReady = SET;
}

/**
 * UART error callbacks
 * UartHandle: UART handle
 * This example shows a simple way to report transfer error, and you can
 * add your own implementation.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	/* Turn LED3 on: Transfer error in reception/transmission process */
	BSP_LED_On(LED3);
}
