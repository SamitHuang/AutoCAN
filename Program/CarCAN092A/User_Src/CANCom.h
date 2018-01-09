#ifndef __CAN_COM_H
#define __CAN_COM_H

#include "config.h"
#include "KeyBoard.h"


#define USE_MANNUAL_RECOVER 0


#define __CAN1_USED__ 1
#define CAN_REC_DISABLE 0
#define ID_SDB	(u32)0x456
#define ID_EMS	(u32)0x278

//-----Ω” ’µƒID≈‰÷√
#define ID_HVAC	(u32)0x435
#define ID_DVD  (u32)0x5A0
#define ID_AC   (u32)0x5EA
#define ID_DVR	(u32)0x6A0
#define ID_BCM 	(u32)0x392
#define ID_DVD_EVENT	(u32)0x5EB	//send 3 times per 100ms
//extern const u32 rIDList[]={ID_HVAC,ID_DVD,ID_AC,ID_DVR};


enum{SLEEP=0,NORMAL=1,INIT=2};

typedef struct CAN_ReadBack_tt
{
  u8	start_idx;
	u8 	len;
	u32 id;
	volatile u8  *pval;
}CAN_ReadBack_t;

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

void Keys2candata(u16 keys, uint8_t *dat);
void CANInit(void);
TestStatus CAN_Interrupt(void);
TestStatus CAN_Polling(void);
void CANChipSet(u8 onoff);
u8 CAN_ChkBusoff();
u8 CAN_ChkMode();

extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;
extern volatile u16 rpm;
//extern CAN_ReadBack_t ReadBackTable[];
extern volatile u8 BCMKeyPosition;
extern volatile u8 DVDKeyRearDefrost;
extern volatile u8 VoiceRearDefrostRequest;
extern volatile u8 EngineRunningStatus;
extern volatile u8 ACFrontDefrostRequest;
extern volatile u32 lastUpdateBCMKeyPosition;

#endif