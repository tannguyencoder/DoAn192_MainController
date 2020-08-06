#ifndef __PUMP_H
#define __PUMP_H
#include "stm32f10x.h"

#define P_NuA GPIO_Pin_12
#define P_NuB GPIO_Pin_13
#define P_Water GPIO_Pin_14
#define P_Mix GPIO_Pin_15
#define PORT_PUMP GPIOB
#define RCC_PUMP RCC_APB2Periph_GPIOB

enum PState {P_OFF=0,P_ON=1};
enum Pump{PNuA=0,PNuB,PWater,PMix};
void PumpInit(void);
void PumpControl(enum Pump p,enum PState s);
#endif
