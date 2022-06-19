
#include "AdvanceTim.h" 

static void ADVANCE_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1_PIN  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CH_PORT, &GPIO_InitStructure);

  // 输出比较通道互补通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CHN_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_CH1N_PIN  ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_CHN_PORT, &GPIO_InitStructure);

  // 输出比较通道刹车通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_BKIN_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  ADVANCE_TIM_BKIN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ADVANCE_TIM_BKIN_PORT, &GPIO_InitStructure);
	// BKIN引脚默认先输出低电平
	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT,ADVANCE_TIM_BKIN_PIN);
}





// ANSIC C  C89 C语言的标准的话
// C99 支持任意地方定义变量
// C11 这个是最新的C语言标准
static void ADVANCE_TIM_Mode_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_OCInitTypeDef  TIM_OCInitStructure;
		TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
		// 开启定时器时钟,即内部时钟CK_INT=72M
	ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/

	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_PERIOD;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= ADVANCE_TIM_PSC;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/		

	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 互补输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// 互补输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	// 互补输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	// 设置占空比大小
	TIM_OCInitStructure.TIM_Pulse = ADVANCE_TIM_PULSE;


  TIM_OC1Init(ADVANCE_TIM,&TIM_OCInitStructure);	 								 	//使能通道1
	TIM_OC1PreloadConfig(ADVANCE_TIM,TIM_OCPreload_Enable);				 	  //使能预装载	
	
	TIM_OC2Init(ADVANCE_TIM,&TIM_OCInitStructure);                    //使能通道2
	TIM_OC2PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);          //使能预装载	

	TIM_OC3Init(ADVANCE_TIM,&TIM_OCInitStructure);	 								 	//使能通道3
	TIM_OC3PreloadConfig(ADVANCE_TIM,TIM_OCPreload_Enable);				 	  //使能预装载	


	/*-------------------刹车和死区结构体初始化-------------------*/
	// 有关刹车和死区结构体的成员具体可参考BDTR寄存器的描述

  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	// 输出比较信号死区时间配置，具体如何计算可参考 BDTR:UTG[7:0]的描述
  TIM_BDTRInitStructure.TIM_DeadTime = 10;  //[7:5]0xx 死区=[7:0]*13.89ns  例：11*13.89ns=152.79ns
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	// 当BKIN引脚检测到高电平的时候，输出比较信号被禁止，就好像是刹车一样
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);
		

	TIM_Cmd(ADVANCE_TIM,ENABLE);	        // 使能计数器
	TIM_CtrlPWMOutputs(ADVANCE_TIM,ENABLE);	//PWM输出使能																		
}


void ADVANCE_TIM_Init(void)
{
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_Mode_Config();

}







/*********************************************END OF FILE**********************/
