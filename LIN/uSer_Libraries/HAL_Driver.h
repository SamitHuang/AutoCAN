/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_Driver_H
#define __HAL_Driver_H

#include "stm8s.h"
#include "stdio.h"


                   
/*----------------------------------------------------------------------------*/
/*--------------------------------TIM2----------------------------------------*/
/*----------------------------------------------------------------------------*/
#define TIM2PERIOD                         1000		         

/*----------------------------------------------------------------------------*/
/*--------------------------------ADC-----------------------------------------*/
/*----------------------------------------------------------------------------*/
#define ADC_Channel_Max                    5 

extern unsigned int g_uInt_ADC[ADC_Channel_Max];

extern void CLK_INIT(void);

extern void TIM1_INIT(uint16_t Frequency_Hz,FunctionalState NewState);

extern void TIM2_INIT(void);

extern void TIM4_INIT(void);
extern void DelaySoftUs(unsigned int xUs);
extern void DelaySoftMs(unsigned int xMs);
extern void DelayUs(unsigned int xUs);
extern void DelayMs(unsigned int xMs);

extern void EXTI_INIT(EXTI_Port_TypeDef EXTI_PORT_GPIOx,EXTI_Sensitivity_TypeDef EXTI_Sensitivity);

extern void UART2_INIT(uint32_t baudRate);
extern void UserSend8(unsigned char data);
extern void UserSendString(unsigned char *s);
extern void UserSendIntString(int nInt);
extern void UserSendFloatString(float nfloat); 

extern void E2P_Write(unsigned int addr, unsigned char p_data[], unsigned int len);
extern void E2P_Read(unsigned int addr, unsigned char p_data[], unsigned int len);

extern void ADC_INIT(ADC1_ConvMode_TypeDef ADC1_ConversionMode, ADC1_Channel_TypeDef ADC1_Channel, 
              ADC1_PresSel_TypeDef ADC1_PrescalerSelection, ADC1_ExtTrig_TypeDef ADC1_ExtTrigger,
              FunctionalState ADC1_ExtTriggerState, ADC1_Align_TypeDef ADC1_Align, 
              ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel, FunctionalState ADC1_SchmittTriggerState);
extern void Get_ONE_CHANNEL_ADC(ADC1_ConvMode_TypeDef ADC1_ConversionMode, 
              ADC1_Channel_TypeDef ADC1_Channel, ADC1_Align_TypeDef ADC1_Align);
#endif
