/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
// ������
 GetKeyValue() �����ص�ǰ���µļ�ֵ
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "HAL_Driver.h"
#include "HCHO_Driver.h"
//#include "Nixie_Tube_Driver.h"
#include "Key.h"


#define DEBUG_MODE 0
#define REQ_CHK_SUM 0
#define SLAVE_ID 0xD8
#define MASTER_SEND_ID 0x97
    
extern KeyIO_t keyIO[KEY_NUM];
extern volatile bool isWakeupByKey;
    
uint16_t flag_KEY_Down_Cnt=0;

//��������
#define PRD_KEY_SCAN       10  //ms
#define PRD_CONTROL        50  //ms
#define PRD_NOT_OPERATE    4000  //ms

//�����ʱ
volatile uint16_t taskKeyCnt=0;
volatile uint16_t taskControlCnt=0;
volatile uint32_t notOperateCnt=0;       //�޲�����ʱ

//ȫ��ϵͳ����
volatile u8 indKeysValue=0;             //��ǰ��ֵ
//u8  motorSelected=MOTOR_NONE;     //��ǰѡ��ĵ��
u8 runningDir=0xff;      //������ת�ķ���
volatile u16 matKeysValue=0;

volatile bool isUartDataUpdate;
volatile u8 uartData8;  //���ڼ�ʱ����
u8 linData[11]={0};
bool isBCMLockTrigged,isBCMUnlockTrigged,isLeftSelectTrigged,isRightSelectTrigged;
bool isMasterSleep;
u8 linDataRec[11]={0};
//for debugger
BitStatus keyBitStatus[6]={RESET};
volatile u16 chkSleepCnt=0;
volatile u16 ledSleepCnt=0;
static u16 wakeUpGapCnt=0;
bool keysReqMasterWakeUp=0;

static u8 uartBuff[72];
static u8 uartCnt;

bool fPowerOn;
u8 sendWakeWithoutResp;
bool inWakeupDeadTime;
u16 wdt;


void DeepHaltPre()
{
  disableInterrupts();
  
  KeyExtIntInit();
  // UART2_DeInit(); txd pd5 rxd pd6
  GPIO_Init(GPIOD,GPIO_PIN_6,GPIO_MODE_IN_PU_IT);  
  GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_IN_PU_IT);  
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL ); //EXTI_SENSITIVITY_FALL_ONLY
  
  LINICSleep();
  
  enableInterrupts();
}

void HaltPrepare() 
{
  //CLK_INIT(); 
  disableInterrupts();
  //�ر��������õ���ߡ� TOBE DONE��
  LEDDeinit();
  TIM2_Cmd(DISABLE);
  TIM2_DeInit();
  
  //PD1 SWIM ����LINоƬ����
  LINICSleep();
  KeyExtIntInit();
  
  //��ʱ��
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV8);
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV32);
  
  
  // 
 // UART2_DeInit();
 // GPIO_Init(GPIOD,GPIO_PIN_6,GPIO_MODE_IN_PU_IT);  
 // EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY); 
  UART2_INIT(19200);
  
  enableInterrupts();
  
};

void SystemRecover()
{
 
  
  WWDG->CR|=0x80; //WDGA=1���������Ź�
  WWDG->CR&=~0x40; //T6��0��������λ
  
  //WWDG->CR |= 0x80;
  //WWDG->CR &= 0xbf;
  disableInterrupts();
  CLK_INIT();
  
  
  EXTI_DeInit();
  
  LIN_Init();
  LEDInit();
  
  UART2_INIT(19200);
   //-----------------------------Keys----------------------------//
  InvidualKeysInit();
  MatrixKeyBoardInit();
  //------------
  //TIM4_INIT();  //for delae
  LINICWakeup();
  
  TIM2_INIT();    //for task counter
  TIM2_Cmd(ENABLE);
  
 // DelaySoftMs(100);
  enableInterrupts(); 
}

