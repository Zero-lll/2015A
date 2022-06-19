#include "PID.h"
#include "PID_STRUCT.h"
#include "key.h"
float Target_Speed=0.5,Speed_KP=100,Speed_KI=30,Speed_KD=0;
extern int o;
//uint16_t Duty;

float SpeedContorl_PID (float Now_Speed,float Target_Speed)
{   
//  
//     if(o==0)
//     {
     //期望速度
	// Speed_KP=80,Speed_KI=0.77,Speed_KD=0;        //10,0.8
//    }
//   else if(o==1)  
//   {
//      	    //    LED1( ON );	           //期望速度
//	 Speed_KP=-1,Speed_KI=-0.7,Speed_KD=0;   
//   }
    // static float Bias,temp,Integral_bias,Last_Bias;
     Bias=Target_Speed-Now_Speed;                                  //求出偏差，由测量值减去目标值。
     Integral_bias+=Bias;                                    //求出偏差的积分
	 Integral_bias=Integral_bias>1900?1900:(Integral_bias<(-1900)?(-1900):Integral_bias);  //积分限幅
     temp=Speed_KP*Bias+Speed_KI*Integral_bias+Speed_KD*(Bias-Last_Bias);       //位置式PID控制器   
     Last_Bias=Bias;                                       //保存上一次偏差 
     return temp;                                           //增量输出
}


// float Target=1;	//期望速度
//	
//	
//  float KP=1,KI=0.7,KD=0;        //10,0.8

//float Contorl_PID (float Now_Speed,float Target_Speed)
//{   
//  
//    // static float Bias,temp,Integral_bias,Last_Bias;
//     Bias=Target_Speed-Now_Speed;                                  //求出偏差，由测量值减去目标值。
//     Integral_bias+=Bias;                                    //求出偏差的积分
//	 Integral_bias=Integral_bias>1900?1900:(Integral_bias<(-1900)?(-1900):Integral_bias);  //积分限幅
//     temp=Speed_KP*Bias+Speed_KI*Integral_bias+Speed_KD*(Bias-Last_Bias);       //位置式PID控制器
//     Last_Bias=Bias;                                       //保存上一次偏差 
//     return temp;                                           //增量输出
//}


////增量式PID算法
//void PID_IncrementMode(PID_IncrementType* PID)
//{
// int16_t dErrP, dErrI, dErrD;
// 
// dErrP = PID->errNow - PID->errOld1;

// dErrI = PID->errNow;

// dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

// PID->errOld2 = PID->errOld1; //二阶误差微分
// PID->errOld1 = PID->errNow;  //一阶误差微分

// /*增量式PID计算*/
// PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;
// 
// if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;
//	
// if(PID->dCtrOut > PID->errILim)  PID->dCtrOut = PID->errILim;
//	
// if(PID->dCtrOut < -1*PID->errILim) PID->dCtrOut = -1*PID->errILim;
//	 
// 
// PID->ctrOut = PID->ctrOut + PID->dCtrOut;
// 

// if(PID->ctrOut > PID->OutLim_Max) PID->ctrOut = PID->OutLim_Max;
// if(PID->ctrOut < PID->OutLim_Min) PID->ctrOut = PID->OutLim_Min;
//}
///*******************************************************************************************************/

////**********************PID_Vac*************************/
//float Set_Vac = 1.2; //需要校准
//PID_IncrementType PID_Vac;//定义PID算法的结构体
//float PID_Control_Iac(float ture_value)		
//{
//	float M = 0;
//	PID_Vac.errNow = Set_Vac-ture_value;
//	PID_Vac.kp     = 1100;
//	PID_Vac.ki     = 0.5;
//	PID_Vac.kd     = 10;
//	PID_Vac.errILim    = 2000;//积分限幅  51200
//	PID_Vac.OutLim_Max = 1500;//输出限幅
//	PID_Vac.OutLim_Min = 0.1;
//	PID_IncrementMode(&PID_Vac);
//	M = PID_Vac.ctrOut;
//	return M;
//}

///*****************************************PID***********************************************/
//float ideal_value=5.0;
////PID_IncrementType PID_Control;//定义PID算法的结构体
//PID_AbsoluteType PID_Control;
//void User_PidControl(float ture_value)
//{
//   PID_Control.errNow = ideal_value-ture_value; //计算并写入速度误差
//   	
//   PID_Control.kp      =10.0;//60; //32;////33;              //45   //10.38;//15//1464.7; //15.38;//13            //写入比例系数为15
//	 PID_Control.ki      = 5.0;//10;//2.73;////3.0;            //1.2    //0.5;//5//17;//2.88;//1.3;              //写入积分系数为5
//	 PID_Control.kd      = 0.1;                   //0;//0.05//0.12;//0;//0.05              //写入微分系数为5
//   PID_Control.errILim = 1700;           //写入误差积分上限为1000  //下限为零

//   PID_AbsoluteMode(&PID_Control);       //执行绝对式PID算法
//   Duty = (uint16_t)PID_Control.ctrOut;
//	 if(Duty>1700) Duty=1700;
////	 TIM_SetCompare1(TIM2, Duty);//设置TIMx捕获比较2寄存器值
//	
//    TIM_SetCompare1(TIM1  , Duty);        //调用函数改变占空比
//	 // printf("\r\n Duty value = %d V \r\n",Duty);
//	
//}

//    typedef struct 
//    {
//    //int      SetPoint;                                 //设定目标 Desired Value
//    double   Proportion;                               //比例常数 Proportional Const
//    double   Integral;                                 //积分常数 Integral Const
//    double   Derivative;                               //微分常数 Derivative Const
//    int      LastError;                                //Error[-1]
//    int      PrevError;                                //Error[-2]
//    }PID;

//    //定义PID相关宏
//    // 这三个参数设定对电机运行影响非常大
//    /*************************************/
//    #define  P_DATA      0                             //P参数
//    #define  I_DATA      0.5                             //I参数
//    #define  D_DATA      0                            //D参数



//    static PID sPID;
//    static PID *sptr = &sPID;
//    /**************PID参数初始化********************************/
//    void PID_Init(void) 
//    {
//    sptr->LastError=0;            //Error[-1]
//    sptr->PrevError=0;            //Error[-2]
//    sptr->Proportion=P_DATA;      //比例常数 Proportional Const
//    sptr->Integral=I_DATA;        //积分常数  Integral Const
//    sptr->Derivative=D_DATA;      //微分常数 Derivative Const
//    //sptr->SetPoint=500;           //设定目标Desired Value
//    }
//    /********************增量式PID控制设计************************************/
//    //NextPoint当前输出值
//    //SetPoint设定值
//    float Set_Vac = 1.2;
//    int PID_Calc(int NextPoint,int SetPoint) 
//    {
//    int iError,Outpid;                                   //当前误差
//    iError=SetPoint-NextPoint;                           //增量计算
//    Outpid=(sptr->Proportion * iError)                   //E[k]项
//          -(sptr->Integral * sptr->LastError)      //E[k-1]项
//          +(sptr->Derivative * sptr->PrevError);   //E[k-2]项
//          
//    sptr->PrevError=sptr->LastError;                     //存储误差，用于下次计算
//    sptr->LastError=iError;
//    return(Outpid);                                      //返回增量值
//    }



