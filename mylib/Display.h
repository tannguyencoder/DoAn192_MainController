#ifndef __DISPLAY_H
#define __DISPLAY_H
#include <stm32f10x.h>

#define D_NuA GPIO_Pin_8
#define D_NuB GPIO_Pin_9
#define D_Water GPIO_Pin_10
#define D_Mix GPIO_Pin_11
#define PORT_DISPLAY GPIOA
#define RCC_DISPLAY RCC_APB2Periph_GPIOA

enum DState {D_OFF=0,D_ON=1};
enum dNumber{DNuA=0,DNuB,DWater,DMix};
void DisplayInit(void);
void DisplayControl(enum dNumber d,enum DState s);
#endif
