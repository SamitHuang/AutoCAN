#include "CANCom.h"

#define _USE_075_BOARD 1


CanTxMsg TxMessage;
CanRxMsg RxMessage;

volatile TestStatus TestRx;
extern uint8_t canRet;
volatile u16 rpm;

volatile u8 BCMKeyPosition=0;
volatile u8 DVDKeyRearDefrost=0;
volatile u8 VoiceRearDefrostRequest=0;
volatile u8 EngineRunningStatus=0;
volatile u8 ACFrontDefrostRequest=0;
volatile u32 lastUpdateBCMKeyPosition=0;


//将bit: start_idx,start_idx+1,...start_idx+len-1 的值读出来,存于pval. 如bit:19,20
//todo: 不支持跨字节的多位提取。如(15,3)->取bit 15,16,17，跨了第2,3字节
#define RB_NUM 5
CAN_ReadBack_t ReadBackTable[RB_NUM]={
			{19,2,ID_BCM,&BCMKeyPosition},
			{7,1,ID_DVD,&DVDKeyRearDefrost},
			{2,2,ID_DVD_EVENT,&VoiceRearDefrostRequest},
			{43,1,ID_EMS,&EngineRunningStatus},
			{38,1,ID_HVAC,&ACFrontDefrostRequest}
		};

//读取复杂逻辑的信号，写到readback表
void ReadLogicIput(u8 *datRec, u32 id){
	u8 i;
	
	for(i=0;i<RB_NUM;i++){
		if(id == ReadBackTable[i].id ){
			u8 Bn, bn,bitMask,val;
			Bn = ReadBackTable[i].start_idx / 8;	//在第几个字节
			bn = ReadBackTable[i].start_idx % 8;	//第几位
			bitMask= (u8)((0x01<<ReadBackTable[i].len) - 1)<<bn;	//
			val=(datRec[Bn] & bitMask) >> bn;
				
			*(ReadBackTable[i].pval)=val;
			if(ReadBackTable[i].pval == &BCMKeyPosition){
				lastUpdateBCMKeyPosition=millis();
			}
			
		}
	}
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
  if ((RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 8))
  {
		//if(CheckValidRecID(RxMessage.StdId))//交由ledupdate做ID过滤
		//回读，更新LED灯
		LEDUpdate(RxMessage.Data,RxMessage.StdId);
		//回读逻辑功能需要的信息
		ReadLogicIput(RxMessage.Data,RxMessage.StdId);
		//回读转速
		if(RxMessage.StdId==ID_EMS){
			uint8_t engErr=0;
			engErr = (RxMessage.Data[4] & 0x01);	//bit32
			if(engErr==0)	//no err
				rpm = (RxMessage.Data[0] * 256 + RxMessage.Data[1]) * 0.25 ;
			else 
				rpm = 0;
		}
  }
}


//key075_t keys;
//将开关状态打包成表格中的CAN数据
void Keys2candata(u16 sw, uint8_t *dat) 
{
	u8 i;
	static u8 msgCnt=0;
	
	for(i=0;i<IND_KEY_NUM;i++)
	{
		if((sw & (((u16)1)<<i)) ==0)
			*((u16 *)dat) &=~(((u16)1)<<(indKeyIO[i].bitn));
		else
			*((u16 *)dat) |= ((u16)1)<<(indKeyIO[i].bitn);
			
	}
	
}
/*
u8 CheckValidRecID(u32 id)
{
	uint8_t i=0;
	uint8_t ret=0;
	
	
	for(i=0;i<sizeof(rIDList)/sizeof(u32);i++)
		if(id == rIDList[i])
			ret = 1;
	
	return ret;
}
*/


void CANInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	//CLK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
 // RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	//IO 
	#if(_USE_075_BOARD)	//mini board
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//STB for CAN chip
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//STB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	#else	//075 board
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);
	
	#endif
	
	  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
	//CAN_InitStructure.CAN_ABOM = ENABLE;
  CAN_InitStructure.CAN_AWUM = ENABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
#if(1)
  /* CAN Baudrate = 500kbps*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_13tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
  CAN_InitStructure.CAN_Prescaler = 3;
#else
  /* CAN Baudrate = 500kbps*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 8;
#endif
  CAN_Init(CAN1, &CAN_InitStructure);
	
	//使能busoff中断
	//CAN_ITConfig(CAN1, CAN_IT_BOF, ENABLE); 

  /* CAN filter init */
#ifdef  __CAN1_USED__
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
#else /*__CAN2_USED__*/
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
#endif  /* __CAN1_USED__ */

  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
}

