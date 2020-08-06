#ifndef __SWITCHCONTROL_H
#define __SWITCHCONTROL_H
#include "Lib.h"

void EXTI5_NuA(void);
void EXTI4_NuB(void);
void EXTI3_Water(void);
void EXTI15_Mix(void);
void SwitchInit(void);
void Switch_Disable(void);
void Switch_Enable(void);

#endif
