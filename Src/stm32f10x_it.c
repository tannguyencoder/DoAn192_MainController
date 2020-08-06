#include <Lib.h>
/*******************Variable********************/
static u8 sw0 = 0, sw1 = 0, sw2 = 0, sw3 = 0;
static uint8_t t = 0, t_A = 0;
static uint16_t t_send = 0;
static u8 c_DataCLI = 0, c_DataMIX = 0, c_DataWater = 0;
static char sel1 = 0, sel2 = 0, sel3 = 0;
uint8_t Pumped[100];
static uint32_t flowrate = 0;
static double B_LIn = 0, B_Lp1 = 0, B_Lp2 = 0;
/***********************************************/
u8 flagHandMIX=0,flagHandWater=0,flagHandA=0,flagHandB=0;
u8 flagCLI = 0, flagMIX = 0, flagWater = 0 ,flagCount=0;
u8 flagW = 0, flagP1 = 0, flagP2 = 0;
uint32_t count = 0;
double LWater = 0, LPump1 = 0, LPump2 = 0;
double LIn = 0, Lp1 = 0, Lp2 = 0;
char DataMix[30] = {}, DataCLI[22] = {}, DataWater[100] = {}, DataPumpA[100] = {}, DataPumpB[100] = {}, result[35]="",result1[36]="";
extern uint8_t H_DataCLI[18],H_DataMix[30];
/*************************************************/
const double flow_Pump1 = 10, flow_Pump2 = 20; //L/minute
/*
 *START Timer using for Control Pump
*/

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		t++;
		if ((t > 0) && (t <= 100)&&(flagW == 1))
		{
			flagCount=1;
		}
		if ((t > 100) && (t <= 101)&&(flagW == 1))
		{
     	flagCount=0;
			flowrate = count;
			LWater += (double)(flowrate / (7.5 * 60));
			B_LIn = LWater;
			if ((LWater > LIn)&&!(flagHandWater==1))
			{
				flagW = 0;
				LWater = 0;
				PumpControl(PWater,P_OFF);
				DisplayControl(DWater,D_OFF);
			}
			count = 0;
			t = 0;
		}
	}
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}



void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		t_send++;
		Listen_Enable(USART3);
		if ((t_send > 1000) && (t_send <= 1001))
		{
			sprintf(Pumped, "%s,%4.1f,%4.1f,%4.1f", result1, B_LIn, B_Lp1, B_Lp2);
			RS485_PutString(USART3, Pumped,52);
			t_send = 0;
		}
	}
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
}




void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		t_A++;
		if ((t_A > 100) && (t_A <= 101))
		{
			if(flagP1==1){
				LPump1 += (double)(flow_Pump1 / 600);
				B_Lp1 = LPump1;
				if ((LPump1 > Lp1)&&!(flagHandA==1))
				{
					LPump1 = 0;
					flagP1 = 0;
					PumpControl(PNuA,P_OFF);
					DisplayControl(DNuA,D_OFF);
				}
			}
			if(flagP2==1){
				LPump2 += (double)(flow_Pump2/600);
				B_Lp2 = LPump2;
				if ((LPump2 > Lp2)&&!(flagHandB==1))
				{
					flagP2 = 0;
					LPump2 = 0;
					PumpControl(PNuB,P_OFF);
					DisplayControl(DNuB,D_OFF);
				}
			}
			t_A = 0;
				
		}
	}
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
}



/*
 *END Timer using for Control Pump
*/
/*
 *START Interupt for Switch  
*/



//PumpNuA
void EXTI9_5_IRQHandler(void)
{
	if ((EXTI_GetFlagStatus(EXTI_Line5) != RESET))
	{
		delay(50);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0)
		{
			sw0++;
			if (sw0 > 0 && sw0 <= 1)
			{
				DisplayControl(DNuA, D_ON);
				PumpControl(PNuA, P_ON);
				flagHandA=1;;
				flagP1 = 1;
			}
			else if (sw0 > 1 && sw0 <= 2)
			{
				DisplayControl(DNuA, D_OFF);
				PumpControl(PNuA, P_OFF);
				sw0 = 0;
				LPump1 = 0;
				Lp1 = 0;
				flagHandA=0;
				flagP1 = 0;
			}
		}

		EXTI_ClearFlag(EXTI_Line5);
	}
}



