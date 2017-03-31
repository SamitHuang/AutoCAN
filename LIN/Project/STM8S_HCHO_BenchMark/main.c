/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
// 按键：
 GetKeyValue() ，返回当前按下的键值
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

//任务周期
#define PRD_KEY_SCAN       10  //ms
#define PRD_CONTROL        50  //ms
#define PRD_NOT_OPERATE    4000  //ms

//任务计时
volatile uint16_t taskKeyCnt=0;
volatile uint16_t taskControlCnt=0;
volatile uint32_t notOperateCnt=0;       //无操作计时

//全局系统变量
volatile u8 indKeysValue=0;             //当前键值
//u8  motorSelected=MOTOR_NONE;     //当前选择的电机
u8 runningDir=0xff;      //正在运转的方向
volatile u16 matKeysValue=0;

volatile bool isUartDataUpdate;
volatile u8 uartData8;  //串口即时数据
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
  //关闭其他不用的外高。 TOBE DONE！
  LEDDeinit();
  TIM2_Cmd(DISABLE);
  TIM2_DeInit();
  
  //PD1 SWIM 控制LIN芯片休眠
  LINICSleep();
  KeyExtIntInit();
  
  //降时钟
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
 
  
  WWDG->CR|=0x80; //WDGA=1，开启看门狗
  WWDG->CR&=~0x40; //T6置0，触发复位
  
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
  
  //halt();// 停机
  
 // CLK_INIT();   //内部时钟，设定为16M
 // KeyExtIntInit();
 // halt();
 // SystemInit();
  disableInterrupts();
  CLK_INIT();   //内部时钟，设定为16M
  

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
  
  //关闭不使用的外设时钟，仅留TIM2 UART2
  
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
    //任务1----按键扫描
    if(taskKeyCnt>=PRD_KEY_SCAN)
    {
        taskKeyCnt=0;
        
        //计时判断休眠 
        chkSleepCnt++;
        if(chkSleepCnt >= 700)  //判断主机是否休眠，即停止轮询。 7s
        {
          chkSleepCnt = 0; //防溢出
          isMasterSleep =TRUE;
    #if(DEBUG_MODE==1)
          UserSendString("Detect master fall sleep\r\n");
    #endif
    
        }
        
        //休眠后采取的动作
        if(isMasterSleep) 
        {
          //关闭LED
          LEDSet(LED_BCM_LOCK,0);
          LEDSet(LED_WIN_LOCK,0);
          LEDSet(LED_LEFT,0);
          LEDSet(LED_RIGHT,0);
          
          //进行低功耗
          //关闭其他外设，
          DeepHaltPre();//停机前关闭不需要的外设，打开四个外部按键的中断
          halt();//挂机，等待唤醒
          SystemRecover();//系统初始化函数
          chkSleepCnt=0;
          //if(isWakeupByKey){
          LIN_WakeMasterUp();
          isMasterSleep=TRUE;
          //isWakeupByKey=FALSE;
          //}
          //chkSleepCnt=0;           
          //UserSendString("Recover")
        }
        
        //读按键，用于回传及唤醒 
        indKeysValue=ReadKeysValue();
        //按键触发判断 
        matKeysValue = MatrixdKeyBoardScan();
        
        //按键唤醒
        isBCMLockTrigged = matKeysValue & (0x0001 << BCM_LOCK);
        isBCMUnlockTrigged = matKeysValue & (0x0001 << BCM_UNLOCK);
        isLeftSelectTrigged = indKeysValue & (0x01 << KEY_SELECT_LEFT);
        isRightSelectTrigged = indKeysValue & (0x01 << KEY_SELECT_RIGHT);
        
        
        if(chkSleepCnt>=20)//chkSleepCnt未被及时清零，认为主机休眠了
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
          //进行唤醒状态机
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
        //定时1.5s
        if(inWakeupDeadTime==TRUE){
          wdt++;
          if(wdt>=150){
            wdt=0;
            inWakeupDeadTime=FALSE;
          }
        }
    }
   
    //实时处理LIN主机信号
    if(isUartDataUpdate)
    {
      static u8 state=0;
      static u8 linRecCnt=0;
      u8 i;
      
  
      isUartDataUpdate=FALSE; 
      
      uartBuff[uartCnt++] = uartData8;
      if(uartCnt >= 72)
        uartCnt=0;
      
      //处理响应
      switch(state)
      {
      case 0:     //同步场
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
      case 1:     //标识符场  //主机要求从机返回数据
        if( uartData8 == SLAVE_ID)      
        {
          //state=2;
          
          //从机返回数据。 未考虑响应间隔是不是精确!!!!!
          DelaySoftUs(400);
          for(i=0;i<9;i++)
              linData[i]=0;
          //linData[0] = 0; 
          State2LinData(indKeysValue, matKeysValue, &linData[1]);
         
          //Enhance校验和 id + data
          linData[8] = SLAVE_ID;
          for(i=0;i<8;i++)     
          {
            if( (u16)(linData[8] + linData[i]) <= 0xff)
              linData[8] += linData[i];
            else                //进位，加carry 
            {
              linData[8] += linData[i];
              linData[8] ++;
            }
          }
          linData[8] = ~linData[8];
          //发送
          for(i=0;i<9;i++)
            UserSend8(linData[i]);
          
          state=0;      //完成
          
        }
        else if(uartData8 == MASTER_SEND_ID)    //主机继续发送数据
        {
          state=3;
          linDataRec[1]=MASTER_SEND_ID;
          notOperateCnt=0;                      //以判断主机是否停止轮询
          
        }
        else
          state=0;
        
        break;
      case 2:   
        break;
      case 3:   //主机继续发送数据
        linDataRec[linRecCnt++] = uartData8;
#if(REQ_CHK_SUM)
        if(linRecCnt>=9)        //8字节数据，1字节校验
        {
          u8 chkSum;
          
          linRecCnt=0;
          //校验对比
          chkSum=MASTER_SEND_ID;
          for(i=0;i<8;i++)      //ID + data 和校验
            chkSum += linDataRec[i];
          chkSum = ~chkSum;
          
          if(chkSum == linDataRec[8])  //校验通过
          {
            //处理数据，排除是自己发的
            LIN_ProcessMasterData(&linDataRec[0]);
            
          }

          state=0;
        }
#else
       if(linRecCnt>=8)        //8字节数据，1字节校验
       {
          linRecCnt=0;
          //处理数据，排除是自己发的
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
