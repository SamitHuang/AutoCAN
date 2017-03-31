#include "Nixie_Tube_Driver.h"
#include "stm8s.h"

uint8_t NixieData[3]={0},flag_COMSelectCnt=0;
void Nixie_Tube_Init(void)
{
  GPIO_Init(NIXIE_COM1_PORT,NIXIE_COM1_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_COM2_PORT,NIXIE_COM2_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_COM3_PORT,NIXIE_COM3_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  
  GPIO_Init(NIXIE_A_PORT,NIXIE_A_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_B_PORT,NIXIE_B_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_C_PORT,NIXIE_C_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_D_PORT,NIXIE_D_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_E_PORT,NIXIE_E_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_F_PORT,NIXIE_F_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_G_PORT,NIXIE_G_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(NIXIE_DP_PORT,NIXIE_DP_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
}
void NixieTubeTest(void)
{
  uint8_t j,i;
  for(j=1;j<4;j++)
  {
    NixieTubeCOMSelect(j);
    for(i=0;i<10;i++)
    {
       NixieTube(i); 
       DelayMs(200);
       NixieTube(10);
       DelayMs(1);
    }
  }
}
void NixieTubeCOMSelect(uint8_t COMx)
{
  switch (COMx)
  {
    case 1:
      NIXIE_COM1ON;
      NIXIE_COM2OFF;
      NIXIE_COM3OFF;
      break;
    case 2:
      NIXIE_COM1OFF;
      NIXIE_COM2ON;
      NIXIE_COM3OFF;
      break;
    case 3:
      NIXIE_COM1OFF;
      NIXIE_COM2OFF;
      NIXIE_COM3ON;
      break;    
    case 4:
      NIXIE_COM1OFF;
      NIXIE_COM2OFF;
      NIXIE_COM3OFF;
      break;
    default:
      break;  
  }
}
void NixieTube(unsigned char data)  
{                                   
  unsigned char tempdata=0;         
  tempdata=data & 0x7F;             
  switch (tempdata)                 
  {                                 
    case 0:                         
            NixieTubeAON;           
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDON;           
            NixieTubeEON;           
            NixieTubeFON;           
            NixieTubeGOFF;          
            break;                  
    case 1:                         
            NixieTubeAOFF;          
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDOFF;          
            NixieTubeEOFF;          
            NixieTubeFOFF;          
            NixieTubeGOFF;          
            break;                  
    case 2:                         
            NixieTubeAON;           
            NixieTubeBON;           
            NixieTubeCOFF;          
            NixieTubeDON;           
            NixieTubeEON;           
            NixieTubeFOFF;          
            NixieTubeGON;           
            break;                  
    case 3:                         
            NixieTubeAON;           
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDON;           
            NixieTubeEOFF;          
            NixieTubeFOFF;          
            NixieTubeGON;           
            break;                  
    case 4:                         
            NixieTubeAOFF;          
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDOFF;          
            NixieTubeEOFF;          
            NixieTubeFON;           
            NixieTubeGON;           
            break;                  
    case 5:                         
            NixieTubeAON;           
            NixieTubeBOFF;          
            NixieTubeCON;           
            NixieTubeDON;           
            NixieTubeEOFF;          
            NixieTubeFON;           
            NixieTubeGON;           
            break;                  
    case 6:                         
            NixieTubeAON;           
            NixieTubeBOFF;          
            NixieTubeCON;           
            NixieTubeDON;           
            NixieTubeEON;           
            NixieTubeFON;           
            NixieTubeGON;           
            break;                  
    case 7:                         
            NixieTubeAON;           
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDOFF;          
            NixieTubeEOFF;          
            NixieTubeFOFF;          
            NixieTubeGOFF;          
            break;                  
    case 8:                         
            NixieTubeAON;           
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDON;           
            NixieTubeEON;           
            NixieTubeFON;           
            NixieTubeGON;           
            break;                  
    case 9:                         
            NixieTubeAON;           
            NixieTubeBON;           
            NixieTubeCON;           
            NixieTubeDON;           
            NixieTubeEOFF;          
            NixieTubeFON;           
            NixieTubeGON;           
            break;                  
    case 10:             //all off  
            NixieTubeAOFF;          
            NixieTubeBOFF;          
            NixieTubeCOFF;          
            NixieTubeDOFF;          
            NixieTubeEOFF;          
            NixieTubeFOFF;          
            NixieTubeGOFF;          
            break;                  
    case 11:             //all on   
            NixieTubeAON;           
            NixieTubeBON;	          
            NixieTubeCON;	          
            NixieTubeDON;	          
            NixieTubeEON;	          
            NixieTubeFON;	          
            NixieTubeGON;	          
            break;   
    case 12:             //all on   
            NixieTubeAOFF;           
            NixieTubeBOFF;	          
            NixieTubeCOFF;	          
            NixieTubeDOFF;	          
            NixieTubeEOFF;	          
            NixieTubeFOFF;	          
            NixieTubeGON;	          
            break;  
    default:                        
            break;                  
  }                                 
  if(data & 0x80)                   
  {                                 
          NixieTubeDPON;            
  }                                 
  else                              
  {                                 
          NixieTubeDPOFF;           
  }                                 
}                                   
void UnpackageHCHO(unsigned int data,unsigned int data1,uint8_t Data_ADC)
{
  if(Data_ADC)
  {
    if(data>=100)
    {
      NixieData[0]=data/100;
      NixieData[0]|=0x80;
      NixieData[1]=data%100/10;
      NixieData[2]=data%10;
    }
    else if(data<100 && data>=10)
    {
      NixieData[0]=0;
      NixieData[0]|=0x80;
      NixieData[1]=data/10;
      NixieData[2]=data%10;							
    }
    else if(data<10)
    {
      NixieData[0]=0;
      NixieData[0]|=0x80;
      NixieData[1]=0;
      NixieData[2]=data%10;							
    }
  }
  else
  {
    if(data1>999)
    {
      data1=999;
    }
    if(data1>=100)
    {
      NixieData[0]=data1/100;
      NixieData[1]=data1%100/10;
      NixieData[2]=data1%10;
    }
    else if(data1<100 && data1>=10)
    {
      NixieData[0]=10;
      NixieData[1]=data1/10;
      NixieData[2]=data1%10;							
    }
    else if(data1<10)
    {
      NixieData[0]=10;
      NixieData[1]=10;
      NixieData[2]=data1%10;							
    }
  }
  
}