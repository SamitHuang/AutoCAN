

#include "Led.h"
#include "UART1.h"
#include "config.h"

LED_t LEDCtrl;
//接口显存
LEDBuf_t LEDBuf;



//PB0 T3C3 LED1, PB1 T3C4 LED2
//pwm频率20KHz
void LEDBreathInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
		uint16_t PrescalerValue = 0;    //控制电机PWM频率
	
	//TIM2 clock enable  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	                     
  //GPIOB and AFIO(RCC_APB2Periph_AFIO)¸´ÓÃ¹¦ÄÜclock enable 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //打开外设A的时钟和复用时钟
  //GPIOB Configuration:
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		                 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	TIM_DeInit(TIM3);
//	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
	// Time base configuration 
  TIM_TimeBaseStructure.TIM_Prescaler =72-1;	               //ÉèÖÃÔ¤·ÖÆµ£º²»Ô¤·ÖÆµ£¬¼´Îª1MHz	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //ÏòÉÏ¼ÆÊýÄ£Ê½	 
  TIM_TimeBaseStructure.TIM_Period = 20000-1;                      //µ±¶¨Ê±Æ÷´Ó0¼ÆÊýµ½19999£¬¼´Îª20000´Î£¬ÎªÒ»¸ö¶¨Ê±ÖÜÆÚ 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	   //ÉèÖÃÊ±ÖÓ·ÖÆµÏµÊý£º²»·ÖÆµ
  //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//PWM1 Mode configuration: Channel3
	TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	          
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;	                 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //µ±¶¨Ê±Æ÷¼ÆÊýÖµÐ¡ÓÚCCR1_ValÊ±Îª¸ßµçÆ½
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	                  //Ê¹ÄÜÍ¨µÀ1
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	// PWM1 Mode configuration: Channel4
  TIM_OCInitStructure.TIM_Pulse = 0;	                 //ÉèÖÃÍ¨µÀ4µÄµçÆ½Ìø±äÖµ£¬Êä³öÁíÍâÒ»¸öÕ¼¿Õ±ÈµÄPWM
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	                //Ê¹ÄÜÍ¨µÀ
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM3, ENABLE);	                    // Ê¹ÄÜTIM2ÖØÔØ¼Ä´æÆ÷ARR
	
	TIM3->CCR3 = 19999;
	TIM3->CCR4 = 19999;
	
	 // TIM3 enable counter 
  TIM_Cmd(TIM3, ENABLE);                                   
  TIM_CtrlPWMOutputs(TIM3, ENABLE);						     

}
//更新频率100Hz
void LEDBreathUpdate(void)
{
	static uint16_t t=0;
	static volatile int32_t LED_PWM_count=0;

	LED_PWM_count = 19999 * sinf(3.1415926f * (float)t  / 100.0f);
	t++;
	if(t>=100)
			t=0;
		
  //TIM2_Mode_Config(2000-1,LED_PWM_count,LED_PWM_count);	
	//TIM2_PWM_duty(LED_PWM_count,LED_PWM_count); 
	TIM3->CCR3= LED_PWM_count;	                 
  TIM3->CCR4= LED_PWM_count;	  
}

/********************************************
              Led初始化函数
功能：
1.配置Led接口IO输出方向
2.关闭所有Led(开机默认方式)
描述：
Led接口：
Led1-->PA11
Led2-->PA8
Led3-->PB4
Led4-->PB3
对应IO=1，灯亮
********************************************/
void LedInit(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO  , ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	AFIO->MAPR|=2<<24;      //关闭JATG,千万不能将SWD也关闭，否则芯片作废，亲测!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		 // turn off all led
	//GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4);
	
	//LedA_off;//LedB_off;LedC_off;LedD_off;
	/*

    RCC->APB2ENR|=1<<2;    //使能PORTA时钟	
    RCC->APB2ENR|=1<<3;    //使能PORTB时钟	

    RCC->APB2ENR|=1<<0;      //使能复用时钟	   
    GPIOB->CRL&=0XFFFF0F0F;  //PB1,3推挽输出
    GPIOB->CRL|=0X00003030;
    GPIOB->ODR|=5<<1;        //PB1,3上拉

    GPIOA->CRH&=0XFFFF0FF0;  //PA8,11推挽输出
    GPIOA->CRH|=0X00003003;
    GPIOA->ODR|=9<<0;        //PA1,11上拉
*/
}

//底层更新 ，10Hz
void LEDReflash(void)
{
 
		if(LEDBuf.bits.A)
			LedA_on;
		else
			LedA_off;
		
		if(LEDBuf.bits.B)
			LedB_on;
		else
			LedB_off;
		
		if(LEDBuf.bits.C)
			LedC_on;
		else
			LedC_off;
		
		if(LEDBuf.bits.D)
			LedD_on;
		else
			LedD_off;
		
// 		
// 		if(LEDBuf.bits.D)
// 			LedD_on;
// 		else
// 			LedD_off;
}

//事件驱动层
void LEDFSM(void)
{
//	static uint16_t cnt=0;
//	uint8_t event=0;
	
	switch(LEDCtrl.event)
	{
		case E_READY:
				if(++LEDCtrl.cnt >= 3)		//0 1 2 in loop, 0 on ,else off
					LEDCtrl.cnt=0;
				if(LEDCtrl.cnt==0)
						LEDBuf.byte =LA|LB;
				else
						LEDBuf.byte =0;
			break;
		case E_CALI:
				LEDBuf.byte=LA|LB;
			break;
		case E_BAT_LOW:
				if(++LEDCtrl.cnt >= 3)		//0 1  in loop
					LEDCtrl.cnt=0;
				if(LEDCtrl.cnt==0)
						LEDBuf.byte =0x0f;
				else
						LEDBuf.byte =0;
			break;
		case E_CALI_FAIL:
				if(++LEDCtrl.cnt >= 4)
					LEDCtrl.cnt=0;
				if(LEDCtrl.cnt<2)
						LEDBuf.byte =LC|LD;
				else
						LEDBuf.byte =LA|LB;
			break;
		case E_LOST_RC:
				if(++LEDCtrl.cnt >= 4)
					LEDCtrl.cnt=0;
				LEDBuf.byte= 1<<LEDCtrl.cnt ;
//				if(LEDCtrl.cnt==0)
//						LEDBuf.byte =LA;
//				else
//						LEDBuf.byte =0;
			break;
		case E_AUTO_LANDED:
				 LEDBuf.byte=0x0f;
			break;
		
		case E_BatChg:
				 LEDBuf.byte=0x00;
			break;
		
	}
	
	LEDReflash();
}


