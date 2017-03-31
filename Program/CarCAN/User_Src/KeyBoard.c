#include "KeyBoard.h" 

#define GPIO_PORT_SW_DEACTIVATE	GPIOA
#define GPIO_PIN_SW_DEACTIVATE	GPIO_Pin_8

#define GPIO_PORT_SW_ENABLE	GPIOB
#define GPIO_PIN_SW_ENABLE	GPIO_Pin_14

#define GPIO_PORT_SW_VSETPLUS	GPIOB
#define GPIO_PIN_SW_VSETPLUS	GPIO_Pin_13

#define GPIO_PORT_SW_VSETMINUS	GPIOB
#define GPIO_PIN_SW_VSETMINUS	GPIO_Pin_12

#define IND_KEY_NUM 4
KeyIO_t indKeyIO[IND_KEY_NUM] = {{GPIO_PORT_SW_DEACTIVATE,GPIO_PIN_SW_DEACTIVATE},
											{GPIO_PORT_SW_ENABLE,GPIO_PIN_SW_ENABLE},
											{GPIO_PORT_SW_VSETPLUS,GPIO_PIN_SW_VSETPLUS},
											{GPIO_PORT_SW_VSETMINUS,GPIO_PIN_SW_VSETMINUS},
											};

//键值缓存
volatile key075_t keysBuff; 

static void ADCInit(void);



//
void KeyInit(void)
{
	//独立按键  PA8 -Deactivate PB14 - Enable
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SW_DEACTIVATE;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉，待定，或浮空。GPIO_Mode_IN_FLOATING
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT_SW_DEACTIVATE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SW_ENABLE;	
	GPIO_Init(GPIO_PORT_SW_ENABLE, &GPIO_InitStructure);
	
	//vSetPuls PB13 vSetMinus PB12
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SW_VSETPLUS;	
	GPIO_Init(GPIO_PORT_SW_VSETPLUS, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SW_VSETMINUS;	
	GPIO_Init(GPIO_PORT_SW_VSETMINUS, &GPIO_InitStructure);
	
	//ADC按键 
	ADCInit();
	
	
}

static void ADCInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	
  //tauGap ADC12 IN7 PA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//通道12
	RCC->APB2ENR|=1<<9;    //ADC1????	  
	RCC->APB2RSTR|=1<<9;   //ADC1??
	RCC->APB2RSTR&=~(1<<9);//????	    
	RCC->CFGR&=~(3<<14);   //??????	
	//SYSCLK/DIV2=12M ADC?????12M,ADC????????14M!
	//?????ADC?????! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //??????
	ADC1->CR1|=0<<16;      //??????  
	ADC1->CR1&=~(1<<8);    //?????	  
	ADC1->CR2&=~(1<<1);    //??????
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	     //??????  
	ADC1->CR2|=1<<20;      //???????(SWSTART)!!!	???????????
	ADC1->CR2&=~(1<<11);   //???	 
	ADC1->CR2|=1<<23;      //???????

	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20;     //1????????? ??????????1 			   
	//????1?????
	
  //通道12的采样周期为 28.5
 	ADC1->SMPR1&=~(3<<6);  //????16?????	 
	ADC1->SMPR1|=3<<6;     //??16  239.5??,?????????????	 

	ADC1->CR2|=1<<0;	   //??AD???	 
	ADC1->CR2|=1<<3;       //??????  
	while(ADC1->CR2&1<<3); //?????? 			 
  //???????????????????????????????? 		 
	ADC1->CR2|=1<<2;        //??AD??	   
	while(ADC1->CR2&1<<2);  //??????

}
//获得某通道ADC值
u16 GetADC(u8 ch)   
{
	//GetADC	value	 
	ADC1->SQR3&=0XFFFFFFE0;//????1 ??ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //???????? 
	while(!(ADC1->SR&1<<1));//??????	 	   
	return ADC1->DR;		    //??adc?	
}


//每10ms调用一次
void KeyScan(void)
{
	static u8 indKeyStatePre[4]={2,2,2,2};
//	static u8 indKeyStatePrePre[4]={2,2,2,2};
	u16 adVal;
  u8 i;
	//独立按键  
  for(i=0;i<IND_KEY_NUM;i++)
	{
		u8 tempVal=0;
		tempVal = GPIO_ReadInputDataBit(indKeyIO[i].GPIO_Port,indKeyIO[i].GPIO_Pin);
		if(indKeyStatePre[i] == tempVal )  //两次读值一样，即过滤掉机械抖动
		{
				if(i == 0)
					keysBuff.key.deactivate=!tempVal;	//低电平为按下
				else if(i==1)
					keysBuff.key.enable=!tempVal;
				else if(i==2)
					keysBuff.key.vSetPlus=!tempVal;
				else if(i==3)
					keysBuff.key.vSetMinus=!tempVal;
		}
		indKeyStatePre[i] = tempVal;
//		indKeyStatePrePre[i] = indKeyStatePre[i];
	}
	
	//ADC按键采样，暂不取平均，不要求精确
	adVal=GetADC(7);
	if(adVal<0.25*4096)	//tauGapSetMinus Down
	{
		keysBuff.key.tauGapSetMinus=0;
		keysBuff.key.tauGapSetPlus=1;
	}
	else if(adVal<0.75*4096)	//tauGapSetPlus Down
	{
		keysBuff.key.tauGapSetPlus=0;
		keysBuff.key.tauGapSetMinus=1;
	}
	else		//Null
	{
		keysBuff.key.tauGapSetPlus=0;
		keysBuff.key.tauGapSetMinus=0;
	}
	
	
}
