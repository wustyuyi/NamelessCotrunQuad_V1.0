/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ��Դ����������ѣ������ߵ���ʷ�Ѿ�֤�����ڹ�����������£���������Ŀ�Դ������������˰����ߣ��Է��ز�����
								Ŀ���Ƶķ�ʽ�в�ͨ���õĿ�Դ��Ŀ��Ҫ��רְ��Ա�����ۺ�����ְ��ֽ�ѧ��ͳ���û�����������ʵ������ɶԲ�
								Ʒ��һ�δ���������������������ۺϿ��ǣ������ɿؿ�Դ�����У������������˾���漤��ܴ��룬�汾������ʵ��
								���ܣ����ڹ�˾��Ʒ���������������Ӱ��ͻ�ѧϰ���������ȫ�����Ÿ��ͻ�ѧϰ���ͻ���ֲ�Ͷ��ο��������뱣����
								���Ȩ��
-----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------
*                                                 Ϊʲôѡ���������£�
*                                         �ж����ļ۸�������׵Ŀ�Դ�ɿأ�
*                                         ����ҵ������֮������µ��ۺ����
*                                         ׷�����û����飬��Ч����ѧϰ֮·��
*                                         ���²��ٹµ�������������տ�Դ�߶ȣ�
*                                         ��Ӧ���ҷ�ƶ���٣��ٽ��������ƹ�ƽ��
*                                         ��ʱ���ܶ�����ʣ����������˹�ͬ�塣 
-----------------------------------------------------------------------------------------------------------------------
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��2��Ⱥ465082224��1��Ⱥ540707961����Ա������
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �������¹����׿�TI��Դ�ɿ���Ƴ��ԡ�֪��ר��:https://zhuanlan.zhihu.com/p/54471146
*               �޸�����:2019/11/27                    
*               �汾���۷���PRO����WisdomPilot_Pro_V1.0.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2019-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"

//��ȡSD����ָ�����������ݣ���ͨ������1���
//sec�����������ַ���
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);						//�����ڴ�
	if(SD_ReadDisk(buf,sec,1)==0)	//��ȡ0����������
	{	
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//��ӡsec��������    	   
		printf("\r\nDATA ENDED\r\n");
	}
	myfree(buf);//�ͷ��ڴ�	
}

