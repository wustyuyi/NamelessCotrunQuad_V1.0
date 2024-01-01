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
#ifndef _CALIBRATIONROUTINES_H
#define _CALIBRATIONROUTINES_H

#include "stm32f10x.h"

typedef struct
{
  float x_sumplain ;
  float x_sumsq;
  float x_sumcube ;
  
  float y_sumplain ;
  float y_sumsq ;
  float y_sumcube ;
  
  float z_sumplain ;
  float z_sumsq ;
  float z_sumcube ;
  
  float xy_sum ;
  float xz_sum ;
  float yz_sum ;
  
  float x2y_sum ;
  float x2z_sum ;
  float y2x_sum ;
  float y2z_sum ;
  float z2x_sum ;
  float z2y_sum ;
  
  unsigned int size;
}Least_Squares_Intermediate_Variable;


int sphere_fit_least_squares(const float x[], const float y[], const float z[],
                             unsigned int size, unsigned int max_iterations,float delta,
                             float *sphere_x, float *sphere_y, float *sphere_z,
                             float *sphere_radius);

void LS_Init(Least_Squares_Intermediate_Variable * pLSQ);
unsigned int LS_Accumulate(Least_Squares_Intermediate_Variable * pLSQ, float x, float y, float z);
void LS_Calculate(Least_Squares_Intermediate_Variable * pLSQ, unsigned int max_iterations, float delta,
                  float *sphere_x, float *sphere_y, float *sphere_z,
                  float *sphere_radius);

extern Least_Squares_Intermediate_Variable Mag_LS;
#endif

