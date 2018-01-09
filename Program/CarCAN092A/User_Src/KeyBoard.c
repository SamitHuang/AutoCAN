#include "KeyBoard.h" 

#define PIN_DEFROST_CTRL GPIO_Pin_3
#define PIN_WIND_HEAT_CTRL GPIO_Pin_4
#define PIN_DEFROST_LED GPIO_Pin_0
#define PIN_WIND_HEAT_LED GPIO_Pin_5

#define BIT_SDB_REAR_DEFROST	9
#define BIT_SDB_FRONT_WIND_HEAT 12

//u8 ctrlSw[2]={0};
u8 swRearDefrostTrig=0,swFrontWindHeatTrig=0;
u8 isFrontWindHeatExist=0;
//u8 swDefrostState=0,swWindHeatState=0;

void InsertVal2Keybuff(u8 CAN_bitn,u8 val);


#ifdef BOARD_092
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOB,GPIO_Pin_9,1,GPIOA,GPIO_Pin_4,2,ID_HVAC},		//AC Off
											{GPIOB,GPIO_Pin_8,5, GPIOA,GPIO_Pin_7,6,ID_HVAC},		//AC Cycle
											{GPIOB,GPIO_Pin_7,3, GPIOB,GPIO_Pin_1,31,ID_HVAC},		//AC Max
											{GPIOA,GPIO_Pin_8,8, GPIOB,GPIO_Pin_10,38,ID_HVAC},		//Front Defrost
											{GPIOB,GPIO_Pin_6,BIT_SDB_REAR_DEFROST,GPIOB,GPIO_Pin_0,0xFF,0},//R_Defrost		//���˪��״̬�ķ���Ҫ�ۺ��жϣ����⴦��
											{GPIOB,GPIO_Pin_13,0,GPIOB,GPIO_Pin_11,29,ID_HVAC},	//AC Request--->A/C
											{GPIOA,GPIO_Pin_15,14,0,0,0,0},		//PM25  //GPIOA,GPIO_Pin_4,63,ID_DVD}
											{GPIOB,GPIO_Pin_5,7,0,0},		//Fan down
											{GPIOA,GPIO_Pin_9,6,0,0},		//Fan up
											};
#endif
#ifdef BOARD_092A //H
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOB,GPIO_Pin_9,1,GPIOA,GPIO_Pin_4,2,ID_HVAC},		//AC Off
											{GPIOB,GPIO_Pin_8,2, GPIOA,GPIO_Pin_7,54,ID_HVAC},		//Rear AC
											{GPIOB,GPIO_Pin_7,4, GPIOB,GPIO_Pin_1,44,ID_HVAC},		//Climate
											{GPIOA,GPIO_Pin_8,8, GPIOB,GPIO_Pin_10,38,ID_HVAC},	//Front Defrost
											{GPIOB,GPIO_Pin_6,BIT_SDB_REAR_DEFROST,GPIOB,GPIO_Pin_0,0xFF,0},//R_Defrost sw
											{GPIOB,GPIO_Pin_13,13,GPIOB,GPIO_Pin_11,55,ID_AC},	//Anion
											{GPIOA,GPIO_Pin_15,14,0,0,0,0},		//PM25 - 10 
											//{GPIOA,GPIO_Pin_9,5, 0,0,0,0},		//AC Cycle
											//{GPIOB,GPIO_Pin_5,BIT_SDB_FRONT_WIND_HEAT,0,0,0,0},		//Front Wind heat sw
											{GPIOB,GPIO_Pin_5,7,0,0},		//Fan down
											{GPIOA,GPIO_Pin_9,6,0,0},		//Fan up									
											};
