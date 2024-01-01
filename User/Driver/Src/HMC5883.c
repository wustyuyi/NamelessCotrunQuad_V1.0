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
#include "HMC5883.h"

//-----HMC5983ID-----//
#define HMC5883L_DEVICE_ID  0x48
uint8 extern_mag_id[3]={0};
uint8_t Extern_Mag_Work_Flag=0;


void	HMC5883L_Initial(void)
{
  extern_mag_id[0] = Single_ReadI2C(HMC5883L_Addr,0x0A);
  if( extern_mag_id[0] == HMC5883L_DEVICE_ID)    Extern_Mag_Work_Flag=1;
  Single_WriteI2C(HMC5883L_Addr,0x00,0x78);//配置寄存器A：采样平均数1 输出速率75Hz 正常测量
  Single_WriteI2C(HMC5883L_Addr,0x01,0xE0);//配置寄存器B：增益控制
  Single_WriteI2C(HMC5883L_Addr,0x02,0x00);//模式寄存器：连续测量模式
}

const int16_t Mag_Rotate_Table[8][3]=
{
  1, 1, 1,
  1,-1, 1,
  1, 1,-1,
  1,-1,-1,
  -1, 1, 1,
  -1,-1, 1,  
  -1, 1,-1,
  -1,-1,-1
};
#define Mag_Rotate_Type  0 
void Mag_Data_Rotate(Mag_Unit *data_input,uint8_t rotate_type)//磁力计倾角补偿前提是：三轴磁场与三轴加计同轴
{
  data_input->x*=Mag_Rotate_Table[rotate_type][0];
  data_input->y*=Mag_Rotate_Table[rotate_type][1];
  data_input->z*=Mag_Rotate_Table[rotate_type][2];
}


float Data_X_MAG[N2];
float Data_Y_MAG[N2];
float Data_Z_MAG[N2];
float GildeAverageValueFilter_MAG(float NewValue,float *Data)
{
  float max,min;
  float sum;
  unsigned char i;
  Data[0]=NewValue;
  max=Data[0];
  min=Data[0];
  sum=Data[0];
  for(i=N2-1;i!=0;i--)
  {
    if(Data[i]>max) max=Data[i];
    else if(Data[i]<min) min=Data[i];
    sum+=Data[i];
    Data[i]=Data[i-1];
  }
  i=N2-2;
  sum=sum-max-min;
  sum=sum/i;
  return(sum);
}

float thx,thy;
float MAGData[3]={0};
//磁力机航向角计算与补偿：https://blog.csdn.net/u013636775/article/details/72675148
void	HMC5883L_Read(void)
{
  float   x,y,z;
  float x1,y1,z1;
  unsigned char BUF[6];
  float angle;
  uint8_t status;
  status = Single_ReadI2C(HMC5883L_Addr,0x09);
  if ((status & 0x01) == 0x01)
  {
    BUF[0]=Single_ReadI2C(HMC5883L_Addr,0x03);//OUT_X_L_A
    BUF[1]=Single_ReadI2C(HMC5883L_Addr,0x04);//OUT_X_H_A
    BUF[2]=Single_ReadI2C(HMC5883L_Addr,0x05);//OUT_Z_L_A
    BUF[3]=Single_ReadI2C(HMC5883L_Addr,0x06);//OUT_Z_H_A
    BUF[4]=Single_ReadI2C(HMC5883L_Addr,0x07);//OUT_Y_L_A
    BUF[5]=Single_ReadI2C(HMC5883L_Addr,0x08);//OUT_Y_H_A
    x=(BUF[0] << 8) | BUF[1]; //Combine MSB and LSB of X Data output register
    z=(BUF[2] << 8) | BUF[3]; //Combine MSB and LSB of Z Data output register
    y=(BUF[4] << 8) | BUF[5];
    if(x>0x7fff)  x-=0xffff;
    if(y>0x7fff)  y-=0xffff;
    if(z>0x7fff)  z-=0xffff;
    
    x/=MAG_GAIN_SCALE7;
		y/=MAG_GAIN_SCALE7;
		z/=MAG_GAIN_SCALE7;
		
    Compass.x=x;
    Compass.y=y;
    Compass.z=z;
    
    x=(float)(GildeAverageValueFilter_MAG(x,Data_X_MAG));
    y=(float)(GildeAverageValueFilter_MAG(y,Data_Y_MAG));
    z=(float)(GildeAverageValueFilter_MAG(z,Data_Z_MAG));
    
    DataMag.x=x;
    DataMag.y=y;
    DataMag.z=z;
    Mag_Data_Rotate(&DataMag,Mag_Rotate_Type);
    Compass.x=DataMag.x;
		Compass.y=DataMag.y;
		Compass.z=DataMag.z;
		
		
    Mag_Data[0]=x1=DataMag.x-Mag_Offset[0];
    Mag_Data[1]=y1=DataMag.y-Mag_Offset[1];
    Mag_Data[2]=z1=DataMag.z-Mag_Offset[2];
    
    MagN.x=thx = x1 * Cos_Roll+ z1 * Sin_Roll;
    MagN.y=thy = x1 * Sin_Pitch*Sin_Roll
      + y1 * Cos_Pitch
        - z1 * Cos_Roll*Sin_Pitch;
    angle=atan2(thx, thy) * 57.296;
    HMC5883L_Yaw=angle;
  }
}

unsigned int HMC5883L_Sample_Cnt;
/***************************************************
函数名: void HMC5883L_StateMachine(void)
说明:	磁力计读取状态机
入口:	无
出口:	无
备注:	放在定时器调度即可
注释者：无名小哥
****************************************************/
void HMC5883L_StateMachine(void)
{
  HMC5883L_Sample_Cnt++;
  if(HMC5883L_Sample_Cnt==2)
  {
    Single_WriteI2C(HMC5883L_Addr,0x00,0x78);//配置寄存器A：采样平均数1 输出速率75Hz 正常测量
  }
  else if(HMC5883L_Sample_Cnt>=4)
  {
    HMC5883L_Read();
    HMC5883L_Sample_Cnt=0;
  }
}

