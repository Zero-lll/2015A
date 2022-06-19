#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
extern int o;								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_0;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE4,3

// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB,PORTE时钟

//	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_4;//KEY0,KEY1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB4,3

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
//		else if(WK_UP==1)return WKUP_PRES;
	}
	//else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	    
 	return 0;// 无按键按下
}






void EXTIX_Init(void)
{  
		EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟



   //GPIO.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
  	NVIC_Init(&NVIC_InitStructure); 
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
  	NVIC_Init(&NVIC_InitStructure); 
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
  	NVIC_Init(&NVIC_InitStructure); 
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}



//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键KEY1
	{				 
		Target_Speed+=0.1;
		
	}	
//		else if();
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==0)	 //按键KEY1
	{				 
		Target_Speed-=0.1;
		
	}	
//		else if();
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE3上的中断标志位  
}

void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0)	 //按键KEY1
	{				 
		o=1;
        LED1( ON );	
        Target_Speed=30;
        
       // LED1( OFF );	
		
	}	
//		else if();
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除LINE3上的中断标志位  
}

//void EXTIXInit(void)
//{
//		NVIC_InitTypeDef	 	NVIC_InitStructure;
//   	EXTI_InitTypeDef 		EXTI_InitStructure;
//	KEY_Init();	 
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);	//使能复用功能时钟
//	 
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);//按键PB 3	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//按键PB４

//	//按键+中断
//	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_InitStructure);
//	//按键-中断
//	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_InitStructure);

//	//按键+优先级		
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键 + 所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//		//按键-优先级
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键 - 所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级1 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);

//}


//void EXTI5_IRQHandler(void)
//{		
//		vu8 key=0;	
// 		key=KEY_Scan(1);	//得到键值
//	   	if(key-1)
//		{		
//							Set_Vac-=0.1;
//		}
//		EXTI_ClearITPendingBit(EXTI_Line5);
//}

//void EXTI4_IRQHandler(void)
//{		
//		vu8 key=0;	
// 		key=KEY_Scan(1);	//得到键值
//	   	if(key)
//		{
//			delay_ms(10);
//		if(key)
//		{						
//			Set_Vac-=0.1;
//		}
//	    }
//		EXTI_ClearITPendingBit(EXTI_Line4);
//}

// 
