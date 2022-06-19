#ifndef __BSP_ADVANCETIME_H
#define __BSP_ADVANCETIME_H


#include "stm32f10x.h"
extern u16 output;
/************�߼���ʱ��TIM�������壬ֻ��TIM1��TIM8************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������ʹ�ø߼����ƶ�ʱ��TIM1

#define            ADVANCE_TIM                   TIM1
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM1
// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            ADVANCE_TIM_PERIOD            (1440-1)//1440-1
#define            ADVANCE_TIM_PSC               (1-1) //4
#define            ADVANCE_TIM_PULSE              800


// TIM1 ����Ƚ�ͨ��
#define            ADVANCE_TIM_CH_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH_PORT          GPIOA
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_8
#define            ADVANCE_TIM_CH2_PIN           GPIO_Pin_9
#define            ADVANCE_TIM_CH3_PIN           GPIO_Pin_10

// TIM1 ����Ƚ�ͨ���Ļ���ͨ��
#define            ADVANCE_TIM_CHN_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CHN_PORT          GPIOB
#define            ADVANCE_TIM_CH1N_PIN           GPIO_Pin_13
#define            ADVANCE_TIM_CH2N_PIN           GPIO_Pin_14
#define            ADVANCE_TIM_CH3N_PIN           GPIO_Pin_15
// TIM1 ����Ƚ�ͨ����ɲ��ͨ��
#define            ADVANCE_TIM_BKIN_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_BKIN_PORT          GPIOB
#define            ADVANCE_TIM_BKIN_PIN           GPIO_Pin_12



void ADVANCE_TIM_Init(void);


void ADVANCE_TIM_Init(void);


#endif	/* __BSP_ADVANCETIME_H */


