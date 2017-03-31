#include "HAL_Driver.h"
#include "stm8s.h"



  
#ifdef __GNUC__ 
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch) 
#else 
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f) 
#endif  
PUTCHAR_PROTOTYPE 
{ 
//发送数据代码
  UserSend8(ch);
  return ch; 
} 

unsigned int g_uInt_ADC[ADC_Channel_Max]={0};

/*----------------------------------------------------------------------------*/
/*------------------------------DIGITAl---------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*---------------------------------CLK----------------------------------------*/
/*----------------------------------------------------------------------------*/
//设定时钟频率为16M
void CLK_INIT(void)
{
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  CLK_ClockSecuritySystemEnable();//开启时钟安全系统
  disableInterrupts();
}
/*----------------------------------------------------------------------------*/
/*---------------------------------TIM1---------------------------------------*/
/*----------------------------------------------------------------------------*/
//Frequency_Hz 分频16M,使用16位的周期设定值，PWM最小能到15Hz
void TIM1_INIT(uint16_t Frequency_Hz,FunctionalState NewState)
{
  uint16_t T_Load=1000/Frequency_Hz*1000;
  uint16_t default_Value;
  if(T_Load>100)
  {
    default_Value=T_Load/100;
  }
  else
  {
    default_Value=1;    
  }
  TIM1_DeInit();
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,T_Load,0);                           //1M时钟
  TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
                    default_Value, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, 
                    TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET); 
  TIM1_Cmd(NewState);
}
/*----------------------------------------------------------------------------*/
/*---------------------------------TIM2---------------------------------------*/
/*----------------------------------------------------------------------------*/
void TIM2_INIT(void)
{
  TIM2_DeInit();
  TIM2_PrescalerConfig(TIM2_PRESCALER_16,TIM2_PSCRELOADMODE_UPDATE);     //16分频成1MHZ，EGR不产生更新事件//
  TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);                                  //使能中断
  TIM2_SetCounter(65536-TIM2PERIOD);                                     //装入初值  MS=1000*1000/TIM2PERIOD
  TIM2_Cmd(ENABLE);                                                      //计时器打开
}
/*----------------------------------------------------------------------------*/
/*----------------------------TIM4&DELAY--------------------------------------*/
/*----------------------------------------------------------------------------*/
//Delay 时基设定
void TIM4_INIT(void)
{
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_8,1);																	
  TIM4_ITConfig(TIM4_IT_UPDATE,DISABLE);
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
}
void DelaySoftUs(unsigned int xUs)
{
  while(xUs--);
}
void DelaySoftMs(unsigned int xMs)
{
  unsigned int i;
  while(xMs--)
  {
    for(i=5462;i>0;i--);
  }
}
void DelayUs(unsigned int xUs)
{
  TIM4_Cmd(ENABLE);
  xUs=(unsigned int)(xUs/3.5);
  while(xUs--)
  {
    while(!TIM4_GetFlagStatus(TIM4_FLAG_UPDATE));
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  }
  TIM4_Cmd(DISABLE);
}
void DelayMs(unsigned int xMs)
{
  while(xMs--)
  {
    DelayUs(1000);
  }
}
/*----------------------------------------------------------------------------*/
/*---------------------------------EXIT---------------------------------------*/
/*----------------------------------------------------------------------------*/
void EXTI_INIT(EXTI_Port_TypeDef EXTI_PORT_GPIOx,EXTI_Sensitivity_TypeDef EXTI_Sensitivity) 
{
  EXTI_DeInit();																					 //复位外部中断
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOx,EXTI_Sensitivity);   
}
/*----------------------------------------------------------------------------*/
/*---------------------------------UART1--------------------------------------*/
/*----------------------------------------------------------------------------*/


