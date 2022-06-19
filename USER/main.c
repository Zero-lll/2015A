#include "stm32f10x.h"
#include "sys.h"


/************************************************
����PWM�� TIM1 PA8|PB13 ��IR2110

   ADC  ͨ��0 PA0 ���������  Iout
		ͨ��1 PA1 �������ѹ  Vin
		ͨ��2 PA2 �������ѹ  Vout

EC11��ת������ A/B��    TIM4  PB6/PB7  ����PA3

SD-----����IR2110����  ��1ʧЧ  ---PB14

������----PB8

OLED    SCL---PA5     SDA---PA7

TIM3�ж� ��ʱ
************************************************/
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
//extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

extern uint8_t flag_1ms;
extern uint8_t flag_2ms;
extern uint8_t flag_200us ;
extern uint8_t flag_5ms;
extern float Set_Vac;
u16 adcx;
int i;
float summ;
float Vin,Vout,Vout1,Iout;		//�Ƕ�
int o;
// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	
//float ADC_ConvertedValueLocal[NOFCHANEL];  
//float Vin;
//float Vout;
//float Iout_Temp;
//float Iout;
float Iout_Temp;
extern u16 output,b; 
extern float change;

u8 string[10] = {0};

//  u16 stopcif=0;
//u8 temp;
// void Delay(u32 count)
// {
//   u32 i=0;
//   for(;i<count;i++);
// }

 int main(void)
 {
	delay_init();
	NVIC_Config();
	uart_init(115200);
	BEEP_Init();
	Adc1_Init();
    OLED_Init();
    OLED_Clear();
	LED_GPIO_Config();
	KEY_Init();
	EXTIX_Init();
	BEEP_Init();
//	Encoder_TIM4_Init();
	TIM3_Int_Init(9999,71);   //10ms  	
//	TIM2_Int_Init(3599,0); //   50us
	ADVANCE_TIM_Init(); // 50K
//     TIM3_PWM_Init(1399,0);
//     SpeedContorl_PID();
//	 TIM_SetCompare1(TIM1,500); 
     PBout(8)=1;
        o=0;
  while(1)
	{	
	    Vin=(float) ADC_filter(ADC_Channel_1)/4096*3.3/0.03927*0.1;//dianya10.225-10.138
		Vout=(float) ADC_filter(ADC_Channel_2)/4096*3.3;
 
        Vout=Vout* 1.909 ;//dianliu
        Vout-= 3.122;
        if(Vout<0.05)
            Vout=0;

        Vout1=(float) ADC_filter(ADC_Channel_6)/4096*3.3*20.88+0.04183;
     
        if(Vin>24)
          PBout(8)=0;

		sprintf((char *)string,"pwm :%d  ",b);//0300
  	    OLED_ShowString(0,0,string,16);
        
        if(o==0){
		sprintf((char *)string,"V:%.3f  ",Vin);//0300
     	OLED_ShowString(0,2,string,16);
		OLED_ShowString(110,2,"V",16);
            OLED_ShowString(110,6,"A",16);
        }
        
//        else if(o==1)
//        {
//        sprintf((char *)string,"V:%.3f  ",Vout1);//0300
//     	OLED_ShowString(0,2,string,16);
//		OLED_ShowString(110,2,"V",16);
//        OLED_ShowString(110,6,"V",16);
//        }
        
		sprintf((char *)string,"I:%.3f  ",Vout);//0300
        OLED_ShowString(0,4,string,16);
		OLED_ShowString(110,4,"A",16);
        
        sprintf((char *)string,"Set:%.2f",Target_Speed);//0300
    	OLED_ShowString(0,6,string,16);
	//	OLED_ShowString(110,6,"A",16);
        
//		sprintf((char *)string,"Vin:%.3f V",Vin);//0300
//  	OLED_ShowString(0,0,string,16);
	     delay_ms(500);
		
//		if(flag_2ms==1)
//		{
//			flag_2ms=0;
//			if(Read_Speed(4)>0) Target_Voltage+=1;
//			if(Read_Speed(4)<0) Target_Voltage-=1;
//		
//		}
//				if(flag_5ms==1)
//		{
//		    flag_5ms=0;
//	

////		
////			

		}
			
 }
