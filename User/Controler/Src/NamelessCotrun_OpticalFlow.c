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
#include "NamelessCotrun_OpticalFlow.h"

uint8_t OpticalFlow_Is_Work=0;
float opticalflow_high=1000;//默认1m=100cm=1000mm
flow_float opt_data;
flow_integral_frame opt_origin_data;
Vector2f opt_filter_data; //滤波后的像素位移
Vector2f opt_gyro_data;   //光流角速度
Vector2f opt_gyro_filter_data;//光流经过旋转互补滤波后的角速度
Vector2f gyro_filter_data;//低通同步相位的角速度
Butter_Parameter OpticalFlow_Parameter,OpticalFlow_Gyro_Parameter;
Butter_BufferData Buffer_OpticalFlow[2],Buffer_OpticalFlow_Gyro[2];
void  OpticalFlow_CF(float flow_height,Vector2f accel,Vector2f flow);
void OpticalFlow_Init()
{
  Set_Cutoff_Frequency(50, 15,&OpticalFlow_Parameter);//20
  Set_Cutoff_Frequency(50, 10,&OpticalFlow_Gyro_Parameter);//同步相位
}
uint8_t Optflow_Prase()//50hz
{
  for(uint16_t i=0;i<=14;i++)
  {
    if(OpticalFlow_Ringbuf.Ring_Buff[i]==0xfe//帧头
       &&OpticalFlow_Ringbuf.Ring_Buff[i+1]==0x0a//帧长
         &&OpticalFlow_Ringbuf.Ring_Buff[i+13]==0x55)//帧尾
    {
      opt_origin_data.pixel_flow_x_integral=(int16_t)(OpticalFlow_Ringbuf.Ring_Buff[i+3]<<8)|OpticalFlow_Ringbuf.Ring_Buff[i+2];
      opt_origin_data.pixel_flow_y_integral=(int16_t)(OpticalFlow_Ringbuf.Ring_Buff[i+5]<<8)|OpticalFlow_Ringbuf.Ring_Buff[i+4];
			
			opt_origin_data.pixel_flow_x_integral*=(-1);					
			opt_origin_data.pixel_flow_y_integral*=(-1);
			
      opt_origin_data.integration_timespan= (int16_t)(OpticalFlow_Ringbuf.Ring_Buff[i+7]<<8)|OpticalFlow_Ringbuf.Ring_Buff[i+6];
      opt_origin_data.qual=OpticalFlow_Ringbuf.Ring_Buff[i+12];      
      opt_filter_data.x=LPButterworth(opt_origin_data.pixel_flow_x_integral,&Buffer_OpticalFlow[0],&OpticalFlow_Parameter);
      opt_filter_data.y=LPButterworth(opt_origin_data.pixel_flow_y_integral,&Buffer_OpticalFlow[1],&OpticalFlow_Parameter);   
      opt_data.x=(opt_origin_data.pixel_flow_x_integral*opticalflow_high)/10000.0f;//单位:乘以高度单位mm后为实际位移mm
      opt_data.y=(opt_origin_data.pixel_flow_y_integral*opticalflow_high)/10000.0f;//单位:乘以高度单位mm后为实际位移mm     
      opt_data.dt=(int16_t)(opt_origin_data.integration_timespan*0.001f);//单位ms
      opt_data.qual=opt_origin_data.qual;    
      opt_gyro_data.x=(opt_filter_data.x)/200.0f;//光流角速度rad/s
      opt_gyro_data.y=(opt_filter_data.y)/200.0f;//光流角速度rad/s         
      gyro_filter_data.x=LPButterworth(Roll_Gyro,&Buffer_OpticalFlow_Gyro[0],&OpticalFlow_Gyro_Parameter)/57.3f;//陀螺仪相位同步角速度
      gyro_filter_data.y=LPButterworth(Pitch_Gyro,&Buffer_OpticalFlow_Gyro[1],&OpticalFlow_Gyro_Parameter)/57.3f;//陀螺仪相位同步角速度
      opt_gyro_filter_data.x=OpticalFlow_Rotate_Complementary_Filter(opt_gyro_data.x,gyro_filter_data.x,'x');//光流角速度与陀螺仪角速度融合 
      opt_gyro_filter_data.y=OpticalFlow_Rotate_Complementary_Filter(opt_gyro_data.y,gyro_filter_data.y,'y'); //光流角速度与陀螺仪角速度融合 
      return 1;
    }
  }
  return 0;
}


uint8_t Optflow_Is_Okay=0;
void Optflow_Statemachine(void)
{
  static uint16_t Optflow_Cnt=0;
  if(OpticalFlow_Is_Work==1)//若初始化时，存在光流外设
  {
    Optflow_Cnt++;
    if(Optflow_Cnt>=4)//20ms解析一次
    {
      Optflow_Is_Okay=Optflow_Prase();
      Optflow_Cnt=0;
    }
    OpticalFlow_CF(NamelessQuad.Position[_YAW],SINS_Accel_Body,opt_gyro_filter_data);
  }
}


