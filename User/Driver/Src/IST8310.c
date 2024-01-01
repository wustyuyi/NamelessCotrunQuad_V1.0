/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                开源并不等于免费，先驱者的历史已经证明，在国内这个环境下，毫无收益的开源，单靠坊间个人爱好者，自发地参与项
								目完善的方式行不通，好的开源项目需要请专职人员做好售后服务、手把手教学、统计用户反馈需求、在实践中完成对产
								品的一次次完善与迭代升级。经过综合考虑，无名飞控开源代码中，程序仅保留公司正版激活功能代码，版本激活无实际
								功能，属于公司产品常规出厂操作，不影响客户学习，其余代码全部开放给客户学习，客户移植和二次开发代码请保留代
								码版权。
-----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------
*                                                 为什么选择无名创新？
*                                         感动人心价格厚道，最靠谱的开源飞控；
*                                         国内业界良心之作，最精致的售后服务；
*                                         追求极致用户体验，高效进阶学习之路；
*                                         萌新不再孤单求索，合理把握开源尺度；
*                                         响应国家扶贫号召，促进教育体制公平；
*                                         新时代奋斗最出彩，建人类命运共同体。 
-----------------------------------------------------------------------------------------------------------------------
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：2号群465082224、1号群540707961（人员已满）
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               公司官网:www.nameless.tech
*               无名创新国内首款TI开源飞控设计初衷、知乎专栏:https://zhuanlan.zhihu.com/p/54471146
*               修改日期:2019/11/27                    
*               版本：慧飞者PRO——WisdomPilot_Pro_V1.0.0
*               版权所有，盗版必究。
*               Copyright(C) 2019-2025 武汉无名创新科技有限公司 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               重要提示：
*               正常淘宝咸鱼转手的飞控、赠送朋友、传给学弟的都可以进售后群学习交流，
*               不得直接在网上销售无名创新资料，无名创新代码有声明版权，他人不得将
*               资料代码传网上供他人下载，不得以谋利为目的销售资料代码，发现有此操
*               作者，公司会提前告知，请1天内及时处理，否则你的学校、单位、姓名、电
*               话、地址信息会被贴出在公司官网、官方微信公众平台、官方技术博客、知乎
*               专栏以及淘宝店铺首页予以公示公告，此种所作所为，会成为个人污点，影响
*               升学、找工作、社会声誉、很快就很在无人机界出名，后果很严重。
*               因此行为给公司造成重大损失者，会以法律途径解决，感谢您的合作，谢谢！！！
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "IST8310.h"
#include "HMC5883.h"


void IST8310_Init(void)
{
  Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x41,0x24);//开启16x内部平均
  Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x42,0xC0);//Set/Reset内部平均
	extern_mag_id[2]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,IST8310_REG_WIA);
}



