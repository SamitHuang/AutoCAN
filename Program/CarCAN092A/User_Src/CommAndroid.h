#ifndef __COMM_ANDROID_H
#define __COMM_ANDROID_H

#include "config.h"
#include "MotorS.h"

typedef enum{REQ_MOTION_STATUS=0,REQ_MOTION_POSITION,SET_GIMBAL_ATTI,INTERRUPT,SET_MOTOR,REQ_MOTOR_POSITION,SET_MOTOR_SPEED,SET_MOTOR_POS_ONLY,REQ_VERSION,REQ_ID,CHG_ID,REQ_MOTOR_TEST,SET_ACTION} android_cmd_type;

void CommAndroid(uint8_t c);

extern char isAndroidCmdUpdated;
extern uint8_t androidCmd;
extern uint8_t actionCode;


#endif