//#include "SysConfig.h"
#include "config.h"        //包含所有的驱动头文件
#include "KeyBoard.h"
#include "CANCom.h" 



//volatile uint8_t canRecData;
uint16_t i=0;
u32 tPre=0;
char rotDir=0;
u8 trig=0;

int volume=0;

void NVIC_Configuration(void);


/********************************************
********************************************/
int main(void)
{
//	SystemClock_HSE(3);           //系统时钟初始化，时钟源外部晶振HSEs  8*1=8MHz; 已在SystemInit()中被设置
	
	cycleCounterInit();				// Init cycle counter
	SysTick_Config(SystemCoreClock / 1000);	//SysTick开启系统tick定时器并初始化其中断，1ms
	/*
	LedInit(); //IO初始化
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	*/
	KeyAndLEDInit();
	EncoderInit();
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
//#if(CAN_REC_DISABLE)
	NVIC_Configuration();	//CAN NVIC Conifg - rec interrupt
//#endif

	//UART1_init(SysClock,9600); //串口1初始化
	//UART2_init(19200);

#if(0)  //(CAN_MODE_NOW==CAN_MODE_LOOPBACK)
	TestRx=CAN_Polling();
	if (TestRx == FAILED)
    GPIO_SetBits(GPIOB, GPIO_Pin_14);
  else
    GPIO_ResetBits(GPIOB, GPIO_Pin_14);

	TestRx=CAN_Interrupt();
	if (TestRx == FAILED)
    GPIO_SetBits(GPIOB, GPIO_Pin_15);
  else
    GPIO_ResetBits(GPIOB, GPIO_Pin_15);
#endif
	
//normal mode
	CANInit();
//#if(CAN_REC_DISABLE)
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	//接收中断中的pending interrupt
//#endif

	TxMessage.StdId = ID_CCP;
  TxMessage.ExtId = 0x01;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
  TxMessage.DLC = 8;	//数据长度
	for(i=0;i<8;i++)
		TxMessage.Data[i] = 0;
//	TxMessage.Data[0] = 0xA0;
//	TxMessage.Data[7] = 0xA7;
		
	tPre = millis();
	while(1)
	{
		
		if( millis() >= tPre + 10)
		{
			static u16 keysBuffPre;
			static u8 tDiv=0;

			tPre = millis();
			//keysBuffPre = keysBuff;
			KeyScan();
			if(++tDiv >=2)
			{
				tDiv=0;
				rotDir=EncoderRead();	//detect increase or dec...
				if(rotDir==2)
					volume--;
				else if(rotDir==1)
					volume++;
				Keys2candata(keysBuff,TxMessage.Data);
				CAN_Transmit(CAN1, &TxMessage);
				
			}
			/*
			if(0)
			{
				static char rotDirPre=0;
				tDiv=0;
				rotDirPre=rotDir;
				rotDir=EncoderRead();
				if((rotDir!=0) || (rotDir!=rotDirPre))
					trig=1;
			}*/
			//printf("Test Cnt: %d\r\n",);
		}
		
	}
}

void TIM3_IRQHandler(void)		//打印中断服务程序
{	
    if(( TIM_GetITStatus(TIM3 , TIM_IT_CC1) != RESET ))
    {     
			TIM_ClearITPendingBit(TIM3 , TIM_IT_CC1);   //清除中断标志   
			
			rotDir=EncoderRead();
			
				
			trig=1;
		}
		if ( TIM_GetITStatus(TIM3 , TIM_IT_CC2)!=RESET)
		{
			rotDir=EncoderRead();
			trig=1;
			TIM_ClearITPendingBit(TIM3 , TIM_IT_CC2); 
		}
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

#ifndef STM32F10X_CL
#ifdef  __CAN1_USED__
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
#else  /*__CAN2_USED__*/
  /* CAN2 is not implemented in the device */
   #error "CAN2 is implemented only in Connectivity line devices"
#endif /*__CAN1_USED__*/
#else
#ifdef  __CAN1_USED__
  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
#else  /*__CAN2_USED__*/
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
#endif /*__CAN1_USED__*/

#endif /* STM32F10X_CL*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

