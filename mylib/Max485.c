#include "Max485.h"
GPIO_InitTypeDef gpiors485;

void Send_Enable(USART_TypeDef *USARTx)
{
    if (USARTx == USART1)
    {
        GPIO_SetBits(Uart1_Port_Control, Uart1_Pin_Control);
    }
    else if (USARTx == USART2)
    {
        GPIO_SetBits(Uart2_Port_Control, Uart2_Pin_Control);
    }
    else if (USARTx == USART3)
    {
        GPIO_SetBits(Uart3_Port_Control, Uart3_Pin_Control);
    }
}
void Listen_Enable(USART_TypeDef *USARTx)
{
    if (USARTx == USART1)
    {
        GPIO_ResetBits(Uart1_Port_Control, Uart1_Pin_Control);
    }
    else if (USARTx == USART2)
    {
        GPIO_ResetBits(Uart2_Port_Control, Uart2_Pin_Control);
    }
    else if (USARTx == USART3)
    {
        GPIO_ResetBits(Uart3_Port_Control, Uart3_Pin_Control);
    }
}
void RS485_Init(void)
{
    RCC_APB2PeriphClockCmd(Uart1_RCC_Control, ENABLE);
    gpiors485.GPIO_Mode = GPIO_Mode_Out_PP;
    gpiors485.GPIO_Pin = Uart1_Pin_Control;
    gpiors485.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Uart1_Port_Control, &gpiors485);
	
	
    RCC_APB2PeriphClockCmd(Uart2_RCC_Control, ENABLE);
    gpiors485.GPIO_Mode = GPIO_Mode_Out_PP;
    gpiors485.GPIO_Pin = Uart2_Pin_Control;
    gpiors485.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Uart2_Port_Control, &gpiors485);
	
	
    RCC_APB2PeriphClockCmd(Uart3_RCC_Control, ENABLE);
    gpiors485.GPIO_Mode = GPIO_Mode_Out_PP;
    gpiors485.GPIO_Pin = Uart3_Pin_Control;
    gpiors485.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Uart3_Port_Control, &gpiors485);
	
    Listen_Enable(USART1);
    Listen_Enable(USART2);
    Listen_Enable(USART3);
}
void RS485_PutChar(USART_TypeDef *USARTx, char c)
{
    while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE))
    {
    }
    USART_SendData(USARTx, c);
}

void RS485_PutString(USART_TypeDef *USARTx, char *s, uint8_t num)
{
	uint8_t i = 0;
    while (i<num)
    {
        Send_Enable(USARTx);
        RS485_PutChar(USARTx, *(s+i));
				i++;
				//delay(3);
        Listen_Enable(USARTx);
    }
}
