#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"


void Adc1_Init(void);
void Adc2_Init(void);
u16 Get_Adc( u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);
u16 ADC_filter(u8 ch);
 
#endif 
