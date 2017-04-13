#include "KeyBoard.h" 

//主要配置
//#define BOARD_099B 1


//SPecial Bit 非一位控制的开关量. Todo: 写得更具有通用性。{ID_ESP,ID_AVM,ID_PDC,ID_HUD,ID_NVS}
#define SP_BIT_EMS_STARTSTOP 50
#define SP_BIT_BSA_SYS_STS 22
#define SP_BIT_FRONT_RADAR 30



//todo: 将协议中所有位，写入一个共用结构体，以成员名调用
#ifdef BOARD_099
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_4,18,0,0,0,0},		//KEY1 AVM_Skey ; 
											{GPIOA,GPIO_Pin_5,19, GPIOB,GPIO_Pin_11,6,ID_AVM},	//KEY2 LDWS Skey；LED: LDWS Skey LED
											{GPIOA,GPIO_Pin_6,17, 0,0,0,0},		//KEY3 NVS Skey; 
											{GPIOA,GPIO_Pin_7,15, GPIOB,GPIO_Pin_10,2,ID_ESP},	//KEY4 ESC Off  LED: ESC LED
											{GPIOB,GPIO_Pin_0,16,	GPIOB,GPIO_Pin_2,15,ID_ESP},	//KEY5 HDC 			LED: HDC LED ??????
											{GPIOB,GPIO_Pin_1,26,0,0},		//KEY6 DVD NAVI	
											{GPIOC,GPIO_Pin_15,6,GPIOB,GPIO_Pin_3,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY7 Front Radar: 
											{GPIOC,GPIO_Pin_14,7,GPIOB,GPIO_Pin_5,SP_BIT_BSA_SYS_STS,ID_PDC},		//KEY8 BSA Switch			LED: BSA LED, 由PDC中BSASysSts即Bit22-23控制
											{GPIOC,GPIO_Pin_13,20,GPIOB,GPIO_Pin_7,1,ID_HUD},		//KEY9 HUD Skey: 		LED: HUD SKey LED
											{GPIOB,GPIO_Pin_6,21,0,0},		//KEY10 HUD Up
											{GPIOB,GPIO_Pin_4,22,0,0},		//KEY11 HUD Down
											//{GPIOA,GPIO_Pin_15,SP_KEY_STARTSTOP,GPIOB,GPIO_Pin_9,SP_BIT_EMS_STARTSTOP,ID_EMS},		//KEY12 StartStopSwith (A:NC)	LED: StartStop LED (A:NC)
											};
#endif

#ifdef BOARD_099A
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_4,18,0,0,0,0},		//KEY1 AVM_Skey ; 
											{GPIOA,GPIO_Pin_5,19, GPIOB,GPIO_Pin_11,6,ID_AVM},	//KEY2 LDWS Skey；LED: LDWS Skey LED
											{GPIOA,GPIO_Pin_6,17, 0,0,0,0},		//KEY3 NVS Skey; 
											{GPIOA,GPIO_Pin_7,15, GPIOB,GPIO_Pin_10,2,ID_ESP},	//KEY4 ESC Off  LED: ESC LED
											{GPIOB,GPIO_Pin_0,16,	GPIOB,GPIO_Pin_2,15,ID_ESP},	//KEY5 HDC 			LED: HDC LED ??????
											{GPIOB,GPIO_Pin_1,26,0,0},		//KEY6 DVD NAVI	
											{GPIOC,GPIO_Pin_15,6,GPIOB,GPIO_Pin_3,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY7 Front Radar: 
											{GPIOC,GPIO_Pin_14,7,GPIOB,GPIO_Pin_5,SP_BIT_BSA_SYS_STS,ID_PDC},		//KEY8 BSA Switch			LED: BSA LED
											{GPIOC,GPIO_Pin_13,20,GPIOB,GPIO_Pin_7,1,ID_HUD},		//KEY9 HUD Skey: 		LED: HUD SKey LED
											{GPIOB,GPIO_Pin_6,21,0,0},		//KEY10 HUD Up
											{GPIOB,GPIO_Pin_4,22,0,0},		//KEY11 HUD Down
											{GPIOA,GPIO_Pin_15,SP_KEY_STARTSTOP,GPIOB,GPIO_Pin_9,SP_BIT_EMS_STARTSTOP,ID_EMS},		//KEY12 StartStopSwith (A:NC)	LED: StartStop LED (A:NC)
											};
