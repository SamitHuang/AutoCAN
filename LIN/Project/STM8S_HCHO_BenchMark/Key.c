
#include "Key.h"

//----��������

KeyIO_t keyIO[KEY_NUM] = {
                    {GPIOC,GPIO_PIN_3}, // Key Left Select ֧�ֻ���
                    {GPIOA,GPIO_PIN_2}, // Key Right Select ֧�ֻ���
                    {GPIOC,GPIO_PIN_6}, // Key Direction Up
                    {GPIOD,GPIO_PIN_3}, // Key Dir Down
                    {GPIOC,GPIO_PIN_5}, // Key Direction Left 
                    {GPIOD,GPIO_PIN_2}, // Key Direction Right
                    {GPIOC,GPIO_PIN_7}, // window lock
                    {GPIOD,GPIO_PIN_0},  //MIRRO FOLD
                    
};
static u8 keyState[KEY_NUM]={0};

//1*10 �������
/*
KeyIO_t keyBoardIO_X[2] = {
                    {GPIOB,GPIO_PIN_0}, //X1: 
                    {GPIOB,GPIO_PIN_5}, //X2:
};*/                
#define KEY_Y_NUM 10
KeyIO_t keyBoardIO_Y[KEY_Y_NUM]={
                    {GPIOE,GPIO_PIN_5}, //Y1: bcm lock          ֧�ֻ���
                    {GPIOB,GPIO_PIN_0}, //Y2: left rear down 
                    {GPIOB,GPIO_PIN_1}, //Y3: left rear up 
                    {GPIOB,GPIO_PIN_2}, //Y4: left front down
                    {GPIOD,GPIO_PIN_4}, //Y5: Left front up 
                    {GPIOD,GPIO_PIN_7}, //Y6: BCM unlock        ֧�ֻ���
                    {GPIOB,GPIO_PIN_4}, //Y7: right rear down 
                    {GPIOB,GPIO_PIN_3}, //Y8: right rear up 
                    {GPIOB,GPIO_PIN_5}, //Y9: right front down  
                    {GPIOF,GPIO_PIN_4}, //Y10: right front up 
                    
};

//LED
#define LED_NUM 4
KeyIO_t ledIO[LED_NUM] = {
                    {GPIOC,GPIO_PIN_2}, //Left LED
                    {GPIOA,GPIO_PIN_1}, //Right LED
                    {GPIOC,GPIO_PIN_4}, //Window lock led
                    {GPIOC,GPIO_PIN_1}, //bcm lock led
                   // {GPIOC,GPIO_PIN_5}, //
                    
};



void KeyExtIntInit(void)
{
  uint8_t i=0;
  

  //�밴����������������Ϊ����ģʽ
  GPIO_Init(keyIO[KEY_SELECT_LEFT].GPIOx,keyIO[KEY_SELECT_LEFT].GPIO_Pin,GPIO_MODE_IN_PU_IT);    
  GPIO_Init(keyIO[KEY_SELECT_RIGHT].GPIOx,keyIO[KEY_SELECT_RIGHT].GPIO_Pin,GPIO_MODE_IN_PU_IT);  
  
  GPIO_Init(keyBoardIO_Y[BCM_LOCK].GPIOx,keyBoardIO_Y[BCM_LOCK].GPIO_Pin,GPIO_MODE_IN_PU_IT);  
  GPIO_Init(keyBoardIO_Y[BCM_UNLOCK].GPIOx,keyBoardIO_Y[BCM_UNLOCK].GPIO_Pin,GPIO_MODE_IN_PU_IT);  
  
  //��GPIOD�˿�����Ϊ�����ش����ж�--��Ϊ���������ʱ����һ���ߵ�ƽ���γ�ʱ����һ���½���
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA,EXTI_SENSITIVITY_FALL_ONLY); 
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_FALL_ONLY); 
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD,EXTI_SENSITIVITY_FALL_ONLY); 
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE,EXTI_SENSITIVITY_FALL_ONLY); 
  
 
  
  //��PD7���ŵ�TLI�ж�����Ϊ�½����ж�,TLI��������ȼ��ж�
  //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
}


void LINICSleep(void)
{
  GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_OD_HIZ_SLOW);
  GPIO_WriteLow(GPIOD,GPIO_PIN_1);
}

