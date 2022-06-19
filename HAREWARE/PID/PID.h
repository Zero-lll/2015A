#ifndef __PID_H
#define	__PID_H

#include "stm32f10x.h"


float SpeedContorl_PID (float Now_Speed,float Target_Speed);
float Contorl_PID(float Now,float Target);
//float Voltage_PID (float Now_Speed,float Target_Speed);
static float Bias,temp,Integral_bias,Last_Bias;
extern float Target_Speed,Now_Speed,Now,Target;
//extern float PID_Control_Iac(float ture_value);
//void PID_Init(void); 
//int PID_Calc(int NextPoint,int Setpoint);
//void User_PidControl(float ture_value);
//void PID(void);
#endif
