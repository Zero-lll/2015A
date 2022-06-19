#ifndef __FUNTION_H
#define __FUNTION_H



/*增量式PID算法，接口参数结构类型*/
typedef struct 
{
 /*PID算法接口变量，用于获取或修改PID算法的特性*/
 float kp;     //比例系数
 float ki;     //积分系数
 float kd;     //微分系数
 
 float errNow; //当前的误差
 float errILim;//积分限幅
 float dCtrOut;//控制增量输出
 float ctrOut;//控制输出
 float OutLim_Max;//输出限幅
 float OutLim_Min;//输出限幅
 
 /*PID算法内部变量，其值不能修改*/
 float errOld1;
 float errOld2;
 
}PID_IncrementType;



#endif
