/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               修改日期:2018/8/30
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
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