#endif
#ifdef BOARD_099B
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_4,32,0,0,0,0},		//KEY1 DVD_TEL
											{GPIOA,GPIO_Pin_5,25, GPIOB,GPIO_Pin_11,6,ID_AVM},	//KEY2 LDWS Skey；LED: LDWS Skey LED
											{GPIOA,GPIO_Pin_6,24, 0,0,0,0},		//KEY3 DVD MENU; 
											{GPIOA,GPIO_Pin_7,15, GPIOB,GPIO_Pin_10,2,ID_ESP},	//KEY4 ESC Off  LED: ESC LED
											{GPIOB,GPIO_Pin_0,16,	GPIOB,GPIO_Pin_2,15,ID_ESP},	//KEY5 HDC 			LED: HDC LED ??????
											{GPIOB,GPIO_Pin_1,26,0,0},		//KEY6 DVD NAVI	
											{GPIOC,GPIO_Pin_15,6,GPIOB,GPIO_Pin_3,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY7 Front Radar: 
											{GPIOC,GPIO_Pin_14,27,0,0,0,0},		//KEY8 DVD SET			LED: BSA LED
											{GPIOC,GPIO_Pin_13,33,0,0,0,0},		//KEY9 DVD Radio: 		LED: HUD SKey LED
											{GPIOB,GPIO_Pin_6,34,0,0},		//KEY10 DVD Seekup
											{GPIOB,GPIO_Pin_4,35,0,0},		//KEY11 DVD Seekdown
											//{GPIOB,GPIO_Pin_6,9,0,0},		//KEY12 NC	LED: StartStop LED (A:NC)
											};
#endif
#ifdef BOARD_099C
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_4,32,0,0,0,0},		//KEY1 DVD_TEL
											{GPIOA,GPIO_Pin_5,19, GPIOB,GPIO_Pin_11,6,ID_AVM},	//KEY2 DVD MODE；LED: LDWS Skey LED
											{GPIOA,GPIO_Pin_6,18, 0,0,0,0},		//KEY3 AVM Skey; 
											{GPIOA,GPIO_Pin_7,15, GPIOB,GPIO_Pin_10,2,ID_ESP},	//KEY4 ESC Off  LED: ESC LED
											{GPIOB,GPIO_Pin_0,16,	GPIOB,GPIO_Pin_2,15,ID_ESP},	//KEY5 HDC 			LED: HDC LED ??????
											{GPIOB,GPIO_Pin_1,26,0,0},		//KEY6 DVD NAVI	
											{GPIOC,GPIO_Pin_15,6,GPIOB,GPIO_Pin_3,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY7 Front Radar: 
											{GPIOC,GPIO_Pin_14,7,GPIOB,GPIO_Pin_5,SP_BIT_BSA_SYS_STS,ID_PDC},		//KEY8 BSA Switch			LED: BSA LED
											{GPIOC,GPIO_Pin_13,33,0,0,0,0},		//KEY9 DVD Radio: 		LED: HUD SKey LED
											{GPIOB,GPIO_Pin_6,34,0,0},		//KEY10 DVD Seekup
											{GPIOB,GPIO_Pin_4,35,0,0},		//KEY11 DVD Seekdown
											//{GPIOB,GPIO_Pin_6,9,0,0},		//KEY12 NC	LED: StartStop LED (A:NC)
											};
