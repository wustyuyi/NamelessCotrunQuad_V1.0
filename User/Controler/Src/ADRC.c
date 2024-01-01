/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ��Դ����������ѣ������ߵ���ʷ�Ѿ�֤�����ڹ�����������£���������Ŀ�Դ������������˰����ߣ��Է��ز�����
								Ŀ���Ƶķ�ʽ�в�ͨ���õĿ�Դ��Ŀ��Ҫ��רְ��Ա�����ۺ�����ְ��ֽ�ѧ��ͳ���û�����������ʵ������ɶԲ�
								Ʒ��һ�δ���������������������ۺϿ��ǣ������ɿؿ�Դ�����У������������˾���漤��ܴ��룬�汾������ʵ��
								���ܣ����ڹ�˾��Ʒ���������������Ӱ��ͻ�ѧϰ���������ȫ�����Ÿ��ͻ�ѧϰ���ͻ���ֲ�Ͷ��ο��������뱣����
								���Ȩ��
-----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------
*                                                 Ϊʲôѡ���������£�
*                                         �ж����ļ۸�������׵Ŀ�Դ�ɿأ�
*                                         ����ҵ������֮������µ��ۺ����
*                                         ׷�����û����飬��Ч����ѧϰ֮·��
*                                         ���²��ٹµ�������������տ�Դ�߶ȣ�
*                                         ��Ӧ���ҷ�ƶ���٣��ٽ��������ƹ�ƽ��
*                                         ��ʱ���ܶ�����ʣ����������˹�ͬ�塣 
-----------------------------------------------------------------------------------------------------------------------
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��2��Ⱥ465082224��1��Ⱥ540707961����Ա������
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �������¹����׿�TI��Դ�ɿ���Ƴ��ԡ�֪��ר��:https://zhuanlan.zhihu.com/p/54471146
*               �޸�����:2019/11/27                    
*               �汾���۷���PRO����WisdomPilot_Pro_V1.0.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2019-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "ADRC.h"

Fhan_Data ADRC_Pitch_Controller;
Fhan_Data ADRC_Roll_Controller;
const float ADRC_Unit[4][16]=
{
  /*TD����΢����   �Ľ�����TD,h0=N*h      ����״̬�۲���ESO           �Ŷ�����     ���������*/
  /*  r     h      N                  beta_01   beta_02    beta_03     b0     beta_0  beta_1     beta_2     N1     C    alpha1  alpha2  zeta       b*/
  {1000000 ,0.005 , 5,               300,      10000,      100000,      0.5,    0.85,   1.5,      0.0003,       2,    5,    0.9,   1.2,    0.03,    0.1},
  {1000000 ,0.005 , 5,               300,      10000,      100000,      0.5,    0.85,   1.5,      0.0003,       2,    5,    0.9,   1.2,    0.03,    0.1},
  {300000  ,0.005 , 3,               300,      4000,      10000,     100,   0.2,    1.2,      0.0010,       5,      5,    0.8,   1.5,    0.03,    0.05},
};


float Constrain_Float(float amt, float low, float high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

Butter_Parameter ADRC_Div_LPF_Parameter={
  //200---20hz
  1,    -1.14298050254,   0.4128015980962,
  0.06745527388907,   0.1349105477781,  0.06745527388907
};
float ADRC_LPF(float curr_inputer,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  /* ���ٶȼ�Butterworth�˲� */
  /* ��ȡ����x(n) */
  Buffer->Input_Butter[2]=curr_inputer;
  /* Butterworth�˲� */
  Buffer->Output_Butter[2]=
    Parameter->b[0] * Buffer->Input_Butter[2]
      +Parameter->b[1] * Buffer->Input_Butter[1]
	+Parameter->b[2] * Buffer->Input_Butter[0]
          -Parameter->a[1] * Buffer->Output_Butter[1]
            -Parameter->a[2] * Buffer->Output_Butter[0];
  /* x(n) ���б��� */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n) ���б��� */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
  return (Buffer->Output_Butter[2]);
}





