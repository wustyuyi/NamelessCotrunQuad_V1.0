#include "Headfile.h"
#include "Time.h"
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
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
void Timer4_Configuration(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
TIM_DeInit(TIM4);
TIM_TimeBaseStructure.TIM_Period=5000;
TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
TIM_ClearFlag(TIM4, TIM_FLAG_Update);
TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
TIM_Cmd(TIM4, ENABLE);
}

/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
uint8 US_100_Start=0,US_100_Finished=1,US_100_Sampling_Cnt=0,US_100_Retry_Cnt=0;
uint8 ADNS3080_Cnt=0;
uint8 HC_SR04_Cnt=0;
Testime Time4_Delta;
uint16_t High_Okay_flag=0;
void TIM4_IRQHandler(void)//5ms刷新一次
{
 if( TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET )
 {
      Test_Period(&Time4_Delta);//系统调度时间测试器
      NRF24L01_RC();//遥控器查询接收，非中端方式
 /*************加速度计、陀螺仪数字量采集***********/
      GET_MPU_DATA();//1.4ms
 /*************磁力计+气压计状态机更新***********/
#ifdef IMU_BOARD_GY86
      MS5611_StateMachine_20ms();
      HMC5883L_StateMachine();
#endif
#ifdef IMU_BOARD_NC686
      SPL06_001_StateMachine();
      Get_Mag_IST8310();
#endif
#ifdef IMU_BOARD_NC683
      FBM320_StateMachine();
      Get_Mag_IST8310();
#endif
 /*************姿态解算***********/
     AHRSUpdate_GraDes_Delay_Corretion(X_w_av,Y_w_av,Z_w_av,
                             X_g_av,Y_g_av,Z_g_av);
    HC_SR04_Cnt++;
    if(HC_SR04_Cnt>=15)//75ms
    {
      HC_SR04_Start();
      HC_SR04_Cnt=0;
    }
#if  (Optical_Enable==1)
    Optflow_Statemachine();
#endif
    SINS_Prepare();//得到载体相对导航系的三轴运动加速度
    if(High_Okay_flag==1)//高度惯导融合
    {
      Strapdown_INS_High();
      //Strapdown_INS_High_Kalman();
    }
    if(GPS_ISR_CNT>=300
    &&GPS_Update_finished==1)//GPS_PVT语句更新完毕后，开始解析
    {
      GPS_PVT_Parse();//GPS串口数据帧解析
      GPS_Update_finished=0;
      Set_GPS_Home();//设置Home点
    }
    if(GPS_Sate_Num>=9       //定位星数
          &&GPS_Quality<=3.0//定位信号质量,有效定位
            &&GPS_Home_Set==1)//Home点已设置
    {
      //Strapdown_INS_Horizontal();
      Filter_Horizontal();
      Bling_Set(&Light_4,2000,1000,0.5,0,GPIOA,WORK_LED,1);
    }

    Total_Control();//总控制器
    Control_Output();//控制量总输出
    if(PPM_Isr_Cnt==100)//PPM接收正常才进行传感器标定检测
    {
        Accel_Calibration_Check();//加速度标定检测
        Mag_Calibration_Check();//磁力计标定检测
    }
    Bling_Working(Bling_Mode);//状态指示灯

    Angle_Calculate();//加速度计欧拉角计算
    DMA_Send_StateMachine();//DMA传输，只使用山外上位机
    //ANO_SEND_StateMachine();//DMA传输，只使用ANO地面站
    //DMA_SEND_Tradeoff();//DMA传输，两路地面站机同时工作

    TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);
 }
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/