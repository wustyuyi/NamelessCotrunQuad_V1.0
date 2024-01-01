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
#include "Filter.h"

//-----Butterworth变量 Matlab fdatool设计-----//
//设计方法见博客：http://blog.csdn.net/u011992534/article/details/73743955
//-----Butterworth变量-----//
Butter_Parameter Butter_80HZ_Parameter_Acce,Butter_60HZ_Parameter_Acce,Butter_51HZ_Parameter_Acce,
Butter_30HZ_Parameter_Acce,Butter_20HZ_Parameter_Acce,Butter_15HZ_Parameter_Acce,
Butter_10HZ_Parameter_Acce,Butter_5HZ_Parameter_Acce,Butter_2HZ_Parameter_Acce;
Butter_BufferData Butter_Buffer[3];
Butter_BufferData Butter_Buffer_Feedback[3];
Butter_BufferData Butter_Buffer_SINS[3];
Butter_Parameter Butter_5HZ_Parameter_RC;
/****************************************
Butterworth低通滤波器参数初始化：http://blog.csdn.net/u011992534/article/details/73743955
***************************************/
void Butterworth_Parameter_Init(void)
{
  Set_Cutoff_Frequency(Sampling_Freq, 80,&Butter_80HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 60,&Butter_60HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 51,&Butter_51HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 30,&Butter_30HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 20,&Butter_20HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 15,&Butter_15HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 10,&Butter_10HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 5 ,&Butter_5HZ_Parameter_Acce);
  Set_Cutoff_Frequency(Sampling_Freq, 2 ,&Butter_2HZ_Parameter_Acce);
	Set_Cutoff_Frequency(50, 10 ,&Butter_5HZ_Parameter_RC);
}

/*************************************************
函数名:	float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
说明:	加速度计低通滤波器
入口:	float curr_input 当前输入加速度计,滤波器参数，滤波器缓存
出口:	无
备注:	2阶Butterworth低通滤波器
*************************************************/
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  /* 加速度计Butterworth滤波 */
  /* 获取最新x(n) */
  Buffer->Input_Butter[2]=curr_input;
    /* Butterworth滤波 */
    Buffer->Output_Butter[2]=
      Parameter->b[0] * Buffer->Input_Butter[2]
        +Parameter->b[1] * Buffer->Input_Butter[1]
          +Parameter->b[2] * Buffer->Input_Butter[0]
            -Parameter->a[1] * Buffer->Output_Butter[1]
              -Parameter->a[2] * Buffer->Output_Butter[0];
  /* x(n) 序列保存 */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n) 序列保存 */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
	
  for(uint16_t i=0;i<3;i++)
	{
	  if(isnan(Buffer->Output_Butter[i])==1) 
			Buffer->Output_Butter[i]=curr_input;
		if(isnan(Buffer->Input_Butter[i])==1)  
			Buffer->Input_Butter[i]=curr_input;
	}
  return Buffer->Output_Butter[2];
}

Butter_Parameter Notch_Filter_Parameter_55hz={
  //200hz---55hz-5hz  采样-陷波频率-带宽
  1,   0.3008218748187,   0.9229897627825,
  0.9614948813912,   0.3008218748187,   0.9614948813912
};
Butter_Parameter Notch_Filter_Parameter_60hz={
  //200hz---60hz-5hz  采样-陷波频率-带宽
  1,   0.5942365167088,   0.9229897627825,
  0.9614948813912,   0.5942365167088,   0.9614948813912
};
Butter_Parameter Notch_Filter_Parameter_65hz={
  //200hz---65hz-5hz  采样-陷波频率-带宽
  1,   0.8730190833996,   0.9229897627825,
  0.9614948813912,   0.8730190833996,   0.9614948813912
};

