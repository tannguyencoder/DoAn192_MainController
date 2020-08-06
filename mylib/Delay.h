#ifndef __DELAY_H
#define __DELAY_H 
#include "stm32f10x.h"

void DelayInit(void);
void Delay1Ms(void);
void delay(uint32_t T_ms);
void delay_us(uint32_t T_us);
#endif