#endif
#ifdef BOARD_092B //K
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOB,GPIO_Pin_9,1,GPIOA,GPIO_Pin_4,2,ID_HVAC},		//AC Off
											{GPIOB,GPIO_Pin_8,2, GPIOA,GPIO_Pin_7,54,ID_HVAC},		//Rear AC
											{GPIOB,GPIO_Pin_7,4, GPIOB,GPIO_Pin_1,44,ID_HVAC},		//Climate
											{GPIOA,GPIO_Pin_8,8, GPIOB,GPIO_Pin_10,38,ID_HVAC},	//Front Defrost
											{GPIOB,GPIO_Pin_6,BIT_SDB_REAR_DEFROST,GPIOB,GPIO_Pin_0,0xFF,0},//R_Defrost sw
											{GPIOB,GPIO_Pin_13,13,GPIOB,GPIO_Pin_11,55,ID_AC},	//Anion
											{GPIOA,GPIO_Pin_15,14,0,0,0,0},		//PM25	//GPIOA,GPIO_Pin_4,63,ID_DVD
											{GPIOA,GPIO_Pin_9,11,GPIOA,GPIO_Pin_1,7,ID_DVR},		//DVD Urgency 
											{GPIOB,GPIO_Pin_5,BIT_SDB_FRONT_WIND_HEAT,GPIOA,GPIO_Pin_5,0xFF,0},		//Front Wind heat sw
//											{GPIOB,GPIO_Pin_5,6,0,0},		//Fan up
//											{GPIOA,GPIO_Pin_9,7,0,0},		//Fan down
											};
#endif
#ifdef BOARD_092C
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOB,GPIO_Pin_9,1,GPIOA,GPIO_Pin_4,2,ID_HVAC},		//AC Off
											{GPIOB,GPIO_Pin_8,2, GPIOA,GPIO_Pin_7,45,ID_HVAC},		//Rear AC
											{GPIOB,GPIO_Pin_7,4, GPIOB,GPIO_Pin_1,44,ID_HVAC},		//Climate
											{GPIOA,GPIO_Pin_8,8, GPIOB,GPIO_Pin_10,38,ID_HVAC},	//Front Defrost
											{GPIOB,GPIO_Pin_6,BIT_SDB_REAR_DEFROST,GPIOB,GPIO_Pin_0,0xFF,0},//R_Defrost sw
											{GPIOB,GPIO_Pin_13,13,GPIOB,GPIO_Pin_11,55,ID_AC},	//Anion
											{GPIOA,GPIO_Pin_15,14,0,0,0,0},		//PM25	//GPIOA,GPIO_Pin_4,63,ID_DVD
											{GPIOA,GPIO_Pin_9,11,GPIOA,GPIO_Pin_1,7,ID_DVR},		//DVD Urgency 
											{GPIOB,GPIO_Pin_5,5,GPIOA,GPIO_Pin_5,6,ID_HVAC},		//Front Wind heat sw
											};
#endif

#ifdef BOARD_092C_MASS_PRODUCE  //F,K  This corresponds to 092K
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOB,GPIO_Pin_9,1,GPIOA,GPIO_Pin_4,2,ID_HVAC},		//AC Off
											{GPIOB,GPIO_Pin_8,2, GPIOA,GPIO_Pin_7,54,ID_HVAC},		//Rear AC
											{GPIOB,GPIO_Pin_7,4, GPIOB,GPIO_Pin_1,44,ID_HVAC},		//Climate
											{GPIOA,GPIO_Pin_8,8, GPIOB,GPIO_Pin_10,38,ID_HVAC},	//Front Defrost
											{GPIOB,GPIO_Pin_6,BIT_SDB_REAR_DEFROST,GPIOB,GPIO_Pin_0,0xFF,0},//R_Defrost sw
											{GPIOB,GPIO_Pin_13,13,GPIOB,GPIO_Pin_11,55,ID_AC},	//Anion
											{GPIOA,GPIO_Pin_15,10,0,0,0,0},		//PM25	//GPIOA,GPIO_Pin_4,63,ID_DVD
											{GPIOA,GPIO_Pin_9,11,GPIOA,GPIO_Pin_1,7,ID_DVR},		//DVD Urgency 
											{GPIOB,GPIO_Pin_5,5,GPIOA,GPIO_Pin_5,6,ID_HVAC},		//ACCycle
//											{GPIOB,GPIO_Pin_5,6,0,0},		//Fan up
//											{GPIOA,GPIO_Pin_9,7,0,0},		//Fan down
											};
#endif

