#include <Lib.h>
extern char DataWater[100], DataPumpA[100], DataPumpB[100], DataCLI[30], DataMix[30],result[35],result1[36];
extern double LWater, LPump1, LPump2;
extern u8 flagCLI, flagMIX, flagHandMIX, flagHandWater, flagHandA, flagHandB;
extern u8 flagW, flagP1, flagP2;
extern double LIn, Lp1, Lp2;
extern uint32_t count;
char B_DataMix[16] = " 0.0,   0.0, 0.0", B_DataCLI[18] = " 0.0, 0.0,     0.0",H_DataCLI[18]="",H_DataMix[30]="";
static u8 flagHand=0;

uint16_t crc1_receive,crc2_receive;
uint16_t crc1,crc2;
int main(void)
{
	System_Init();
	while(1)
	{
		//Listen_Enable(USART1);
		if (!((flagHandA == 1) || (flagHandB == 1) || (flagHandMIX == 1) || (flagHandWater == 1)))
		{
			flagHand=0;
		}
		if ((flagHandA == 1) || (flagHandB == 1) || (flagHandMIX == 1) || (flagHandWater == 1))
		{
			flagHand=1;
		}
		if (DataWater[0] && DataPumpA[0] && DataPumpB[0])
		{
			if (DataWater[0] != 'u')
			{
				LIn = atof(DataWater);
				if(flagHand==1){LIn=0;}
				if (LIn > 0.1)
				{
					NVIC_EnableIRQ(TIM2_IRQn);
					LWater = 0;
					flagW = 1;
					PumpControl(PWater, P_ON);
					DisplayControl(DWater, D_ON);
					count = 0;
				}
				if (LIn < 0.1)
				{
					flagW = 0;
				}
			}
			if (DataPumpA[0] != 'u')
			{
				Lp1 = atof(DataPumpA);
				if(flagHand==1){Lp1=0;}
				if (Lp1 > 0.1)
				{
					LPump1 = 0;
					flagP1 = 1;
					PumpControl(PNuA, P_ON);
					DisplayControl(DNuA, D_ON);
				}
				if (Lp1 < 0.1)
				{
					flagP1 = 0;
				}
			}
			if (DataPumpB[0] != 'u')
			{
				Lp2 = atof(DataPumpB);
				if(flagHand==1){Lp2=0;}
				if (Lp2 > 0.1)
				{
					LPump2 = 0;
					flagP2 = 1;
					PumpControl(PNuB, P_ON);
					DisplayControl(DNuB, D_ON);
				}

				if (Lp2 < 0.1)
				{
					flagP2 = 0;
				}
			}

			resetData(&DataWater);
			resetData(&DataPumpA);
			resetData(&DataPumpB);
		}
		if (flagCLI == 1)
		{
			NVIC_DisableIRQ(USART1_IRQn);
			strcpy(H_DataCLI,DataCLI);
			crc1='a';
			crc1_receive=*(H_DataCLI+18);
			crc1_receive=crc1_receive<<8;
			uint8_t temp5=*(H_DataCLI+19);
			crc1_receive=crc1_receive|temp5;
			for (int i=0;i<18;i++)
			{
				crc1+=*(H_DataCLI+i);
			}
			if (crc1==crc1_receive)
			{
 				strncpy(B_DataCLI, H_DataCLI,18);
				sprintf(result, "%s,%s",B_DataCLI, B_DataMix);
				strncpy(result1, result,35);
			}
			resetData(&DataCLI);
			flagCLI = 0;
			NVIC_EnableIRQ(USART1_IRQn);
		}
		if (flagMIX == 1)
		{
			strcpy(H_DataMix,DataMix);
			crc2='a';
			crc2_receive=*(H_DataMix+16);
			crc2_receive=crc2_receive<<8;
			crc2_receive=crc2_receive|*(H_DataMix+17);
			for (int i=0;i<16;i++)
			{
				crc2+=*(H_DataMix+i);
			}
			if (crc2==crc2_receive)
			{
				strncpy(B_DataMix, H_DataMix,16);
				sprintf(result, "%s,%s",B_DataCLI, B_DataMix);
				strncpy(result1, result,35);
			}
			
			resetData(&DataMix);
			flagMIX = 0;
			
		}
		
		TestYs201(10);
	}
	
}
