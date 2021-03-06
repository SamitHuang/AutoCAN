#ifndef __KEY_BOARD_H
#define __KEY_BOARD_H

#include "config.h"
#include "CANCom.h"

typedef enum
{ 
  PM25=0,AC_CYCLE,AC_MAX,FRONT_DEFROST,AC_REQUEST,AC_OFF,FAN_UP,FAN_DOWN
}keyName_tt;

//#define BOARD_095 1
#define BOARD_095A 1
//#define BOARD_095B 1
//#define BOARD_095C 1


#define IND_KEY_NUM 14

#define SP_KEY_STARTSTOP  9


typedef struct KeyIO_tt
{
  GPIO_TypeDef*    GPIO_Port;
  uint16_t 				 GPIO_Pin;
	uint8_t 				 bitn;
	GPIO_TypeDef*    LED_Port;
  uint16_t 				 LED_Pin;
	uint8_t				 		rbitn;
	u32 					 		rID;
}KeyIO_t;

void KeyAndLEDInit(void);										
u8 KeyScan(void);
void LEDUpdate(u8 *datRec, u32 id);
void EncoderInit(void);
char EncoderRead(void);
void LEDSMSet(GPIO_TypeDef* GPIOx,uint16_t PINx,u8 val);
void LEDFlashSM();
void LEDRadarSMSet(GPIO_TypeDef* GPIOx,uint16_t PINx,u8 val);
void LEDRadarFlashSM();

//��������
typedef union key075
{
  uint8_t val;
	struct {
	u8 enable :1;
	u8 set:1;
	u8 resume :1;
	u8 deactivate :1;
	u8 vSetPlus :1;
	u8 vSetMinus :1;
	u8 tauGapSetPlus :1;
	u8 tauGapSetMinus :1;
	}key;
}key075_t;

extern KeyIO_t indKeyIO[IND_KEY_NUM];
extern volatile u16 keysBuff,swBuff; 


#endif