int16_t Sign_ADRC(float Input)
{
  int16_t output=0;
  if(Input>1E-6) output=1;
  else if(Input<-1E-6) output=-1;
  else output=0;
  return output;
}

int16_t Fsg_ADRC(float x,float d)
{
  int16_t output=0;
  output=(Sign_ADRC(x+d)-Sign_ADRC(x-d))/2;
  return output;
}


void ADRC_Init(Fhan_Data *fhan_Input1,Fhan_Data *fhan_Input2)
{
  fhan_Input1->r=ADRC_Unit[0][0];
  fhan_Input1->h=ADRC_Unit[0][1];
  fhan_Input1->N0=(uint16)(ADRC_Unit[0][2]);
  fhan_Input1->beta_01=ADRC_Unit[0][3];
  fhan_Input1->beta_02=ADRC_Unit[0][4];
  fhan_Input1->beta_03=ADRC_Unit[0][5];
  fhan_Input1->b0=ADRC_Unit[0][6];
  fhan_Input1->beta_0=ADRC_Unit[0][7];
  fhan_Input1->beta_1=ADRC_Unit[0][8];
  fhan_Input1->beta_2=ADRC_Unit[0][9];
  fhan_Input1->N1=(uint16)(ADRC_Unit[0][10]);
  fhan_Input1->c=ADRC_Unit[0][11];
  
  fhan_Input1->alpha1=ADRC_Unit[0][12];
  fhan_Input1->alpha2=ADRC_Unit[0][13];
  fhan_Input1->zeta=ADRC_Unit[0][14];
  fhan_Input1->b=ADRC_Unit[0][15];
  
  fhan_Input2->r=ADRC_Unit[1][0];
  fhan_Input2->h=ADRC_Unit[1][1];
  fhan_Input2->N0=(uint16)(ADRC_Unit[1][2]);
  fhan_Input2->beta_01=ADRC_Unit[1][3];
  fhan_Input2->beta_02=ADRC_Unit[1][4];
  fhan_Input2->beta_03=ADRC_Unit[1][5];
  fhan_Input2->b0=ADRC_Unit[1][6];
  fhan_Input2->beta_0=ADRC_Unit[1][7];
  fhan_Input2->beta_1=ADRC_Unit[1][8];
  fhan_Input2->beta_2=ADRC_Unit[1][9];
  fhan_Input2->N1=(uint16)(ADRC_Unit[1][10]);
  fhan_Input2->c=ADRC_Unit[1][11];
  
  fhan_Input2->alpha1=ADRC_Unit[1][12];
  fhan_Input2->alpha2=ADRC_Unit[1][13];
  fhan_Input2->zeta=ADRC_Unit[1][14];
  fhan_Input2->b=ADRC_Unit[1][15];
}



//ADRC���ٸ���΢����TD���Ľ����㷨fhan
void Fhan_ADRC(Fhan_Data *fhan_Input,float expect_ADRC)//����ADRC���ȹ���
{
  float d=0,a0=0,y=0,a1=0,a2=0,a=0;
  float x1_delta=0;//ADRC״̬���������
  x1_delta=fhan_Input->x1-expect_ADRC;//��x1-v(k)���x1�õ���ɢ���¹�ʽ
  fhan_Input->h0=fhan_Input->N0*fhan_Input->h;//��h0���h��������ٸ���΢�����ٶȳ�������
  d=fhan_Input->r*fhan_Input->h0*fhan_Input->h0;//d=rh^2;
  a0=fhan_Input->h0*fhan_Input->x2;//a0=h*x2
  y=x1_delta+a0;//y=x1+a0
  a1=sqrt(d*(d+8*ABS(y)));//a1=sqrt(d*(d+8*ABS(y))])
  a2=a0+Sign_ADRC(y)*(a1-d)/2;//a2=a0+sign(y)*(a1-d)/2;
  a=(a0+y)*Fsg_ADRC(y,d)+a2*(1-Fsg_ADRC(y,d));
  fhan_Input->fh=-fhan_Input->r*(a/d)*Fsg_ADRC(a,d)
    -fhan_Input->r*Sign_ADRC(a)*(1-Fsg_ADRC(a,d));//�õ�����΢�ּ��ٶȸ�����
  fhan_Input->x1+=fhan_Input->h*fhan_Input->x2;//�������ٸ���״̬��x1
  fhan_Input->x2+=fhan_Input->h*fhan_Input->fh;//�������ٸ���״̬��΢��x2
}


