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
#ifndef _IST8310_H_
#define _IST8310_H_


#define IST8310_SLAVE_ADDRESS     (0x0E<<1)
#define IST8310_REG_STB           0x0C	//Self-Test response
#define IST8310_REG_INFO          0x01	//More Info
#define IST8310_REG_WIA           0x00	//Who I am
#define IST8310_REG_DATAX         0x03	//Output Value x
#define IST8310_REG_DATAY         0x05	//Output Value y
#define IST8310_REG_DATAZ         0x07	//Output Value z
#define IST8310_REG_STAT1         0x02	//Status register
#define IST8310_REG_STAT2         0x09	//Status register
#define IST8310_REG_CNTRL1        0x0A	//Control setting register 1
#define IST8310_REG_CNTRL2        0x0B	//Control setting register 2
#define IST8310_REG_CNTRL3        0x0D	//Control setting register 3
#define IST8310_REG_OFFSET_START  0xDC	//Offset
#define IST8310_REG_SELECTION_REG 0x42   //Sensor Selection register
#define IST8310_REG_TEST_REG      0x40   //Chip Test register
#define IST8310_REG_TUNING_REG    0x47    //Bandgap Tuning register
/*---IST8310 cross-axis matrix Address-----------------danny-----*/
#define IST8310_REG_XX_CROSS_L    0x9C  //cross axis xx low byte
#define IST8310_REG_XX_CROSS_H    0x9D  //cross axis xx high byte
#define IST8310_REG_XY_CROSS_L    0x9E  //cross axis xy low byte
#define IST8310_REG_XY_CROSS_H    0x9F  //cross axis xy high byte
#define IST8310_REG_XZ_CROSS_L    0xA0  //cross axis xz low byte
#define IST8310_REG_XZ_CROSS_H    0xA1  //cross axis xz high byte                          =       ;
#define IST8310_REG_YX_CROSS_L    0xA2  //cross axis yx low byte
#define IST8310_REG_YX_CROSS_H    0xA3  //cross axis yx high byte
#define IST8310_REG_YY_CROSS_L    0xA4  //cross axis yy low byte
#define IST8310_REG_YY_CROSS_H    0xA5  //cross axis yy high byte
#define IST8310_REG_YZ_CROSS_L    0xA6  //cross axis yz low byte
#define IST8310_REG_YZ_CROSS_H    0xA7  //cross axis yz high byte                    =       ;
#define IST8310_REG_ZX_CROSS_L    0xA8  //cross axis zx low byte
#define IST8310_REG_ZX_CROSS_H    0xA9  //cross axis zx high byte
#define IST8310_REG_ZY_CROSS_L    0xAA  //cross axis zy low byte
#define IST8310_REG_ZY_CROSS_H    0xAB  //cross axis zy high byte
#define IST8310_REG_ZZ_CROSS_L    0xAC  //cross axis zz low byte
#define IST8310_REG_ZZ_CROSS_H    0xAD  //cross axis zz high byte
#define IST8310_AXES_NUM          3

typedef struct {
  uint8_t Buf[6];
  float Mag_Data[3];
  float Mag_Data_Correct[3];
  float thx;
  float thy;
  float x;
  float y;
  float z;
  float Angle_Mag;
}IST8310;

extern IST8310 Mag_IST8310;
extern float Earth_Magnetic_Field_Intensity;
void IST8310_Init(void);
void Get_Mag_IST8310(void);
void Compass_Tradeoff(void);

#endif



