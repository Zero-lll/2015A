#include "timer.h"
#include "usart.h"

#include "PID.h"
#include "PID_STRUCT.h"
//V1.1 20120904
//1,Ôö¼ÓTIM3_PWM_Initº¯Êı¡£
//2,Ôö¼ÓLED0_PWM_VALºê¶¨Òå£¬¿ØÖÆTIM3_CH2Âö¿í									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//Í¨ÓÃ¶¨Ê±Æ÷3ÖĞ¶Ï³õÊ¼»¯
//ÕâÀïÊ±ÖÓÑ¡ÔñÎªAPB1µÄ2±¶£¬¶øAPB1Îª36M
//arr£º×Ô¶¯ÖØ×°Öµ¡£
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
//ÕâÀïÊ¹ÓÃµÄÊÇ¶¨Ê±Æ÷3!
//extern float ADC_ConvertedValueLocal[NOFCHANEL];    

//// ¾Ö²¿±äÁ¿£¬ÓÃÓÚ±£´æ×ª»»¼ÆËãºóµÄµçÑ¹Öµ 

int PWM_out1,PWM_out2,a;
 u16 b,output=0;
 u16 output1=0;
float change;
extern int o;
extern float Iout,Vout,Vin,Set_Vac,Vout1;
 /*¾ø¶ÔÖµº¯Êı*/
int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}


void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Ê±ÖÓÊ¹ÄÜ

	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 ¼ÆÊıµ½5000Îª500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  10KhzµÄ¼ÆÊıÆµÂÊ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM3ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷

	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIMxÍâÉè
							 
}
//¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò
void TIM3_IRQHandler(void)   //TIM3ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //¼ì²éÖ¸¶¨µÄTIMÖĞ¶Ï·¢ÉúÓë·ñ:TIM ÖĞ¶ÏÔ´ 
		{ 
	
//			if(Iout>=2.5)stopcif=1;//¹ıÁ÷±£»¤
			//Í¨¹ıPID¼ÆËãPWMÕ¼¿Õ±È ³äµç BUCK ×ó¶ËºãÑ¹
             
            if(o==0)
                { if(Vout>0){
                output=SpeedContorl_PID(Vout,Target_Speed);
             //   output1=SpeedContorl_PID1(Vin,Target_Speed1);
                    b=output;
			if(output>1300)//91%
 				output=1300;
                  if(output<450)//91%
 				output=450;
            TIM_SetCompare1(TIM1,output);//±Õ»·PI¼ÆËãºóÊä³{
       //     TIM_SetCompare3(TIM3,output1);
        }	}
//            else if(o==1)                
//            {  
//                LED1(OFF);
//                output=SpeedContorl_PID(Vout1,Target_Speed);
//                
//                if(output>1400)//91%
// 				output=1400;
//            	if(output<750)//91%
//                  output=750;
//            if(a==0){output=1000;}
//            a++;
//            TIM_SetCompare1(TIM1,output);
//            }

		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //Çå³ıTIM2¸üĞÂÖĞ¶Ï±êÖ¾	
}

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //Ê±ÖÓÊ¹ÄÜ

	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 ¼ÆÊıµ½5000Îª500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  10KhzµÄ¼ÆÊıÆµÂÊ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM3ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷

	TIM_Cmd(TIM2,ENABLE);  //Ê¹ÄÜTIMxÍâÉè
							 
}
//¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò
//void TIM2IRQHandler(void)   //TIM3ÖĞ¶Ï
//{  
////	int PWM_out;
//	if (TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET) //¼ì²éÖ¸¶¨µÄTIMÖĞ¶Ï·¢ÉúÓë·ñ:TIM ÖĞ¶ÏÔ´ 
//		{
//  	time_count++;
//		if(time_count/4==0)
//		{
//			flag_200us = 1;
//		}
//		if(time_count==20)    
//		{
//			time_count = 0;
//			flag_1ms = 1;
//		}
//			
//		}
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //Çå³ıTIM2¸üĞÂÖĞ¶Ï±êÖ¾	
//}
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//Ê¹ÄÜ¶¨Ê±Æ÷3Ê±ÖÓ
 //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
   //ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ,Êä³öTIM3 CH4µÄPWMÂö³å²¨ĞÎ	GPIOB.1
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //TIM3_CH1,ch2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM3_CH4,ch3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
 
   //³õÊ¼»¯TIM3
	TIM_TimeBaseStructure.TIM_Period =arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î» 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
//	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC3
//  TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
 /* TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿
	*/
//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
//  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIM3
	

}