#ifdef BOARD_092G //J
KeyIO_t indKeyIO[IND_KEY_NUM] = {
											{GPIOB,GPIO_Pin_9,1,GPIOA,GPIO_Pin_4,2,ID_HVAC},		//AC Off
											{GPIOB,GPIO_Pin_8,2, GPIOA,GPIO_Pin_7,54,ID_HVAC},		//Rear AC
											{GPIOB,GPIO_Pin_7,4, GPIOB,GPIO_Pin_1,44,ID_HVAC},		//Climate
											{GPIOA,GPIO_Pin_8,8, GPIOB,GPIO_Pin_10,38,ID_HVAC},	//Front Defrost
											{GPIOB,GPIO_Pin_6,BIT_SDB_REAR_DEFROST,GPIOB,GPIO_Pin_0,0xFF,0},//R_Defrost sw
											{GPIOB,GPIO_Pin_13,13,GPIOB,GPIO_Pin_11,55,ID_AC},	//Anion
											{GPIOA,GPIO_Pin_15,14,0,0,0,0},		//PM25	//GPIOA,GPIO_Pin_4,63,ID_DVD
											{GPIOA,GPIO_Pin_9,11,GPIOA,GPIO_Pin_1,7,ID_DVR},		//DVD Urgency 
											{GPIOB,GPIO_Pin_5,5,GPIOA,GPIO_Pin_5,6,ID_HVAC},		//ACCycle
											};
#endif



//��ֵ����
volatile u16 keysBuff; 
//����״̬���棬����ֵ�Ӱ��±���ɿ�ʱ������״̬��ת��
volatile u16 swBuff;

static void ADCInit(void);



