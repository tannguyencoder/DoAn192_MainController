#ifndef __MAX485_H
#define __MAX485_H
/*
 * Import libray
*/

#include <Delay.h>
#include <Uart.h>
#include <stm32f10x.h>

/*
 * Define macro for Control Max485
 */

#define Uart1_Pin_Control   GPIO_Pin_8
#define Uart1_Port_Control  GPIOB
#define Uart1_RCC_Control   RCC_APB2Periph_GPIOB

#define Uart2_Pin_Control   GPIO_Pin_1
#define Uart2_Port_Control  GPIOA
#define Uart2_RCC_Control   RCC_APB2Periph_GPIOA

#define Uart3_Pin_Control   GPIO_Pin_1
#define Uart3_Port_Control  GPIOB
#define Uart3_RCC_Control   RCC_APB2Periph_GPIOB

/*
 * Function 
 */
void Send_Enable(USART_TypeDef *USARTx);
void Listen_Enable(USART_TypeDef *USARTx);
void RS485_Init(void);
void RS485_PutChar(USART_TypeDef *USARTx, char c);
void RS485_PutString(USART_TypeDef *USARTx, char *s, uint8_t num);
#endif