void LINICWakeup(void)
{
  GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_OD_HIZ_SLOW);
  GPIO_WriteHigh(GPIOD,GPIO_PIN_1);
}


//-------------------------LIN & ӳ�亯��---------------------------------//
void LIN_Init(void)
{
  GPIO_Init(GPIOD,GPIO_PIN_7,GPIO_MODE_OUT_PP_LOW_FAST);        //NSLP
  GPIO_Init(GPIOD,GPIO_PIN_4,GPIO_MODE_OUT_PP_LOW_FAST);        //NWAK
  GPIO_WriteHigh(GPIOD,GPIO_PIN_7);
  GPIO_WriteHigh(GPIOD,GPIO_PIN_4);
  
}
#define KEY_TOTAL_NUM 18
void State2LinData(u8 indKeyVal, u16 matrixKeyVal,u8 linKeysState[8])
{
  u32 myKeysStateInt32;
  u8 myKeysState[3];
  //u8 linKeysState[8]={0,0,0,0,0,0,0,0};
  u8 reflectTable[KEY_TOTAL_NUM]={20,21,22,23,24,25,16,19,26,7,5,3,1,27,15,13,11,9};    //ӳ���ϵ
  u8 i;
  
  //�Ƚ�18��״̬λ�ϲ���һ��u32��B0 - B7Ϊ8������������B8-B17Ϊ�������
  myKeysState[0] =indKeyVal  ;//((u32)matrixKeyVal << 16) | indKeyVal;
  myKeysState[1] = matrixKeyVal & 0xf;
  myKeysState[2] = matrixKeyVal >> 8;
  myKeysStateInt32 = ((u32)matrixKeyVal << 8) | indKeyVal;
  //�Լ�����ļ�λ˳�� ӳ�䵽 ���Ҷ���ļ�λֵ˳��
  for(i=0;i<KEY_TOTAL_NUM;i++)
  {
    u8 byteN,bitN;
    byteN=reflectTable[i] / 8;
    bitN = reflectTable[i] % 8;
    if((myKeysStateInt32 & ((u32)1 << i) )!= 0)
    {
      linKeysState[byteN] |= (u8)1 << bitN;
    }
  }
  /*
  //������BCMLock����������. ռ����2���ڵ�3�ֽڣ�b2:b3λ
  linKeysState[3] &= 0xf3;
  if(matrixKeyVal & ((u16)1 << BCM_LOCK))
      linKeysState[3] |= 0x01 << 2;
  else if(matrixKeyVal & ((u16)1 << BCM_UNLOCK))
      linKeysState[3] |= 0x02 << 2;
  
  */
  
  
}

void LIN_WakeMasterUp(void)
{
  UserSend8(0x00);
}
//ֻ����������
void LIN_ProcessMasterData(u8 *linData)
{
  
  LEDSet(LED_BCM_LOCK, linData[0] & (0x01 << 3));
  LEDSet(LED_WIN_LOCK,linData[0] & (0x01 << 4));
  LEDSet(LED_LEFT,linData[0] & (0x01 << 6));
  LEDSet(LED_RIGHT,linData[0] & (0x01 << 7));

}
//-------------------------------key board--------------------------------------------------//
//��ʼ��
void MatrixKeyBoardInit(void)
{
  u8 i;
  
  //x1
  //GPIO_Init(keyBoardIO_X[0].GPIOx,keyBoardIO_X[0].GPIO_Pin,GPIO_MODE_OUT_PP_LOW_FAST);
  //x2
  //GPIO_Init(keyBoardIO_X[1].GPIOx,keyBoardIO_X[1].GPIO_Pin,GPIO_MODE_OUT_PP_LOW_FAST);
  
  for(i=0;i<KEY_Y_NUM;i++)
    GPIO_Init(keyBoardIO_Y[i].GPIOx,keyBoardIO_Y[i].GPIO_Pin,GPIO_MODE_IN_PU_NO_IT);
}
/*
//�趨ɨ�����
static void SetKeyBoardX(bool x1, bool x2)
{
    if(x1)
      GPIO_WriteHigh(keyBoardIO_X[0].GPIOx,keyBoardIO_X[0].GPIO_Pin);
    else
      GPIO_WriteLow(keyBoardIO_X[0].GPIOx,keyBoardIO_X[0].GPIO_Pin);
    
    if(x2)
      GPIO_WriteHigh(keyBoardIO_X[1].GPIOx,keyBoardIO_X[1].GPIO_Pin);
    else
      GPIO_WriteLow(keyBoardIO_X[1].GPIOx,keyBoardIO_X[1].GPIO_Pin);
    
      
    
}*/
//��ȡ��ʱ��ֵ�����ֵ��
static u16 ReadKeyBoardY(void)
{
  BitStatus p=SET;
  u8 i;
  u16 yKeysState=0;
  
  
  for(i=0;i<KEY_Y_NUM;i++)
  {
    p=GPIO_ReadInputPin(keyBoardIO_Y[i].GPIOx,keyBoardIO_Y[i].GPIO_Pin);
    if(p==RESET)        //���º󣬻��Ϊ�͵�ƽ
    {
      yKeysState = yKeysState | ((u16)1<<i);
    }
  }
  
  return yKeysState;
  
  
}
//�������ɨ�裬����10������״̬,˳������enum��������͡�10ms~20����һ�Σ�ͨ����ʱ������������
u16  MatrixdKeyBoardScan(void)
{
  u16 keysVal;
  
  keysVal=ReadKeyBoardY();

  return keysVal;
  
}