u32 totald,freed;
Sensor_Okay_Flag Sensor_Init_Flag;
/***************************************************
������: void HardWave_Init(void)
˵��:	����Ӳ����Դ��ʼ��
���:	��
����:	��
��ע:	�ɿ��ڲ���Դ�������ʼ��
ע���ߣ�����С��
****************************************************/
void HardWave_Init(void)
{
	System_Init(72);     			//оƬʱ�ӳ�ʼ��	
	USART1_Init(115200); 			//�����ڳ�ʼ��		
  Bling_Init();       		  //ָʾ�ơ�����IO��ʼ��	
	Soft_I2C_Init();     		  //���ģ��I2C��ʼ��
  Key_Init();         		  //������ʼ��
  PPM_Init();          		  //PPMң�������ճ�ʼ��
  HC_SR04_Init();      		  //��������ʼ��
  PWM_Init();          		  //PWM��ʼ����TIM3��TIM4	
#if (SD_Log_Enable)
	delay_ms(1000);		
	while(SD_Init())		//��ⲻ��SD��
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
	u32 sd_size=SD_GetSectorCount();//�õ�������
	printf("Sdcard Size is %d M",(sd_size>>11));	
	mem_init();							//��ʼ���ڴ��
	SD_Read_Sectorx(0);
	exfuns_init();
	f_mount(fs,"0:",1);//����SD��
	
	f_mkdir("0:/nametech");
	f_open(file,"0:/nametech/imu.txt", FA_CREATE_NEW|FA_OPEN_ALWAYS| FA_WRITE);//4ms
	f_close(file);
#endif
  Init_MPU6050();      				 //MPU6050��ʼ�������ѡ����ò���Ƶ�ʡ����̵�
  delay_ms(500);
  IMU_Calibration(); 			   	 //��������ƫ�궨
  HMC5883L_Initial();	         //HMC5883��ʼ��
	QMC5883L_Init();             //QMC5883��ʼ��
  IST8310_Init();			         //������IST8310��ʼ��
  SPL06_Init();				         //��ѹ��SPL01_001��ʼ��
  /*******************IMU��ʼ������*************************/
  delay_ms(500);
  Mag_LS_Init();	       			 //��������С���˷�������ϳ�ʼ��
  Parameter_Init();            //������������ʼ��
  NCQ_Quad_Init();             //��ʼ��Ԫ����ʼ��
  Butterworth_Parameter_Init();//�˲���������ʼ��
  RC_Calibration_Trigger();    //ң�����궨������ʼ��
  LCD_CLS();                   //����
  Set_GPS_USART();             //�ϵ���ѯ�Զ�����GPS
  USART3_Init(115200);         //�����ڳ�ʼ������OPENMV
  OpticalFlow_Init();          //LC306������������ʼ��
  USART4_Init(19200);          //����4��������������
  USART5_Init();               //����5
  PID_Paramter_Init_With_Flash();//PID��������ʼ��������ͨ������վ�޸Ĳ���//Total_PID_Init();PID��������ʼ����ֻ��ͨ�������޸Ĳ���
  Horizontal_Calibration_Init();//ˮƽ�궨������ʼ��
	Other_Parameter_Init();      //����������ʼ��
	ADRC_Init(&ADRC_Pitch_Controller,&ADRC_Roll_Controller);//�Կ��ſ�������ʼ��
	Temperature_Ctrl_Init();     //�¿�ϵͳ��ʼ��
	Simulation_PWM_Init();       //ģ��PWM��ʼ��   
  Chip_ADC_Init();             //оƬAD����ʼ��
  SDK_Init();                  //�ɿ�SDK��ʼ��
  TIM2_Configuration_Cnt();    //TIM2�����ʱ��ʱ��
  Timer1_Configuration();      //TIM1������ȶ�ʱ��
  NVIC_Configuration();        //�ж����ȼ�����
}


/***************************************************
������: void NVIC_Configuration(void)
˵��:	�ж����ȼ�����
���:	��
����:	��
��ע:	ϵͳ�ж�ʱ�����������ʱ����ȫ�����Թ��������
        ȷ�������˶����Ƚ���        
ע���ߣ�����С��
****************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;//����NVIC��ʼ���ṹ��
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ����2������μ�misc.h line80 
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;////GPS���ݽ����ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
  
	//PPM���ջ�
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    
	
  //������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  //�ɿ�ϵͳ��ʱ��
  NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn ;//������ʱ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
	//SBUS�������� 
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //�жϺţ�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ���
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //��Ӧ���ȼ���
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    
	  
  //������
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
   
  //���ô��ڹ���ʹ�� 
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	
  //-----NRF24L01�����ж�-----//
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  //�ɿ�������ȶ�ʱ��
  NVIC_InitStructure.NVIC_IRQChannel=TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



/***************************************************
������: void NCQ_Init(void)
˵��:	ϵͳ��ʼ��
���:	��
����:	��
��ע:	���ȶ�ȡ�ض�Ƭ����־λ�����߽���
        ���У׼ģʽ����������ʼ��        
ע���ߣ�����С��
****************************************************/
void NCQ_Init(void)
{
  ReadFlashParameterOne(ESC_CALIBRATION_FLAG,&ESC_Calibration_Flag);
  if(ESC_Calibration_Flag==1)
  {
    ESC_HardWave_Init();//ֻ��ʼ��У׼����ı�Ҫ��Դ 
  }
  else
  {
    HardWave_Init();//�ɿذ��ڲ���Դ����������ʼ��
  }
}

