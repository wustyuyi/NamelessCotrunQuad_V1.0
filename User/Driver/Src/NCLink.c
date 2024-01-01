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
#include "Headfile.h"//用户自己库函数头文件
#include "NCLink.h"


static uint8_t NCLink_Head[2]={0xFF,0xFC};//数据帧头
static uint8_t NCLink_End[2] ={0xA1,0xA2};//数据帧尾
uint8_t NCLink_Send_Ask_Flag[10]={0};//飞控接收获取参数命令请求，给地面站发送标志位
uint8_t NCLink_Send_Check_Flag[20]={0};//数据解析成功，飞控给地面站发送标志位
uint8_t nclink_databuf[100];//待发送数据缓冲区
uint8_t rc_update_flag=0;//遥控器数据更新标志位
uint8_t unlock_flag=0x02,takeoff_flag=0;//解锁、起飞标志位
uint8_t move_flag=0,mode_order=0;//SDK移动标志位、移动顺序
uint16_t move_distance=0;//SDK移动距离
uint8_t cal_flag=0,cal_step=0,cal_cmd=0,shutdown_now_cal_flag=0;//传感器校准标志位
uint32_t Guide_Flight_Lng=0,Guide_Flight_Lat=0,Guide_Flight_Cnt=0;
uint8_t Guide_Flight_Flag=0;
ngs_sdk_control ngs_sdk;
/***************************************************************************************
@函数名：Serial_Data_Send(uint8_t *buf, uint32_t cnt)
@入口参数：buf:待发送数据
			     cnt:待发送字长
@出口参数：无
功能描述：串口发送函数
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Serial_Data_Send(uint8_t *buf, uint32_t cnt)  
{
	//USART1_Send(buf,cnt);//用户移植时，重写此串口发送函数
  USART1_Send_Dma(buf,cnt);
	USB_TxWrite(buf,cnt);
}

/***************************************************************************************
@函数名：Pilot_Status_Tick(void) 
@入口参数：无
@出口参数：无
功能描述：飞控接收状态显示
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Pilot_Status_Tick(void)  
{
	Bling_Set(&Light_1,500,50,0.2,0,GPIOC,GPIO_Pin_6,0);//用户移植时，重写此函数
}


union
{
unsigned char floatByte[4];
float floatValue;
}FloatUnion;
/***************************************************************************************
@函数名：void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript)
@入口参数：FloatValue:float值
			     Byte:数组
		       Subscript:指定从数组第几个元素开始写入
@出口参数：无
功能描述：将float数据转成4字节数据并存入指定地址
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript)
{
	FloatUnion.floatValue = (float)2;
	if(FloatUnion.floatByte[0] == 0)//小端模式
	{
		FloatUnion.floatValue = *FloatValue;
		Byte[Subscript]     = FloatUnion.floatByte[0];
		Byte[Subscript + 1] = FloatUnion.floatByte[1];
		Byte[Subscript + 2] = FloatUnion.floatByte[2];
		Byte[Subscript + 3] = FloatUnion.floatByte[3];
	}
	else//大端模式
	{
		FloatUnion.floatValue = *FloatValue;
		Byte[Subscript]     = FloatUnion.floatByte[3];
		Byte[Subscript + 1] = FloatUnion.floatByte[2];
		Byte[Subscript + 2] = FloatUnion.floatByte[1];
		Byte[Subscript + 3] = FloatUnion.floatByte[0];
	}
}


/***************************************************************************************
@函数名：void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue)
@入口参数：Byte:数组
			     Subscript:指定从数组第几个元素开始写入
		       FloatValue:float值
@出口参数：无
功能描述：从指定地址将4字节数据转成float数据
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue)
{
	FloatUnion.floatByte[0]=Byte[Subscript];
	FloatUnion.floatByte[1]=Byte[Subscript + 1];
	FloatUnion.floatByte[2]=Byte[Subscript + 2];
	FloatUnion.floatByte[3]=Byte[Subscript + 3];
	*FloatValue=FloatUnion.floatValue;
}


/***************************************************************************************
@函数名：void NCLink_Send_Status(float roll,float pitch,float yaw,
											           float roll_gyro,float pitch_gyro,float yaw_gyro,
												         float imu_temp,float vbat,uint8_t fly_model,uint8_t armed)
@入口参数：roll:横滚角
			     pitch:俯仰角
           yaw:偏航角
					 roll_gyro:偏航角速度
					 pitch_gyro:偏航角速度
					 yaw_gyro:偏航角速度
					 imu_temp:IMU温度
					 vbat:偏航角速度
					 fly_model:飞行模式
					 armed:解锁状态
@出口参数：无
功能描述：发送姿态、温度、飞控状态给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Status(float roll,float pitch,float yaw,
											  float roll_gyro,float pitch_gyro,float yaw_gyro,
												float imu_temp,float vbat,uint8_t fly_model,uint8_t armed)
{
  uint8_t _cnt=0;
  int16_t _temp;
	int32_t _temp1;
  uint8_t sum = 0;
  uint8_t i;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_STATUS;
  nclink_databuf[_cnt++]=0;
  
  _temp = (int)(roll*100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int)(pitch*100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int)(yaw*100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);  
  _temp1=100*roll_gyro;
	nclink_databuf[_cnt++]=BYTE3(_temp1);
  nclink_databuf[_cnt++]=BYTE2(_temp1);
  nclink_databuf[_cnt++]=BYTE1(_temp1);
  nclink_databuf[_cnt++]=BYTE0(_temp1);
	_temp1=100*pitch_gyro;
	nclink_databuf[_cnt++]=BYTE3(_temp1);
  nclink_databuf[_cnt++]=BYTE2(_temp1);
  nclink_databuf[_cnt++]=BYTE1(_temp1);
  nclink_databuf[_cnt++]=BYTE0(_temp1);
	
	_temp1=100*yaw_gyro;
	nclink_databuf[_cnt++]=BYTE3(_temp1);
  nclink_databuf[_cnt++]=BYTE2(_temp1);
  nclink_databuf[_cnt++]=BYTE1(_temp1);
  nclink_databuf[_cnt++]=BYTE0(_temp1);
	
  _temp = (int16_t)(100*imu_temp);//单位℃
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	

  _temp = (int16_t)(100*vbat);//单位V
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
	
	
  nclink_databuf[_cnt++]=fly_model;//飞行模式
  nclink_databuf[_cnt++]=armed;//上锁0、解锁1
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@函数名：void NCLink_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,
																 int16_t g_x,int16_t g_y,int16_t g_z,
															   int16_t m_x,int16_t m_y,int16_t m_z)
@入口参数：a_x:加速度计X轴原始数字量
			     a_y:加速度计Y轴原始数字量
           a_z:加速度计Z轴原始数字量
					 g_x:陀螺仪X轴原始数字量
					 g_y:陀螺仪Y轴原始数字量
					 g_z:陀螺仪Z轴原始数字量
					 m_x:磁力计X轴原始数字量
					 m_y:磁力计Y轴原始数字量
					 m_z:磁力计Z轴原始数字量
@出口参数：无
功能描述：发送传感器原始数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,
												int16_t g_x,int16_t g_y,int16_t g_z,
												int16_t m_x,int16_t m_y,int16_t m_z)
{
  uint8_t _cnt=0;
  int16_t _temp;
  uint8_t sum = 0;
  uint8_t i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SENSER;
  nclink_databuf[_cnt++]=0;
  
  _temp = a_x;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = a_y;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = a_z;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
	
  _temp = g_x;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = g_y;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = g_z;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  
  _temp = m_x;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = m_y;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = m_z;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  
  nclink_databuf[3] = _cnt-4;
  
  for(i=0;i<_cnt;i++)sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++] = sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@函数名：void NCLink_Send_RCData(uint16_t ch1,uint16_t ch2,uint16_t ch3,uint16_t ch4,
	                               uint16_t ch5,uint16_t ch6,uint16_t ch7,uint16_t ch8)
@入口参数：ch1:遥控器第1通道数据
			     ch2:遥控器第2通道数据
           ch3:遥控器第3通道数据
					 ch4:遥控器第4通道数据
					 ch5:遥控器第5通道数据
					 ch6:遥控器第6通道数据
					 ch7:遥控器第7通道数据
					 ch8:遥控器第8通道数据
@出口参数：无
功能描述：发送遥控器各通道数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_RCData(uint16_t ch1,uint16_t ch2,uint16_t ch3,uint16_t ch4,
	                      uint16_t ch5,uint16_t ch6,uint16_t ch7,uint16_t ch8)
{
  uint8_t _cnt=0,i=0,sum = 0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_RCDATA;
  nclink_databuf[_cnt++]=0;
  nclink_databuf[_cnt++]=BYTE1(ch1);
  nclink_databuf[_cnt++]=BYTE0(ch1);
  nclink_databuf[_cnt++]=BYTE1(ch2);
  nclink_databuf[_cnt++]=BYTE0(ch2);
  nclink_databuf[_cnt++]=BYTE1(ch3);
  nclink_databuf[_cnt++]=BYTE0(ch3);
  nclink_databuf[_cnt++]=BYTE1(ch4);
  nclink_databuf[_cnt++]=BYTE0(ch4);
  nclink_databuf[_cnt++]=BYTE1(ch5);
  nclink_databuf[_cnt++]=BYTE0(ch5);
  nclink_databuf[_cnt++]=BYTE1(ch6);
  nclink_databuf[_cnt++]=BYTE0(ch6);
  nclink_databuf[_cnt++]=BYTE1(ch7);
  nclink_databuf[_cnt++]=BYTE0(ch7);
  nclink_databuf[_cnt++]=BYTE1(ch8);
  nclink_databuf[_cnt++]=BYTE0(ch8);
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@函数名：NCLink_Send_GPSData(int32_t lng,int32_t lat,int32_t alt,int16_t pdop,uint8_t fixstate,uint8_t numsv)
@入口参数：lng:GPS经度
			     lat:GPS纬度
           alt:GPS海拔
					 pdop:GPS定位精度
					 fixstate:GPS定位状态
					 numsv:GPS有效定位星数
@出口参数：无
功能描述：发送GPS定位数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_GPSData(int32_t lng,int32_t lat,int32_t alt,int16_t pdop,uint8_t fixstate,uint8_t numsv)
{
	uint16_t sum = 0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_GPS;
  nclink_databuf[_cnt++]=0;
  
	nclink_databuf[_cnt++]=BYTE3(lng);
  nclink_databuf[_cnt++]=BYTE2(lng);
  nclink_databuf[_cnt++]=BYTE1(lng);
  nclink_databuf[_cnt++]=BYTE0(lng);
  
  nclink_databuf[_cnt++]=BYTE3(lat);
  nclink_databuf[_cnt++]=BYTE2(lat);
  nclink_databuf[_cnt++]=BYTE1(lat);
  nclink_databuf[_cnt++]=BYTE0(lat);  

  nclink_databuf[_cnt++]=BYTE3(alt);
  nclink_databuf[_cnt++]=BYTE2(alt);
  nclink_databuf[_cnt++]=BYTE1(alt);
  nclink_databuf[_cnt++]=BYTE0(alt);

  nclink_databuf[_cnt++]=BYTE1(pdop);
  nclink_databuf[_cnt++]=BYTE0(pdop);	

  nclink_databuf[_cnt++]=fixstate;
  nclink_databuf[_cnt++]=numsv;
  nclink_databuf[3] = _cnt-4; 
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@函数名：NCLink_Send_Obs_NE(float lat_pos_obs,float lng_pos_obs,float lat_vel_obs,float lng_vel_obs)
@入口参数：lat_pos_obs:GPS北向观测位置
			     lng_pos_obs:GPS东向观测位置
           lat_vel_obs:GPS北向观测速度
					 lng_vel_obs:GPS东向观测速度
@出口参数：无
功能描述：发送GPS位置、速度数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Obs_NE(float lat_pos_obs,float lng_pos_obs,
												float lat_vel_obs,float lng_vel_obs)
{
  uint16_t sum = 0,_cnt=0,i=0;	
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_OBS_NE;
  nclink_databuf[_cnt++]=0;
  
	_temp=100*lat_pos_obs;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*lng_pos_obs;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);  
	
  _temp=100*lat_vel_obs;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

  _temp=100*lng_vel_obs;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@函数名：NCLink_Send_Obs_UOP(float alt_obs_baro,float alt_obs_ult,float opt_vel_p,float opt_vel_r)
@入口参数：alt_obs_baro:气压计观测高度
			     alt_obs_ult:超声波观测高度
           opt_vel_p:光流观测速度-俯仰
					 opt_vel_r:光流观测速度-横滚
@出口参数：无
功能描述：发送高度观测数据、光流速度数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Obs_UOP(float alt_obs_baro,float alt_obs_ult,float opt_vel_p,float opt_vel_r)
{
  uint16_t sum = 0,_cnt=0,i=0;
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_OBS_UOP;
  nclink_databuf[_cnt++]=0;
  
	_temp=100*alt_obs_baro;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*alt_obs_ult;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*opt_vel_p;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*opt_vel_r;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp); 
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@函数名：NCLink_Send_Fusion_U(float alt_pos_fus,float alt_vel_fus,float alt_accel_fus)
@入口参数：alt_pos_fus:竖直方向高度估计
			     alt_vel_fus:竖直方向速度估计
           alt_accel_fus:竖直方向加速度估计
@出口参数：无
功能描述：发送竖直方向状态估计数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Fusion_U(float alt_pos_fus,float alt_vel_fus,float alt_accel_fus)
{
  uint16_t sum = 0,_cnt=0,i=0;
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_FUS_U;
  nclink_databuf[_cnt++]=0;
	_temp=100*alt_pos_fus;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*alt_vel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*alt_accel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
  nclink_databuf[3] = _cnt-4;  
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@函数名：NCLink_Send_Fusion_NE(float lat_pos_fus	,float lng_pos_fus,float lat_vel_fus,
															 float lng_vel_fus,float lat_accel_fus,float lng_accel_fus)
@入口参数：lat_pos_fus:正北方向位置估计
			     lng_pos_fus:正东方向位置估计
           lat_vel_fus:正北方向速度估计
					 lng_vel_fus:正东方向速度估计
			     lat_accel_fus:正北方向加速度估计
           lng_accel_fus:正东方向加速度估计
@出口参数：无
功能描述：发送水平方向状态估计数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Fusion_NE(float lat_pos_fus	,float lng_pos_fus,
											     float lat_vel_fus  ,float lng_vel_fus,
											     float lat_accel_fus,float lng_accel_fus)
{
  u8 sum = 0,_cnt=0,i=0;
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_FUS_NE;
  nclink_databuf[_cnt++]=0;
	_temp=100*lat_pos_fus;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*lng_pos_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*lat_vel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*lng_vel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
	_temp=100*lat_accel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
	_temp=100*lng_accel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@函数名：NCLink_Send_PID(uint8_t group,float pid1_kp,float pid1_ki,float pid1_kd,
																	     float pid2_kp,float pid2_ki,float pid2_kd,
																	     float pid3_kp,float pid3_ki,float pid3_kd
@入口参数：group:PID类别
			     pid1_kp:第1组PID参数比例参数
           pid1_ki:第1组PID参数积分参数
					 pid1_kd:第1组PID参数微分参数
			     pid2_kp:第2组PID参数比例参数
           pid2_ki:第2组PID参数积分参数
					 pid2_kd:第2组PID参数微分参数
			     pid3_kp:第3组PID参数比例参数
           pid3_ki:第3组PID参数积分参数
					 pid3_kd:第3组PID参数微分参数
@出口参数：无
功能描述：发送PID参数数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_PID(uint8_t group,float pid1_kp,float pid1_ki,float pid1_kd,
																	 float pid2_kp,float pid2_ki,float pid2_kd,
																	 float pid3_kp,float pid3_ki,float pid3_kd)
{
  uint8_t _cnt=0,sum = 0,i=0;
  int16_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=group;
  nclink_databuf[_cnt++]=0;
  _temp = (int16_t)(pid1_kp * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid1_ki  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid1_kd  * 100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid2_kp  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid2_ki  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid2_kd * 100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid3_kp  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid3_ki  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid3_kd * 100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@函数名：NCLink_Send_Parameter(uint16_t targeheight,uint16_t safeheight,uint16_t safevbat,uint16_t maxheight,
													     uint16_t maxradius,uint16_t maxupvel,uint16_t maxdownvel,uint16_t maxhorvel)
@入口参数：targeheight:一键起飞目标高度CM
					 safeheight:返航安全高度
					 safevbat:安全电压阈值
					 maxheight:最大飞行高度
					 maxradius:最大飞行半径
					 maxupvel:最大爬升速度
					 maxdownvel:最大下降速度
					 maxhorvel:最大水平速度
@出口参数：无
功能描述：发送其它参数数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Parameter(uint16_t targeheight,uint16_t safeheight,uint16_t safevbat,uint16_t maxheight,
													 uint16_t maxradius,uint16_t maxupvel,uint16_t maxdownvel,uint16_t maxhorvel)
{
  uint8_t _cnt=0,sum = 0,i=0;
  uint16_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_PARA;
  nclink_databuf[_cnt++]=0; 
  _temp = targeheight;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = safeheight;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = safevbat;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxheight;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxradius;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxupvel;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxdownvel;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxhorvel;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp); 
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}



/***************************************************************************************
@函数名：NCLink_Send_Userdata(float userdata1	 ,float userdata2,
											        float userdata3  ,float userdata4,
											        float userdata5  ,float userdata6)
@入口参数：userdata1:用户数据1
					 userdata2:用户数据2
					 userdata3:用户数据3
					 userdata4:用户数据4
					 userdata5:用户数据5
					 userdata6:用户数据6
@出口参数：无
功能描述：发送用户数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_Userdata(float userdata1	 ,float userdata2,
											    float userdata3  ,float userdata4,
											    float userdata5  ,float userdata6)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_USER;
  nclink_databuf[_cnt++]=0;
		
	Float2Byte(&userdata1,nclink_databuf,_cnt);//4
	_cnt+=4;
	Float2Byte(&userdata2,nclink_databuf,_cnt);//8
	_cnt+=4;
	Float2Byte(&userdata3,nclink_databuf,_cnt);//12
	_cnt+=4;
	Float2Byte(&userdata4,nclink_databuf,_cnt);//16
	_cnt+=4;
	Float2Byte(&userdata5,nclink_databuf,_cnt);//20
	_cnt+=4;
	Float2Byte(&userdata6,nclink_databuf,_cnt);//24
	_cnt+=4;//28

  nclink_databuf[3] = _cnt-4;
	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf,_cnt);
}


/***************************************************************************************
@函数名：NCLink_Send_CalRawdata(float gyro_x_raw,float gyro_y_raw,float gyro_z_raw,
											          float acce_x_raw,float acce_y_raw,float acce_z_raw)
@入口参数：gyro_x_raw:角速度校准X轴原始数据
					 gyro_y_raw:角速度校准Y轴原始数据
					 gyro_z_raw:角速度校准Z轴原始数据
					 acce_x_raw:加速度校准X轴原始数据
					 acce_y_raw:加速度校准Y轴原始数据
					 acce_z_raw:加速度校准Z轴原始数据
					 mag_x_raw: 磁力计校准X轴原始数据
					 mag_y_raw: 磁力计校准Y轴原始数据
					 mag_z_raw: 磁力计校准Z轴原始数据
@出口参数：无
功能描述：发送传感器校准原始数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_CalRawdata1(uint8_t gyro_auto_cal_flag,
													  float gyro_x_raw,float gyro_y_raw,float gyro_z_raw,
											      float acce_x_raw,float acce_y_raw,float acce_z_raw)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_RAW1;
  nclink_databuf[_cnt++]=0;
	nclink_databuf[_cnt++]=gyro_auto_cal_flag;
	
	Float2Byte(&gyro_x_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_y_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_z_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_x_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_y_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_z_raw,nclink_databuf,_cnt);
	_cnt+=4;
	
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	Serial_Data_Send(nclink_databuf,_cnt);
	//Serial_Data_Send((unsigned char *)databuf,sizeof(databuf));
}

/***************************************************************************************
@函数名：NCLink_Send_CalRawdata2(float mag_x_raw ,float mag_y_raw ,float mag_z_raw)
@入口参数：mag_x_raw: 磁力计校准X轴原始数据
					 mag_y_raw: 磁力计校准Y轴原始数据
					 mag_z_raw: 磁力计校准Z轴原始数据
@出口参数：无
功能描述：发送传感器校准原始数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_CalRawdata2(float mag_x_raw ,float mag_y_raw ,float mag_z_raw)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_RAW2;
  nclink_databuf[_cnt++]=0;
	
	Float2Byte(&mag_x_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_y_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_z_raw,nclink_databuf,_cnt);
	_cnt+=4;	
	
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	Serial_Data_Send(nclink_databuf,_cnt);
	//Serial_Data_Send((unsigned char *)databuf,sizeof(databuf));
}



/***************************************************************************************
@函数名：NCLink_Send_CalParadata1(float gyro_x_offset,float gyro_y_offset,float gyro_z_offset,
										             float mag_x_offset,float mag_y_offset,float mag_z_offset)
@入口参数：gyro_x_offset:角速度校准后X轴零偏数据
					 gyro_y_offset:角速度校准后Y轴零偏数据
					 gyro_z_offset:角速度校准后Z轴零偏数据
					 mag_x_offset: 磁力计校准后X轴零偏数据
					 mag_y_offset: 磁力计校准后Y轴零偏数据
					 mag_z_offset: 磁力计校准后Z轴零偏数据
@出口参数：无
功能描述：发送传感器校准原始数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_CalParadata1(float gyro_x_offset,float gyro_y_offset,float gyro_z_offset,
										          float mag_x_offset ,float mag_y_offset ,float mag_z_offset)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_PARA1;
  nclink_databuf[_cnt++]=0;
	
	Float2Byte(&gyro_x_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_y_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_z_offset,nclink_databuf,_cnt);
	_cnt+=4;
	
	
	Float2Byte(&mag_x_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_y_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_z_offset,nclink_databuf,_cnt);
	_cnt+=4;	

  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
  
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	
	Serial_Data_Send(nclink_databuf,_cnt);	
}


/***************************************************************************************
@函数名：NCLink_Send_CalParadata1(float acce_x_offset,float acce_y_offset,float acce_z_offset,
														     float acce_x_scale,float acce_y_scale,float acce_z_scale)
@入口参数：acce_x_offset:加速度校准后X轴零偏数据
					 acce_y_offset:加速度校准后Y轴零偏数据
					 acce_z_offset:加速度校准后Z轴零偏数据
					 acce_x_scale: 加速度校准后X轴量程数据
					 acce_y_scale: 加速度校准后Y轴量程数据
					 acce_z_scale: 加速度校准后Z轴量程数据
@出口参数：无
功能描述：发送传感器校准原始数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_CalParadata2(float acce_x_offset,float acce_y_offset,float acce_z_offset,
														 float acce_x_scale ,float acce_y_scale ,float acce_z_scale)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_PARA2;
  nclink_databuf[_cnt++]=0;
	
	
	Float2Byte(&acce_x_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_y_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_z_offset,nclink_databuf,_cnt);
	_cnt+=4;
	
	Float2Byte(&acce_x_scale,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_y_scale,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_z_scale,nclink_databuf,_cnt);
	_cnt+=4;	
		
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
  
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	
	Serial_Data_Send(nclink_databuf,_cnt);	
}

/***************************************************************************************
@函数名：NCLink_Send_CalParadata1(float pitch_offset,float roll_offset)
@入口参数：pitch_offset: 机架水平校准后俯仰零偏数据
					 roll_offset:  机架水平校准后横滚零偏数据
@出口参数：无
功能描述：发送传感器校准原始数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Send_CalParadata3(float pitch_offset ,float roll_offset)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_PARA3;
  nclink_databuf[_cnt++]=0;
	
	Float2Byte(&pitch_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&roll_offset,nclink_databuf,_cnt);
	_cnt+=4;	
	
	
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
  
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	
	Serial_Data_Send(nclink_databuf,_cnt);	
}
/***************************************************************************************
@函数名：void NCLink_Send_Check(uint8_t response)
@入口参数：response:应答
@出口参数：无
功能描述：发送应答数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
static void NCLink_Send_Check(uint8_t response)//地面站应答校验
{
  uint8_t sum = 0,i=0;
  nclink_databuf[0]=NCLink_Head[0];
  nclink_databuf[1]=NCLink_Head[1];
  nclink_databuf[2]=NCLINK_SEND_CHECK;
  nclink_databuf[3]=1;
  nclink_databuf[4]=response;
  for(i=0;i<5;i++) sum ^= nclink_databuf[i];
  nclink_databuf[5]=sum;
	nclink_databuf[6]=NCLink_End[0];
	nclink_databuf[7]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf,8);
}



/***************************************************************************************
@函数名：NCLink_Data_Prase_Prepare(uint8_t data)
@入口参数：data:待解析数据
@出口参数：无
功能描述：飞控解析地面站数据准备，本函数放入串口中断函数内
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Data_Prase_Prepare(uint8_t data)//地面站数据解析
{
  static uint8_t buf[100];
  static uint8_t data_len = 0,data_cnt = 0;
  static uint8_t state = 0;
  if(state==0&&data==NCLink_Head[1])//判断帧头1
  {
    state=1;
    buf[0]=data;
  }
  else if(state==1&&data==NCLink_Head[0])//判断帧头2
  {
    state=2;
    buf[1]=data;
  }
  else if(state==2&&data<0XF1)//功能字节
  {
    state=3;
    buf[2]=data;
  }
  else if(state==3&&data<100)//有效数据长度
  {
    state = 4;
    buf[3]=data;
    data_len = data;
    data_cnt = 0;
  }
  else if(state==4&&data_len>0)//数据接收
  {
    data_len--;
    buf[4+data_cnt++]=data;
    if(data_len==0)  state = 5;
  }
  else if(state==5)//异或校验
  {
    state = 6;
    buf[4+data_cnt++]=data;
  }
	else if(state==6&&data==NCLink_End[0])//帧尾0
	{
			state = 7;
			buf[4+data_cnt++]=data;
	}
	else if(state==7&&data==NCLink_End[1])//帧尾1
	{
			state = 0;
			buf[4+data_cnt]=data;
		  NCLink_Data_Prase_Process(buf,data_cnt+5);//数据解析
	}
  else state = 0;
}




/***************************************************************************************
以上功能代码无需改动，用户移植自飞控平台时，需要将以下全局变量替换掉
***************************************************************************************/