//
void KeyAndLEDInit(void)
{
	//��������  PA8 -Deactivate PB14 - Enable
	GPIO_InitTypeDef GPIO_InitStructure;
	u8 ki; 
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
	for(ki=0;ki < IND_KEY_NUM;ki++)
	{
		//Key
		GPIO_InitStructure.GPIO_Pin = indKeyIO[ki].GPIO_Pin;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //�������������򸡿ա�GPIO_Mode_IN_FLOATING
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
	//additional R Defrost SW
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
	GPIO_InitStructure.GPIO_Pin = PIN_DEFROST_CTRL|PIN_WIND_HEAT_CTRL;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //Tobe confirmed.
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	Control(PIN_WIND_HEAT_CTRL,0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	
}


//������������
void Control(uint16_t pinx, u8 on)
{
	GPIO_TypeDef *GPIOx;
	
	if(pinx==PIN_WIND_HEAT_LED)
		GPIOx=GPIOA;
	else
		GPIOx=GPIOB;
	
	if(on==1)
		GPIO_SetBits(GPIOx, pinx);
	else
		GPIO_ResetBits(GPIOx,pinx);
}

//ÿ10ms����һ�Σ��������KeyScan()����,keys2candata��ǰ��
//#define STAY_TIME (u32)90000	//unit: *10ms
#define TIME_LOST_ON_KEY_POSTION 5000	//unit: ms
void RearDefrostProcessor(void){
	static u8 sd=0;	//state rear defrost 
	static u32 td=0;	//time cnt
	static u8 DVDKeyRearDefrostPre=0;
	static u8 DVDRearDefrostTrig=0;
	u8 isONSignalLost=0;
	u32 	tCur=0;
	//process input
	if((DVDKeyRearDefrostPre==0) && (DVDKeyRearDefrost==1))
		DVDRearDefrostTrig=1;
	DVDKeyRearDefrostPre = DVDKeyRearDefrost;
	
	//state machine
	switch(sd){
	case 0:
		//idle
		if((swRearDefrostTrig==1) || 	//SDB Rear Defrost switch
				(VoiceRearDefrostRequest==2) || //Voice request ON
				(DVDRearDefrostTrig==1)	//DVD request ON
				){
			swRearDefrostTrig=0;
			DVDRearDefrostTrig=0;
			VoiceRearDefrostRequest=0; 	//�����źŲ���һֱ������Ҫ�ֶ�����.
			if(BCMKeyPosition>=2){
				//���ڵ��ΪONʱ����
				Control(PIN_DEFROST_CTRL,1);
				Control(PIN_DEFROST_LED,1);	
				td=0;
				sd=1;
			}
			//InsertVal2Keybuff(BIT_SDB_REAR_DEFROST,1);
			
		}
		break;
	case 1:
		//working
		//timing
		//u8 isTimeOver=0;
		//�ж��ź��Ƿ�ʧ
		tCur=millis();
		if(tCur - lastUpdateBCMKeyPosition >= TIME_LOST_ON_KEY_POSTION)
			isONSignalLost=1;
		//��ʱ15mins
		td++;
		if(td>=90000){//15*60*100,15mins
			td=0;
			Control(PIN_DEFROST_CTRL,0);
			Control(PIN_DEFROST_LED,0);
			sd=0;
		}
		//turn off manually 
		if((swRearDefrostTrig==1) ||
				(VoiceRearDefrostRequest==1) || //request OFF
				(DVDRearDefrostTrig==1) ||
				(isONSignalLost==1) ||
				(BCMKeyPosition<2) 
				){
			swRearDefrostTrig=0;
			DVDRearDefrostTrig=0;
			VoiceRearDefrostRequest=0;
			//VoiceRearDefrostRequest=0; 	//����
			Control(PIN_DEFROST_CTRL,0);
			Control(PIN_DEFROST_LED,0);
			sd=0;
				
		}
		break;
	}
	//�����˪����״̬��CAN���ߣ������������������Ӧ�ź�
	//if(stateRearDefrost==1)
	InsertVal2Keybuff(BIT_SDB_REAR_DEFROST,sd);
}

#ifndef BOARD_092B
//092û�д˹���
void FrontWindHeatProcessor(void){}
#else
void FrontWindHeatProcessor(void){
	static u8 st=0;	//state rear defrost 
	static u32 tc;	//time cnt
	u8 isTimeOver=0;
	u8 isONSignalLost=0;
	u32 	tCur;
	static u8 ACFrontDefrostPre=0;
	u8 ACFrontDefrostTrig=0;
	if(ACFrontDefrostPre==0 && ACFrontDefrostRequest==1)
		ACFrontDefrostTrig=1;
	ACFrontDefrostPre = ACFrontDefrostRequest;
	switch(st){
	case 0:
		//idle
		if((swFrontWindHeatTrig==1)||(ACFrontDefrostTrig==1)){
			swFrontWindHeatTrig=0;
			ACFrontDefrostTrig=0;
			if((EngineRunningStatus==1) && (BCMKeyPosition>=2)){
				//���������������������
				Control(PIN_WIND_HEAT_CTRL,1);
				Control(PIN_WIND_HEAT_LED,1);
				tc=0;
				st=1;
			}
		}
		break;
	case 1:
		
		//working
		//timeing
		//�ж��ź��Ƿ�ʧ
		tCur=millis();
		if(tCur - lastUpdateBCMKeyPosition >= TIME_LOST_ON_KEY_POSTION)
			isONSignalLost=1;
		tc++;
		if(tc>=30000){	//5*60*100
			tc=0;
			isTimeOver=1;
		}
		if((swFrontWindHeatTrig==1) || (isTimeOver==1) || (EngineRunningStatus==0) ||
			(isONSignalLost==1) || (BCMKeyPosition<2 )){ 
			swFrontWindHeatTrig=0;
			Control(PIN_WIND_HEAT_CTRL,0);
			Control(PIN_WIND_HEAT_LED,0);
			st=0;
		}
		break;
	}
}
#endif

//ÿ10ms����һ��
void DefrostAndWindHeatProcessor(void)
{
	static u8 stateDefrost=0,stateWindHeat=0;
	static u32 td=0,ts=0;
	
	switch(stateDefrost){
	case 0://δ����
		if(swRearDefrostTrig==1){
			swRearDefrostTrig=0;
		
			Control(PIN_DEFROST_CTRL,1);
			Control(PIN_DEFROST_LED,1);
			td=0;
			stateDefrost=1;
			
			
		}
		break;
	case 1://�ѿ���
		td++;
		if(td>=90000){//15*60*100,15mins
			Control(PIN_DEFROST_CTRL,0);
			Control(PIN_DEFROST_LED,0);
			stateDefrost=0;
		}
		if(swRearDefrostTrig==1){
			swRearDefrostTrig=0;
			//�ֶ��ر�
			Control(PIN_DEFROST_CTRL,0);
			Control(PIN_DEFROST_LED,0);
			stateDefrost=0;
		}
		break;
	}
	
	switch(stateWindHeat){
	case 0://δ����
		if(swFrontWindHeatTrig==1){
			swFrontWindHeatTrig=0;
			if(rpm>=750)
			{
				Control(PIN_WIND_HEAT_CTRL,1);
				Control(PIN_WIND_HEAT_LED,1);
				ts=0;
				stateWindHeat=1;
			}
			
		}
		break;
	case 1://�ѿ���
		ts++;
		if(ts>=90000){//15*60*100
			Control(PIN_WIND_HEAT_CTRL,0);
			Control(PIN_WIND_HEAT_LED,0);
			stateWindHeat=0;
		}
		if(swFrontWindHeatTrig==1){
			swFrontWindHeatTrig=0;
			//�ֶ��ر�
			Control(PIN_WIND_HEAT_CTRL,0);
			Control(PIN_WIND_HEAT_LED,0);
			stateWindHeat=0;
		}
		//��ת���¹�ϵ
		if(rpm<750)
		{
			//�ֶ��ر�
			Control(PIN_WIND_HEAT_CTRL,0);
			Control(PIN_WIND_HEAT_LED,0);
			stateWindHeat=0;
		}
		break;
	}
}
//����keysbuff��ĳһλֵ ��CAN_bitn��ͨ��Э���е�λ
void InsertVal2Keybuff(u8 CAN_bitn,u8 val){
	u8 i;
	for(i=0;i<IND_KEY_NUM;i++)
	{
		if(indKeyIO[i].bitn==CAN_bitn){
				if(val==0)
					keysBuff &= ~(((u16)1)<<i);
				else
					keysBuff |= ((u16)1)<<i;
		}	
	}
}
//ÿ10ms����һ�Σ���ü�ʱ��ֵ�����ÿ���������߼�����״̬����һ�ν��з�ת
//���ش����ź�
u8 KeyScan(void)
{
	//static u8 indKeyStatePre[IND_KEY_NUM]={2,};
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
					//������λ��������ת
					if((indKeyIO[i].bitn==BIT_SDB_REAR_DEFROST)||(indKeyIO[i].bitn==BIT_SDB_FRONT_WIND_HEAT))
					{
						/* ���÷��� Rear Defrost SW��wind heart Sw
						u8 on=0;
						if((keysBuff & (((u16)1)<<i)) ==0){
								keysBuff |= ((u16)1)<<i;
								on=1;
						}else{
								keysBuff &=~(((u16)1)<<i);
								on=0;
						}*/
						if(indKeyIO[i].bitn==BIT_SDB_REAR_DEFROST){
							swRearDefrostTrig=1;
							//swDefrostState=on;
						}
						if(indKeyIO[i].bitn==BIT_SDB_FRONT_WIND_HEAT){
							swFrontWindHeatTrig=1;
							//swWindHeatState=on;
						}
						ks[i]=1;
					}
					else
					{
						ks[i]=1;
						keysBuff |= ((u16)1)<<i;
					}
				}
				break;
			case 1:	//down
				if(tempVal==1)
				{
					//������λ
					if((indKeyIO[i].bitn==BIT_SDB_REAR_DEFROST)||(indKeyIO[i].bitn==BIT_SDB_FRONT_WIND_HEAT))
					{
						ks[i] = 0;
					}
					else
					{
						ks[i] = 0;
						keysBuff &= ~(((u16)1)<<i);
					}
					//key release��revert sw state
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
	
	return trig;
}
//���ݿ���״̬������LED����
void LEDUpdate(u8 *datRec, u32 id)
{
	u8 i;
	
	
	for(i=0;i<IND_KEY_NUM;i++)
	{
		if(id == indKeyIO[i].rID )
		{
			if((indKeyIO[i].LED_Port !=0 ) && (indKeyIO[i].rbitn!=0xFF))
			{
				u8 Bn, bn;
				Bn = indKeyIO[i].rbitn / 8;	//�ڵڼ����ֽ�
				bn = indKeyIO[i].rbitn % 8;	//�ڼ�λ
				if((datRec[Bn] & (((u8)1)<<bn)) ==0)	//����off
					GPIO_ResetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
				else
					GPIO_SetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
			//	if((sw & (((u16)1)<<i)) ==0)
			//		GPIO_ResetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
			//	else
			//		GPIO_SetBits(indKeyIO[i].LED_Port, indKeyIO[i].LED_Pin);
			}
		}
	}
}
