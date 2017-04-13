//#include "SysConfig.h"
#include "config.h"        //包含所有的驱动头文件
#include "KeyBoard.h"
#include "CANCom.h" 

//volatile uint8_t canRecData; 
uint16_t i=0;
u32 tPre=0;
char rotDir=0;
u8 trig=0;
u8 rollingCounter=0;

void NVIC_Configuration(void);
void IWDG_Configuration(void);

/********************************************
********************************************/
int main(void)
{
//	SystemClock_HSE(3);           //系统时钟初始化，时钟源外部晶振HSE 8*1=8MHz; 已在SystemInit()中被设置
	
	cycleCounterInit();				// Init cycle counter
	SysTick_Config(SystemCoreClock / 1000);	//SysTick开启系统tick定时器并初始化其中断，1ms
	
	LedInit(); //IO初始化
	KeyAndLEDInit();	//
	//GPIO_SetBits(GPIOA, GPIO_Pin_4);	//点亮LED4
	//while(1);
	//GPIO_SetBits(GPIOB, GPIO_Pin_15);
	EncoderInit();
	
//#if(CAN_REC_DISABLE)
	
//#endif

	//UART1_init(SysClock,9600); //串口1初始化
	UART2_init(19200);

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
	IWDG_Configuration();
//normal mode
	CANInit();
//#if(CAN_REC_DISABLE)
	NVIC_Configuration();	//CAN NVIC Conifg - rec interrupt
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
		u8 ret;
		if( millis() >= tPre + 10)
		{
			static u16 keysBuffPre;
			static u8 tDiv=0,logDiv=0;
 
			tPre = millis();
			//keysBuffPre = keysBuff;
			KeyScan();
			LEDRadarFlashSM();
			if(++tDiv >=2)
			{
				tDiv=0;
				rotDir=EncoderRead();	//detect increase or dec...
				
				Keys2candata(keysBuff,TxMessage.Data);
				ret=CAN_Transmit(CAN1, &TxMessage);
				if(ret!=CAN_TxStatus_NoMailBox){
					rollingCounter++;
					if(rollingCounter>=16)
						rollingCounter=0;
				}
				if(++logDiv>=100) //1s发一次
				{
					Uart2PutInt32(CAN1->ESR); 
			//		Uart2PutChar(0x01);
					logDiv=0;
					IWDG_ReloadCounter(); //喂狗
				}
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

void IWDG_Configuration(void)
{
    //使能对寄存器IWDG_PR和IWDG_RLR的写操作
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    //设置IWDG预分频值256:
    //40K/256 = 156HZ(6.4ms)   5s/6.4ms=781；
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    //设置IWDG重装载值，要小于0xfff（因为寄存器是12位的）
    IWDG_SetReload(781);
    //按照IWDG重装载寄存器的值 重新载入IWDG计数值；
    IWDG_ReloadCounter();
    IWDG_Enable();    //使能IWDG
}