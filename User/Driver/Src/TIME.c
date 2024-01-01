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
#include "Time.h"
void Timer1_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_DeInit(TIM1);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  TIM_TimeBaseStructure.TIM_Period=5000;
  TIM_TimeBaseStructure.TIM_Prescaler= (72-1);
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}

Sensor WP_Sensor; 
Sensor_Health Sensor_Flag;
_Baro Baro_Show;
Testime Time1_Delta;
Testime T11;
Testime T22;
float ty=0;
uint16_t High_Okay_flag=0;
/***************************************************
函数名: void TIM1_UP_IRQHandler(void)
说明:	系统调度定时器
入口:	无
出口:	无
备注:	核心部分：传感器采集、滤波、
        姿态解算、惯性导航、控制等都在里面更新      
注释者：无名小哥
****************************************************/
void TIM1_UP_IRQHandler(void)//5ms刷新一次
{
  if( TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET )
  {
		Test_Period(&T11);
    Test_Period(&Time1_Delta);//系统调度时间测试器
    NRF24L01_RC();//遥控器查询接收，非中端方式
    /*************加速度计、陀螺仪数字量采集***********/
    GET_MPU_DATA();//1.4ms
    /*************磁力计+气压计状态机更新***********/
    Compass_Tradeoff();//决策使用外置磁力计，默认内置，使用外置时注意轴向、旋转关系
    SPL06_001_StateMachine();
    /*************姿态解算***********/
    AHRSUpdate_GraDes_TimeSync(X_w_av,Y_w_av,Z_w_av,X_g_av,Y_g_av,Z_g_av);
    //DirectionConsineMatrix(DCM_Gyro,DCM_Acc,MagN);//DCM姿态解算，参考APM
    Optflow_Statemachine();//光流状态机，初始化时存在光流外设
    SINS_Prepare();//得到载体相对导航系的三轴运动加速度
    if(High_Okay_flag==1)//高度惯导融合
    {
      /*
      若存在超声波时，用第二种融合方式，
      因为当观测传感器（气压计、超声波）切换时，三阶互补滤波的中间参数
      需要融合一段时间，才能收敛，而卡尔曼滤波可以直接切换
      */  
      //Strapdown_INS_High();//1、三阶互补滤波惯导融合
      Strapdown_INS_High_Kalman();//2、卡尔曼滤波惯导融合
    } 
    if(GPS_ISR_CNT>=300&&GPS_Update_finished==1)//GPS_PVT语句更新完毕后，开始解析
    {
      GPS_PVT_Parse();//GPS串口数据帧解析
      Set_GPS_Home();//设置Home点
			GPS_Update_finished=0;
    }  
    if(GPS_Home_Set==1)//Home点已设置
    {
      Filter_Horizontal();//水平方向惯导融合
    }
    Total_Control();//总控制器：水平位置+水平速度+姿态（角度+角速度）控制器，高度位置+高度速度+高度加速度控制器
    Control_Output();//控制量总输出
		Temperature_Ctrl_Run();		
		Accel_Calibration_Check();//加速度标定检测
		Mag_Calibration_Check();//磁力计标定检测
		ESC_Calibration_Check();//电调校准检测，进入后需要拔掉电池后进入
		Horizontal_Calibration_Check();//机架水平校准检测，确保机架放置于水平地面后再操作
    Angle_Calculate();//加速度计欧拉角计算，当没有转台平台时，可以作为姿态解算的观测角度
    Bling_Working(Bling_Mode);//状态指示灯		
    Usb_Hid_Receive();//USB虚拟串口查询解析
    NCLink_SEND_StateMachine();//无名创新地面站发送状态机		
    /*
		DMA_Send_Vcan(NamelessQuad.Position[_YAW],
									NamelessQuad.Speed[_YAW],
									NamelessQuad.Acceleration[_YAW],
									WP_Sensor.baro_altitude,
									0,Roll_Gyro,
									0,0);//DMA传输，只使用山外上位机
   */		
    Flight_Control_Fault_ALL();//飞控状态诊断
		
		Test_Period(&T22);	
		ty=T22.Now_Time-T11.Now_Time;
		
		
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
  }
}
