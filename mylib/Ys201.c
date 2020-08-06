#include "Ys201.h"

GPIO_InitTypeDef g_YS; //GPIO struct
EXTI_InitTypeDef e_YS; // EXTI struct
NVIC_InitTypeDef n_YS; // NVIC struct

void TestYs201Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	g_YS.GPIO_Pin = GPIO_Pin_4;
	g_YS.GPIO_Speed = GPIO_Speed_50MHz;
	g_YS.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &g_YS);
}

void TestYs201(u16 t_ms){
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	delay(t_ms);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	delay(t_ms);
}
void Ys201Init(void)
{
	EXTI13_YS201();//xet cai co de khong count
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);
}

void EXTI13_YS201(void)
{
	//cap clock cho ngat ngoai va ngoai vi
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	g_YS.GPIO_Pin = GPIO_Pin_12;
	g_YS.GPIO_Speed = GPIO_Speed_50MHz;
	g_YS.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &g_YS);
	/* mapping */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
	/* Clear the the EXTI line interrupt pending bit */
	EXTI_ClearITPendingBit(EXTI_Line12);
	/*EXTI line Configuration */
	e_YS.EXTI_Mode = EXTI_Mode_Interrupt;
	e_YS.EXTI_Line = EXTI_Line12;
	e_YS.EXTI_Trigger = EXTI_Trigger_Falling;
	e_YS.EXTI_LineCmd = ENABLE;
	EXTI_Init(&e_YS);
	/*NVIC Configuration*/
	n_YS.NVIC_IRQChannel = EXTI15_10_IRQn;
	n_YS.NVIC_IRQChannelPreemptionPriority = 0;
	n_YS.NVIC_IRQChannelSubPriority = 0;
	n_YS.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&n_YS);
}