//ԭ�㸽���������Զε������ݴκ���
float Fal_ADRC(float e,float alpha,float zeta)
{
  int16 s=0;
  float fal_output=0;
  s=(Sign_ADRC(e+zeta)-Sign_ADRC(e-zeta))/2;
  fal_output=e*s/(powf(zeta,1-alpha))+powf(ABS(e),alpha)*Sign_ADRC(e)*(1-s);
  return fal_output;
}




/************����״̬�۲���********************/
//״̬�۲�������beta01=1/h  beta02=1/(3*h^2)  beta03=2/(8^2*h^3) ...
void ESO_ADRC(Fhan_Data *fhan_Input)
{
  fhan_Input->e=fhan_Input->z1-fhan_Input->y;//״̬���
  
  fhan_Input->fe=Fal_ADRC(fhan_Input->e,0.5,fhan_Input->N1*fhan_Input->h);//�����Ժ�������ȡ����״̬�뵱ǰ״̬���
  fhan_Input->fe1=Fal_ADRC(fhan_Input->e,0.25,fhan_Input->N1*fhan_Input->h);
  
  /*************��չ״̬������**********/
  fhan_Input->z1+=fhan_Input->h*(fhan_Input->z2-fhan_Input->beta_01*fhan_Input->e);
  fhan_Input->z2+=fhan_Input->h*(fhan_Input->z3
                                 -fhan_Input->beta_02*fhan_Input->fe
                                   +fhan_Input->b0*fhan_Input->u);
  //ESO����״̬���ٶ��źţ������Ŷ���������ͳMEMS������Ư�ƽϴ󣬹��ƻ����Ư��
  fhan_Input->z3+=fhan_Input->h*(-fhan_Input->beta_03*fhan_Input->fe1);
}


/************���������****************/
/*
void Nolinear_Conbination_ADRC(Fhan_Data *fhan_Input)
{
float d=0,a0=0,y=0,a1=0,a2=0,a=0;
float Sy=0,Sa=0;//ADRC״̬���������

fhan_Input->h1=fhan_Input->N1*fhan_Input->h;

d=fhan_Input->r*fhan_Input->h1*fhan_Input->h1;
a0=fhan_Input->h1*fhan_Input->c*fhan_Input->e2;
y=fhan_Input->e1+a0;
a1=sqrt(d*(d+8*ABS(y)));
a2=a0+Sign_ADRC(y)*(a1-d)/2;

Sy=Fsg_ADRC(y,d);
a=(a0+y-a2)*Sy+a2;
Sa=Fsg_ADRC(a,d);
fhan_Input->u0=-fhan_Input->r*((a/d)-Sign_ADRC(a))*Sa-fhan_Input->r*Sign_ADRC(a);

//a=(a0+y)*Fsg_ADRC(y,d)+a2*(1-Fsg_ADRC(y,d));

//fhan_Input->fh=-fhan_Input->r*(a/d)*Fsg_ADRC(a,d)
//                -fhan_Input->r*Sign_ADRC(a)*(1-Fsg_ADRC(a,d));//�õ�����΢�ּ��ٶȸ�����
}
*/
void Nolinear_Conbination_ADRC(Fhan_Data *fhan_Input)
{
  float temp_e2=0;
  //temp_e2=Constrain_Float(fhan_Input->e2,-3000,3000);
  temp_e2=Constrain_Float(fhan_Input->e2_lpf,-3000,3000);
  fhan_Input->u0=fhan_Input->beta_1*Fal_ADRC(fhan_Input->e1,fhan_Input->alpha1,fhan_Input->zeta)
    +fhan_Input->beta_2*Fal_ADRC(temp_e2,fhan_Input->alpha2,fhan_Input->zeta);
  
}


