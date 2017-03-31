#include "KeyBoard.h" 
#include "ConfigTable.h"

//主要配置
//#define BOARD_099B 1


//非一位控制的开关量. Todo: 写得更具有通用性。{ID_ESP,ID_AVM,ID_PDC,ID_HUD,ID_NVS}
#define KEY_TPMS 0
#define KEY_STARTSTOP 1
//#define SP_BIT_EMS_STARTSTOP 50

#ifdef BOARD_043C
KeyIO_t indKeyIO[] = {
											//{GPIOB,GPIO_Pin_0,36,0,0,0},		//TPMS Reset
											{GPIOA,GPIO_Pin_6,36,0,0,0,0},		//TPMS Reset
											};
#else
KeyIO_t indKeyIO[] = {
											//{GPIOB,GPIO_Pin_0,36,0,0,0},		//TPMS Reset
											//{GPIOB,GPIO_Pin_1,9,GPIOB,GPIO_Pin_5,0,0},	//Startstop 
											{GPIOA,GPIO_Pin_6,36,0,0,0,0},		//TPMS Reset
											{GPIOA,GPIO_Pin_7,9,GPIOB,GPIO_Pin_0,0,0},	//Startstop 
											
											};
#endif
/*
KeyIO_t indKeyIO[] = {
											{GPIOB,GPIO_Pin_0,36,0,0,0},		//TPMS Reset
											{GPIOB,GPIO_Pin_1,9,GPIOB,GPIO_Pin_2,0,0},	//Startstop 
											};
*/

//键值缓存
volatile u16 keysBuff; 
//开关状态缓存，当键值从按下变成松开时，开关状态翻转。
volatile u16 swBuff;
volatile char dirBuff;
u16 encNum=0;
u8 signalStartStop=0,signalTPMS=0;
u8 DDSResetTrigged=0;
											
static void ADCInit(void);

//
void KeyAndLEDInit(void)
{
	//独立按键  PA8 -Deactivate PB14 - Enable
	GPIO_InitTypeDef GPIO_InitStructure;
	u8 ki; 
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	
	//
	
	
	for(ki=0;ki < IND_KEY_NUM;ki++)
	{
		//Key
		GPIO_InitStructure.GPIO_Pin = indKeyIO[ki].GPIO_Pin;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉，待定，或浮空。GPIO_主                                    Mode_IN_FLOATING
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(indKeyIO[ki].GPIO_Port, &GPIO_InitStructure);
		
		//LED
		if(indKeyIO[ki].LED_Port!=0)
		{
			GPIO_InitStructure.GPIO_Pin = indKeyIO[ki].LED_Pin;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //Tobe confirmed.
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(indKeyIO[ki].LED_Port, &GPIO_InitStructure);
		}
	}
}