void main(void)
{
  u8 i=0;
  
  //halt();// ͣ��
  
 // CLK_INIT();   //�ڲ�ʱ�ӣ��趨Ϊ16M
 // KeyExtIntInit();
 // halt();
 // SystemInit();
  disableInterrupts();
  CLK_INIT();   //�ڲ�ʱ�ӣ��趨Ϊ16M
  

  //-----------------------------UART & LIN----------------------------//
  LIN_Init();
  //LINICWakeup();
  UART2_INIT(19200);
  //-----------------------------Keys----------------------------//
  InvidualKeysInit();
  MatrixKeyBoardInit();
  //-----------------------------LEDs----------------------------//
  LEDInit();
  //-------------------------2*5 Matrix Keyboard-----------------//
  
  //TIM4_INIT();  //for delay
  TIM2_INIT();    //for task counter
  TIM2_Cmd(ENABLE);
  
  //�رղ�ʹ�õ�����ʱ�ӣ�����TIM2 UART2
  
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC,DISABLE);
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_CAN,DISABLE);
  
  //NixieTubeTest();
  enableInterrupts();
  
  while(1)
  {
    //����1----����ɨ��
    if(taskKeyCnt>=PRD_KEY_SCAN)
    {
        taskKeyCnt=0;
        
        //��ʱ�ж����� 
        chkSleepCnt++;
        if(chkSleepCnt >= 700)  //�ж������Ƿ����ߣ���ֹͣ��ѯ�� 7s
        {
          chkSleepCnt = 0; //�����
          isMasterSleep =TRUE;
    #if(DEBUG_MODE==1)
          UserSendString("Detect master fall sleep\r\n");
    #endif
    
        }
        
        //���ߺ��ȡ�Ķ���
        if(isMasterSleep) 
        {
          //�ر�LED
          LEDSet(LED_BCM_LOCK,0);
          LEDSet(LED_WIN_LOCK,0);
          LEDSet(LED_LEFT,0);
          LEDSet(LED_RIGHT,0);
          
          //���е͹���
          //�ر��������裬
          DeepHaltPre();//ͣ��ǰ�رղ���Ҫ�����裬���ĸ��ⲿ�������ж�
          halt();//�һ����ȴ�����
          SystemRecover();//ϵͳ��ʼ������
          chkSleepCnt=0;
          //if(isWakeupByKey){
          LIN_WakeMasterUp();
          isMasterSleep=TRUE;
          //isWakeupByKey=FALSE;
          //}
          //chkSleepCnt=0;           
          //UserSendString("Recover")
        }
        
        //�����������ڻش������� 
        indKeysValue=ReadKeysValue();
        //���������ж� 
        matKeysValue = MatrixdKeyBoardScan();
        
        //��������
        isBCMLockTrigged = matKeysValue & (0x0001 << BCM_LOCK);
        isBCMUnlockTrigged = matKeysValue & (0x0001 << BCM_UNLOCK);
        isLeftSelectTrigged = indKeysValue & (0x01 << KEY_SELECT_LEFT);
        isRightSelectTrigged = indKeysValue & (0x01 << KEY_SELECT_RIGHT);
        
        
        if(chkSleepCnt>=20)//chkSleepCntδ����ʱ���㣬��Ϊ����������
        //if(isMasterSleep)
        {
          
          if(isBCMLockTrigged | isBCMUnlockTrigged | isLeftSelectTrigged | isRightSelectTrigged )
          {
            //keysReqMasterWakeUp=1;
            isBCMLockTrigged = FALSE;isBCMUnlockTrigged=FALSE;isLeftSelectTrigged=FALSE;isRightSelectTrigged=FALSE;
            //ledSleepCnt=0;
            if(!inWakeupDeadTime){
              LIN_WakeMasterUp();
              sendWakeWithoutResp++;
            }
            if(sendWakeWithoutResp>=3){
              inWakeupDeadTime=TRUE;
              wdt=0;
            }    
            //wakeUpGapCnt=150;
          }
          /*
          //���л���״̬��
          if(keysReqMasterWakeUp)
          {
           
            
            if(++wakeUpGapCnt>=150)       
            {
              wakeUpGapCnt=0;
              LIN_WakeMasterUp();
              keysReqMasterWakeUp = 0;
            }
             
          }*/
          
        } 
        //��ʱ1.5s
        if(inWakeupDeadTime==TRUE){
          wdt++;
          if(wdt>=150){
            wdt=0;
            inWakeupDeadTime=FALSE;
          }
        }
    }
   
    //ʵʱ����LIN�����ź�
    if(isUartDataUpdate)
    {
      static u8 state=0;
      static u8 linRecCnt=0;
      u8 i;
      
  
      isUartDataUpdate=FALSE; 
      
      uartBuff[uartCnt++] = uartData8;
      if(uartCnt >= 72)
        uartCnt=0;
      
      //������Ӧ
      switch(state)
      {
      case 0:     //ͬ����
        if(uartData8 == 0x55)
        {
          state=1;
          chkSleepCnt=0;      
          ledSleepCnt=0;
          isMasterSleep = FALSE;
          sendWakeWithoutResp=0;
         // keysReqMasterWakeUp = 0;
          
          #if(DEBUG_MODE==1)
            UserSendString("Detect Master has been waken up, oPC= ");
            UserSendIntString(notOperateCnt);
            UserSendString("\r\n");
          #endif
          
        }
        break;
      case 1:     //��ʶ����  //����Ҫ��ӻ���������
        if( uartData8 == SLAVE_ID)      
        {
          //state=2;
          
          //�ӻ��������ݡ� δ������Ӧ����ǲ��Ǿ�ȷ!!!!!
          DelaySoftUs(400);
          for(i=0;i<9;i++)
              linData[i]=0;
          //linData[0] = 0; 
          State2LinData(indKeysValue, matKeysValue, &linData[1]);
         
          //EnhanceУ��� id + data
          linData[8] = SLAVE_ID;
          for(i=0;i<8;i++)     
          {
            if( (u16)(linData[8] + linData[i]) <= 0xff)
              linData[8] += linData[i];
            else                //��λ����carry 
            {
              linData[8] += linData[i];
              linData[8] ++;
            }
          }
          linData[8] = ~linData[8];
          //����
          for(i=0;i<9;i++)
            UserSend8(linData[i]);
          
          state=0;      //���
          
        }
        else if(uartData8 == MASTER_SEND_ID)    //����������������
        {
          state=3;
          linDataRec[1]=MASTER_SEND_ID;
          notOperateCnt=0;                      //���ж������Ƿ�ֹͣ��ѯ
          
        }
        else
          state=0;
        
        break;
      case 2:   
        break;
      case 3:   //����������������
        linDataRec[linRecCnt++] = uartData8;
#if(REQ_CHK_SUM)
        if(linRecCnt>=9)        //8�ֽ����ݣ�1�ֽ�У��
        {
          u8 chkSum;
          
          linRecCnt=0;
          //У��Ա�
          chkSum=MASTER_SEND_ID;
          for(i=0;i<8;i++)      //ID + data ��У��
            chkSum += linDataRec[i];
          chkSum = ~chkSum;
          
          if(chkSum == linDataRec[8])  //У��ͨ��
          {
            //�������ݣ��ų����Լ�����
            LIN_ProcessMasterData(&linDataRec[0]);
            
          }

          state=0;
        }
#else
       if(linRecCnt>=8)        //8�ֽ����ݣ�1�ֽ�У��
       {
          linRecCnt=0;
          //�������ݣ��ų����Լ�����
          LIN_ProcessMasterData(&linDataRec[0]);
          state=0;
        }   
#endif
        
        break;
      
      }

    }
    

  
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
