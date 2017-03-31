#ifndef __HCHO_Driver_H
#define __HCHO_Driver_H

#include "stm8s.h"

extern uint8_t flag_Start_Measure;
extern uint16_t flag_S_cnt;
extern uint16_t HCHOADCBuff,HCHOADCbenchmark,HCHOMgCm3;
extern uint8_t HCHOADCbenchmarkBuff[2];

#define  HCHO_ADC_Channel                           ADC1_CHANNEL_2
#define  HCHO_ADC_SCHMITTTRIGChannel                ADC1_SCHMITTTRIG_CHANNEL2


#define  GET_KEY_VALUE                              GPIO_ReadInputPin(GPIOB,GPIO_PIN_4)

#define  HCHO_ADC_MeasureMax                        40
extern void Get_HCHOValue(void);
#endif