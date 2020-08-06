#include "TimerSetUp.h"

TIM_TimeBaseInitTypeDef timInit;	 //Khai bao truong Timer
NVIC_InitTypeDef NVIC_InitStructure; // NVIC struct

void EXTI_Config_TIM2(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	timInit.TIM_Prescaler = 7200 - 1; //He so chia la 7200
	timInit.TIM_Period = 100 - 1;
	timInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &timInit);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	   //clear update flag
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //enable update interrupt
	TIM_Cmd(TIM2, ENABLE);					   // khoi dong
	//vectorngat
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI_Config_TIM3(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	timInit.TIM_Prescaler = 7200 - 1; //He so chia la 7200
	timInit.TIM_Period = 10 - 1;
	timInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &timInit);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	   //clear update flag
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //enable update interrupt
	TIM_Cmd(TIM3, ENABLE);					   // khoi dong
	//vectorngat
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI_Config_TIM4(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	timInit.TIM_Prescaler = 7200 - 1; //He so chia la 7200
	timInit.TIM_Period = 10 - 1;
	timInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &timInit);

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);	   //clear update flag
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //enable update interrupt
	TIM_Cmd(TIM4, ENABLE);					   // khoi dong
	//vectorngat
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void Timer_Init(void)
{
    EXTI_Config_TIM2();
    EXTI_Config_TIM3();
    EXTI_Config_TIM4();
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM4_IRQn);
}
