/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               修改日期:2018/8/30
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "PX4FLOW.h"

void PX4FLOW_LPFButterworth(void);

static void IIC_delay(void)
{
  volatile int i = 5;	//7
  while (i)
    i--;
}
void SDA_OUT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SDA_IN(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//产生IIC起始信号
void IIC_Start(void)
{
  SDA_OUT();     //sda线输出
  SDA_H;
  IIC_delay();
  SCL_H;
  IIC_delay();
  SDA_L;//START:when CLK is high,DATA change form high to low
  IIC_delay();
  SCL_L;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void IIC_Stop(void)
{
  SDA_OUT();//sda线输出
  SCL_L;
  IIC_delay();
  SDA_L;//STOP:when CLK is high DATA change form low to high
  IIC_delay();
  SCL_H;
  IIC_delay();
  SDA_H;//发送I2C总线结束信号
  IIC_delay();
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
  u8 ucErrTime=0;
  SDA_IN();      //SDA设置为输入
  SDA_H;
  IIC_delay();
  SCL_H;
  IIC_delay();
  //SDA_IN();
  while(SDA_read)
  {
    ucErrTime++;
    if(ucErrTime>250)
    {
      IIC_Stop();
      return 1;
    }
  }
  SCL_L;//时钟输出0
  return 0;
}

//产生ACK应答
void IIC_Ack(void)
{
  SCL_L;
  IIC_delay();
  SDA_OUT();
  SDA_L;
  IIC_delay();
  SCL_H;
  //SDA_H;
  IIC_delay();
  SCL_L;
}
//不产生ACK应答
void IIC_NAck(void)
{
  SCL_L;
  IIC_delay();
  SDA_OUT();
  SDA_H;
  IIC_delay();
  SCL_H;
  IIC_delay();
  SCL_L;
}


//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(u8 txd)
{
  u8 t;
  SDA_OUT();
  SCL_L;;//拉低时钟开始数据传输
  for(t=0;t<8;t++)
  {
    //IIC_SDA=(txd&0x80)>>7;
    if((txd&0x80)>>7)
      SDA_H;
    else
      SDA_L;
    txd<<=1;
    IIC_delay();   //对TEA5767这三个延时都是必须的
    SCL_H;
    IIC_delay();
    SCL_L;
    IIC_delay();
  }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  SDA_IN();//SDA设置为输入
  for(i=0;i<8;i++ )
  {
    receive<<=1;
    SCL_L;
    IIC_delay();
    SCL_H;
    IIC_delay();
    if(SDA_read)  receive++;
  }
  if (!ack)
    IIC_NAck();//发送nACK
  else
    IIC_Ack(); //发送ACK
  return receive;
}


u8 flow_read_data(u8 addr,u8 reg,u8 len,u8 *buf)
{
  IIC_Start();
  IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令
  if(IIC_Wait_Ack())    //等待应答
  {
    IIC_Stop();
    return 1;
  }
  IIC_Send_Byte(reg);    //写寄存器地址
  IIC_Wait_Ack();        //等待应答
  IIC_Start();
  IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令
  IIC_Wait_Ack();        //等待应答
  while(len)
  {
    if(len==1)
      *buf=IIC_Read_Byte(0);//读数据,发送nACK
    else
      *buf=IIC_Read_Byte(1);        //读数据,发送ACK
    len--;
    buf++;
  }
  IIC_Stop();    //产生一个停止条件
  return 0;
}


// IIC读n字节数据
u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{
  IIC_Start();
  IIC_Send_Byte(SlaveAddress<<1);
  if(IIC_Wait_Ack())
  {
    IIC_Stop();
    return 1;
  }
  IIC_Send_Byte(REG_Address);
  IIC_Wait_Ack();
  IIC_Start();
  IIC_Send_Byte(SlaveAddress<<1 | 0x01);
  IIC_Wait_Ack();
  while(len)
  {
    if(len == 1)
    {
      *buf = IIC_Read_Byte(0);
    }
    else
    {
      *buf = IIC_Read_Byte(1);
    }
    buf++;
    len--;
  }
  IIC_Stop();
  return 0;
}

//读8位无符号数据
uint8_t     readu8_date(u8 addr,u8 reg)
{
  u8 buff[1];
  uint8_t date;
  IIC_Read_nByte(addr,reg,1,buff);
  date = buff[0];
  return date;
}
//读16位无符号数据
uint16_t    readu16_date(u8 addr,u8 reg)
{
  u8 buff[2];
  uint16_t date;
  IIC_Read_nByte(addr,reg,2,buff);
  date = buff[1] << 8 | buff[0];
  return date;
  
}

u8 buff[2];
//读16位有符号数据
int16_t     reads16_date(u8 addr,u8 reg)
{
  int16_t date;
  flow_read_data(addr,reg,2,buff);
  date = (((buff[1])<<8)|buff[0]);
  return date;
  ;
}
//读32位无符号数据
uint32_t    readu32_date(u8 addr,u8 reg)
{
  u8 buff[4];
  int16_t date;
  IIC_Read_nByte(addr,reg,2,buff);
  date = buff[3] << 24 | buff[2] << 16 | buff[1] << 8 | buff[0];
  return date;
}



i2c_frame PX4FLOW_Origion;
int16  a_P[10];
int16 b_P=0;
void PX4_Capture(void)
{
  PX4FLOW_Origion.gyro_x_rate=reads16_date(PX4FLOW_ADDR,GYRO_X_RATE);
  PX4FLOW_Origion.gyro_y_rate=reads16_date(PX4FLOW_ADDR,GYRO_Y_RATE);
  PX4FLOW_Origion.gyro_z_rate=reads16_date(PX4FLOW_ADDR,GYRO_Z_RATE);
  
  PX4FLOW_Origion.pixel_flow_x_sum=reads16_date(PX4FLOW_ADDR,FRAME_COUNT_SINCE_LAST_READOUT);
  
  PX4FLOW_Origion.flow_comp_m_x=reads16_date(PX4FLOW_ADDR,FLOW_COMP_M_X);//X方向速度,单位m/s
  PX4FLOW_Origion.flow_comp_m_y=reads16_date(PX4FLOW_ADDR,FLOW_COMP_M_Y);//Y方向速度,单位m/s
  PX4FLOW_Origion.ground_distance=reads16_date(PX4FLOW_ADDR,GROUND_DISTANCE1);//对地距离,单位mm
}


float  PX4FLOW_Data_LPF[3]={0};
uint16 PX4_State_Cnt=0;
float PX4FLOW_Vel_North=0,PX4FLOW_Vel_East=0;
float PX4FLOW_Pos_North=0,PX4FLOW_Pos_East=0;
uint16 PX4FLOW_Update_Flag=0;
void PX4_State_Machine_Capture(void)//20ms
{
  PX4_State_Cnt++;
  if(PX4_State_Cnt==1)
  {
    PX4FLOW_Origion.flow_comp_m_x=(int16)(0.1*reads16_date(PX4FLOW_ADDR,FLOW_COMP_M_X));//X方向速度,单位cm/s
  }
  else if(PX4_State_Cnt==2)
  {
    PX4FLOW_Origion.flow_comp_m_y=(int16)(0.1*reads16_date(PX4FLOW_ADDR,FLOW_COMP_M_Y));//Y方向速度,单位cm/s
  }
  else if(PX4_State_Cnt==3)
  {
    PX4FLOW_Origion.ground_distance=(int16)(0.1*reads16_date(PX4FLOW_ADDR,GROUND_DISTANCE1));//对地距离,单位cm
  }
  else if(PX4_State_Cnt==4)
  {
    //PX4FLOW_Origion.qual=reads16_date(PX4FLOW_ADDR,QUAL);
  }
  else if(PX4_State_Cnt==5)
  {
    PX4_State_Cnt=0;
    PX4FLOW_LPFButterworth();
    PX4FLOW_Vel_North=-PX4FLOW_Data_LPF[1]*Cos_Yaw-PX4FLOW_Data_LPF[0]*Sin_Yaw;
    PX4FLOW_Vel_East=PX4FLOW_Data_LPF[1]*Sin_Yaw+PX4FLOW_Data_LPF[0]*Cos_Yaw;
    PX4FLOW_Pos_North+=PX4FLOW_Vel_North*0.01;
    PX4FLOW_Pos_East+=PX4FLOW_Vel_East*0.01;
    PX4FLOW_Update_Flag=1;
  }
}


Butter_BufferData Butter_PX4FLOW[3];
Butter_Parameter PX4FLOW_LPF_Parameter={
  //100 2hz
  1,   -1.822694925196,    0.837181651256,
  0.003621681514929, 0.007243363029857, 0.003621681514929,
};


float PX4FLOW_LPF(float curr_inputer,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
  /* 加速度计Butterworth滤波 */
  Buffer->Input_Butter[2]=curr_inputer;/* 获取最新x(n) */
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
  return (Buffer->Output_Butter[2]);
}

void PX4FLOW_LPFButterworth()
{
  PX4FLOW_Data_LPF[0]=PX4FLOW_LPF(PX4FLOW_Origion.flow_comp_m_x,
                                  &Butter_PX4FLOW[0],
                                  &PX4FLOW_LPF_Parameter);
  PX4FLOW_Data_LPF[1]=PX4FLOW_LPF(PX4FLOW_Origion.flow_comp_m_y,
                                  &Butter_PX4FLOW[1],
                                  &PX4FLOW_LPF_Parameter);
  PX4FLOW_Data_LPF[2]=PX4FLOW_LPF(PX4FLOW_Origion.ground_distance,
                                  &Butter_PX4FLOW[2],
                                  &PX4FLOW_LPF_Parameter);
}



/**********************************************/
uint8 optical_flow_origion[6]={0};
struct optical{
  uint8 X_Delta_LSB;
  uint8 X_Delta_MSB;
  uint8 Y_Delta_LSB;
  uint8 Y_Delta_MSB;
  uint8 Cnt;
  uint8 Label;
  int16 X_Delta;
  int16 Y_Delta;
};
struct optical optical_data;
u8 optical_buf[6]={0};
int16_t JH_Test=0;
void OPTICAL_FLOW(void)
{
  //IIC_Read_nByte(0xD8,0x51,6,(u8 *)optical_buf);
  JH_Test=Single_ReadI2C(0x68,0x20);
  //IIC_Read_nByte(0x68,0x19,6,(u8 *)optical_buf);
  optical_data.X_Delta=optical_buf[1]<<8+optical_buf[0];
  optical_data.Y_Delta=optical_buf[3]<<8+optical_buf[2];
}



//BMP180校准系数
short AC1;
short AC2;
short AC3;
unsigned short AC4;
unsigned short AC5;
unsigned short AC6;
short B1;
short B2;
short MB;
short MC;
short MD;

u8 BMP180_ID=0;          //BMP180的ID
float True_Temp=0;       //实际温度,单位:℃
float True_Press=0;      //实际气压,单位:Pa
float True_Altitude=0;   //实际高度,单位:m
long int UT,UP;
#define BMP180_SlaveAddr 0xee   //BMP180的器件地址


/*从BMP180中读1个字节的数据*/
u8 BMP180_ReadOneByte(u8 ReadAddr)
{
  u8 temp = 0;
  temp=Single_ReadI2C(BMP180_SlaveAddr,ReadAddr);
  return (temp);
}

/*从BMP180中读2个字节的数据*/
short BMP180_ReadTwoByte(u8 ReadAddr)
{
  short temp;
  temp=Double_ReadI2C(BMP180_SlaveAddr,ReadAddr);
  return temp;
}



/*向BMP180的寄存器写一个字节的数据*/
void Write_OneByteToBMP180(u8 RegAdd, u8 Data)
{
  Single_WriteI2C(BMP180_SlaveAddr,RegAdd,Data);
}

/*读取BMP180的校准系数*/
void Read_CalibrationData(void)
{
  AC1 = BMP180_ReadTwoByte(0xaa);
  AC2 = BMP180_ReadTwoByte(0xac);
  AC3 = BMP180_ReadTwoByte(0xae);
  AC4 = BMP180_ReadTwoByte(0xb0);
  AC5 = BMP180_ReadTwoByte(0xb2);
  AC6 = BMP180_ReadTwoByte(0xb4);
  B1 = BMP180_ReadTwoByte(0xb6);
  B2 = BMP180_ReadTwoByte(0xb8);
  MB = BMP180_ReadTwoByte(0xba);
  MC = BMP180_ReadTwoByte(0xbc);
  MD = BMP180_ReadTwoByte(0xbe);
}

/*读BMP180没有经过补偿的温度值*/
long Get_BMP180UT(void)
{
  long UT;
  
  Write_OneByteToBMP180(0xf4,0x2e);       //write 0x2E into reg 0xf4
  delay_ms(10);                           //wait 4.5ms
  UT = BMP180_ReadTwoByte(0xf6);          //read reg 0xF6(MSB),0xF7(LSB)
  //printf(\"UT:%ld \r\n\",UT);
  
  return UT;
}



/*读BMP180没有经过补偿的压力值*/
long Get_BMP180UP(void)
{
  long UP=0;
  
  Write_OneByteToBMP180(0xf4,0x34);       //write 0x34 into reg 0xf4
  delay_ms(10);                           //wait 4.5ms
  UP = BMP180_ReadTwoByte(0xf6);
  UP &= 0x0000FFFF;
  //printf(\"UP:%ld \r\n\",UP);
  
  return UP;
}

#define OSS  3  //25.5
//#define OSS  2  //13.5
//#define OSS  1  //7.5
//#define OSS  0  //4.5
/*把未经过补偿的温度和压力值转换为时间的温度和压力值
*True_Temp:实际温度值,单位:℃
*True_Press:时间压力值,单位:Pa
*True_Altitude:实际海拔高度,单位:m
*/
void Convert_UncompensatedToTrue(long UT,long UP)
{
  long X1,X2,X3,B3,B5,B6,B7,T,P;
  unsigned long B4;
  
  X1 = ((UT-AC6)*AC5)>>15;
  X2 = ((long)MC<<11)/(X1+MD);
  B5 = X1+X2;
  T = (B5+8)>>4;
  True_Temp = T/10.0;
  //printf(\"Temperature:%.1f \r\n\",True_Temp);
  B6 = B5-4000;
  X1 = (B2*B6*B6)>>23;
  X2 = (AC2*B6)>>11;
  X3 = X1+X2;
  B3 = (((long)AC1*4+X3)+2)/4;
  X1 = (AC3*B6)>>13;
  X2 = (B1*(B6*B6>>12))>>16;
  X3 = ((X1+X2)+2)>>2;
  B4 = AC4*(unsigned long)(X3+32768)>>15;
  B7 = ((unsigned long)UP-B3)*(50000>>OSS);
  if (B7 < 0x80000000)
  {
    P = (B7*2)/B4;
  }
  else P=(B7/B4)*2;
  X1 = (P/256)*(P/256);
  X1 = (X1*3038)>>16;
  X2 = (-7357*P)>>16;
  P = P+((X1+X2+3791)>>4);
  True_Press = P;
  //True_Altitude = 44330*(1-pow((P/101325.0),(1.0/5.255)));
}

float Press_Offset=0;
uint8 Press_Offset_Okay=0;
float Get_Altitude(float baroPress)
{
  float Tempbaro=(float)(baroPress/Press_Offset)*1.0;
  True_Altitude = 4433000.0f * (1 - powf((float)(Tempbaro),0.190295f));
  return True_Altitude;
}

Butter_BufferData Butter_BMP180;
Butter_Parameter BMP180_LPF_Parameter={
  //25 2hz
  //1,   -1.307285028849,   0.4918122372226,
  //0.04613180209331,  0.09226360418663,  0.04613180209331,
  //25 1hz
  1,   -1.647459981077,   0.7008967811884,
  0.01335920002786,  0.02671840005571,  0.01335920002786
};
void BMP180_Convert_UncompensatedToTrue(long UT,long UP)
{
  int32_t X1,X2,X3,B3,B5,B6,T,P;
  unsigned long int B4,B7;
  int32_t tmp=0;
  X1=((int32_t)UT-AC6)*AC5>>15;
  X2=((int32_t)MC<<11)/(X1+MD);
  B5=X1+X2;
  T=(B5+8)>>4;
  True_Temp = T/10.0;
  
  
  B6=B5-4000;
  X1=(B2*(B6*B6>>12))>>11;
  X2=AC2*B6>>11;
  X3=X1+X2;
  
  tmp=AC1;
  tmp=(tmp*4+X3)<<OSS;
  B3=(tmp+2)/4;
  //B3=((AC1*4+X3)+2)<<2;
  X1=AC3*B6>>13;
  X2=(B1*(B6*B6>>12))>>16;
  X3=((X1+X2)+2)>>2;
  B4=AC4*(unsigned long int)(X3+32768)>>15;
  B7=((unsigned long int)UP-B3)*(50000>>OSS);
  if (B7 < 0x80000000)
  {
    P = (B7*2)/B4;
  }
  else P=(B7/B4)*2;
  X1 = (P>>8)*(P>>8);
  X1 = (X1*3038)>>16;
  X2 = (-7357*P)>>16;
  P = P+((X1+X2+3791)>>4);
  //True_Press = P;
  True_Press=PX4FLOW_LPF(P,&Butter_BMP180,&BMP180_LPF_Parameter);
  
  //True_Altitude = 44330*(1-pow((P/101325.0),(1.0/5.255)));
}





long int UT,UP;
uint8 BMP180_Buf[3]={0};
int Press_Ready_Cnt=0;
void BMP180_StateMachine()
{
  static int BMP180_Cnt=0;
  
  BMP180_Cnt++;
  if(BMP180_Cnt==1)
  {
    Write_OneByteToBMP180(0xf4,0x2e);       //write 0x2E into reg 0xf4
  }
  else if(BMP180_Cnt==3)
  {
    UT = BMP180_ReadTwoByte(0xf6);          //read reg 0xF6(MSB),0xF7(LSB)
    Write_OneByteToBMP180(0xf4,0x34+(OSS<<6));//)OSS=3  25.5ms
  }
  else if(BMP180_Cnt==10)
  {
    UP=Three_ReadI2C(BMP180_SlaveAddr,0xf6);
    UP = (unsigned long int)(UP>>(8-OSS));
    
    BMP180_Convert_UncompensatedToTrue(UT,UP);
    BMP180_Cnt=0;
    
    
    if(Press_Ready_Cnt<=100) Press_Ready_Cnt++;
    
    if(Press_Ready_Cnt==100)
    {
      Press_Offset=True_Press;
      Press_Offset_Okay=1;
      if(Press_Offset_Okay==1)
      {
        True_Altitude=Get_Altitude(True_Press);
      }
      
      NamelessQuad.Position[_YAW]=True_Altitude;
      High_Okay_flag=1;
    }
    if(Press_Offset_Okay==1)
    {
      True_Altitude=Get_Altitude(True_Press);
    }
  }
}

