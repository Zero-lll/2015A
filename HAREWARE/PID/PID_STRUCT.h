#ifndef __FUNTION_H
#define __FUNTION_H



/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct 
{
 /*PID�㷨�ӿڱ��������ڻ�ȡ���޸�PID�㷨������*/
 float kp;     //����ϵ��
 float ki;     //����ϵ��
 float kd;     //΢��ϵ��
 
 float errNow; //��ǰ�����
 float errILim;//�����޷�
 float dCtrOut;//�����������
 float ctrOut;//�������
 float OutLim_Max;//����޷�
 float OutLim_Min;//����޷�
 
 /*PID�㷨�ڲ���������ֵ�����޸�*/
 float errOld1;
 float errOld2;
 
}PID_IncrementType;



#endif
