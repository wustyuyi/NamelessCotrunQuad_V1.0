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

//读取SD卡的指定扇区的内容，并通过串口1输出
//sec：扇区物理地址编号
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);						//申请内存
	if(SD_ReadDisk(buf,sec,1)==0)	//读取0扇区的内容
	{	
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//打印sec扇区数据    	   
		printf("\r\nDATA ENDED\r\n");
	}
	myfree(buf);//释放内存	
}

u32 totald,freed;
Sensor_Okay_Flag Sensor_Init_Flag;
/***************************************************
函数名: void HardWave_Init(void)
说明:	板载硬件资源初始化
入口:	无
出口:	无
备注:	飞控内部资源、外设初始化
注释者：无名小哥
****************************************************/
void HardWave_Init(void)
{
	System_Init(72);     			//芯片时钟初始化	
	USART1_Init(115200); 			//主串口初始化		
  Bling_Init();       		  //指示灯、测试IO初始化	
	Soft_I2C_Init();     		  //软件模拟I2C初始化
  Key_Init();         		  //按键初始化
  PPM_Init();          		  //PPM遥控器接收初始化
  HC_SR04_Init();      		  //超声波初始化
  PWM_Init();          		  //PWM初始化—TIM3、TIM4	
#if (SD_Log_Enable)
	delay_ms(1000);		
	while(SD_Init())		//检测不到SD卡
	{
		LEDR=!LEDR;
		delay_ms(500);
		LEDR=!LEDR;		
		LEDG=!LEDG;
		delay_ms(500);
		LEDG=!LEDG;
		LEDB=!LEDB;
		delay_ms(500);
		LEDB=!LEDB;		
	}
	u32 sd_size=SD_GetSectorCount();//得到扇区数
	printf("Sdcard Size is %d M",(sd_size>>11));	
	mem_init();							//初始化内存池
	SD_Read_Sectorx(0);
	exfuns_init();
	f_mount(fs,"0:",1);//挂载SD卡
	
	f_mkdir("0:/nametech");
	f_open(file,"0:/nametech/imu.txt", FA_CREATE_NEW|FA_OPEN_ALWAYS| FA_WRITE);//4ms
	f_close(file);
#endif
  Init_MPU6050();      				 //MPU6050初始化、唤醒、设置采样频率、量程等
  delay_ms(500);
  IMU_Calibration(); 			   	 //陀螺仪零偏标定
  HMC5883L_Initial();	         //HMC5883初始化
	QMC5883L_Init();             //QMC5883初始化
  IST8310_Init();			         //磁力计IST8310初始化
  SPL06_Init();				         //气压计SPL01_001初始化
  /*******************IMU初始化结束*************************/
  delay_ms(500);
  Mag_LS_Init();	       			 //磁力计最小二乘法球面拟合初始化
  Parameter_Init();            //控制器参数初始化
  NCQ_Quad_Init();             //初始四元数初始化
  Butterworth_Parameter_Init();//滤波器参数初始化
  RC_Calibration_Trigger();    //遥控器标定参数初始化
  LCD_CLS();                   //清屏
  Set_GPS_USART();             //上电轮询自动配置GPS
  USART3_Init(115200);         //副串口初始化解析OPENMV
  OpticalFlow_Init();          //LC306光流传感器初始化
  USART4_Init(19200);          //串口4、解析光流数据
  USART5_Init();               //串口5
  PID_Paramter_Init_With_Flash();//PID控制器初始化，可以通过地面站修改参数//Total_PID_Init();PID控制器初始化，只能通过程序修改参数
  Horizontal_Calibration_Init();//水平标定参数初始化
	Other_Parameter_Init();      //其它参数初始化
	ADRC_Init(&ADRC_Pitch_Controller,&ADRC_Roll_Controller);//自抗扰控制器初始化
	Temperature_Ctrl_Init();     //温控系统初始化
	Simulation_PWM_Init();       //模拟PWM初始化   
  Chip_ADC_Init();             //芯片AD检测初始化
  SDK_Init();                  //飞控SDK初始化
  TIM2_Configuration_Cnt();    //TIM2程序计时定时器
  Timer1_Configuration();      //TIM1任务调度定时器
  NVIC_Configuration();        //中断优先级设置
}


/***************************************************
函数名: void NVIC_Configuration(void)
说明:	中断优先级定义
入口:	无
出口:	无
备注:	系统中断时间在整体设计时，已全部测试过最大开销，
        确保程序运动的稳健性        
注释者：无名小哥
****************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级组别2，具体参见misc.h line80 
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;////GPS数据接收中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
  
	//PPM接收机
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    
	
  //超声波
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  //飞控系统定时器
  NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn ;//计数定时器
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
	//SBUS解析串口 
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //中断号；
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级；
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //响应优先级；
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    
	  
  //副串口
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
   
  //备用串口光流使用 
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	
  //-----NRF24L01数据中断-----//
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  //飞控任务调度定时器
  NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



/***************************************************
函数名: void NCQ_Init(void)
说明:	系统初始化
入口:	无
出口:	无
备注:	首先读取特定片区标志位，决策进入
        电调校准模式还是正常初始化        
注释者：无名小哥
****************************************************/
void NCQ_Init(void)
{
  ReadFlashParameterOne(ESC_CALIBRATION_FLAG,&ESC_Calibration_Flag);
  if(ESC_Calibration_Flag==1)
  {
    ESC_HardWave_Init();//只初始化校准电调的必要资源 
  }
  else
  {
    HardWave_Init();//飞控板内部资源、相关外设初始化
  }
}

