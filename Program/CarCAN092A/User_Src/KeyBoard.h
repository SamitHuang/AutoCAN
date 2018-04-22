#ifndef __KEY_BOARD_H
#define __KEY_BOARD_H

#include "config.h"
#include "CANCom.h"

#define BOARD_092  1 
//#define BOARD_092A 1
//#define BOARD_092B 1
//#define BOARD_092C 1
//#define BOARD_092G 1
//#define BOARD_092C_MASS_PRODUCE 1


#ifdef BOARD_092
	#define IND_KEY_NUM 9
#endif
#ifdef BOARD_092A
	#define IND_KEY_NUM 9
#endif
#ifdef BOARD_092B
	#define IND_KEY_NUM 9
#endif
#ifdef BOARD_092C
	#define IND_KEY_NUM 9
#endif
#ifdef BOARD_092C_MASS_PRODUCE
	#define IND_KEY_NUM 9
#endif
#ifdef BOARD_092G
	#define IND_KEY_NUM 9
#endif

typedef enum
{ 
  PM25=0,AC_CYCLE,AC_MAX,FRONT_DEFROST,AC_REQUEST,AC_OFF,FAN_UP,FAN_DOWN
}keyName_tt;




typedef struct KeyIO_tt
{
  GPIO_TypeDef*    GPIO_Port;
  uint16_t 				 GPIO_Pin;
	uint8_t 				 bitn;
	GPIO_TypeDef*    LED_Port;
  uint16_t 				 LED_Pin; 
	uint8_t 				 rbitn;	
	u32 						 rID;
}KeyIO_t;


void KeyAndLEDInit(void);										
u8 KeyScan(void);
void LEDUpdate(u8 *datRec, u32 id);
void Control(uint16_t pinx, u8 on);
void DefrostAndWindHeatProcessor(void);
void FrontWindHeatProcessor(void);
void RearDefrostProcessor(void);

//°´¼ü»º´æ
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
extern u8 swDefrostTrig,swWindHeatTrig;
extern u8 swDefrostState,swWindHeatState;



#endif