Butter_Parameter Notch_Filter_Parameter_75hz={
  //200hz---75hz-50hz  采样-陷波频率-带宽
  1,   0.9372808715784,   0.3255153203391,
  0.6627576601696,   0.9372808715784,   0.6627576601696
};
Notch_Filter_BufferData  Notch_Filter_Buffer;
/************************************************/
float Notch_Filter(float curr_input,Notch_Filter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  float temp=0;
  /* 获取最新x(n) */ 
  Buffer->Output_Butter[0]= Parameter->a[0]*curr_input
    -Parameter->a[1]*Buffer->Output_Butter[1]
      -Parameter->a[2]*Buffer->Output_Butter[2];
  /* 计算陷波滤波器输出 */
  temp=Parameter->b[0]*Buffer->Output_Butter[0]
    +Parameter->b[1]*Buffer->Output_Butter[1]
      +Parameter->b[2]*Buffer->Output_Butter[2];
  /* y(n) 序列保存 */
  Buffer->Output_Butter[2]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[0]; 	
  return temp;
}


Butter_Parameter Bandstop_Filter_Parameter_30_98={
  //200hz---30hz-98hz  采样-阻带
  1,   0.6270403082828,  -0.2905268567319,
  0.354736571634,   0.6270403082828,    0.354736571634
};
Butter_Parameter Bandstop_Filter_Parameter_30_94={
  //200hz---30hz-94hz  采样-阻带
  1,   0.5334540355829,  -0.2235264828971,
  0.3882367585514,   0.5334540355829,   0.3882367585514
};
Butter_BufferData  Bandstop_Filter_Buffer[2];
float BPF_Butterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  /* 加速度计Butterworth滤波 */
  /* 获取最新x(n) */
  Buffer->Input_Butter[2]=curr_input;
  /* Butterworth滤波 */
  Buffer->Output_Butter[2]=
    Parameter->b[0] * Buffer->Input_Butter[2]
      +Parameter->b[1] * Buffer->Input_Butter[1]
        +Parameter->b[2] * Buffer->Input_Butter[0]
          -Parameter->a[1] * Buffer->Output_Butter[1]
            -Parameter->a[2] * Buffer->Output_Butter[0];
  /* x(n) 序列保存 */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n) 序列保存 */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
	for(uint16_t i=0;i<3;i++)
	{
	  if(isnan(Buffer->Output_Butter[i])==1) 
			Buffer->Output_Butter[i]=curr_input;
		if(isnan(Buffer->Input_Butter[i])==1)  
			Buffer->Input_Butter[i]=curr_input;
	}
  return Buffer->Output_Butter[2];
}



