#ifndef __Nixie_Tube_Driver_H
#define __Nixie_Tube_Driver_H

#include "stm8s.h"
#include "HAL_Driver.h"

#define Display_xS                                   20*1000/(1000/(TIM2PERIOD/1000))

#define NIXIE_COM3_PORT                              GPIOA     
#define NIXIE_COM2_PORT                              GPIOA     
#define NIXIE_COM1_PORT                              GPIOC     
                                                               
#define NIXIE_COM3_PIN                               GPIO_PIN_1
#define NIXIE_COM2_PIN                               GPIO_PIN_2
#define NIXIE_COM1_PIN                               GPIO_PIN_5
                                                               
#define NIXIE_B_PORT                                 GPIOD     
#define NIXIE_A_PORT                                 GPIOC     
#define NIXIE_C_PORT                                 GPIOC     
#define NIXIE_D_PORT                                 GPIOD     
#define NIXIE_E_PORT                                 GPIOD     
#define NIXIE_F_PORT                                 GPIOA     
#define NIXIE_G_PORT                                 GPIOC     
#define NIXIE_DP_PORT                                GPIOD    
                                                               
#define NIXIE_B_PIN                                  GPIO_PIN_4
#define NIXIE_A_PIN                                  GPIO_PIN_3
#define NIXIE_C_PIN                                  GPIO_PIN_7
#define NIXIE_D_PIN                                  GPIO_PIN_2
#define NIXIE_E_PIN                                  GPIO_PIN_3
#define NIXIE_F_PIN                                  GPIO_PIN_3
#define NIXIE_G_PIN                                  GPIO_PIN_6
#define NIXIE_DP_PIN                                 GPIO_PIN_1

#define NIXIE_COM1ON                                 GPIO_WriteLow(NIXIE_COM1_PORT ,NIXIE_COM1_PIN) 
#define NIXIE_COM2ON				     GPIO_WriteLow(NIXIE_COM2_PORT ,NIXIE_COM2_PIN)	
#define NIXIE_COM3ON                                 GPIO_WriteLow(NIXIE_COM3_PORT ,NIXIE_COM3_PIN) 
                                                     
#define NIXIE_COM1OFF                                GPIO_WriteHigh(NIXIE_COM1_PORT ,NIXIE_COM1_PIN)
#define NIXIE_COM2OFF			     	     GPIO_WriteHigh(NIXIE_COM2_PORT ,NIXIE_COM2_PIN)
#define NIXIE_COM3OFF                                GPIO_WriteHigh(NIXIE_COM3_PORT ,NIXIE_COM3_PIN)


#define NixieTubeAON                                 GPIO_WriteLow(NIXIE_A_PORT ,NIXIE_A_PIN ) 
#define NixieTubeBON				     GPIO_WriteLow(NIXIE_B_PORT ,NIXIE_B_PIN )	
#define NixieTubeCON                                 GPIO_WriteLow(NIXIE_C_PORT ,NIXIE_C_PIN ) 
#define NixieTubeDON				     GPIO_WriteLow(NIXIE_D_PORT ,NIXIE_D_PIN ) 
#define NixieTubeEON			             GPIO_WriteLow(NIXIE_E_PORT ,NIXIE_E_PIN ) 
#define NixieTubeFON				     GPIO_WriteLow(NIXIE_F_PORT ,NIXIE_F_PIN ) 
#define NixieTubeGON                                 GPIO_WriteLow(NIXIE_G_PORT ,NIXIE_G_PIN ) 
#define NixieTubeDPON                                GPIO_WriteLow(NIXIE_DP_PORT ,NIXIE_DP_PIN)

#define NixieTubeAOFF                                GPIO_WriteHigh(NIXIE_A_PORT ,NIXIE_A_PIN ) 
#define NixieTubeBOFF				     GPIO_WriteHigh(NIXIE_B_PORT ,NIXIE_B_PIN )	
#define NixieTubeCOFF                                GPIO_WriteHigh(NIXIE_C_PORT ,NIXIE_C_PIN ) 
#define NixieTubeDOFF			     	     GPIO_WriteHigh(NIXIE_D_PORT ,NIXIE_D_PIN ) 
#define NixieTubeEOFF			             GPIO_WriteHigh(NIXIE_E_PORT ,NIXIE_E_PIN ) 
#define NixieTubeFOFF				     GPIO_WriteHigh(NIXIE_F_PORT ,NIXIE_F_PIN ) 
#define NixieTubeGOFF                                GPIO_WriteHigh(NIXIE_G_PORT ,NIXIE_G_PIN ) 
#define NixieTubeDPOFF                               GPIO_WriteHigh(NIXIE_DP_PORT ,NIXIE_DP_PIN)

extern uint8_t NixieData[3],flag_COMSelectCnt;

extern void Nixie_Tube_Init(void);
extern void NixieTubeTest(void);
extern void NixieTubeCOMSelect(uint8_t COMx);
extern void NixieTube(unsigned char data);
extern void UnpackageHCHO(unsigned int data,unsigned int data1,uint8_t Data_ADC);
#endif