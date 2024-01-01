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
#include "SBUS.h"


#define SBUS_RANGE_MIN 200.0f
#define SBUS_RANGE_MAX 1800.0f

#define SBUS_TARGET_MIN 1000.0f
#define SBUS_TARGET_MAX 2000.0f

/* pre-calculate the floating point stuff as far as possible at compile time */
#define SBUS_SCALE_FACTOR ((SBUS_TARGET_MAX - SBUS_TARGET_MIN) / (SBUS_RANGE_MAX - SBUS_RANGE_MIN))
#define SBUS_SCALE_OFFSET (int)(SBUS_TARGET_MIN - (SBUS_SCALE_FACTOR * SBUS_RANGE_MIN + 0.5f))



//const float _sbusScale = 0.625749f; //Matlab拟合出的量程因子
//const float _sbusBias =  875.23353f;//Matlab拟合出的零偏
const float _sbusScale = SBUS_SCALE_FACTOR; //Matlab拟合出的量程因子
const float _sbusBias =  SBUS_SCALE_OFFSET;//Matlab拟合出的零偏


uint16_t SBUS_Channel[16]={0};
uint16_t SBUS_Channel_User[16]={0};
/***************************************************
函数名: void Process(uint8_t *raw,uint16_t *result)
说明:	SBUS数据解析
入口:	原始数据、解析数据
出口:	无
备注:	无
注释者：无名小哥
****************************************************/
void Process(uint8_t *raw,uint16_t *result)
{
  uint8_t bitsToRead=3; // bitsToRead表示需要从下一个字节中读取多少bit。规律：bitsToRead 每次总是增加 3
  uint8_t bitsToShift;
  uint8_t startByte=21;
  uint8_t channelId=15;
  do
  {
    result[channelId]=raw[startByte];
    if(bitsToRead<=8)
    {
      result[channelId]<<=bitsToRead;
      bitsToShift=8-bitsToRead;
      result[channelId]+=(raw[startByte-1]>>bitsToShift);
    }
    else
    {
      result[channelId]<<=8;
      result[channelId]+=raw[startByte-1];
      startByte--;
      bitsToRead-=8;
      result[channelId]<<=bitsToRead;
      bitsToShift=8-bitsToRead;
      result[channelId]+=(raw[startByte-1]>>bitsToShift);
    }
    result[channelId]&=0x7FF;
    channelId--;
    startByte--;
    bitsToRead+=3;
  }while(startByte>0);
}


uint8_t sbus_update_flag=0;
/***************************************************
函数名: bool SBUS_Linear_Calibration(void)
说明:	SBUS数据线性化处理
入口:	无
出口:	无
备注:	无
注释者：无名小哥
****************************************************/
bool SBUS_Linear_Calibration(void)
{
  for(uint16_t i=0;i<=25;i++)
  {
    if(COM5_Ringbuf.Ring_Buff[i]==0x0f&&COM5_Ringbuf.Ring_Buff[i+24]==0x00)
    {
      Process((uint8_t *)(&COM5_Ringbuf.Ring_Buff[i+1]),SBUS_Channel);
      for(uint8_t i = 0; i < 16; i++)//linear calibration
      {     
        SBUS_Channel_User[i] = (uint16_t)(SBUS_Channel[i] * _sbusScale+0.5f + _sbusBias);
        //SBUS_Channel_User[i] = (uint16_t)(1000*SBUS_Channel[i]/2048)+1000;
      }    
      memcpy(PPM_Databuf,SBUS_Channel_User,10*sizeof(uint16));//将SBUS解析完毕的数据拷贝到PPM数据区  
      sbus_update_flag=1;
      return true;
    }
  }
  sbus_update_flag=0;
  return false;
}