//每10ms调用一次，获得即时键值，获得每个按键的逻辑开关状态，按一次进行反转
//返回触发信号
u8 KeyScan(void)
{
	static u8 ksStartStop=0,ksTPMS=0;
	static u16 cntS=0,cntT=0,sendCnt=0;
	u8 tempVal=0;
	
	//TPMS Reset
	tempVal = GPIO_ReadInputDataBit(indKeyIO[KEY_TPMS].GPIO_Port,indKeyIO[KEY_TPMS].GPIO_Pin);
	switch(ksTPMS)
	{
		case 0://idle
			if(tempVal == 0)
			{
				ksTPMS=1;
				cntS=1;
			}
			break;
		case 1:
			if(tempVal==1)
				ksTPMS=0;
			else{
				cntS++;
				if(cntS>=1){//300){ //3s按键按下有效
					cntS=0;
					ksTPMS=2;
					signalTPMS=1;
					sendCnt=0;
					//DDSResetTrigged=1;	//发2s DDS Reset
				}	
			}
			break;
		case 2:
			if(tempVal==1){//release
				ksTPMS=0;
				signalTPMS = 0;
			}
				
			break;
	}
	/*
	if(DDSResetTrigged){
		//发送2s的DDS Reset信号
		
		if(sendCnt++ < 200)
			signalTPMS=1;
		else
		{
			signalTPMS=0;
			DDSResetTrigged=0;
			sendCnt=0;
		}
	}*/
#ifndef BOARD_043C
	//StartStop
	tempVal = GPIO_ReadInputDataBit(indKeyIO[KEY_STARTSTOP].GPIO_Port,indKeyIO[KEY_STARTSTOP].GPIO_Pin);
	switch(ksStartStop)
	{
		case 0://idle
			if(tempVal == 0)
			{
				ksStartStop=1;
				cntS=1;
			}
			break;
		case 1:
			if(tempVal==1)
				ksStartStop=0;
			else{
				cntS++;
				if(cntS>=50){ //500ms按键按下有效
					cntS=0;
					ksStartStop=2;
					signalStartStop = !signalStartStop;
					//if(signalStartStop==1)
					//SaveParamsToEEPROM(signalStartStop);	//存到
				}	
			}
			break;
		case 2:
			if(tempVal==1){
				ksStartStop=0;
			}
			break;
		
	}
	if(signalStartStop){
		keysBuff |= (u16)1 << KEY_STARTSTOP;
		GPIO_SetBits(indKeyIO[KEY_STARTSTOP].LED_Port, indKeyIO[KEY_STARTSTOP].LED_Pin);
	}
	else{ 
		keysBuff &= ~(u16)1 << KEY_STARTSTOP;
		GPIO_ResetBits(indKeyIO[KEY_STARTSTOP].LED_Port, indKeyIO[KEY_STARTSTOP].LED_Pin);
	}
#endif
	
	if(signalTPMS)
		keysBuff |= (u16)1 << KEY_TPMS;
	else 
		keysBuff &= ~(u16)1 << KEY_TPMS;
	
	return 1;
	/*
	//static u8 indKeyStatePre[IND_KEY_NUM]={2};
	static u8 ks[IND_KEY_NUM]={0};
	u8 trig=0;
//	static u8 indKeyStatePrePre[4]={2,2,2,2};
  u8 i;
	for(i=0;i<IND_KEY_NUM;i++)
	{
		u8 tempVal=0;
		tempVal = GPIO_ReadInputDataBit(indKeyIO[i].GPIO_Port,indKeyIO[i].GPIO_Pin);
		switch(ks[i])
		{
			case 0: //idle up
				if(tempVal==0)
				{
					ks[i]=1;
					keysBuff |= ((u16)1)<<i;
				}
				break;
			case 1:	//down
				if(tempVal==1)
				{
					ks[i] = 0;
					keysBuff &= ~(((u16)1)<<i);
					//key release，revert sw state
					if((swBuff & (((u16)1)<<i)) ==0)
						swBuff |= ((u16)1)<<i;
					else
						swBuff &=~(((u16)1)<<i);
					trig=1;
				}
				break;
			//case 2:	//release
			//	break;
		}
	}
	
	//EncoderRead();
	
	return trig;
	*/
}
/*
//根据开关状态来设置LED亮灭
void LEDUpdate(u8 *datRec, u32 id)
{
	u8 i;
	
	
	for(i=0;i<IND_KEY_NUM;i++)
	{
		if(indKeyIO[i].rID == id)
		{
			if(indKeyIO[i].LED_Port !=0 )
			{
				u8 Bn, bn;
				Bn = indKeyIO[i].rbitn / 8;	//在第几个字节
				bn = indKeyIO[i].rbitn % 8;	//第几位
				
				if((datRec[Bn] & (((u8)1)<<bn)) ==0)	//开关off
					GPIO_ResetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
				else
					GPIO_SetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
				//非一位控制的开关量的处理
				if(indKeyIO[i].rbitn == SP_BIT_EMS_STARTSTOP)
				{
					if((datRec[Bn] & (((u8)0x0f)<<bn)) ==0)	//开关off
						GPIO_ResetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
					else
						GPIO_SetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
				}
			}
		}
	}
}
*/



void EncoderInit(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_ICInitTypeDef TIM_ICInitStructure;

		/* Encoder unit connected to TIM3, 4X mode */    
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		/* TIM3 clock source enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		/* Enable GPIOA, clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

		GPIO_StructInit(&GPIO_InitStructure);
		/* Configure PA.06,07 as encoder input */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* Enable the TIM3 Update Interrupt 
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);*/

		/* Timer configuration in Encoder mode */
		TIM_DeInit(TIM3);
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

		TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
		TIM_TimeBaseStructure.TIM_Period = 0xffff;	//TOBE Confirmed 
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

		TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
																 TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_ICFilter = 6;
		TIM_ICInit(TIM3, &TIM_ICInitStructure);

		/*// Clear all pending interrupts
		TIM_ClearFlag(TIM3, TIM_IT_CC1);TIM_ClearFlag(TIM3, TIM_IT_CC2);
		TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);	//暂时不用中断 TIM_IT_Update
		TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);	
		*/
		//Reset counter
		TIM3->CNT = 0;

		// ENC_Clear_Speed_Buffer();

		TIM_Cmd(TIM3, ENABLE); 
}


//中断中执行，或者轮询。仅是按钮，中断中执行较合适。
char EncoderRead(void)
{
	static u8 isSetup=0;
	static u16 encNumPre=0;
	char dir=0;
		
	if(!isSetup)
	{
		encNum = TIM_GetCounter(TIM3);
		isSetup=1;
		return 0;
	}
	
	encNumPre = encNum;
	encNum = TIM_GetCounter(TIM3);
	
	if((encNum>encNumPre )|| (encNumPre - encNum > 0xffff/2))	//decrease
	{
		dir=2;
	}
	else if((encNum < encNumPre )|| (encNum - encNumPre > 0xffff/2))
	{
		dir=1;
	}
	else
		dir=0;
	
	return dir;
		
		
	
	
}
