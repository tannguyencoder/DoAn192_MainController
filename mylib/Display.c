#include <Display.h>

GPIO_InitTypeDef g_disp;
void DisplayInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_DISPLAY, ENABLE);
	g_disp.GPIO_Mode = GPIO_Mode_Out_PP;
	g_disp.GPIO_Pin = D_NuA | D_NuB | D_Mix | D_Water;
	g_disp.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DISPLAY, &g_disp);
	DisplayControl(DNuA, D_OFF);
	DisplayControl(DNuB, D_OFF);
	DisplayControl(DWater, D_OFF);
	DisplayControl(DMix, D_OFF);
}

void DisplayControl(enum dNumber d, enum DState s)
{
	if (d == DNuA)
	{
		if (s == D_OFF)
			GPIO_SetBits(PORT_DISPLAY, D_NuA);
		else
			GPIO_ResetBits(PORT_DISPLAY, D_NuA);
	}
	else if (d == DNuB)
	{
		if (s == D_OFF)
			GPIO_SetBits(PORT_DISPLAY, D_NuB);
		else
			GPIO_ResetBits(PORT_DISPLAY, D_NuB);
	}
	else if (d == DWater)
	{
		if (s == D_OFF)
			GPIO_SetBits(PORT_DISPLAY, D_Water);
		else
			GPIO_ResetBits(PORT_DISPLAY, D_Water);
	}
	else if (d == DMix)
	{
		if (s == D_OFF)
			GPIO_SetBits(PORT_DISPLAY, D_Mix);
		else 
			GPIO_ResetBits(PORT_DISPLAY,D_Mix);
	}
}