float Acce_Control[3]={0};
float Acce_Control_Feedback[3]={0};
float Acce_SINS[3]={0};
void Acce_Control_Filter()
{
  /**********************惯导加速度LPF_60hz**************************/
  Vector3f Body_Frame,Earth_Frame;
  
  Acce_SINS[0]=LPButterworth(X_Origion,
                             &Butter_Buffer_SINS[0],&Butter_15HZ_Parameter_Acce);//30
  Acce_SINS[1]=LPButterworth(Y_Origion,
                             &Butter_Buffer_SINS[1],&Butter_15HZ_Parameter_Acce);
  Acce_SINS[2]=LPButterworth(Z_Origion,
                             &Butter_Buffer_SINS[2],&Butter_15HZ_Parameter_Acce);//用作惯导融合的加速度计量
  
  Acce_Control[0]=LPButterworth(X_Origion,
                                &Butter_Buffer[0],&Butter_51HZ_Parameter_Acce);
  Acce_Control[1]=LPButterworth(Y_Origion
                                ,&Butter_Buffer[1],&Butter_51HZ_Parameter_Acce);
  Acce_Control[2]=LPButterworth(Z_Origion
                                ,&Butter_Buffer[2],&Butter_51HZ_Parameter_Acce);
  
  Body_Frame.x=Acce_Control[0];
  Body_Frame.y=Acce_Control[1];
  Body_Frame.z=Acce_Control[2];
  Vector_From_BodyFrame2EarthFrame(&Body_Frame,&Earth_Frame);
  FilterAfter_NamelessQuad.Acceleration[_YAW]=Earth_Frame.z;
  FilterAfter_NamelessQuad.Acceleration[_PITCH]=Earth_Frame.x;
  FilterAfter_NamelessQuad.Acceleration[_ROLL]=Earth_Frame.y;
  FilterAfter_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
  FilterAfter_NamelessQuad.Acceleration[_YAW]-=AcceGravity;
  FilterAfter_NamelessQuad.Acceleration[_YAW]*=100;//加速度cm/s^2
  FilterAfter_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
  FilterAfter_NamelessQuad.Acceleration[_PITCH]*=100;//加速度cm/s^2
  FilterAfter_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
  FilterAfter_NamelessQuad.Acceleration[_ROLL]*=100;//加速度cm/s^2
  
  /**********************加速度反馈量LPF_5hz*****************************************************************************/
  Acce_Control_Feedback[0]=LPButterworth(X_Origion,
                                         &Butter_Buffer_Feedback[0],&Butter_5HZ_Parameter_Acce);//用作加速度反馈的加速度计量  15
  Acce_Control_Feedback[1]=LPButterworth(Y_Origion
                                         ,&Butter_Buffer_Feedback[1],&Butter_5HZ_Parameter_Acce);
  Acce_Control_Feedback[2]=LPButterworth(Z_Origion
                                         ,&Butter_Buffer_Feedback[2],&Butter_5HZ_Parameter_Acce);
//  Acce_Control_Feedback[0]=X_Origion;
//  Acce_Control_Feedback[1]=Y_Origion;
//  Acce_Control_Feedback[2]=Z_Origion;
  /******************如果定高时，发现飞机有时莫名抽、抖，可以把加速度反馈滤波截止频率降低，APM飞控用的Fc=2Hz******************/
  
  Body_Frame.x=Acce_Control_Feedback[0];
  Body_Frame.y=Acce_Control_Feedback[1];
  Body_Frame.z=Acce_Control_Feedback[2];
  Vector_From_BodyFrame2EarthFrame(&Body_Frame,&Earth_Frame);
  Filter_Feedback_NamelessQuad.Acceleration[_YAW]=Earth_Frame.z;
  Filter_Feedback_NamelessQuad.Acceleration[_PITCH]=Earth_Frame.x;
  Filter_Feedback_NamelessQuad.Acceleration[_ROLL]=Earth_Frame.y;
  Filter_Feedback_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
  Filter_Feedback_NamelessQuad.Acceleration[_YAW]-=AcceGravity;
  Filter_Feedback_NamelessQuad.Acceleration[_YAW]*=100;//加速度cm/s^2
  Filter_Feedback_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
  Filter_Feedback_NamelessQuad.Acceleration[_PITCH]*=100;//加速度cm/s^2
  Filter_Feedback_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
  Filter_Feedback_NamelessQuad.Acceleration[_ROLL]*=100;//加速度cm/s^2
}

// discrete low pass filter, cuts out the
// high frequency noise that can drive the controller crazy
//derivative = _last_derivative + _d_lpf_alpha * (derivative - _last_derivative);
float set_lpf_alpha(int16_t cutoff_frequency, float time_step)
{
  // calculate alpha
  float lpf_alpha;
  float rc = 1/(2*PI*cutoff_frequency);
  lpf_alpha = time_step / (time_step + rc);
  return lpf_alpha;
}
//https://blog.csdn.net/sszhouplus/article/details/43113505
//https://blog.csdn.net/shengzhadon/article/details/46784509
//https://blog.csdn.net/shengzhadon/article/details/46791903
//https://blog.csdn.net/shengzhadon/article/details/46803401
/************************************************************************/
void Set_Cutoff_Frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF)
{
  float fr = sample_frequent / cutoff_frequent;
  float ohm = tanf(M_PI_F / fr);
  float c = 1.0f + 2.0f * cosf(M_PI_F / 4.0f) * ohm + ohm * ohm;
  if (cutoff_frequent <= 0.0f) {
    // no filtering
    return;
  }
  LPF->b[0] = ohm * ohm / c;
  LPF->b[1] = 2.0f * LPF->b[0];
  LPF->b[2] = LPF->b[0];
  LPF->a[0]=1.0f;
  LPF->a[1] = 2.0f * (ohm * ohm - 1.0f) / c;
  LPF->a[2] = (1.0f - 2.0f * cosf(M_PI_F / 4.0f) * ohm + ohm * ohm) / c;
}

