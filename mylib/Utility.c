#include "Utility.h"

void resetData(char *c)
{
	int i;
	for (i = 0; i < 99; i++)
	{
		*(c + i) = '\0';
	}
}
void System_Init(void){
	Uart_Init();
	DisplayInit();
	PumpInit();
	DelayInit();
	Timer_Init();
	TestYs201Init();
	SwitchInit();
	Ys201Init();
	RS485_Init();
}