void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback_ADRC)
{
  fhan_Input->Last_TD_Input=fhan_Input->TD_Input;
  fhan_Input->TD_Input=expect_ADRC;
  fhan_Input->TD_Input_Div=(fhan_Input->TD_Input-fhan_Input->Last_TD_Input)/fhan_Input->h;
  
  fhan_Input->Last_ESO_Input=fhan_Input->ESO_Input;
  fhan_Input->ESO_Input=feedback_ADRC;
  fhan_Input->ESO_Input_Div=(fhan_Input->ESO_Input-fhan_Input->Last_ESO_Input)/fhan_Input->h;
  
  /*�Կ��ſ�������1��*/
  /********
      **
      **
      **
      **
      **
  ********/
  /*****
  ���Ź��ȹ��̣�����Ϊ����������
  ��TD����΢�����õ���
  ���������ź�x1����������΢���ź�x2
  ******/
  Fhan_ADRC(fhan_Input,expect_ADRC);
  
  /*�Կ��ſ�������2��*/
  /********
          *
          *
  *  * *  *
  *
  *
  ********/
  /************ϵͳ���ֵΪ��������״̬������ESO����״̬�۲���������*********/
  fhan_Input->y=feedback_ADRC;
  /*****
  ����״̬�۲������õ������źŵ�����״̬��
  1��״̬�ź�z1��
  2��״̬�ٶ��ź�z2��
  3��״̬���ٶ��ź�z3��
  ����z1��z2������Ϊ״̬������TD΢�ָ������õ���x1,x2�����
  ���������Ժ���ӳ�䣬����betaϵ����
  ��ϵõ�δ����״̬���ٶȹ����Ŷ�������ԭʼ������u
  *********/
  ESO_ADRC(fhan_Input);//�ͳɱ�MEMS�����Ư�ƣ���չ������z3�����Ư�ƣ�Ŀǰ��ʱδ�뵽�취�����δ�õ�z3
  /*�Կ��ſ�������3��*/
  /********
         **
      **
     **
      **
        **
  ********/
  /********״̬������***/
  fhan_Input->e0+=fhan_Input->e1*fhan_Input->h;//״̬������
  fhan_Input->e1=fhan_Input->x1-fhan_Input->z1;//״̬ƫ����
  fhan_Input->e2=fhan_Input->x2-fhan_Input->z2;//״̬΢����
  fhan_Input->e2_lpf=ADRC_LPF(fhan_Input->e2,
                              &fhan_Input->ADRC_LPF_Buffer,
                              &ADRC_Div_LPF_Parameter);//������˹��ͨ��õ���΢����,20hz
  /********�������*******/
  /*
  fhan_Input->u0=//fhan_Input->beta_0*fhan_Input->e0
  +fhan_Input->beta_1*fhan_Input->e1
  +fhan_Input->beta_2*fhan_Input->e2;
  */
  Nolinear_Conbination_ADRC(fhan_Input);
  /**********�Ŷ�����*******/
  fhan_Input->u=fhan_Input->u0//-fhan_Input->z3/fhan_Input->b;
    -fhan_Input->z3/fhan_Input->b0;
  //fhan_Input->u+=Constrain_Float(fhan_Input->beta_0*fhan_Input->e0,-150,150);
  //����MEMS������Ư�ƱȽ����أ���beta_03ȡֵ�Ƚϴ�ʱ����ʱ��z3Ư�ƱȽϴ�Ŀǰ�������Ŷ�����������
  fhan_Input->u=Constrain_Float(fhan_Input->u0,-450,450);//�������Ŷ�����
  //fhan_Input->u=Constrain_Float(fhan_Input->u,-450,450);//�����Ŷ�����
}

void ADRC_Integrate_Reset(Fhan_Data *fhan_Input)  {fhan_Input->e0=0.0f;}

