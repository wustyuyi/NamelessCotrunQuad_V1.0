#ifndef _ADRC_H_
#define _ADRC_H_
/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               �޸�����:2018/8/30
*               �汾���۷��ߡ���V1.0.1
*               ��Ȩ���У�����ؾ���
*               Copyright(C) �人�Ƽ���ѧ�����ƴ��Ŷ� 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
typedef struct
{
/*****���Ź��ȹ���*******/
float x1;//����΢����״̬��
float x2;//����΢����״̬��΢����
float r;//ʱ��߶�
float h;//ADRCϵͳ����ʱ��
uint16 N0;//����΢��������ٶȳ���h0=N*h

float h0;
float fh;//����΢�ּ��ٶȸ�����
/*****����״̬�۲���*******/
/******��ϵͳ���y������u�����ٹ���ϵͳ״̬���Ŷ�*****/
float z1;
float z2;
float z3;//���ݿ��ƶ����������������ȡ���Ŷ���Ϣ
float e;//ϵͳ״̬���
float y;//ϵͳ�����
float fe;
float fe1;
float beta_01;
float beta_02;
float beta_03;
float b;


/**********ϵͳ״̬������*********/
float e0;//״̬��������
float e1;//״̬ƫ��
float e2;//״̬��΢����
float u0;//���������ϵͳ���
float u;//���Ŷ�����������
float b0;//�Ŷ�����

/*********��һ�������ʽ*********/
float beta_0;//����
float beta_1;//��������ϲ���
float beta_2;//u0=beta_1*e1+beta_2*e2+(beta_0*e0);
/*********�ڶ��������ʽ*********/
float alpha1;//u0=beta_1*fal(e1,alpha1,zeta)+beta_2*fal(e2,alpha2,zeta)
float alpha2;//0<alpha1<1<alpha2
float zeta;//���Զε����䳤��
/*********�����������ʽ*********/
float h1;//u0=-fhan(e1,e2,r,h1);
uint16 N1;//����΢��������ٶȳ���h0=N*h
/*********�����������ʽ*********/
float c;//u0=-fhan(e1,c*e2*e2,r,h1);

float e2_lpf;
Butter_BufferData ADRC_LPF_Buffer;//��������ͨ�����������

float TD_Input;
float Last_TD_Input;
float TD_Input_Div;

float ESO_Input;
float Last_ESO_Input;
float ESO_Input_Div;
}Fhan_Data;



void ADRC_Init(Fhan_Data *fhan_Input1,Fhan_Data *fhan_Input2);
void Fhan_ADRC(Fhan_Data *fhan_Input,float expect_ADRC);
void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback);
void ADRC_Integrate_Reset(Fhan_Data *fhan_Input) ;
extern Fhan_Data ADRC_Pitch_Controller,ADRC_Roll_Controller;

void Advanced_ESO(Fhan_Data *fhan_Input);
#endif