/***************************************************************************************
@函数名：NCLink_Send_Check_Status_Parameter(void)
@入口参数：无
@出口参数：无
功能描述：发送应答数据、请求数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
uint8_t NCLink_Send_Check_Status_Parameter(void)
{
	if(NCLink_Send_Check_Flag[0]==1)//飞控解析第1组PID参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PID1_3);
		 NCLink_Send_Check_Flag[0]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[1]==1)//飞控解析第2组PID参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PID4_6);
		 NCLink_Send_Check_Flag[1]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[2]==1)//飞控解析第3组PID参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PID7_9);
		 NCLink_Send_Check_Flag[2]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[3]==1)//飞控解析第4组PID参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PID10_12);
		 NCLink_Send_Check_Flag[3]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[4]==1)//飞控解析第5组PID参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PID13_15);
		 NCLink_Send_Check_Flag[4]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[5]==1)//飞控解析第6组PID参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PID16_18);
		 NCLink_Send_Check_Flag[5]=0;
		 return 1;
	}
  else if(NCLink_Send_Check_Flag[6]==1)//飞控解析其它参数成功，返回状态给地面站
	{
	   NCLink_Send_Check(NCLINK_SEND_PARA);
		 NCLink_Send_Check_Flag[6]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[7]==1)//飞控解析遥控器数据成功，返回状态给地面站
	{
		 NCLink_Send_Check(NCLINK_SEND_RC);	
		 NCLink_Send_Check_Flag[7]=0;
		 return 1;
	}
  else if(NCLink_Send_Check_Flag[8]==1)//飞控解析位移数据成功，返回状态给地面站
	{
		 NCLink_Send_Check(NCLINK_SEND_DIS);
		 NCLink_Send_Check_Flag[8]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[9]==1)//飞控传感器校准完毕，返回状态给地面站
	{
		 NCLink_Send_Check(NCLINK_SEND_CAL);
		 NCLink_Send_Check_Flag[9]=0;
		
		 NCLink_Send_Check_Flag[10]=1;//每次校准完毕自动刷新地面站校准数据
		 return 1;
	}
  else if(NCLink_Send_Check_Flag[10]==1)//飞控传感器校准成功，返回状态给地面站
	{
		 static uint8_t cnt=0;
		 if(cnt==0)
		 {
		   NCLink_Send_Check(NCLINK_SEND_CAL_READ);	
			 cnt=1;
		 }
		 else if(cnt==1)
		 {
			 NCLink_Send_CalParadata1(gyro_offset.x,gyro_offset.y,gyro_offset.z,Mag_Offset[0],Mag_Offset[1],Mag_Offset[2]);		 
		   cnt=2;
		 }
		 else if(cnt==2)
		 {
				NCLink_Send_CalParadata2(B[0]*GRAVITY_MSS,B[1]*GRAVITY_MSS,B[2]*GRAVITY_MSS,K[0],K[1],K[2]);	 
		    cnt=3;
		 }      
		 else if(cnt==3)
		 {
			  NCLink_Send_CalParadata3(Pitch_Offset,Roll_Offset);
		    cnt=0;
			  NCLink_Send_Check_Flag[10]=0;
		 } 
		 return 1;
	}	
	else if(NCLink_Send_Ask_Flag[0]==1)//接收到地面站读取PID参数请求，飞控发送第1组PID参数给地面站
	{
		NCLink_Send_PID(NCLINK_SEND_PID1_3,Total_Controller.Roll_Gyro_Control.Kp,
										Total_Controller.Roll_Gyro_Control.Ki,
										Total_Controller.Roll_Gyro_Control.Kd,
										Total_Controller.Pitch_Gyro_Control.Kp,
										Total_Controller.Pitch_Gyro_Control.Ki,
										Total_Controller.Pitch_Gyro_Control.Kd,
										Total_Controller.Yaw_Gyro_Control.Kp,
										Total_Controller.Yaw_Gyro_Control.Ki,
										Total_Controller.Yaw_Gyro_Control.Kd);
		NCLink_Send_Ask_Flag[0]=0;
		return 1;
	}
	else if(NCLink_Send_Ask_Flag[1]==1)//接收到地面站读取PID参数请求，飞控发送第2组PID参数给地面站
	{
			NCLink_Send_PID(NCLINK_SEND_PID4_6,Total_Controller.Roll_Angle_Control.Kp,
											Total_Controller.Roll_Angle_Control.Ki,
											Total_Controller.Roll_Angle_Control.Kd,
											Total_Controller.Pitch_Angle_Control.Kp,
											Total_Controller.Pitch_Angle_Control.Ki,
											Total_Controller.Pitch_Angle_Control.Kd,
											Total_Controller.Yaw_Angle_Control.Kp,
											Total_Controller.Yaw_Angle_Control.Ki,
											Total_Controller.Yaw_Angle_Control.Kd);
			NCLink_Send_Ask_Flag[1]=0;
			return 1;
	}
  else if(NCLink_Send_Ask_Flag[2]==1)//接收到地面站读取PID参数请求，飞控发送第3组PID参数给地面站
  {
			NCLink_Send_PID(NCLINK_SEND_PID7_9,Total_Controller.High_Position_Control.Kp,
											Total_Controller.High_Position_Control.Ki,
											Total_Controller.High_Position_Control.Kd,
											Total_Controller.High_Speed_Control.Kp,
											Total_Controller.High_Speed_Control.Ki,
											Total_Controller.High_Speed_Control.Kd,
										  Total_Controller.High_Acce_Control.Kp,
											Total_Controller.High_Acce_Control.Ki,
											Total_Controller.High_Acce_Control.Kd);
			NCLink_Send_Ask_Flag[2]=0;
			return 1;
  }
  else if(NCLink_Send_Ask_Flag[3]==1)//接收到地面站读取PID参数请求，飞控发送第4组PID参数给地面站
  {
			NCLink_Send_PID(NCLINK_SEND_PID10_12,Total_Controller.Latitude_Position_Control.Kp,
											Total_Controller.Latitude_Position_Control.Ki,
											Total_Controller.Latitude_Position_Control.Kd,
											Total_Controller.Latitude_Speed_Control.Kp,
											Total_Controller.Latitude_Speed_Control.Ki,
											Total_Controller.Latitude_Speed_Control.Kd,
			                Total_Controller.SDK_Roll_Position_Control.Kp,
											Total_Controller.SDK_Roll_Position_Control.Ki,
										  Total_Controller.SDK_Roll_Position_Control.Kd); 
			NCLink_Send_Ask_Flag[3]=0;
			return 1;
	}
	else if(NCLink_Send_Ask_Flag[4]==1)//接收到地面站读取PID参数请求，飞控发送第5一组PID参数给地面站
	{
		NCLink_Send_PID(NCLINK_SEND_PID13_15,Total_Controller.Optical_Position_Control.Kp
										 ,Total_Controller.Optical_Position_Control.Ki
										 ,Total_Controller.Optical_Position_Control.Kd
										 ,Total_Controller.Optical_Speed_Control.Kp
										 ,Total_Controller.Optical_Speed_Control.Ki
										 ,Total_Controller.Optical_Speed_Control.Kd
										 ,Pitch_Roll_Feedforward_Kp,0,Pitch_Roll_Feedforward_Kd);
		NCLink_Send_Ask_Flag[4]=0;
		return 1;
	}
	else if(NCLink_Send_Ask_Flag[5]==1)//接收到地面站读取PID参数请求，飞控发送第6组PID参数给地面站
	{
		NCLink_Send_PID(NCLINK_SEND_PID16_18,
									  0,0,0,
										0,0,0,
										0,0,0);
		NCLink_Send_Ask_Flag[5]=0;
		return 1;
	}
	else if(NCLink_Send_Ask_Flag[6]==1)//接收到地面站读取其它参数请求，飞控发送其它参数给地面站
	{
		 NCLink_Send_Parameter(Target_Height,Safe_Height,Safe_Vbat,Max_Height,Max_Radius,Max_Upvel,Max_Downvel,Max_Horvel);
		 NCLink_Send_Ask_Flag[6]=0;
		 return 1;	
	}
	else return 0;
}

/***************************************************************************************
@函数名：NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num)
@入口参数：data_buf:待解析数据帧
					 num:数据帧长
@出口参数：无
功能描述：根据提取出的数据帧，解析每一帧数据数据
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num)//飞控数据解析进程
{
  uint8_t sum = 0;
  for(uint8_t i=0;i<(num-3);i++)  sum ^= *(data_buf+i);
  if(!(sum==*(data_buf+num-3)))    																					return;//判断sum	
	if(!(*(data_buf)==NCLink_Head[1]&&*(data_buf+1)==NCLink_Head[0]))         return;//判断帧头
	if(!(*(data_buf+num-2)==NCLink_End[0]&&*(data_buf+num-1)==NCLink_End[1])) return;//帧尾校验  
  if(*(data_buf+2)==0X01)//地面站请求状态解析
  {
    if(*(data_buf+4)==0X01)		//地面站发送读取当前PID参数请求
    {
      NCLink_Send_Ask_Flag[0]=1;//飞控发送第1组PID参数，请求位置1
      NCLink_Send_Ask_Flag[1]=1;//飞控发送第2组PID参数，请求位置1
      NCLink_Send_Ask_Flag[2]=1;//飞控发送第3组PID参数，请求位置1
      NCLink_Send_Ask_Flag[3]=1;//飞控发送第4组PID参数，请求位置1
      NCLink_Send_Ask_Flag[4]=1;//飞控发送第5组PID参数，请求位置1
      NCLink_Send_Ask_Flag[5]=1;//飞控发送第6组PID参数，请求位置1
      Pilot_Status_Tick();
    }	
    else if(*(data_buf+4)==0X02)   //地面站发送恢复默认PID参数请求
    {
      Sort_PID_Flag=3;
      Pilot_Status_Tick();
    }
		else if(*(data_buf+4)==0X03)//地面站发送读取当前其它参数请求    
    {
      NCLink_Send_Ask_Flag[6]=1;//飞控发送其它参数请求位置1
      Pilot_Status_Tick();
    }
		else if(*(data_buf+4)==0X04)//地面站发送恢复默认其它参数请求  
    {
      NCLink_Send_Ask_Flag[6]=1;//恢复默认参数，并将默认参数发送到地面站
			Sort_Other_Para_Cnt=0x01;
      Pilot_Status_Tick();
    }
  }
  else if(*(data_buf+2)==0X02)                             //接收PID1-3
  {
    Total_Controller.Roll_Gyro_Control.Kp  = 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
    Total_Controller.Roll_Gyro_Control.Ki  = 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
    Total_Controller.Roll_Gyro_Control.Kd  = 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
    Total_Controller.Pitch_Gyro_Control.Kp = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
    Total_Controller.Pitch_Gyro_Control.Ki = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
    Total_Controller.Pitch_Gyro_Control.Kd = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
    Total_Controller.Yaw_Gyro_Control.Kp   = 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
    Total_Controller.Yaw_Gyro_Control.Ki   = 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
    Total_Controller.Yaw_Gyro_Control.Kd   = 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
		NCLink_Send_Check_Flag[0]=1;
  }
  else if(*(data_buf+2)==0X03)                             //接收PID4-6
  {
    Total_Controller.Roll_Angle_Control.Kp  = 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.Roll_Angle_Control.Ki  = 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.Roll_Angle_Control.Kd  = 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.Pitch_Angle_Control.Kp   = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.Pitch_Angle_Control.Ki   = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.Pitch_Angle_Control.Kd   = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
    Total_Controller.Yaw_Angle_Control.Kp    = 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) );
    Total_Controller.Yaw_Angle_Control.Ki    = 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19) );
    Total_Controller.Yaw_Angle_Control.Kd    = 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
		NCLink_Send_Check_Flag[1]=1;
  }
  else if(*(data_buf+2)==0X04)                             //接收PID7-9
  {
    Total_Controller.High_Position_Control.Kp= 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.High_Position_Control.Ki= 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.High_Position_Control.Kd= 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.High_Speed_Control.Kp   = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.High_Speed_Control.Ki   = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.High_Speed_Control.Kd   = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
    Total_Controller.High_Acce_Control.Kp		 = 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) );
    Total_Controller.High_Acce_Control.Ki		 = 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19) );
    Total_Controller.High_Acce_Control.Kd		 = 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
    /***********************位置控制：位置、速度参数共用一组PID参数**********************************************************/
    Total_Controller.Longitude_Speed_Control.Kp=Total_Controller.Latitude_Speed_Control.Kp;
    Total_Controller.Longitude_Speed_Control.Ki=Total_Controller.Latitude_Speed_Control.Ki;
    Total_Controller.Longitude_Speed_Control.Kd=Total_Controller.Latitude_Speed_Control.Kd;
		NCLink_Send_Check_Flag[2]=1;
  }
  else if(*(data_buf+2)==0X05)                             //接收PID9-11
  {
    Total_Controller.Latitude_Position_Control.Kp= 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.Latitude_Position_Control.Ki= 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.Latitude_Position_Control.Kd= 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.Latitude_Speed_Control.Kp   = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.Latitude_Speed_Control.Ki   = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.Latitude_Speed_Control.Kd   = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
		Total_Controller.SDK_Roll_Position_Control.Kp= 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) );
		Total_Controller.SDK_Roll_Position_Control.Ki= 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19) );
		Total_Controller.SDK_Roll_Position_Control.Kd= 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
    /***********************位置控制：位置、速度参数共用一组PID参数**********************************************************/
    Total_Controller.Longitude_Position_Control.Kp=Total_Controller.Latitude_Position_Control.Kp;
    Total_Controller.Longitude_Position_Control.Ki=Total_Controller.Latitude_Position_Control.Ki;
    Total_Controller.Longitude_Position_Control.Kd=Total_Controller.Latitude_Position_Control.Kd;
		Total_Controller.Longitude_Speed_Control.Kp=Total_Controller.Latitude_Speed_Control.Kp;
		Total_Controller.Longitude_Speed_Control.Ki=Total_Controller.Latitude_Speed_Control.Ki;
		Total_Controller.Longitude_Speed_Control.Kd=Total_Controller.Latitude_Speed_Control.Kd;
		
		Total_Controller.SDK_Pitch_Position_Control.Kp = Total_Controller.SDK_Roll_Position_Control.Kp;
		Total_Controller.SDK_Pitch_Position_Control.Ki = Total_Controller.SDK_Roll_Position_Control.Ki;
		Total_Controller.SDK_Pitch_Position_Control.Kd = Total_Controller.SDK_Roll_Position_Control.Kd;
		
		NCLink_Send_Check_Flag[3]=1;
  }
  else if(*(data_buf+2)==0X06)                             //接收PID12-15
  {
    Total_Controller.Optical_Position_Control.Kp = 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.Optical_Position_Control.Ki = 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.Optical_Position_Control.Kd = 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.Optical_Speed_Control.Kp = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.Optical_Speed_Control.Ki = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.Optical_Speed_Control.Kd = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
    
		Pitch_Roll_Feedforward_Kp= 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) ); 
		Pitch_Roll_Feedforward_Kd= 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
		NCLink_Send_Check_Flag[4]=1;		
  }
  else if(*(data_buf+2)==0X07)                             //接收PID16-18
  {
		NCLink_Send_Check_Flag[5]=1;
    Sort_PID_Flag=1;	
    Pilot_Status_Tick();
  }
	else if(*(data_buf+2)==0X08)                             //其它参数
  {
    Target_Height =(int16_t)(*(data_buf+4)<<8)|*(data_buf+5);
    Safe_Height =(int16_t)(*(data_buf+6)<<8)|*(data_buf+7);
    Safe_Vbat =(int16_t)(*(data_buf+8)<<8)|*(data_buf+9);
    Max_Height =(int16_t)(*(data_buf+10)<<8)|*(data_buf+11);
    Max_Radius =(int16_t)(*(data_buf+12)<<8)|*(data_buf+13);
    Max_Upvel =(int16_t)(*(data_buf+14)<<8)|*(data_buf+15);
    Max_Downvel =(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
    Max_Horvel =(int16_t)(*(data_buf+18)<<8)|*(data_buf+19);
		NCLink_Send_Check_Flag[6]=1;
		Pilot_Status_Tick();
		
		Sort_Other_Para_Cnt=0x02;
  }
  else if(*(data_buf+2)==0X09)                             //遥控器参数
  {
    PPM_Databuf[0]=(int16_t)(*(data_buf+4)<<8)|*(data_buf+5);
    PPM_Databuf[1]=(int16_t)(*(data_buf+6)<<8)|*(data_buf+7);
    PPM_Databuf[2]=(int16_t)(*(data_buf+8)<<8)|*(data_buf+9);
    PPM_Databuf[3]=(int16_t)(*(data_buf+10)<<8)|*(data_buf+11);
    PPM_Databuf[4]=(int16_t)(*(data_buf+12)<<8)|*(data_buf+13);
    PPM_Databuf[5]=(int16_t)(*(data_buf+14)<<8)|*(data_buf+15);
    PPM_Databuf[6]=(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
    PPM_Databuf[7]=(int16_t)(*(data_buf+18)<<8)|*(data_buf+19);
		rc_update_flag=1;
		
		unlock_flag=*(data_buf+20);
		takeoff_flag=*(data_buf+21);		
		NCLink_Send_Check_Flag[7]=1;
		Pilot_Status_Tick();	
  }
	else if(*(data_buf+2)==0X0A)                             //地面站控制移动数据
  {		
    ngs_sdk.move_mode=*(data_buf+4),
		ngs_sdk.mode_order=*(data_buf+5);
    ngs_sdk.move_distance=(uint16_t)(*(data_buf+6)<<8)|*(data_buf+7);;
    ngs_sdk.update_flag=true;
		
		ngs_sdk.move_flag.sdk_front_flag=false;
		ngs_sdk.move_flag.sdk_behind_flag=false;
		ngs_sdk.move_flag.sdk_left_flag=false;
		ngs_sdk.move_flag.sdk_right_flag=false;
		ngs_sdk.move_flag.sdk_up_flag=false;
		ngs_sdk.move_flag.sdk_down_flag=false;
		
		if(*(data_buf+4)==SDK_FRONT)
		{					
			ngs_sdk.move_flag.sdk_front_flag=true;
			ngs_sdk.f_distance=ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_BEHIND) 
		{					
			ngs_sdk.move_flag.sdk_behind_flag=true;
			ngs_sdk.f_distance=-ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_LEFT)  
		{			
			ngs_sdk.move_flag.sdk_left_flag=true;
			ngs_sdk.f_distance=-ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_RIGHT)
		{					
			ngs_sdk.move_flag.sdk_right_flag=true;
			ngs_sdk.f_distance=ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_UP)
		{  				
			ngs_sdk.move_flag.sdk_up_flag=true;
			ngs_sdk.f_distance=ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_DOWN) 
		{					
			ngs_sdk.move_flag.sdk_down_flag=true;
			ngs_sdk.f_distance=-ngs_sdk.move_distance;
		}				
		NCLink_Send_Check_Flag[8]=1;
		Pilot_Status_Tick();	
  }
	else if(*(data_buf+2)==0X0B)                             //地面站发送校准数据
  {		
    cal_flag=*(data_buf+4),
		cal_step=*(data_buf+5);
		cal_cmd=*(data_buf+6);
		
		if(cal_flag==0x00&&cal_step==0x00&&cal_cmd==0x00)//提前终止当前校准
		{
		  shutdown_now_cal_flag=1;
		}	
		else
		{
			if(cal_cmd==0x01)
			{
				NCLink_Send_Check_Flag[10]=1;
				cal_cmd=0x00;
			}
	  }
		Pilot_Status_Tick();			
  }
	else if(*(data_buf+2)==0X0C)
  {
		Guide_Flight_Lng =((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
		Guide_Flight_Lat =((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
		Guide_Flight_Cnt++;;
		Guide_Flight_Flag=1;
		Pilot_Status_Tick();
	}		
}


/***************************************************************************************
@函数名：NCLink_SEND_StateMachine(void)
@入口参数：无
@出口参数：无
功能描述：状态机——飞控发送数据给地面站
@作者：无名小哥
@日期：2020年01月17日
****************************************************************************************/
void NCLink_SEND_StateMachine(void)
{
	static uint16_t NCLink_Cnt=0;
	if(!NCLink_Send_Check_Status_Parameter())//判断地面站有无请求数据、是否需要发送应答
	{
		if(NCLink_Cnt==0)//飞控姿态等基本信息
		{
			NCLink_Cnt=1;
			NCLink_Send_Status(Roll,Pitch,Yaw,
												 Roll_Gyro,Pitch_Gyro,Yaw_Gyro,
												 WP_Sensor.temperature,Battery_Valtage,Controler_High_Mode,Controler_State);
		}
		else if(NCLink_Cnt==1)//飞控传感器原始数据
		{
			NCLink_Cnt=2;
			NCLink_Send_Senser((int16_t)WP_Sensor.accel_raw.x,(int16_t)WP_Sensor.accel_raw.y,(int16_t)WP_Sensor.accel_raw.z,
												 (int16_t)WP_Sensor.gyro_raw.x,(int16_t)WP_Sensor.gyro_raw.y,(int16_t)WP_Sensor.gyro_raw.z,
												 (int16_t)WP_Sensor.mag_raw.x,(int16_t)WP_Sensor.mag_raw.y,(int16_t)WP_Sensor.mag_raw.z);
		}
		else if(NCLink_Cnt==2)//飞控接收遥控器数据
		{
			NCLink_Cnt=3;
			NCLink_Send_RCData(PPM_Databuf[0],PPM_Databuf[1],
												 PPM_Databuf[2],PPM_Databuf[3],
												 PPM_Databuf[4],PPM_Databuf[5],
												 PPM_Databuf[6],PPM_Databuf[7]);
		}
		else if(NCLink_Cnt==3)//飞控解析GPS信息
		{
			NCLink_Cnt=4;
			NCLink_Send_GPSData(Longitude_Origion,Latitude_Origion,Altitude_Origion,GPS_Pos_DOP,GPS_FixType,GPS_Sate_Num);
		}
		else if(NCLink_Cnt==4)//飞控水平观测位置、速度
		{
			NCLink_Cnt=5;
			NCLink_Send_Obs_NE(Earth_Frame_To_XYZ.N,Earth_Frame_To_XYZ.E,GPS_Speed_Resolve[1],GPS_Speed_Resolve[0]);
		}
		else if(NCLink_Cnt==5)//飞控竖直观测位置、光流速度
		{
			NCLink_Cnt=6;
			NCLink_Send_Obs_UOP(WP_Sensor.baro_altitude,HC_SR04_Distance,opt_gyro_data.y,opt_gyro_data.x);
		}
		else if(NCLink_Cnt==6)//飞控竖直状态估计
		{
			NCLink_Cnt=7;
			NCLink_Send_Fusion_U(NamelessQuad.Position[_YAW],
													 NamelessQuad.Speed[_YAW],
													 NamelessQuad.Acceleration[_YAW]);
		}
		else if(NCLink_Cnt==7)//飞控水平状态估计
		{
			NCLink_Cnt=8;
			NCLink_Send_Fusion_NE(NamelessQuad.Position[_ROLL],
														NamelessQuad.Position[_PITCH],
														NamelessQuad.Acceleration[_ROLL],
														NamelessQuad.Acceleration[_PITCH],
														NamelessQuad.Speed[_ROLL],
														NamelessQuad.Speed[_PITCH]);	
		}
		else if(NCLink_Cnt==8)//用户数据波形显示
		{
		//NCLink_Cnt=9;
			NCLink_Send_Userdata(NamelessQuad.Position[_YAW],
													 NamelessQuad.Speed[_YAW],
													 NamelessQuad.Acceleration[_YAW],
													 WP_Sensor.baro_altitude,
													 HC_SR04_Distance,
													 0);								
		}
		else if(NCLink_Cnt==9)//传感器校准原始数据
		{
			NCLink_Cnt=10;
		  NCLink_Send_CalRawdata1(Gyro_Safety_Calibration_Flag,
			                       WP_Sensor.gyro_raw.x*Gyro_Range_Scale,WP_Sensor.gyro_raw.y*Gyro_Range_Scale,WP_Sensor.gyro_raw.z*Gyro_Range_Scale,
			                       WP_Sensor.accel_raw.x*ACCEL_TO_1G,WP_Sensor.accel_raw.y*ACCEL_TO_1G,WP_Sensor.accel_raw.z*ACCEL_TO_1G);
		}
		else if(NCLink_Cnt==10)//传感器校准原始数据
		{
			NCLink_Cnt=0;
		  NCLink_Send_CalRawdata2(Compass.x,Compass.y,Compass.z);
		}		
		else NCLink_Cnt=0;
 }
}

