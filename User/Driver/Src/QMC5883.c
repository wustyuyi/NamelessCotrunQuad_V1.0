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
*               修改日期:2020/03/24                   
*               版本：躺赢者PRO——CarryPilot_V3.0.1
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
#include "QMC5883.h"



#define GPS_QMC5883_ENABLE 1//使用GPS模组上的qmc5883使能




uint8_t QMC5883L_Read_Reg(uint8_t reg)
{
	return Single_ReadI2C(QMC5883L_RD_ADDRESS,reg); 
}

void QMC5883L_Write_Reg(uint8_t reg, uint8_t data)
{
	Single_WriteI2C(QMC5883L_WR_ADDRESS,reg,data);
}


void QMC5883L_Read_Data(int16_t *MagX,int16_t *MagY,int16_t *MagZ) // (-32768 / +32768)
{
	*MagX=((int16_t)QMC5883L_Read_Reg(QMC5883L_DATA_READ_X_LSB) | (((int16_t)QMC5883L_Read_Reg(QMC5883L_DATA_READ_X_MSB))<<8));
	*MagY=((int16_t)QMC5883L_Read_Reg(QMC5883L_DATA_READ_Y_LSB) | (((int16_t)QMC5883L_Read_Reg(QMC5883L_DATA_READ_Y_MSB))<<8));
	*MagZ=((int16_t)QMC5883L_Read_Reg(QMC5883L_DATA_READ_Z_LSB) | (((int16_t)QMC5883L_Read_Reg(QMC5883L_DATA_READ_Z_MSB))<<8));
}


int16_t QMC5883L_Read_Temperature()
{
	return (((int16_t)QMC5883L_Read_Reg(QMC5883L_TEMP_READ_LSB)) | (((int16_t)QMC5883L_Read_Reg(QMC5883L_TEMP_READ_MSB))<<8))/100;
}


void QMC5883L_Initialize(_qmc5883l_MODE MODE,_qmc5883l_ODR ODR,_qmc5883l_RNG RNG,_qmc5883l_OSR OSR)
{
	QMC5883L_Write_Reg(QMC5883L_CONFIG_3,0x01);
	QMC5883L_Write_Reg(QMC5883L_CONFIG_1,MODE | ODR | RNG | OSR);
}

void QMC5883L_Reset()
{
	QMC5883L_Write_Reg(QMC5883L_CONFIG_2,0x81);
}

void QMC5883L_InterruptConfig(_qmc5883l_INT INT)
{
	if(INT==INTERRUPT_ENABLE){QMC5883L_Write_Reg(QMC5883L_CONFIG_2,0x00);}
	else {QMC5883L_Write_Reg(QMC5883L_CONFIG_2,0x01);}
}


_qmc5883l_status QMC5883L_DataIsReady()
{
	uint8_t Buffer=QMC5883L_Read_Reg(QMC5883L_STATUS);
	if((Buffer&0x00)==0x00)	  {return NO_NEW_DATA;}
	else if((Buffer&0x01)==0X01){return NEW_DATA_IS_READY;}
	return NORMAL;
}

_qmc5883l_status QMC5883L_DataIsSkipped()
{
	uint8_t Buffer=QMC5883L_Read_Reg(QMC5883L_STATUS);
	if((Buffer&0x00)==0X00)	  {return NORMAL;}
	else if((Buffer&0x04)==0X04){return DATA_SKIPPED_FOR_READING;}
		return NORMAL;
}

_qmc5883l_status QMC5883L_DataIsOverflow()
{
	uint8_t Buffer=QMC5883L_Read_Reg(QMC5883L_STATUS);
	if((Buffer&0x00)==0X00)	  {return NORMAL;}
	else if((Buffer&0x02)==0X02){return DATA_OVERFLOW;}
		return NORMAL;
}


void QMC5883L_ResetCalibration() 
{ 
	Xmin=Xmax=Ymin=Ymax=0;
} 

 
float QMC5883L_Heading(int16_t Xraw,int16_t Yraw,int16_t Zraw) 
{ 
   float X=Xraw,Y=Yraw,Z=Zraw; 
   float Heading;
   if(X<Xmin) {Xmin = X;} 
   else if(X>Xmax) {Xmax = X;} 
   if(Y<Ymin) {Ymin = Y;} 
   else if(Y>Ymax) {Ymax = Y;} 
   
   if( Xmin==Xmax || Ymin==Ymax ) {return 0.0;} 
 	 X -= (Xmax+Xmin)/2; 
   Y -= (Ymax+Ymin)/2; 
   X = X/(Xmax-Xmin); 
   Y = Y/(Ymax-Ymin); 
   Heading = atan2(Y,X); 
		//EAST
	 Heading += QMC5883L_DECLINATION_ANGLE;
	//WEST
	//Heading -= QMC5883L_DECLINATION_ANGLE;	
if(Heading <0)
{Heading += 2*M_PI;}
else if(Heading > 2*M_PI)
{Heading -= 2*M_PI;}
return Heading; 
} 


