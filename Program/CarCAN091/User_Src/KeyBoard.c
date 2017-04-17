#include "KeyBoard.h" 

//主要配置。
//#define BOARD_091 1
//#define BOARD_091A 1
//#define BOARD_091B 1
#define BOARD_091C 1

#define SP_BIT_BSA_SYS_STS 22
#define SP_BIT_FRONT_RADAR 30

#ifdef BOARD_091
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_9,16,GPIOA,GPIO_Pin_8,15,ID_ESP},		//KEY1 HDC. 
											{GPIOB,GPIO_Pin_13,15, GPIOB,GPIO_Pin_12,2,ID_ESP},		//KEY2 ESC； ESC LED; --> TOBE Fixed!!
											{GPIOB,GPIO_Pin_10,6, GPIOB,GPIO_Pin_11,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY3 Front radar
											{GPIOB,GPIO_Pin_14,31, 0,0},	//KEY4 MUTE
											{GPIOB,GPIO_Pin_0,24,0,0},	//KEY5 MENU (B:BSA_SW); NC
											{GPIOB,GPIO_Pin_15,32,0,0},		//KEY6 TEL		
											{GPIOA,GPIO_Pin_4,26,0,0},		//KEY7 NAV_SW
											{GPIOA,GPIO_Pin_15,33,0,0},		//KEY8 RADIO (B:AVM key) 
											{GPIOB,GPIO_Pin_9,25,0,0},		//KEY9 MODE (B:NVS) ; LED NC (NVS)
											{GPIOB,GPIO_Pin_4,27,0,0},		//KEY10 HUD_SET (91:SET_SW); NC
											{GPIOB,GPIO_Pin_8,30,0,0},		//KEY11 BACK (B:LDWS)
											{GPIOB,GPIO_Pin_6,34,0,0},		//KEY12 HUD_UP	(91:SEEK+)
											{GPIOB,GPIO_Pin_7,35,0,0},		//KEY13 HUD_DONW (91:SEEK-)
											{GPIOA,GPIO_Pin_5,23,0,0},		//KEY14 KEY ON Power
											};
#endif
#ifdef BOARD_091A
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_9,16,GPIOA,GPIO_Pin_8,15,ID_ESP},		//KEY1 HDC 
											{GPIOB,GPIO_Pin_13,15, GPIOB,GPIO_Pin_12,2,ID_ESP},		//KEY2 ESC
											{GPIOB,GPIO_Pin_10,6, GPIOB,GPIO_Pin_11,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY3 Front radar
											{GPIOB,GPIO_Pin_14,31, 0,0},	//KEY4 MUTE
											{GPIOB,GPIO_Pin_0,24,GPIOB,GPIO_Pin_1,SP_BIT_BSA_SYS_STS,ID_PDC},	//KEY5 MENU (B:BSA_SW); BSA_LED
											{GPIOB,GPIO_Pin_15,32,0,0},		//KEY6 TEL		
											{GPIOA,GPIO_Pin_4,26,0,0},		//KEY7 NAV_SW
											{GPIOA,GPIO_Pin_15,33,0,0},		//KEY8 RADIO (B:AVM key)
											{GPIOB,GPIO_Pin_9,25,0,0},		//KEY9 MODE (B:NVS) ; LED NC (NVS)
											{GPIOB,GPIO_Pin_4,20,GPIOB,GPIO_Pin_5,1,ID_HUD},		//KEY10 HUD_SET (91:SET_SW) ; HUD_LED
											{GPIOB,GPIO_Pin_8,30,0,0},		//KEY11 BACK (B:LDWS); NC
											{GPIOB,GPIO_Pin_6,21,0,0},		//KEY12 HUD_UP	(91:SEEK+)
											{GPIOB,GPIO_Pin_7,22,0,0},		//KEY13 HUD_DONW (91:SEEK-)
											{GPIOA,GPIO_Pin_5,23,0,0},		//KEY14 KEY ON Power	//状态待定
											};
