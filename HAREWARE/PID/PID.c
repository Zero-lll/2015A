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
     //�����ٶ�
	// Speed_KP=80,Speed_KI=0.77,Speed_KD=0;        //10,0.8
//    }
//   else if(o==1)  
//   {
//      	    //    LED1( ON );	           //�����ٶ�
//	 Speed_KP=-1,Speed_KI=-0.7,Speed_KD=0;   
//   }
    // static float Bias,temp,Integral_bias,Last_Bias;
     Bias=Target_Speed-Now_Speed;                                  //���ƫ��ɲ���ֵ��ȥĿ��ֵ��
     Integral_bias+=Bias;                                    //���ƫ��Ļ���
	 Integral_bias=Integral_bias>1900?1900:(Integral_bias<(-1900)?(-1900):Integral_bias);  //�����޷�
     temp=Speed_KP*Bias+Speed_KI*Integral_bias+Speed_KD*(Bias-Last_Bias);       //λ��ʽPID������   
     Last_Bias=Bias;                                       //������һ��ƫ�� 
     return temp;                                           //�������
}


// float Target=1;	//�����ٶ�
//	
//	
//  float KP=1,KI=0.7,KD=0;        //10,0.8

//float Contorl_PID (float Now_Speed,float Target_Speed)
//{   
//  
//    // static float Bias,temp,Integral_bias,Last_Bias;
//     Bias=Target_Speed-Now_Speed;                                  //���ƫ��ɲ���ֵ��ȥĿ��ֵ��
//     Integral_bias+=Bias;                                    //���ƫ��Ļ���
//	 Integral_bias=Integral_bias>1900?1900:(Integral_bias<(-1900)?(-1900):Integral_bias);  //�����޷�
//     temp=Speed_KP*Bias+Speed_KI*Integral_bias+Speed_KD*(Bias-Last_Bias);       //λ��ʽPID������
//     Last_Bias=Bias;                                       //������һ��ƫ�� 
//     return temp;                                           //�������
//}


////����ʽPID�㷨
//void PID_IncrementMode(PID_IncrementType* PID)
//{
// int16_t dErrP, dErrI, dErrD;
// 
// dErrP = PID->errNow - PID->errOld1;

// dErrI = PID->errNow;

// dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

// PID->errOld2 = PID->errOld1; //�������΢��
// PID->errOld1 = PID->errNow;  //һ�����΢��

// /*����ʽPID����*/
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
//float Set_Vac = 1.2; //��ҪУ׼
//PID_IncrementType PID_Vac;//����PID�㷨�Ľṹ��
//float PID_Control_Iac(float ture_value)		
//{
//	float M = 0;
//	PID_Vac.errNow = Set_Vac-ture_value;
//	PID_Vac.kp     = 1100;
//	PID_Vac.ki     = 0.5;
//	PID_Vac.kd     = 10;
//	PID_Vac.errILim    = 2000;//�����޷�  51200
//	PID_Vac.OutLim_Max = 1500;//����޷�
//	PID_Vac.OutLim_Min = 0.1;
//	PID_IncrementMode(&PID_Vac);
//	M = PID_Vac.ctrOut;
//	return M;
//}

///*****************************************PID***********************************************/
//float ideal_value=5.0;
////PID_IncrementType PID_Control;//����PID�㷨�Ľṹ��
//PID_AbsoluteType PID_Control;
//void User_PidControl(float ture_value)
//{
//   PID_Control.errNow = ideal_value-ture_value; //���㲢д���ٶ����
//   	
//   PID_Control.kp      =10.0;//60; //32;////33;              //45   //10.38;//15//1464.7; //15.38;//13            //д�����ϵ��Ϊ15
//	 PID_Control.ki      = 5.0;//10;//2.73;////3.0;            //1.2    //0.5;//5//17;//2.88;//1.3;              //д�����ϵ��Ϊ5
//	 PID_Control.kd      = 0.1;                   //0;//0.05//0.12;//0;//0.05              //д��΢��ϵ��Ϊ5
//   PID_Control.errILim = 1700;           //д������������Ϊ1000  //����Ϊ��

//   PID_AbsoluteMode(&PID_Control);       //ִ�о���ʽPID�㷨
//   Duty = (uint16_t)PID_Control.ctrOut;
//	 if(Duty>1700) Duty=1700;
////	 TIM_SetCompare1(TIM2, Duty);//����TIMx����Ƚ�2�Ĵ���ֵ
//	
//    TIM_SetCompare1(TIM1  , Duty);        //���ú����ı�ռ�ձ�
//	 // printf("\r\n Duty value = %d V \r\n",Duty);
//	
//}

//    typedef struct 
//    {
//    //int      SetPoint;                                 //�趨Ŀ�� Desired Value
//    double   Proportion;                               //�������� Proportional Const
//    double   Integral;                                 //���ֳ��� Integral Const
//    double   Derivative;                               //΢�ֳ��� Derivative Const
//    int      LastError;                                //Error[-1]
//    int      PrevError;                                //Error[-2]
//    }PID;

//    //����PID��غ�
//    // �����������趨�Ե������Ӱ��ǳ���
//    /*************************************/
//    #define  P_DATA      0                             //P����
//    #define  I_DATA      0.5                             //I����
//    #define  D_DATA      0                            //D����



//    static PID sPID;
//    static PID *sptr = &sPID;
//    /**************PID������ʼ��********************************/
//    void PID_Init(void) 
//    {
//    sptr->LastError=0;            //Error[-1]
//    sptr->PrevError=0;            //Error[-2]
//    sptr->Proportion=P_DATA;      //�������� Proportional Const
//    sptr->Integral=I_DATA;        //���ֳ���  Integral Const
//    sptr->Derivative=D_DATA;      //΢�ֳ��� Derivative Const
//    //sptr->SetPoint=500;           //�趨Ŀ��Desired Value
//    }
//    /********************����ʽPID�������************************************/
//    //NextPoint��ǰ���ֵ
//    //SetPoint�趨ֵ
//    float Set_Vac = 1.2;
//    int PID_Calc(int NextPoint,int SetPoint) 
//    {
//    int iError,Outpid;                                   //��ǰ���
//    iError=SetPoint-NextPoint;                           //��������
//    Outpid=(sptr->Proportion * iError)                   //E[k]��
//          -(sptr->Integral * sptr->LastError)      //E[k-1]��
//          +(sptr->Derivative * sptr->PrevError);   //E[k-2]��
//          
//    sptr->PrevError=sptr->LastError;                     //�洢�������´μ���
//    sptr->LastError=iError;
//    return(Outpid);                                      //��������ֵ
//    }