#endif
#ifdef BOARD_099D	//跟B相近, 多了StartStopSwitch
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_4,32,0,0,0,0},		//KEY1 DVD_TEL
											{GPIOA,GPIO_Pin_5,25, GPIOB,GPIO_Pin_11,6,ID_AVM},	//KEY2 LDWS Skey；LED: LDWS Skey LED
											{GPIOA,GPIO_Pin_6,24, 0,0,0,0},		//KEY3 DVD MENU; 
											{GPIOA,GPIO_Pin_7,15, GPIOB,GPIO_Pin_10,2,ID_ESP},	//KEY4 ESC Off  LED: ESC LED
											{GPIOB,GPIO_Pin_0,16,	GPIOB,GPIO_Pin_2,15,ID_ESP},	//KEY5 HDC 			LED: HDC LED ??????
											{GPIOB,GPIO_Pin_1,26,0,0},		//KEY6 DVD NAVI	
											{GPIOC,GPIO_Pin_15,6,GPIOB,GPIO_Pin_3,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY7 Front Radar: 
											{GPIOC,GPIO_Pin_14,27,0,0,0,0},		//KEY8 DVD SET			LED: BSA LED
											{GPIOC,GPIO_Pin_13,33,0,0,0,0},		//KEY9 DVD Radio: 		LED: HUD SKey LED
											{GPIOB,GPIO_Pin_6,34,0,0},		//KEY10 DVD Seekup
											{GPIOB,GPIO_Pin_4,35,0,0},		//KEY11 DVD Seekdown
											{GPIOA,GPIO_Pin_15,SP_KEY_STARTSTOP,GPIOB,GPIO_Pin_9,SP_BIT_EMS_STARTSTOP,ID_EMS},		//KEY12 StartStopSwith (A:NC)	LED: StartStop LED (A:NC)
											};
#endif
#ifdef BOARD_099E	//跟C相近,多了StartStopSwitch
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_4,32,0,0,0,0},		//KEY1 DVD_TEL
											{GPIOA,GPIO_Pin_5,19, GPIOB,GPIO_Pin_11,6,ID_AVM},	//KEY2 DVD MODE；LED: LDWS Skey LED
											{GPIOA,GPIO_Pin_6,18, 0,0,0,0},		//KEY3 AVM Skey; 
											{GPIOA,GPIO_Pin_7,15, GPIOB,GPIO_Pin_10,2,ID_ESP},	//KEY4 ESC Off  LED: ESC LED
											{GPIOB,GPIO_Pin_0,16,	GPIOB,GPIO_Pin_2,15,ID_ESP},	//KEY5 HDC 			LED: HDC LED ??????
											{GPIOB,GPIO_Pin_1,26,0,0},		//KEY6 DVD NAVI	
											{GPIOC,GPIO_Pin_15,6,GPIOB,GPIO_Pin_3,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY7 Front Radar: 
											{GPIOC,GPIO_Pin_14,7,GPIOB,GPIO_Pin_5,SP_BIT_BSA_SYS_STS,ID_PDC},		//KEY8 BSA Switch			LED: BSA LED
											{GPIOC,GPIO_Pin_13,33,0,0,0,0},		//KEY9 DVD Radio: 		LED: HUD SKey LED
											{GPIOB,GPIO_Pin_6,34,0,0},		//KEY10 DVD Seekup
											{GPIOB,GPIO_Pin_4,35,0,0},		//KEY11 DVD Seekdown
											{GPIOA,GPIO_Pin_15,SP_KEY_STARTSTOP,GPIOB,GPIO_Pin_9,SP_BIT_EMS_STARTSTOP,ID_EMS},		//KEY12 StartStopSwith (A:NC)	LED: StartStop LED (A:NC)
											};
#endif

//键值缓存
volatile u16 keysBuff; 
//开关状态缓存，当键值从按下变成松开时，开关状态翻转。
volatile u16 swBuff;
volatile char dirBuff;
u16 encNum=0;
											
static void ADCInit(void);