float OpticalFlow_Rotate_Complementary_Filter(float optflow_gyro,float gyro,uint8_t axis)
{
  float optflow_gyro_filter=0;
  if(axis=='x') optflow_gyro_filter=optflow_gyro-constrain_float(gyro,-3,3);//2
  else optflow_gyro_filter=optflow_gyro-constrain_float(gyro,-3,3);
  return optflow_gyro_filter;
}





SINS OpticalFlow_SINS;
Testime Optical_Delta;
Vector2f OpticalFlow_Position={0};
Vector2f OpticalFlow_Speed={0};
Vector2f OpticalFlow_Speed_Err={0};
Vector2f OpticalFlow_Position_Err={0};
uint16_t Optflow_Sync_Cnt=0;
float CF_Parameter[2]={0.05f,0.0f};//光流互补滤波权重
                                   //光流位置融合权重给为0，表示不加入修正位置修正，因为低成本光流模块漂移较大，亦可以给较小值如0.2f
#define Optical_Output_Dt  0.02f//50hz
void  OpticalFlow_CF(float flow_height,Vector2f accel,Vector2f flow)
{
  float use_height=0;
  float optical_dt=0;
  Vector2f speed_delta={0};
  Test_Period(&Optical_Delta);
  optical_dt=Optical_Delta.Time_Delta/1000.0f;
  use_height = flow_height; 
  if(Optflow_Is_Okay==1)//存在数据光流更新时，20ms一次
  {  
    OpticalFlow_Speed.x=flow.x*use_height;//光流速度
    OpticalFlow_Speed.y=flow.y*use_height;//光流速度
    OpticalFlow_Position.x+=OpticalFlow_Speed.x*Optical_Output_Dt;//光流位移
    OpticalFlow_Position.y+=OpticalFlow_Speed.y*Optical_Output_Dt;//光流位移
    OpticalFlow_Speed_Err.x=OpticalFlow_Speed.x-OpticalFlow_SINS.Speed[_PITCH];
    OpticalFlow_Speed_Err.y=OpticalFlow_Speed.y-OpticalFlow_SINS.Speed[_ROLL];
    OpticalFlow_Position_Err.x=OpticalFlow_Position.x-OpticalFlow_SINS.Position[_PITCH];
    OpticalFlow_Position_Err.y=OpticalFlow_Position.y-OpticalFlow_SINS.Position[_ROLL];
    Optflow_Is_Okay=0;
    //OpticalFlow_Speed_Err.x=OpticalFlow_Speed.x-OpticalFlow_SINS.Pos_History[_PITCH][Optflow_Sync_Cnt];
    //OpticalFlow_Speed_Err.y=OpticalFlow_Speed.y-OpticalFlow_SINS.Pos_History[_ROLL][Optflow_Sync_Cnt];
  }
  else
  {
    OpticalFlow_Speed_Err.x=0;
    OpticalFlow_Speed_Err.y=0;
    OpticalFlow_Position_Err.x=0;
    OpticalFlow_Position_Err.y=0;
  }
  
  OpticalFlow_SINS.Acceleration[_PITCH]=-accel.x;//惯导加速度沿载体机头
  OpticalFlow_SINS.Acceleration[_ROLL]=accel.y;//惯导加速度沿载体横滚（机头右侧）
  
  OpticalFlow_SINS.Speed[_PITCH]+=OpticalFlow_SINS.Acceleration[_PITCH]*optical_dt+CF_Parameter[0]*OpticalFlow_Speed_Err.x;
  OpticalFlow_SINS.Speed[_ROLL]+=OpticalFlow_SINS.Acceleration[_ROLL]*optical_dt+CF_Parameter[0]*OpticalFlow_Speed_Err.y;
  
  speed_delta.x=OpticalFlow_SINS.Acceleration[_PITCH]*optical_dt;
  speed_delta.y=OpticalFlow_SINS.Acceleration[_ROLL]*optical_dt;
  
  OpticalFlow_SINS.Position[_PITCH]+=OpticalFlow_SINS.Speed[_PITCH]*optical_dt
    +0.5*speed_delta.x*optical_dt+CF_Parameter[1]*OpticalFlow_Position_Err.x;
  OpticalFlow_SINS.Position[_ROLL]+=OpticalFlow_SINS.Speed[_ROLL]*optical_dt
    +0.5*speed_delta.y*optical_dt+CF_Parameter[1]*OpticalFlow_Position_Err.y;
  
  
  OpticalFlow_SINS.Pos_History[_ROLL][0]=OpticalFlow_SINS.Position[_ROLL];
  OpticalFlow_SINS.Pos_History[_PITCH][0]=OpticalFlow_SINS.Position[_PITCH];  
  //for(uint16_t i=Num-1;i>0;i--)
  //{
  //  OpticalFlow_SINS.Pos_History[_ROLL][i]=OpticalFlow_SINS.Pos_History[_ROLL][i-1];
  //  OpticalFlow_SINS.Pos_History[_PITCH][i]=OpticalFlow_SINS.Pos_History[_PITCH][i-1]; 
  //}  
}
