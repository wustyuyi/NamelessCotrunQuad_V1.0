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
#ifndef __HMC5883_H_
#define __HMC5883_H_


//*****B�Ĵ���������������***********/
#define MAG_GAIN_SCALE0 1370//0x00   0.88Ga
#define MAG_GAIN_SCALE1 1090//0x20   1.30Ga
#define MAG_GAIN_SCALE2 820//0x40    1.90Ga
#define MAG_GAIN_SCALE3 660//0x60    2.50Ga
#define MAG_GAIN_SCALE4 440//0x80    4.00Ga
#define MAG_GAIN_SCALE5 390//0xA0    4.70Ga
#define MAG_GAIN_SCALE6 330//0xC0    5.66Ga
#define MAG_GAIN_SCALE7 230//0xE0    8.10Ga


extern float Mag_Data[3];

#define N2 5
extern float Data_X_MAG[N2];
extern float Data_Y_MAG[N2];
extern float Data_Z_MAG[N2];

float GildeAverageValueFilter_MAG(float NewValue,float *Data);
#define	HMC5883L_Addr   0x3C	//�ų�������������ַ
void HMC5883L_Initial(void);
void HMC5883L_Read(void);
void HMC5883L_StateMachine(void);

extern float MAGData[3];
extern uint8_t Extern_Mag_Work_Flag;
extern uint8 extern_mag_id[3];

#endif


