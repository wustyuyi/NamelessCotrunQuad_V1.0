/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ��Դ����������ѣ������ߵ���ʷ�Ѿ�֤�����ڹ�����������£���������Ŀ�Դ������������˰����ߣ��Է��ز�����
								Ŀ���Ƶķ�ʽ�в�ͨ���õĿ�Դ��Ŀ��Ҫ��רְ��Ա�����ۺ�����ְ��ֽ�ѧ��ͳ���û�����������ʵ������ɶԲ�
								Ʒ��һ�δ���������������������ۺϿ��ǣ������ɿؿ�Դ�����У������������˾���漤��ܴ��룬�汾������ʵ��
								���ܣ����ڹ�˾��Ʒ���������������Ӱ��ͻ�ѧϰ���������ȫ�����Ÿ��ͻ�ѧϰ���ͻ���ֲ�Ͷ��ο��������뱣����
								���Ȩ��
-----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ���������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------
*                                                 Ϊʲôѡ���������£�
*                                         �ж����ļ۸�������׵Ŀ�Դ�ɿأ�
*                                         ����ҵ������֮������µ��ۺ����
*                                         ׷�����û����飬��Ч����ѧϰ֮·��
*                                         ���²��ٹµ��������������տ�Դ�߶ȣ�
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
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�������������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _CONTROL_CONFIG_H
#define _CONTROL_CONFIG_H

#include "control_althold.h"
#include "control_poshold.h"
#include "control_land.h"


#define Self_Balance_Mode 1//���ȡ�����̬�����Ų���
#define High_Hold_Mode    2//����ģʽ
#define Pos_Free_Mode 1//ˮƽλ��no fixed
#define Pos_Hold_Mode 2//����ģʽ
//GPS�����´�˿���ģʽ��ֱ����̬��
#define Speed_Mode 0  //GPS����ģʽ�£���˿���
#define Angle_Mode 1  //GPS����ģʽ�£����ֱ�Ӹ���̬������

/*****************ң�����г�����**********************/
#define  Climb_Up_Speed_Max    400//������������ٶȣ�cm/s 150 250  400
#define  Climb_Down_Speed_Max  200//��������½��ٶȣ�cm/s  80 120  180

/****************************************************************
���������رȽ�Сʱ���������½��������ٶȱȽϴ�
�ᵼ�����ӳ����������̬�������ò�����������
ʹ�ÿ��������½�ʱ����̬��ƽ�ȣ����˹��̳���ʱ�䳤��
�ᵼ����̬���ڵò���������ֱ�����ը���������رȽ�
Сʱ���ɽ��������ٶ���Сһ�㣬���������������ȼ�����
*******************************************************************/
#define  Climb_Up_Acceleration_Max     400//��������������ٶȣ�cm/s^2   500
#define  Climb_Down_Acceleration_Max   250//��������½����ٶȣ�cm/s^2   300


#define  Thr_Start  1100//��ת��������������ǲ�����2d��̫��ᵼ�¹�����
#define  Thr_Fly_Start  1150//��������� 1150
#define  Thr_Hover_Default 1500//Ĭ����ͣ���ţ�ֱ�Ӷ������ʱ��1500
#define  Thr_Min 1000
#define  Thr_Idle 1100//���ŵ��٣�ȡ�ӽ���ת����ֵ����1150
#define  Nav_Speed_Max  500//�������ˮƽ�ٶ�Ϊ5m/s
#define  Flight_Safe_Vbat  11200   //11200mv=11.2V

/*****************һ����ɸ߶����ã���λΪcm������100��ʾԭ����ɵ���Գ�ʼλ��1�׸ߵ�λ��**********************/
#define  Auto_Launch_Target 100//һ����ɵ�Ŀ��߶ȣ������ɸ߶ȣ�ʹ�ó�����ʱ�����𳬹������������̣��Ƽ�200����

#define  Flight_Max_Height     5000//�����и߶�5000M
#define  Flight_Max_Radius     5000//�����а뾶5000M

#endif