//-------------------------------Indivual keys --------------------------------------------------//
void InvidualKeysInit(void)
{
  u8 i;
  for(i=0;i<KEY_NUM;i++)
      GPIO_Init(keyIO[i].GPIOx,keyIO[i].GPIO_Pin,GPIO_MODE_IN_PU_NO_IT);
  
  
}


//0 δ����
//1 ����
u8 ScanOneKey(u8 keyNum)
{
  BitStatus tempVal=RESET;
  
  tempVal=GPIO_ReadInputPin(keyIO[keyNum].GPIOx,keyIO[keyNum].GPIO_Pin);
  if(tempVal==0)
    return 1;
  else
    return 0;
  /*
  switch(keyState[keyNum])
  {
      case KS_IDLE:
      if(tempVal==0)
            keyState[keyNum]=KS_DOWN;  
         return 0;

      break;
      case KS_DOWN:			 
            keyState[keyNum]=KS_PRESS; 								 
            return 1;
      break;
      case(KS_PRESS):
          if(tempVal!=0)		//�ȴ��ͷ�
          {
             keyState[keyNum]=KS_IDLE;		  			  
          }
          return 1;
      break;
  //    case(KS_UP):					//������ɵ����¼�  
   //       kSAny=KS_IDLE;
  //    break;	    
  }	
  return 0;
  */
  
  
}

//ɨ�����а��������ؼ�����Bit0 - Bit7��Ӧ8������˳������enum���������
u8 ReadKeysValue(void)
{
  u8 keysVal=0;
  u8 i=0;
//  u8 pressCnt=0;
  
  for(i=0;i<KEY_NUM;i++)
  {
    if(ScanOneKey(i)!=0)
    {
      keysVal=keysVal | ((u32)1<<i);
      
    }
  }
  //if(pressCnt>1)        //���ͬʱ����
  //  key=0xfe;
  
  return keysVal;

}




//-------------------------------KEDs--------------------------------------------------//
//led
// 

void LEDDeinit(void)
{
  u8 i;
  for(i=0;i<LED_NUM;i++)
    GPIO_Init(ledIO[i].GPIOx,ledIO[i].GPIO_Pin,GPIO_MODE_IN_FL_NO_IT);
}
void LEDInit(void)
{
  u8 i;
  for(i=0;i<LED_NUM;i++)
    GPIO_Init(ledIO[i].GPIOx,ledIO[i].GPIO_Pin,GPIO_MODE_OUT_PP_LOW_FAST);
}


void LEDSet(LED_option_t ledNum, bool on)
{

  if(on)
      GPIO_WriteHigh(ledIO[(u8)ledNum].GPIOx,ledIO[(u8)ledNum].GPIO_Pin);
    else
      GPIO_WriteLow(ledIO[(u8)ledNum].GPIOx,ledIO[(u8)ledNum].GPIO_Pin);
  
  
}

