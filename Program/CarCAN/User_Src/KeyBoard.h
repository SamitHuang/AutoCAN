#ifndef __KEY_BOARD_H
#define __KEY_BOARD_H

#include "config.h"

typedef struct KeyIO_tt
{
  GPIO_TypeDef*    GPIO_Port;
  uint16_t 				 GPIO_Pin;
}KeyIO_t;

void KeyInit(void);										
void KeyScan(void);

//°´¼ü»º´æ
typedef union key075
{
  uint8_t val;
	struct {
	u8 enable :1;
	u8 vSetMinus : 1;
  u8 vSetPlus: 1;
	u8 deactivate :1;
	u8 valid :1; //u8 resume :1;
	u8 reserve2 :1;
	u8 tauGapSetPlus :1;//u8 set:1;
	u8 tauGapSetMinus :1;
	}key;
}key075_t;

extern volatile key075_t keysBuff; 

#endif

