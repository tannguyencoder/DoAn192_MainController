#include "Uart.h"

USART_InitTypeDef uartInit;
GPIO_InitTypeDef g_uartInit;

/*-----------TX Config--------------*/
void TX_Config(void)
{
	/*PB10-UART3 - PB6-UART1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	g_uartInit.GPIO_Mode = GPIO_Mode_AF_PP;
	g_uartInit.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_6;
	g_uartInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &g_uartInit);

	/*PA2-UART2*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	g_uartInit.GPIO_Mode = GPIO_Mode_AF_PP;
	g_uartInit.GPIO_Pin = GPIO_Pin_2;
	g_uartInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &g_uartInit);
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
}

/*-----------RX Config--------------*/
void RX_Config(void)
{
	/*PB11-UART3 - PB7-UART1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	g_uartInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	g_uartInit.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_7;
	g_uartInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &g_uartInit);


	/*PA3-UART2*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	g_uartInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	g_uartInit.GPIO_Pin = GPIO_Pin_3;
	g_uartInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &g_uartInit);
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
}
/*-----------Setup Uart--------------*/
void USART_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	uartInit.USART_BaudRate = 9600;
	uartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uartInit.USART_Parity = USART_Parity_No;
	uartInit.USART_StopBits = USART_StopBits_1;
	uartInit.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART3, &uartInit);
	USART_Init(USART2, &uartInit);
	USART_Init(USART1, &uartInit);

	USART_Cmd(USART3, ENABLE);
	USART_Cmd(USART2, ENABLE);
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
/*------- Init Uart-------------*/
void Uart_Init(void){
	USART_Config();
	RX_Config();
	TX_Config();
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	
}