//PumpNuB
void EXTI4_IRQHandler(void)
{
	if ((EXTI_GetFlagStatus(EXTI_Line4) != RESET))
	{
		delay(50);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
		{
			sw1++;
			if (sw1 > 0 && sw1 <= 1)
			{
				DisplayControl(DNuB, D_ON);
				PumpControl(PNuB, P_ON);
				flagHandB=1;
				flagP2 = 1;
			}
			else if (sw1 > 1 && sw1 <= 2)
			{
				DisplayControl(DNuB, D_OFF);
				PumpControl(PNuB, P_OFF);
				sw1 = 0;
				flagHandB=0;
				sw1 = 0;
				flagP2 = 0;
				LPump2 = 0;
				Lp2 = 0;
			}
		}
		EXTI_ClearFlag(EXTI_Line4);
	}
}



//PumpWater
void EXTI3_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(EXTI_Line3) != RESET)
	{
		delay(50);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0)
		{
			sw2++;
			if (sw2 > 0 && sw2 <= 1)
			{
				DisplayControl(DWater, D_ON);
				PumpControl(PWater, P_ON);
				flagHandWater=1;
				NVIC_EnableIRQ(TIM2_IRQn);
				flagW = 1;
			}
			else if (sw2 > 1 && sw2 <= 2)
			{
				LIn = 0;
				LWater = 0;
				DisplayControl(DWater, D_OFF);
				PumpControl(PWater, P_OFF);
				flagHandWater=0;
				flagW = 0;
				NVIC_DisableIRQ(TIM2_IRQn);
				sw2 = 0;
				flagCount=0;
				count=0;
			}
		}
		EXTI_ClearFlag(EXTI_Line3);
	}
}



//pumpMix and Flowmeter
void EXTI15_10_IRQHandler(void)
{
	if ((EXTI_GetFlagStatus(EXTI_Line12) != RESET))
	{
		if (flagCount == 1)
			count = count + 1;
		EXTI_ClearFlag(EXTI_Line12);
	}

	if (EXTI_GetFlagStatus(EXTI_Line15) != RESET)
	{
		delay(50);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)
		{
			sw3++;
			if (sw3 > 0 && sw3 <= 1)
			{
				DisplayControl(DMix, D_ON);
				
				//Switch_Disable();
				PumpControl(PMix, P_ON);
				flagHandMIX = 1;
				count = 0;
			}
			else if (sw3 > 1 && sw3 <= 2)
			{
				DisplayControl(DMix, D_OFF);
				PumpControl(PMix, P_OFF);
				//Switch_Enable();
				flagHandMIX = 0;
				count = 0;
				sw3 = 0;
			}
		}

		EXTI_ClearFlag(EXTI_Line15);
	}
}
/*
 * END Interupt for Switch  
*/

/*
 *START Uart Interupt for send Data 
*/


// using for climate

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		uint8_t data1 = USART_ReceiveData(USART1);
		/*static uint8_t i=0;
		
		*(DataCLI+i)=data1;
		i=(i+23)%22;*/
		if (data1 == 'z')
		{
			sel3 = 0;
			flagCLI = 1;
			c_DataCLI = 0;
		}
		if (sel3 == 'a')
		{
			DataCLI[c_DataCLI] = data1;
			c_DataCLI++;
		}
		if (data1 == 'a')
		{
			sel3 = 'a';
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}


//using for MIX
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		char data2 = USART_ReceiveData(USART2);
		if (data2 == 'z')
		{
			sel2 = 0;
			flagMIX = 1;
			c_DataMIX = 0;
		}
		if (sel2 == 'a')
		{
			DataMix[c_DataMIX] = data2;
			c_DataMIX++;
		}
		if (data2 == 'a')
		{
			sel2 = 'a';
		}
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}




//using for Water
void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		char data = USART_ReceiveData(USART3);
		if (data == 't')
		{
			sel1 = 0;
			c_DataWater = 0;
		}
		if (sel1 == 'w')
		{
			DataWater[c_DataWater] = data;
			c_DataWater++;
		}
		if (sel1 == 'a')
		{
			DataPumpA[c_DataWater] = data;
			c_DataWater++;
		}
		if (sel1 == 'b')
		{
			DataPumpB[c_DataWater] = data;
			c_DataWater++;
		}
		if (data == 'b')
		{
			sel1 = 'b';
		}
		if (data == 'a')
		{
			sel1 = 'a';
		}
		if (data == 'w')
		{
			sel1 = 'w';
		}
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
/*
 *END Uart Interupt for send Data 
*/
