#include "PVD.h"
#include "ConfigTable.h"


extern u8 signalStartStop;



void PVD_IRQHandler(void)
{
	//dev_pvd_irq_handle();
	EXTI_ClearITPendingBit(EXTI_Line16);
	{
		EXTI_ClearITPendingBit(EXTI_Line16);//clear bit;
		SaveParamsToEEPROM(signalStartStop);	//´æµ½
	}
}

/**************************************************************************
//Function :	void EXTI_Configuration(void)	
//Description :  configures; 
//Input :		none;
//Output :		none
//created by :  **************************************************************************/
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;

  /* Configure EXTI Line16(PVD Output) to generate an interrupt on rising and
     falling edges */
  EXTI_ClearITPendingBit(EXTI_Line16);//(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;//EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/**************************************************************************
//Function :	void PVD_NVIC_Configuration(void)	
//Description :   
//Input :		none;
//Output :		none
//created by :  **************************************************************************/
void PVD_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the PVD Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



void PVD_All_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); //point it;cann't lose it;??????;
	EXTI_Configuration();
	PVD_NVIC_Configuration();
	PWR_PVDLevelConfig(PWR_PVDLevel_2V9);//2.8V;added for PDV;//????;
	PWR_PVDCmd(ENABLE);					 //added for PDV;

}