u8 CAN_ChkBusoff()
{
	ITStatus boff;
	//boff = CheckITStatus(CAN1->ESR, CAN_ESR_BOFF);
	if ((CAN1->ESR & CAN_ESR_BOFF) != (uint32_t)RESET){
		boff=SET;
	}else{
		boff=RESET;
	}
	return boff;
}
/*
void CAN_ReqLeaveBusoff()
{
	//Request initialisation, INit RuQuest, set to 1, 先初始化
  CAN1->MCR |= CAN_MCR_INRQ ;
	delay_us(10);
	//Request leave initialisation, reset to be 0，再进入工作模式
  CAN1->MCR &= ~(uint32_t)CAN_MCR_INRQ;
}
//execute every 1ms
#define WT (int)(2800/1000.0+0.5)	//128*11bits
#define T_REMAIN_QUICK 100
#define T_REMAIN_SLOW  1000
void CAN_RecoverFSM()
{
	static u8 st;
	static u8 tcnt;
	u8 boff;
	boff=CAN_ChkBusoff();
	
	switch(st){
		case 0://working fine
			if(boff==SET){
				u8 modeRet;
				//st=1;
				//CAN_ReqLeaveBusoff();
				modeRet=CAN_OperatingModeRequest(CAN1,CAN_OperatingMode_Initialization);
				if(modeRet==CAN_ModeStatus_Success){
					//init successfully, then enter normal mode
					CAN_OperatingModeRequest(CAN1,CAN_OperatingMode_Normal);
				}else{
					st=1;
				}
			}
			break;
		case 1://quick recover
			//wait time 128*11bits, wt= 2.8ms
			tcnt++;
			if(tcnt>=WT){
				tcnt=0;
				//do ACK(how? just INAK?), check INAK? 
				
			}
			break;
		case 2:
			break;

	}
}
*/

//控制CAN 芯片功耗
void CANChipSet(u8 onoff)
{
	if(onoff == 0)
		GPIO_SetBits(GPIOA, GPIO_Pin_10);
	else
		GPIO_ResetBits(GPIOA, GPIO_Pin_10);
}


TestStatus CAN_Polling(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  CanTxMsg TxMessage;
  CanRxMsg RxMessage;
  uint32_t i = 0;
  uint8_t TransmitMailbox = 0;

  /* CAN register init */
  CAN_DeInit(CAN1);

  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE;
  CAN_InitStructure.CAN_ABOM=DISABLE;
  CAN_InitStructure.CAN_AWUM=DISABLE;
  CAN_InitStructure.CAN_NART=DISABLE;
  CAN_InitStructure.CAN_RFLM=DISABLE;
  CAN_InitStructure.CAN_TXFP=DISABLE;
  CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;

  /* Baudrate = 125kbps*/
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1=CAN_BS1_2tq;
  CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;
  CAN_InitStructure.CAN_Prescaler=12;
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=0;

  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;


  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

  /* transmit */
  TxMessage.StdId=0x11;
  TxMessage.RTR=CAN_RTR_DATA;
  TxMessage.IDE=CAN_ID_STD;
  TxMessage.DLC=2;
  TxMessage.Data[0]=0xCA;
  TxMessage.Data[1]=0xFE;

  TransmitMailbox=CAN_Transmit(CAN1, &TxMessage);
  i = 0;
  while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && (i != 0xFFFF))
  {
    i++;
  }

  i = 0;
  while((CAN_MessagePending(CAN1, CAN_FIFO0) < 1) && (i != 0xFFFF))
  {
    i++;
  }

  /* receive */
  RxMessage.StdId=0x00;
  RxMessage.IDE=CAN_ID_STD;
  RxMessage.DLC=0;
  RxMessage.Data[0]=0x00;
  RxMessage.Data[1]=0x00;
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

  if (RxMessage.StdId!=0x11)
  {
    return FAILED;
  }

  if (RxMessage.IDE!=CAN_ID_STD)
  {
    return FAILED;
  }

  if (RxMessage.DLC!=2)
  {
    return FAILED;
  }

  if ((RxMessage.Data[0]<<8|RxMessage.Data[1])!=0xCAFE)
  {
    return FAILED;
  }

  return PASSED; /* Test Passed */
}
TestStatus CAN_Interrupt(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  CanTxMsg TxMessage;
  uint32_t i = 0;

  /* CAN register init */
  CAN_DeInit(CAN1);


  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM=DISABLE;
  CAN_InitStructure.CAN_ABOM=DISABLE;
  CAN_InitStructure.CAN_AWUM=DISABLE;
  CAN_InitStructure.CAN_NART=DISABLE;
  CAN_InitStructure.CAN_RFLM=DISABLE;
  CAN_InitStructure.CAN_TXFP=DISABLE;
  CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;

  /* Baudrate = 500 Kbps */
  CAN_InitStructure.CAN_BS1=CAN_BS1_2tq;
  CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;
  CAN_InitStructure.CAN_Prescaler=12;
  CAN_Init(CAN1, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=1;

  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

  /* CAN FIFO0 message pending interrupt enable */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	

  /* transmit 1 message */
  TxMessage.StdId=0;
  TxMessage.ExtId=0x1234;
  TxMessage.IDE=CAN_ID_EXT;
  TxMessage.RTR=CAN_RTR_DATA;
  TxMessage.DLC=2;
  TxMessage.Data[0]=0xDE;
  TxMessage.Data[1]=0xCA;
  CAN_Transmit(CAN1, &TxMessage);

  /* initialize the value that will be returned */
  canRet = 0xFF;

  /* receive message with interrupt handling */
  i=0;
  while((canRet == 0xFF) && (i < 0xFFF))
  {
    i++;
  }

  if (i == 0xFFF)
  {
    canRet=0;
  }

  /* disable interrupt handling */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);

  return (TestStatus)canRet;
}