#endif
#ifdef BOARD_091B
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_9,16,GPIOA,GPIO_Pin_8,15,ID_ESP},		//KEY1 HDC 
											{GPIOB,GPIO_Pin_13,15, GPIOB,GPIO_Pin_12,2,ID_ESP},		//KEY2 ESC
											{GPIOB,GPIO_Pin_10,6, GPIOB,GPIO_Pin_11,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY3 Front radar
											{GPIOB,GPIO_Pin_14,31, 0,0},	//KEY4 MUTE
											{GPIOB,GPIO_Pin_0,7,GPIOB,GPIO_Pin_1,SP_BIT_BSA_SYS_STS,ID_PDC},	//KEY5 MENU (B:BSA_SW); BSA_LED
											{GPIOB,GPIO_Pin_15,32,0,0},		//KEY6 TEL		
											{GPIOA,GPIO_Pin_4,26,0,0},		//KEY7 NAV_SW
											{GPIOA,GPIO_Pin_15,18,0,0},		//KEY8 RADIO (B:AVM key)
											{GPIOB,GPIO_Pin_9,17,GPIOC,GPIO_Pin_15,3,ID_NVS},		//KEY9 MODE (B:NVS); NVS_LED
											{GPIOB,GPIO_Pin_4,20,GPIOB,GPIO_Pin_5,1,ID_HUD},		//KEY10 HUD_SET (91:SET_SW); HUD_LED
											{GPIOB,GPIO_Pin_8,19,GPIOC,GPIO_Pin_14,6,ID_AVM},		//KEY11 BACK (B:LDWS) ; LWDS_LED
											{GPIOB,GPIO_Pin_6,21,0,0},		//KEY12 HUD_UP	(91:SEEK+)
											{GPIOB,GPIO_Pin_7,22,0,0},		//KEY13 HUD_DONW (91:SEEK-)
											{GPIOA,GPIO_Pin_5,23,0,0},		//KEY14 KEY ON Power
											};
#endif
#ifdef BOARD_091C
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOA,GPIO_Pin_9,16,GPIOA,GPIO_Pin_8,15,ID_ESP},		//KEY1 HDC. 
											{GPIOB,GPIO_Pin_13,15, GPIOB,GPIO_Pin_12,2,ID_ESP},		//KEY2 ESC； ESC LED; --> TOBE Fixed!!
											{GPIOB,GPIO_Pin_10,6, GPIOB,GPIO_Pin_11,SP_BIT_FRONT_RADAR,ID_PDC},		//KEY3 Front radar
											{GPIOB,GPIO_Pin_14,31, 0,0},	//KEY4 MUTE
											{GPIOB,GPIO_Pin_0,7,GPIOB,GPIO_Pin_1,SP_BIT_BSA_SYS_STS,ID_PDC},	//KEY5 MENU (B C:BSA_SW);  BSA LED
											{GPIOB,GPIO_Pin_15,32,0,0},		//KEY6 TEL		
											{GPIOA,GPIO_Pin_4,18,0,0},		//KEY7 NAV_SW	C:AVM Skey
											{GPIOA,GPIO_Pin_15,33,0,0},		//KEY8 C:RADIO (B:AVM key) 
											{GPIOB,GPIO_Pin_9,25,0,0},		//KEY9 C:DVD MODE (B:NVS) ; LED NC (NVS)
											{GPIOB,GPIO_Pin_4,30,0,0},		//KEY10 C:DVD BACK (91:SET_SW); NC
											{GPIOB,GPIO_Pin_8,19,GPIOC,GPIO_Pin_14,6,ID_AVM},		//KEY11 C: LDWS Skey (B:LDWS)
											{GPIOB,GPIO_Pin_6,34,0,0},		//KEY12 C: DVD_Seekup	(91:SEEK+)
											{GPIOB,GPIO_Pin_7,35,0,0},		//KEY13 C: DVD Seek down  (91:SEEK-)
											{GPIOA,GPIO_Pin_5,23,0,0},		//KEY14 KEY ON Power
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
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉，待定，或浮空。GPIO_Mode_IN_FLOATING
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
/*
	//读取当前的状态
  for(i=0;i<IND_KEY_NUM;i++)
	{
		u8 tempVal=0;
		tempVal = GPIO_ReadInputDataBit(indKeyIO[i].GPIO_Port,indKeyIO[i].GPIO_Pin);
		if(indKeyStatePre[i] == tempVal )  //两次读值一样，即过滤掉机械抖动
		{
			if(tempVal == 0)	//Press down
			  keysBuff |= ((u16)1)<<i;
			else							//Release 
				keysBuff &= ~(((u16)1)<<i);
		}
		indKeyStatePre[i] = tempVal;
//		indKeyStatePrePre[i] = indKeyStatePre[i];
	}
*/
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
	
	
	encNum = TIM_GetCounter(TIM3);
	
	if((fabs(encNum - encNumPre) <= 1) || (fabs(encNum - encNumPre) == 0xffff))
		return 0;
	
	if(((encNum>encNumPre ) && (encNum-encNumPre < 1000))|| ((encNumPre - encNum > 1000)&&(encNumPre>encNum)))	//decrease
	{
		dir=2;
	}
	else if(((encNum < encNumPre ) && (encNumPre - encNum <1000))|| ((encNum - encNumPre > 1000)&&(encNum>encNumPre)))
	{
		dir=1;
	}
	else
		dir=0;
	
	encNumPre = encNum;
	
	return dir;
		
		
	
	
}
