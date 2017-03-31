//#include "SysConfig.h"
#include "config.h"        //包含所有的驱动头文件
#include "KeyBoard.h"
#include "CANCom.h" 
#include "ConfigTable.h"
#include "PVD.h"

//volatile uint8_t canRecData; 
uint16_t i=0;
u32 tPre=0;
char rotDir=0;
u8 trig=0;
void NVIC_Configuration(void);

extern u8 signalStartStop;


/********************************************
********************************************/
int main(void)
{
//	SystemClock_HSE(3);           //系统时钟初始化，时钟源外部晶振HSE 8*1=8MHz; 已在SystemInit()中被设置
	
	cycleCounterInit();				// Init cycle counter
	SysTick_Config(SystemCoreClock / 1000);	//SysTick开启系统tick定时器并初始化其中断，1ms
	
	LedInit(); //IO初始化
	KeyAndLEDInit();	//
	
	STMFLASH_Unlock();            //内部flash解锁

  signalStartStop=LoadParamsFromEEPROM();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
//#if(CAN_REC_DI;SABLE)
	NVIC_Configuration();	//CAN NVIC Conifg - rec interrupt
//#endif

	//UART1_init(SysClock,9600); //串口1初始化
	//UART2_init(19200);
	
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

	PVD_All_Init();
	tPre = millis();
	while(1)
	{
		if( millis() >= tPre + 10)
		{
			static u16 keysBuffPre;
			static u8 tDiv=0;
 
			tPre = millis();
			
			KeyScan();
			if(++tDiv >=2)
			{
				tDiv=0;
			//	rotDir=EncoderRead();	//detect increase or dec...
				Keys2candata(keysBuff,TxMessage.Data);
				CAN_Transmit(CAN1, &TxMessage);
			}
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

