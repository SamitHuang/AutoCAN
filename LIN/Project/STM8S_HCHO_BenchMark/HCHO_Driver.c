#include "HCHO_Driver.h"
#include "stm8s.h"

uint8_t flag_Start_Measure=0;
uint16_t flag_S_cnt=0;
uint16_t HCHOADCBuff=0,HCHOADCbenchmark=0,HCHOMgCm3=0;
uint8_t HCHOADCbenchmarkBuff[2]={0};

void Get_HCHOValue(void)
{
  if(HCHOADCBuff<=HCHOADCbenchmark)
  {
    HCHOMgCm3=(HCHOADCbenchmark-HCHOADCBuff)*40/47;
  }
}