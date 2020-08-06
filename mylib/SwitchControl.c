#include "SwitchControl.h"

GPIO_InitTypeDef g_sw; //GPIO struct
EXTI_InitTypeDef e_SW; // EXTI struct
NVIC_InitTypeDef n_SW; // NVIC struct

void EXTI5_NuA(void)
{
    //cap clock cho ngat ngoai va ngoai vi
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    g_sw.GPIO_Pin = GPIO_Pin_5;
    g_sw.GPIO_Speed = GPIO_Speed_50MHz;
    g_sw.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &g_sw);
    /* mapping */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
    /* Clear the the EXTI line interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_Line5);
    /*EXTI line Configuration */
    e_SW.EXTI_Mode = EXTI_Mode_Interrupt;
    e_SW.EXTI_Line = EXTI_Line5;
    e_SW.EXTI_Trigger = EXTI_Trigger_Falling;
    e_SW.EXTI_LineCmd = ENABLE;
    EXTI_Init(&e_SW);
    /*NVIC Configuration*/
    n_SW.NVIC_IRQChannel = EXTI9_5_IRQn;
    n_SW.NVIC_IRQChannelPreemptionPriority = 0;
    n_SW.NVIC_IRQChannelSubPriority = 0;
    n_SW.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&n_SW);
}
void EXTI4_NuB(void)
{
    //cap clock cho ngat ngoai va ngoai vi
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    g_sw.GPIO_Pin = GPIO_Pin_4;
    g_sw.GPIO_Speed = GPIO_Speed_50MHz;
    g_sw.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &g_sw);
    /* mapping */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
    /* Clear the the EXTI line interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_Line4);
    /*EXTI line Configuration */
    e_SW.EXTI_Mode = EXTI_Mode_Interrupt;
    e_SW.EXTI_Line = EXTI_Line4;
    e_SW.EXTI_Trigger = EXTI_Trigger_Falling;
    e_SW.EXTI_LineCmd = ENABLE;
    EXTI_Init(&e_SW);
    /*NVIC Configuration*/
    n_SW.NVIC_IRQChannel = EXTI4_IRQn;
    n_SW.NVIC_IRQChannelPreemptionPriority = 0;
    n_SW.NVIC_IRQChannelSubPriority = 0;
    n_SW.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&n_SW);
}
void EXTI3_Water(void)
{
    //cap clock cho ngat ngoai va ngoai vi
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    g_sw.GPIO_Pin = GPIO_Pin_3;
    g_sw.GPIO_Speed = GPIO_Speed_50MHz;
    g_sw.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_Init(GPIOB, &g_sw);
	
    /* mapping */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
    /* Clear the the EXTI line interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_Line3);
    /*EXTI line Configuration */
    e_SW.EXTI_Mode = EXTI_Mode_Interrupt;
    e_SW.EXTI_Line = EXTI_Line3;
    e_SW.EXTI_Trigger = EXTI_Trigger_Falling;
    e_SW.EXTI_LineCmd = ENABLE;
    EXTI_Init(&e_SW);
    /*NVIC Configuration*/
    n_SW.NVIC_IRQChannel = EXTI3_IRQn;
    n_SW.NVIC_IRQChannelPreemptionPriority = 0;
    n_SW.NVIC_IRQChannelSubPriority = 0;
    n_SW.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&n_SW);
}
void EXTI15_Mix(void)
{
    //cap clock cho ngat ngoai va ngoai vi
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    g_sw.GPIO_Pin = GPIO_Pin_15;
    g_sw.GPIO_Speed = GPIO_Speed_50MHz;
    g_sw.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &g_sw);
    /* mapping */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
    /* Clear the the EXTI line interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_Line15);
    /*EXTI line Configuration */
    e_SW.EXTI_Mode = EXTI_Mode_Interrupt;
    e_SW.EXTI_Line = EXTI_Line15;
    e_SW.EXTI_Trigger = EXTI_Trigger_Falling;
    e_SW.EXTI_LineCmd = ENABLE;
    EXTI_Init(&e_SW);
    /*NVIC Configuration*/
    n_SW.NVIC_IRQChannel = EXTI15_10_IRQn;
    n_SW.NVIC_IRQChannelPreemptionPriority = 0;
    n_SW.NVIC_IRQChannelSubPriority = 0;
    n_SW.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&n_SW);
}

void SwitchInit(void)
{
    EXTI5_NuA();
    EXTI4_NuB();
    EXTI3_Water();
    EXTI15_Mix();
}
void Switch_Disable(void)
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    NVIC_DisableIRQ(EXTI4_IRQn);
    NVIC_DisableIRQ(EXTI3_IRQn);
}
void Switch_Enable(void)
{
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);
}
