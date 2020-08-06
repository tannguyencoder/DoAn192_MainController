#include "Delay.h"

TIM_TimeBaseInitTypeDef 	delayInit;

//--------------------------------Delay-Config -TIMER3-------------------------------------//
void DelayInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	delayInit.TIM_CounterMode= TIM_CounterMode_Up;
	delayInit.TIM_Period=0xffff;
	delayInit.TIM_Prescaler=72-1;
	TIM_TimeBaseInit(TIM1,&delayInit);
	TIM_Cmd(TIM1,ENABLE);
}
//--------------------------------Function Delay 1ms--------------------------------------//
void Delay1Ms(void){
	TIM_SetCounter(TIM1,0);
	while (TIM_GetCounter(TIM1)<1000){}
}
//--------------------------------Function Delay N ms-------------------------------------//
void delay(uint32_t T_ms){
	while(T_ms)
	{
		Delay1Ms();
		--T_ms;
	}
}
//--------------------------------Function Delay N us-------------------------------------//
void delay_us(uint32_t T_us){
	TIM_SetCounter(TIM1,0);
	while (TIM_GetCounter(TIM1)<T_us){}
}
