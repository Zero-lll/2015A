#include "stm32f10x.h"
#include "sys.h"


/************************************************
互补PWM波 TIM1 PA8|PB13 接IR2110

   ADC  通道0 PA0 测输出电流  Iout
		通道1 PA1 测输入电压  Vin
		通道2 PA2 测输出电压  Vout

EC11旋转编码器 A/B相    TIM4  PB6/PB7  按键PA3

SD-----控制IR2110驱动  置1失效  ---PB14

蜂鸣器----PB8

OLED    SCL---PA5     SDA---PA7

TIM3中断 定时
************************************************/
// ADC1转换的电压值通过MDA方式传到SRAM
//extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

extern uint8_t flag_1ms;
extern uint8_t flag_2ms;
extern uint8_t flag_200us ;
extern uint8_t flag_5ms;
extern float Set_Vac;
u16 adcx;
int i;
float summ;
float Vin,Vout,Vout1,Iout;		//角度
int o;
// 局部变量，用于保存转换计算后的电压值 	
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
