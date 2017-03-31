#ifndef __KEY_H
#define __KEY_H

#include "stm8s.h"
#include "HAL_Driver.h"

//
#define KEY_NUM 8

typedef struct KeyIO_tt
{
  GPIO_TypeDef*    GPIOx;
  GPIO_Pin_TypeDef GPIO_Pin;
  
}KeyIO_t;
//
//enum {KEY_SELECT_LEFT=0,KEY_SELECT_RIGHT,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT};

typedef enum
{
KEY_SELECT_LEFT=0,KEY_SELECT_RIGHT,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,WINDOW_LOCK,MIRROR_FOLD
}ind_keys_option_t;;

typedef enum 
{
BCM_LOCK=0,       LEFT_REAR_DOWN, LEFT_REAR_UP, LEFT_FRONT_DOWN, LEFT_FRONT_UP,
BCM_UNLOCK,     RIGHT_REAR_DOWN,RIGHT_REAR_UP,RIGHT_FRONT_DOWN,RIGHT_FRONT_UP
}matrix_keys_option_t;

typedef enum{KS_IDLE=0,KS_DOWN,KS_PRESS,KS_UP} key_state_t;

//typedef enum{LED_LEFT=0,LED_RIGHT,LED_WIN_LOCK,LED_BCM_LOCK} LED_select_t;
typedef enum {LED_LEFT=0,LED_RIGHT,LED_WIN_LOCK,LED_BCM_LOCK} LED_option_t;


#define KEY_NONE 0xff
#define KEY_MULTI  0xfe //同时多个按下

//#define LED_BCM_REVERSE() GPIO_WriteReverse(LED_LEFT_PORT,LED_LEFT_PIN)  //反转
//#define LED_RIGHT_REVERSE() GPIO_WriteReverse(LED_RIGHT_PORT,LED_RIGHT_PIN)

#define ON  TRUE
#define OFF FALSE


void LIN_Init(void);
void State2LinData(u8 indKeyVal, u16 matrixKeyVal,u8 linKeysState[8]);
void LIN_WakeMasterUp(void);
void LIN_ProcessMasterData(u8 *linRecData);
void InvidualKeysInit(void);
u8 ReadKeysValue(void);
void LEDInit(void);
void LEDSet(LED_option_t ledNum, bool on);
void MatrixKeyBoardInit();
u16  MatrixdKeyBoardScan(void);
void KeyExtIntInit(void);
void LINICSleep(void);
void LINICWakeup(void);
void LEDDeinit();


#endif