void UART2_INIT(uint32_t baudRate)
{
  UART2_DeInit();							 //将串口复位												
  UART2_Init(baudRate,UART2_WORDLENGTH_8D,UART2_STOPBITS_1,
             UART2_PARITY_NO,UART2_SYNCMODE_CLOCK_DISABLE,
             UART2_MODE_TXRX_ENABLE );                                   //115200 波特率，8位，一位停止位，无校验，无流控，发送接受开启
  UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);		                 //开启串口接收和溢出即只要缓冲区中有数据就进入中断（UART1_IT_RXNE 会出错）
}
void UserSend8(unsigned char data)
{
  while(!UART2_GetFlagStatus(UART2_FLAG_TXE));
  UART2_SendData8(data);
  while(!UART2_GetFlagStatus(UART2_FLAG_TC));
}




void UserSendString(unsigned char *s)                                   //发送字符串函数应用指针方法
{
  unsigned char i=0;                                                    //定义一个局部变量用来发送字符串 ++运算
  while(s[i]!='\0')                                                     // 每个字符串结尾都是以\0 结尾的
  {
    UserSend8(s[i]);
    i++;                                                                //i++一次
  }
}
void UserSendIntString(int nInt)
{
  unsigned char nfloatString[5];
  unsigned char nChar;
  if(nInt>0)
  {
    nfloatString[0]=0x20;
  }
  else
  {
    nfloatString[0]='-';
    nInt=-nInt;
  }
  nChar=(unsigned char)(nInt/10);
  if(nChar<10 && nChar>=1)
  {
    nfloatString[1]=nChar+0x30;
    nfloatString[2]='\0';
  }
  else if(nChar>=10 && nChar<100)
  {
    nfloatString[1]=nChar/10+0x30;
    nfloatString[2]=nChar%10+0x30;
    nfloatString[3]='\0';
  }
  else if(nChar==100)
  {
    nfloatString[1]='=';
    nfloatString[2]='1';		
    nfloatString[3]='0';		
    nfloatString[4]='0';
  }
  else if(nChar>100)
  {
    nfloatString[1]='>';
    nfloatString[2]='1';		
    nfloatString[3]='0';		
    nfloatString[4]='0';
  }
  UserSendString(nfloatString);
}
void UserSendFloatString(float nfloat)//发送字符串 函数   应用指针 方法
{
  unsigned char nfloatString[5];
  if(nfloat<0.01)
  {
    nfloatString[0]='<';
    nfloatString[1]='.';
    nfloatString[2]='0';
    nfloatString[3]='1';
  }
  else if(nfloat>=0.01 && nfloat< 0.1)
  {
    nfloatString[0]='0';
    nfloatString[1]='.';
    nfloatString[2]='0';
    nfloatString[3]=(unsigned int)(nfloat*100)%10+0x30;
  }
  else if(nfloat>= 0.1 && nfloat<1.0)
  {
    nfloatString[0]='0';
    nfloatString[1]='.';
    nfloatString[2]=(unsigned int)(nfloat*100)/10+0x30;
    nfloatString[3]=(unsigned int)(nfloat*100)%10+0x30;
  }
  else if(nfloat ==1.0)
  {
    nfloatString[0]='=';
    nfloatString[1]='1';
    nfloatString[2]='\0';
    nfloatString[3]='\0';
  }
  else if(nfloat >1.0)
  {
    nfloatString[0]='>';
    nfloatString[1]='1';
    nfloatString[2]='\0';
    nfloatString[3]='\0';
  }
  UserSendString(nfloatString);
}
/*----------------------------------------------------------------------------*/
/*---------------------------------EEPROM-------------------------------------*/
/*----------------------------------------------------------------------------*/
void E2P_Write(unsigned int addr, unsigned char p_data[], unsigned int len)
{
  u8 i;
  FLASH_Unlock(FLASH_MEMTYPE_DATA);

  for(i = 0; i < len; i++)
  {
    FLASH_ProgramByte(0x4000 + addr + i, p_data[i]);//从0X4000开始寻址
  }

  FLASH_Lock(FLASH_MEMTYPE_DATA);
}
void E2P_Read(unsigned int addr, unsigned char p_data[], unsigned int len)
{
  u8 i;
  FLASH_Unlock(FLASH_MEMTYPE_DATA);

  for(i = 0; i < len; i++)
  {
    p_data[i] =  FLASH_ReadByte(0x4000 + addr + i);//从0X4000开始寻址
  }

  FLASH_Lock(FLASH_MEMTYPE_DATA);
}


