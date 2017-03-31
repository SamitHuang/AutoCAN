#ifndef __CAN_COM_H
#define __CAN_COM_H

#include "config.h"
#include "KeyBoard.h"

#define ID_CCP (u32)0x455

#define ID_ESP (u32)0x211
#define ID_AVM (u32)0x428
#define ID_PDC (u32)0x525
#define ID_HUD (u32)0x434
#define ID_NVS (u32)0x68A
#define ID_EMS (u32)0x281


#define __CAN1_USED__ 1
#define CAN_REC_DISABLE 0

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

void Keys2candata(u16 keys, uint8_t *dat);
void CANInit(void);
TestStatus CAN_Interrupt(void);
TestStatus CAN_Polling(void);
void CANChipSet(u8 onoff);

extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;

#endif