void QMC5883L_Scale(int16_t *X,int16_t *Y,int16_t *Z)
{
	*X*=QMC5883L_SCALE_FACTOR;
	*Y*=QMC5883L_SCALE_FACTOR;
	*Z*=QMC5883L_SCALE_FACTOR;
}


uint8_t qmc_status[3]={0};
void QMC5883L_Init(void)
{

	QMC5883L_Reset();
	delay_ms(5);
  QMC5883L_Initialize(MODE_CONTROL_CONTINUOUS,OUTPUT_DATA_RATE_200HZ,FULL_SCALE_2G,OVER_SAMPLE_RATIO_512);
	
	extern_mag_id[1]=QMC5883L_Read_Reg(QMC5883L_ID);
	
	qmc_status[0]=QMC5883L_Read_Reg(QMC5883L_CONFIG_1);
	qmc_status[1]=QMC5883L_Read_Reg(QMC5883L_CONFIG_2);
	qmc_status[2]=QMC5883L_Read_Reg(QMC5883L_CONFIG_3);
	
	if(extern_mag_id[1]==0xFF
		&&qmc_status[0]!=0xFF
		&&qmc_status[1]!=0xFF
		&&qmc_status[2]!=0xFF)   
	Extern_Mag_Work_Flag=1;	
	else extern_mag_id[1]=0x00;
}


void	QMC5883L_Read(void)
{
  float  x,y,z;
  uint8_t buf[6];
  float angle;
  float thx,thy;
	buf[0]=Single_ReadI2C(QMC5883L_RD_ADDRESS,QMC5883L_DATA_READ_X_LSB);//OUT_X_L_A
	buf[1]=Single_ReadI2C(QMC5883L_RD_ADDRESS,QMC5883L_DATA_READ_X_MSB);//OUT_X_H_A
	buf[2]=Single_ReadI2C(QMC5883L_RD_ADDRESS,QMC5883L_DATA_READ_Y_LSB);//OUT_Y_L_A
	buf[3]=Single_ReadI2C(QMC5883L_RD_ADDRESS,QMC5883L_DATA_READ_Y_MSB);//OUT_Y_H_A
	buf[4]=Single_ReadI2C(QMC5883L_RD_ADDRESS,QMC5883L_DATA_READ_Z_LSB);//OUT_Z_L_A
	buf[5]=Single_ReadI2C(QMC5883L_RD_ADDRESS,QMC5883L_DATA_READ_Z_MSB);//OUT_Z_H_A
	x= (int16_t)((buf[1]<<8)|buf[0])/QMC5883L_CONVERT_GAUSS_2G;
	y= (int16_t)((buf[3]<<8)|buf[2])/QMC5883L_CONVERT_GAUSS_2G;
	z= (int16_t)((buf[5]<<8)|buf[4])/QMC5883L_CONVERT_GAUSS_2G;


#if GPS_QMC5883_ENABLE
	float tmp_x,tmp_y,tmp_z;
  tmp_x=x;tmp_y=y;tmp_z=z;
	x=tmp_x;
	y=-tmp_y;
	z=-tmp_z;
#endif	
//	x=(float)(GildeAverageValueFilter_MAG(x,Data_X_MAG));
//	y=(float)(GildeAverageValueFilter_MAG(y,Data_Y_MAG));
//	z=(float)(GildeAverageValueFilter_MAG(z,Data_Z_MAG));
    
	DataMag.x=x;
	DataMag.y=y;
	DataMag.z=z;
	
	Compass.x=DataMag.x;
	Compass.y=DataMag.y;
	Compass.z=DataMag.z;
		
		
	x=Mag_Data[0]=DataMag.x-Mag_Offset[0];
	y=Mag_Data[1]=DataMag.y-Mag_Offset[1];
	z=Mag_Data[2]=DataMag.z-Mag_Offset[2];
    
	MagN.x=thx = x * Cos_Roll+ z * Sin_Roll;
	MagN.y=thy = x * Sin_Pitch*Sin_Roll
						 + y * Cos_Pitch
						 - z * Cos_Roll*Sin_Pitch;
	angle=atan2(thx, thy) * 57.296;
	HMC5883L_Yaw=angle;
}



void QMC5883L_StateMachine(void)
{
	static unsigned int QMC5883L_Sample_Cnt;
  QMC5883L_Sample_Cnt++;
  if(QMC5883L_Sample_Cnt==4)//10
  {
    QMC5883L_Read();
    QMC5883L_Sample_Cnt=0;
  }
}

