#ifndef __CAN_COM_H
#define __CAN_COM_H

#include "config.h"
#include "KeyBoard.h"




#define __CAN1_USED__ 1
#define CAN_REC_DISABLE 0
#define ID_SDB	(u32)0x456
#define ID_EMS	(u32)0x278

//-----Ω” ’µƒID≈‰÷√
#define ID_HVAC	(u32)0x435
#define ID_DVD  (u32)0x5A0
#define ID_AC   (u32)0x5EA
#define ID_DVR	(u32)0x6A0
//extern const u32 rIDList[]={ID_HVAC,ID_DVD,ID_AC,ID_DVR};

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

void Keys2candata(u16 keys, uint8_t *dat);
void CANInit(void);
TestStatus CAN_Interrupt(void);
TestStatus CAN_Polling(void);
void CANChipSet(u8 onoff);

extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;
extern volatile u16 rpm;

#endif