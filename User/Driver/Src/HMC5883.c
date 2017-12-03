#include "Headfile.h"
#include "HMC5883.h"
/*----------------------------------------------------------------------------------------------------------------------/
        *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
        *               无名科创团队将飞控程序源码提供给购买者，
        *               购买者要为无名科创团队提供保护，
        *               未经作者许可，不得将源代码提供给他人
        *               不得将源代码放到网上供他人免费下载，
        *               更不能以此销售牟利，如发现上述行为，
        *               无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
        *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
        *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
-----------------------------------------------------------------------------------------------------------------------/
	*		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
	*		CSDN博客: http://blog.csdn.net/u011992534
	*               优酷ID：NamelessCotrun无名小哥
	*               无名科创开源飞控QQ群：540707961
        *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
        *               百度贴吧:无名科创开源飞控
        *               修改日期:2017/10/30
        *               版本：V1.1
        *               版权所有，盗版必究。
        *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
        *               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
//-----HMC5983ID-----//
#define HMC5883L_DEVICE_ID  0x48
uint8 statusflag=0,status1,status2,status3;
void	HMC5883L_Initial(void)
{
        statusflag = Single_ReadI2C(HMC5883L_Addr,0x0A);
	if( statusflag != HMC5883L_DEVICE_ID) ;
        Single_WriteI2C(HMC5883L_Addr,0x00,0x78);//配置寄存器A：采样平均数1 输出速率75Hz 正常测量
	Single_WriteI2C(HMC5883L_Addr,0x01,0x00);//配置寄存器B：增益控制
	Single_WriteI2C(HMC5883L_Addr,0x02,0x00);//模式寄存器：连续测量模式
}

float HMC5883L_Yaw=0;
#define N 10
float Data_X_MAG[N];
float Data_Y_MAG[N];
float Data_Z_MAG[N];
float GildeAverageValueFilter_MAG(float NewValue,float *Data)
{
	float max,min;
	float sum;
	unsigned char i;
	Data[0]=NewValue;
	max=Data[0];
	min=Data[0];
	sum=Data[0];
	for(i=N-1;i!=0;i--)
	{
	  if(Data[i]>max) max=Data[i];
	  else if(Data[i]<min) min=Data[i];
	  sum+=Data[i];
	  Data[i]=Data[i-1];
	}
	 i=N-2;
	 sum=sum-max-min;
	 sum=sum/i;
	 return(sum);
}


float MAGData[3]={0};
void	HMC5883L_Read(void)
{
	int   x,y,z;
        float thx,thy;
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

        x=(int)(GildeAverageValueFilter_MAG(x,Data_X_MAG));
        y=(int)(GildeAverageValueFilter_MAG(y,Data_Y_MAG));
        z=(int)(GildeAverageValueFilter_MAG(z,Data_Z_MAG));

        DataMag.x=x;
        DataMag.y=y;
        DataMag.z=z;

        x-=Mag_Offset[0];
        y-=Mag_Offset[1];
        z-=Mag_Offset[2];

        MAGData[0]=x;
        MAGData[1]=y;
        MAGData[2]=z;
        thx = x * Cos_Roll+ z * Sin_Roll;
	thy = x * Sin_Pitch*Sin_Roll
            + y * Cos_Pitch
            - z * Cos_Roll*Sin_Pitch;
        angle=atan2(thx, thy) * 57.296;
        HMC5883L_Yaw=angle;
        }
}

unsigned int HMC5883L_Sample_Cnt;
void HMC5883L_StateMachine(void)
{
    HMC5883L_Sample_Cnt++;
    if(HMC5883L_Sample_Cnt==1)
    {
      Single_WriteI2C(HMC5883L_Addr,0x00,0x78);//配置寄存器A：采样平均数1 输出速率75Hz 正常测量
    }
    else if(HMC5883L_Sample_Cnt>=2)
    {
      HMC5883L_Read();
      HMC5883L_Sample_Cnt=0;
    }
}

