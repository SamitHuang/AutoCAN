//#include "SysConfig.h"
#include "config.h"        //包含所有的驱动头文件
#include "KeyBoard.h"
#include "CANCom.h" 



//volatile uint8_t canRecData;
uint16_t i=0;
u32 tPre=0;
static u8 ctrlDefrostState,ctrlWindHeatState;

void NVIC_Configuration(void);
void IWDG_Configuration(void);

/********************************************
********************************************/
int main(void)
{
//	SystemClock_HSE(3);           //系统时钟初始化，时钟源外部晶振HSEs  8*1=8MHz; 已在SystemInit()中被设置
	GPIO_InitTypeDef GPIO_InitStructure;
	
	cycleCounterInit();				// Init cycle counter
	SysTick_Config(SystemCoreClock / 1000);	//SysTick开启系统tick定时器并初始化其中断，1ms
	/*
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //Tobe confirmed.
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3);
	while(1);
	*/

	KeyAndLEDInit();
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
//#if(!CAN_REC_DISABLE)
	NVIC_Configuration();	//CAN NVIC Conifg - rec interrupt
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
//#if(CAN_REC_DISABLE==1)
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	//接收中断中的pending interrupt
//#endif

	TxMessage.StdId = ID_SDB;
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
		#if(1)
		if( millis() >= tPre + 10)
		{
			static u16 keysBuffPre;
			static u16 tDiv=0,logDiv=0;
			u8 trig=0;
			tPre = millis();
			
			//keysBuffPre = keysBuff;
			KeyScan();
			//处理Defrost和windheat控制
			DefrostAndWindHeatProcessor(); 
			
			if(++tDiv >=10 )	//100ms发一次
			{
				tDiv=0;
				Keys2candata(keysBuff, TxMessage.Data);
				CAN_Transmit(CAN1, &TxMessage);
			}
			if(++logDiv>=100) //1s发一次
			{
				Uart2PutInt32(CAN1->ESR);
		//		Uart2PutChar(0x01);
				logDiv=0;
				IWDG_ReloadCounter(); //喂狗
			}
		}
		#else
		//Keys2candata(keysBuff,TxMessage.Data);
		TxMessage.Data[0]=0x55;
		CAN_Transmit(CAN1, &TxMessage);
		delay_ms(1000 );
		#endif
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

/**
 * 初始化独立看门狗
 * prer:分频数:0~7(只有低 3 位有效!)
 * 分频因子=4*2^prer.但最大值只能是 256!
 * rlr:重装载寄存器值:低 11 位有效.
 * 时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
 */
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