IST8310 Mag_IST8310;
//磁力机航向角计算与补偿：https://blog.csdn.net/u013636775/article/details/72675148
void Get_Mag_IST8310(void)
{
  static uint16_t IST8310_Sample_Cnt=0;
  float MagTemp[3]={0};
  IST8310_Sample_Cnt++;
  if(IST8310_Sample_Cnt==1)
  {
    Single_WriteI2C(IST8310_SLAVE_ADDRESS,IST8310_REG_CNTRL1,0x01);//Single Measurement Mode
  }
  else if(IST8310_Sample_Cnt==4)//至少间隔6ms,此处为8ms
  {
    Mag_IST8310.Buf[0]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x03);//OUT_X_L_A
    Mag_IST8310.Buf[1]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x04);//OUT_X_H_A
    Mag_IST8310.Buf[2]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x05);//OUT_Y_L_A
    Mag_IST8310.Buf[3]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x06);//OUT_Y_H_A
    Mag_IST8310.Buf[4]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x07);//OUT_Z_L_A
    Mag_IST8310.Buf[5]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x08);//OUT_Z_H_A
	
    /*****************合成三轴磁力计数据******************/
    Mag_IST8310.Mag_Data[0]=(int16_t)((Mag_IST8310.Buf[1]<<8)|Mag_IST8310.Buf[0]);
    Mag_IST8310.Mag_Data[1]=(int16_t)((Mag_IST8310.Buf[3]<<8)|Mag_IST8310.Buf[2]);
    Mag_IST8310.Mag_Data[2]=(int16_t)((Mag_IST8310.Buf[5]<<8)|Mag_IST8310.Buf[4]);
		
		Mag_IST8310.Mag_Data[0]/=330.0f;
		Mag_IST8310.Mag_Data[1]/=330.0f;
		Mag_IST8310.Mag_Data[2]/=330.0f;
		
    IST8310_Sample_Cnt=0;
  }
	
  Mag_IST8310.x = Mag_IST8310.Mag_Data[0];
  Mag_IST8310.y = -Mag_IST8310.Mag_Data[1];
  Mag_IST8310.z = Mag_IST8310.Mag_Data[2];
		
  DataMag.x=Compass.x=Mag_IST8310.x;
  DataMag.y=Compass.y=Mag_IST8310.y;
  DataMag.z=Compass.z=Mag_IST8310.z;
	
  MagTemp[0]=GildeAverageValueFilter_MAG(Mag_IST8310.x-Mag_Offset[0],Data_X_MAG);//滑动窗口滤波
  MagTemp[1]=GildeAverageValueFilter_MAG(Mag_IST8310.y-Mag_Offset[1],Data_Y_MAG);
  MagTemp[2]=GildeAverageValueFilter_MAG(Mag_IST8310.z-Mag_Offset[2],Data_Z_MAG);
   
  Mag_Data[0]=Mag_IST8310.Mag_Data_Correct[0]=MagTemp[0];
  Mag_Data[1]=Mag_IST8310.Mag_Data_Correct[1]=MagTemp[1];
  Mag_Data[2]=Mag_IST8310.Mag_Data_Correct[2]=MagTemp[2];
  
  /************磁力计倾角补偿*****************/
  MagN.x=Mag_IST8310.thx = MagTemp[0] * Cos_Roll+ MagTemp[2] * Sin_Roll;
  MagN.y=Mag_IST8310.thy = MagTemp[0] * Sin_Pitch*Sin_Roll
                          +MagTemp[1] * Cos_Pitch
                          -MagTemp[2] * Cos_Roll*Sin_Pitch;
  /***********反正切得到磁力计观测角度*********/
  Mag_IST8310.Angle_Mag=atan2(Mag_IST8310.thx,Mag_IST8310.thy)*57.296;
}


float Earth_Magnetic_Field_Intensity=0;
void Compass_Tradeoff(void)
{
	if(extern_mag_id[2]==0x10)
	{
		Get_Mag_IST8310();
		Earth_Magnetic_Field_Intensity=sqrt(Mag_Data[0]*Mag_Data[0]
																				+Mag_Data[1]*Mag_Data[1]
																					+Mag_Data[2]*Mag_Data[2]);	
	}
	else if(extern_mag_id[0]==0x48)
	{
    HMC5883L_StateMachine();
    Earth_Magnetic_Field_Intensity=sqrt(Mag_Data[0]*Mag_Data[0]
                                        +Mag_Data[1]*Mag_Data[1]
                                          +Mag_Data[2]*Mag_Data[2]);	
	}
  else if(extern_mag_id[1]==0xff)
  { 
    QMC5883L_StateMachine();
    Earth_Magnetic_Field_Intensity=sqrt(Mag_Data[0]*Mag_Data[0]
                                        +Mag_Data[1]*Mag_Data[1]
                                          +Mag_Data[2]*Mag_Data[2]);		
		
  }
  WP_Sensor.mag_raw.x=Compass.x;
	WP_Sensor.mag_raw.y=Compass.y;
	WP_Sensor.mag_raw.z=Compass.z;
}


