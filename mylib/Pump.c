#include "Pump.h"

GPIO_InitTypeDef g_pump;
void PumpInit(void)
{
   RCC_APB2PeriphClockCmd(RCC_PUMP, ENABLE);
	g_pump.GPIO_Mode = GPIO_Mode_Out_PP;
	g_pump.GPIO_Pin = P_NuA | P_NuB | P_Mix | P_Water;
	g_pump.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PUMP, &g_pump);
	PumpControl(PNuA, P_OFF);
	PumpControl(PNuB, P_OFF);
	PumpControl(PWater, P_OFF);
	PumpControl(PMix, P_OFF);
}
void PumpControl(enum Pump p, enum PState s)
{
	if (p == PNuA)
	{
		if (s == P_OFF)
			GPIO_SetBits(PORT_PUMP, P_NuA);
		else
			GPIO_ResetBits(PORT_PUMP, P_NuA);
	}
	else if (p == PNuB)
	{
		if (s == P_OFF)
			GPIO_SetBits(PORT_PUMP, P_NuB);
		else
			GPIO_ResetBits(PORT_PUMP, P_NuB);
	}
	else if (p == PWater)
	{
		if (s == P_OFF)
			GPIO_SetBits(PORT_PUMP, P_Water);
		else
			GPIO_ResetBits(PORT_PUMP, P_Water);
	}
	else if (p == PMix)
	{
		if (s == P_OFF)
			GPIO_SetBits(PORT_PUMP, P_Mix);
		else 
			GPIO_ResetBits(PORT_PUMP,P_Mix);
	}
}
