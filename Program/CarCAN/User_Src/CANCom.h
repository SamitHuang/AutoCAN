#ifndef __CAN_COM_H
#define __CAN_COM_H

#include "config.h"
#include "KeyBoard.h"


#define __CAN1_USED__ 1
#define CAN_REC_DISABLE 1

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

//void Keys2candata(key075_t keys, uint8_t *dat);
void Keys2candata(key075_t keys, int isVoltageValid,uint8_t *dat);
void CANInit(void);
TestStatus CAN_Interrupt(void);
TestStatus CAN_Polling(void);
void CANChipSet(u8 onoff);

extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;

#endif