//
void KeyAndLEDInit(void)
{
	//独立按键  PA8 -Deactivate PB14 - Enable
	GPIO_InitTypeDef GPIO_InitStructure;
	u8 ki; 
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	
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
					#ifdef SP_KEY_STARTSTOP
					if(indKeyIO[i].bitn!=SP_KEY_STARTSTOP)
					{
						ks[i]=1;
						keysBuff |= ((u16)1)<<i;
					}
					else
					{	//做自锁处理，按下翻转
						if((keysBuff & (((u16)1)<<i)) ==0)
							keysBuff |= ((u16)1)<<i;
						else
							keysBuff &=~(((u16)1)<<i);
						
						ks[i]=1;
					}
					#else
					ks[i]=1;
					keysBuff |= ((u16)1)<<i;
					#endif
				}
				break;
			case 1:	//down
				if(tempVal==1)
				{
					#ifdef SP_KEY_STARTSTOP
					if(indKeyIO[i].bitn!=SP_KEY_STARTSTOP)
					{
						ks[i] = 0;
						keysBuff &= ~(((u16)1)<<i);
					}
					else
					{	//特殊按键做自锁处理，松开不变 锁住状态
						ks[i]=0;
					}
					#else
					ks[i] = 0;
					keysBuff &= ~(((u16)1)<<i);
					#endif
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
	/*
	//Start stop key做自锁处理
	#ifdef SP_KEY_STARTSTOP
		if(swBuff & ((u16)1 << 9))
			keysBuff |= (((u16)1)<<9);
		else
			keysBuff &=~(((u16)1)<<9);
	#endif
	*/
	
	//EncoderRead();
	
	return trig;
}
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
				if(indKeyIO[i].rbitn == SP_BIT_BSA_SYS_STS){
					//取bit22-23,
					u8 val=datRec[Bn] & ((u8)0x3<<bn);
					val = val >> bn;
					LEDSMSet(indKeyIO[i].LED_Port,indKeyIO[i].LED_Pin,val);
				}
				if(indKeyIO[i].rbitn == SP_BIT_FRONT_RADAR){
				//取bit30-31
					u8 val=datRec[Bn] & ((u8)0x3<<bn);
					val = val >> bn;
					LEDRadarSMSet(indKeyIO[i].LED_Port,indKeyIO[i].LED_Pin,val);
				}
			}
		}
	}
}
//todo: 若在c++，可封装成class
static GPIO_TypeDef* GPIO_sm;
static uint16_t	PIN_sm;
static u8 st=0;	
void LEDSMSet(GPIO_TypeDef* GPIOx,uint16_t PINx,u8 val)
{
	GPIO_sm=GPIOx;
	PIN_sm=PINx;
	if(val==0){
		GPIO_ResetBits(GPIOx, PINx);
		st=0;
	}
	else if(val==1){
		GPIO_SetBits(GPIOx, PINx);
		st=0;
	}
	else if(val==2){
		st=1;
	}
}
//每10ms调用一次
void LEDFlashSM()
{
	static u8 tcnt=0;
	switch(st){
		case 0:
			//do nothing
			break;
		case 1:
			GPIO_SetBits(GPIO_sm, PIN_sm);
			tcnt=0;
			st=2;
			break;
		case 2:
			//count 330ms
			tcnt++;
			if(tcnt>=33){
				GPIO_ResetBits(GPIO_sm, PIN_sm);
				tcnt=0;
				st=3;
			}
			break;
		case 3:
			//count 670ms
			tcnt++;
			if(tcnt>=66){
				//take 10 more ms to next step 
				tcnt=0;
				st=1;
			}
			break;
	}
	
}

static GPIO_TypeDef* GPIO_smr;
static uint16_t	PIN_smr;
static u8 str=0;	
void LEDRadarSMSet(GPIO_TypeDef* GPIOx,uint16_t PINx,u8 val)
{
	GPIO_smr=GPIOx;
	PIN_smr=PINx;
	if(val==0){
		GPIO_ResetBits(GPIOx, PINx);
		str=0;
	}
	else if(val==1){
		GPIO_SetBits(GPIOx, PINx);
		str=0;
	}
	else if(val==2){
		str=1;
	}
}
//每10ms调用一次
void LEDRadarFlashSM()
{
	static u8 tcnt=0;
	switch(str){
		case 0:
			//do nothing
			break;
		case 1:
			GPIO_SetBits(GPIO_smr, PIN_smr);
			tcnt=0;
			str=2;
			break;
		case 2:
			//count 330ms
			tcnt++;
			if(tcnt>=33){
				GPIO_ResetBits(GPIO_smr, PIN_smr);
				tcnt=0;
				str=3;
			}
			break;
		case 3:
			//count 670ms
			tcnt++;
			if(tcnt>=66){
				//take 10 more ms to next step 
				tcnt=0;
				str=1;
			}
			break;
	}
	
}


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
