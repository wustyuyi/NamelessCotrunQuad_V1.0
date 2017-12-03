#include "Headfile.h"
#include "MS5611.h"
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
float Baro=0;
volatile float Altitude=0;
#define RATE   1
#define size_t	 u8
#define uint8_t  u8
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
//50hz  2hz
const static float b_baro_pressure[3]={0.01335920002786,  0.02671840005571,  0.01335920002786};
const static float a_baro_pressure[3]={1,   -1.647459981077,   0.7008967811884};
float LPButter_BaroAlt(float curr_input)
{
	static float input[3];
	static float output[3];

	/* 气压计高度Butterworth滤波 */
	/* 获取最新x(n) */
	input[2] = curr_input;

	/* Butterworth滤波 */
	output[2] = b_baro_pressure[0] * input[2] + b_baro_pressure[1] * input[1]
	+ b_baro_pressure[2] * input[0] - a_baro_pressure[1] * output[1] - a_baro_pressure[2] * output[0];

	/* x(n) 序列保存 */
	input[0] = input[1];
	input[1] = input[2];
	/* y(n) 序列保存 */
	output[0] = output[1];
	output[1] = output[2];

	return output[2];
}
// ************************************************************************************************************
// I2C general functions
// ************************************************************************************************************
static void i2c_delay(void)
{
//vu8 d=RATE;
// while(d--);
}


void i2c_write(uint8_t data ) {
   u8 i;
   SDA_IOOUT();
   for(i=0;i<8;i++)
   {
    if (data & 0x80)
    SDA_H;
    else
    SDA_L;

    data<<=1;
    i2c_delay();
    SCL_H;
    i2c_delay();
    SCL_L;
    i2c_delay();
   }
   SCL_H;
   i2c_delay();
   SCL_L;
   i2c_delay();
}
void i2c_rep_start(uint8_t address) {
  SDA_IOOUT();
  SDA_H; 									 // send REPEAT START condition
  SCL_H;
  i2c_delay();
  SDA_L;
  i2c_delay();
  SCL_L;
  i2c_write(address);                              // send device address

}

void i2c_stop(void) {

	SDA_IOOUT();
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	i2c_delay();
	SCL_H;
	i2c_delay();
	SDA_H;//发送I2C总线结束信号
	i2c_delay();
}



uint8_t i2c_read(uint8_t ack) {

  uint8_t r=0,i;

	SDA_IOOUT();
	SDA_H;
	i2c_delay();
	SDA_IOIN();
    for(i=0;i<8;i++ )
	{

		SCL_H;
		i2c_delay();
        r<<=1;
        if(SDA_read)r++;
		SCL_L;
        i2c_delay();
    }
  SDA_IOOUT();
  if (!ack)
  {
  	SDA_H;
	i2c_delay();
	SCL_H;
	i2c_delay();
	SCL_L;
	i2c_delay();
  	i2c_stop() ;
  }
  else
  {
  	SDA_L;
	i2c_delay();
	SCL_H;
	i2c_delay();
	SCL_L;
	i2c_delay();
  }
  return r;
}

uint8_t i2c_readAck(void) {
  return i2c_read(1);
}

uint8_t i2c_readNak(void) {
  return i2c_read(0);
}



size_t i2c_read_to_buf(uint8_t add, void *buf, size_t size) {
  size_t bytes_read = 0;
  uint8_t *b = (uint8_t*)buf;

  i2c_rep_start((add<<1) | 1);  // I2C read direction

  while (size--) {
    /* acknowledge all but the final byte */
    *b++ = i2c_read(size > 0);
    /* TODO catch I2C errors here and abort */
    bytes_read++;
  }
  return bytes_read;
}

size_t i2c_read_reg_to_buf(uint8_t add, uint8_t reg, void *buf, size_t size) {
  i2c_rep_start(add<<1); // I2C write direction
  i2c_write(reg);        // register selection
  return i2c_read_to_buf(add, buf, size);
}

/* transform a series of bytes from big endian to little
   endian and vice versa. */
void swap_endianness(void *buf, size_t size) {
  /* we swap in-place, so we only have to
  * place _one_ element on a temporary tray
  */
  uint8_t tray;
  uint8_t *from;
  uint8_t *to;
  /* keep swapping until the pointers have assed each other */
  for (from = (uint8_t*)buf, to = &from[size-1]; from < to; from++, to--) {
    tray = *from;
    *from = *to;
    *to = tray;
  }
}


void i2c_writeReg(uint8_t add, uint8_t reg, uint8_t val) {
  i2c_rep_start(add<<1); // I2C write direction
  i2c_write(reg);        // register selection
  i2c_write(val);        // value to write in register
  i2c_stop();
}

uint8_t i2c_readReg(uint8_t add, uint8_t reg) {
  uint8_t val;
  i2c_read_reg_to_buf(add, reg, &val, 1);
  return val;
}
// ************************************************************************************************************
// I2C Barometer MS561101BA
// ************************************************************************************************************
//
// specs are here: http://www.meas-spec.com/downloads/MS5611-01BA03.pdf
// useful info on pages 7 -> 12
#define uint16_t   u16
#define uint32_t   u32
#define uint64_t   unsigned long long
#define int16_t   s16
#define int32_t   s32
#define int64_t   signed long long

#define  delay(t)   delay_ms(t)

#define MS561101BA_ADDRESS 0x77 //CBR=0 0xEE I2C address when pin CSB is connected to LOW (GND)
//#define MS561101BA_ADDRESS 0x76 //CBR=1 0xEC I2C address when pin CSB is connected to HIGH (VCC)
// registers of the device
#define MS561101BA_PRESSURE    0x40
#define MS561101BA_TEMPERATURE 0x50
#define MS561101BA_RESET       0x1E

// OSR (Over Sampling Ratio) constants
#define MS561101BA_OSR_256  0x00
#define MS561101BA_OSR_512  0x02
#define MS561101BA_OSR_1024 0x04
#define MS561101BA_OSR_2048 0x06
#define MS561101BA_OSR_4096 0x08

//#define OSR MS561101BA_OSR_1024//MS561101BA_OSR_4096
#define OSR MS561101BA_OSR_4096//MS561101BA_OSR_4096

#define BARO_TAB_SIZE   21

//uint32_t currentTime = 0;
int32_t baroPressure;
int32_t baroTemperature;
int32_t baroPressureSum;


static struct {
  // sensor registers from the MS561101BA datasheet
  uint16_t c[7];
  union {uint32_t val; uint8_t raw[4]; } ut; //uncompensated T
  union {uint32_t val; uint8_t raw[4]; } up; //uncompensated P
  uint8_t  state;
  uint32_t deadline;
} ms561101ba_ctx;

void i2c_MS561101BA_reset(){
  i2c_writeReg(MS561101BA_ADDRESS, MS561101BA_RESET, 0);
}

void i2c_MS561101BA_readCalibration(){
  union {uint16_t val; uint8_t raw[2]; } datat;
  uint8_t i;
  for(i=0;i<6;i++)
  {
    i2c_rep_start(MS561101BA_ADDRESS<<1);
    i2c_write(0xA2+2*i);
    delay(10);
    i2c_rep_start((MS561101BA_ADDRESS<<1) | 1);//I2C read direction => 1
    delay(10);
    datat.raw[1] = i2c_readAck();  // read a 16 bit register
    datat.raw[0] = i2c_readNak();
    ms561101ba_ctx.c[i+1] = datat.val;
  }
}

// read uncompensated temperature value: send command first
void i2c_MS561101BA_UT_Start() {
  i2c_rep_start(MS561101BA_ADDRESS<<1);      // I2C write direction
  i2c_write(MS561101BA_TEMPERATURE + OSR);  // register selection
  i2c_stop();
}

void  Baro_init() {
  delay(100);
  i2c_MS561101BA_reset();
  delay(100);
  i2c_MS561101BA_readCalibration();
  delay(100);
  i2c_MS561101BA_UT_Start();
  delay(100);
}



// read uncompensated pressure value: send command first
void i2c_MS561101BA_UP_Start () {
  i2c_rep_start(MS561101BA_ADDRESS<<1);      // I2C write direction
  i2c_write(MS561101BA_PRESSURE + OSR);     // register selection
  i2c_stop();
}

// read uncompensated pressure value: read result bytes
void i2c_MS561101BA_UP_Read () {
  i2c_rep_start(MS561101BA_ADDRESS<<1);
  i2c_write(0);
  i2c_rep_start((MS561101BA_ADDRESS<<1) | 1);
  ms561101ba_ctx.up.raw[2] = i2c_readAck();
  ms561101ba_ctx.up.raw[1] = i2c_readAck();
  ms561101ba_ctx.up.raw[0] = i2c_readNak();
}

// read uncompensated temperature value: read result bytes
void i2c_MS561101BA_UT_Read() {
  i2c_rep_start(MS561101BA_ADDRESS<<1);
  i2c_write(0);
  i2c_rep_start((MS561101BA_ADDRESS<<1) | 1);
  ms561101ba_ctx.ut.raw[2] = i2c_readAck();
  ms561101ba_ctx.ut.raw[1] = i2c_readAck();
  ms561101ba_ctx.ut.raw[0] = i2c_readNak();
}

void i2c_MS561101BA_Calculate()
{
  int32_t off2,sens2,delt;
  int64_t dT,off,sens;
  dT= (int32_t)ms561101ba_ctx.ut.val - ((int32_t)ms561101ba_ctx.c[5] << 8);
  baroTemperature  = 2000 + ((dT * ms561101ba_ctx.c[6])>>23);
  off=((uint32_t)ms561101ba_ctx.c[2] <<16) + ((dT * ms561101ba_ctx.c[4]) >> 7);
  sens=((uint32_t)ms561101ba_ctx.c[1] <<15) + ((dT * ms561101ba_ctx.c[3]) >> 8);

  if (baroTemperature < 2000)
  { // temperature lower than 20st.C
    delt = baroTemperature-2000;
    delt  = 5*delt*delt;
    off2  = delt>>1;
    sens2 = delt>>2;
    if (baroTemperature < -1500)
    { // temperature lower than -15st.C
      delt  = baroTemperature+1500;
      delt  = delt*delt;
      off2  += 7 * delt;
      sens2 += (11 * delt)>>1;
    }
    off  -= off2;
    sens -= sens2;
  }
  baroPressure = (( (ms561101ba_ctx.up.val * sens ) >> 21) - off) >> 15;
}

void Baro_Common()
{
    static int32_t baroHistTab[BARO_TAB_SIZE];
    static uint8_t baroHistIdx;
    uint8_t indexplus1 = (baroHistIdx + 1);
    if (indexplus1 == BARO_TAB_SIZE) indexplus1 = 0;
    baroHistTab[baroHistIdx] = baroPressure;
    baroPressureSum += baroHistTab[baroHistIdx];
    baroPressureSum -= baroHistTab[indexplus1];
    baroHistIdx = indexplus1;
  }

uint8_t Baro_update()
{
  // first UT conversion is started in init procedure
 if (ms561101ba_ctx.state == 0)
 {
    i2c_MS561101BA_UT_Read();
    i2c_MS561101BA_UP_Start();
    Baro_Common();               // moved here for less timecycle spike
    ms561101ba_ctx.state = 1;
    return 1;
 }
 else
 {
    i2c_MS561101BA_UP_Read();
    i2c_MS561101BA_UT_Start();
    i2c_MS561101BA_Calculate();
    ms561101ba_ctx.state = 0;
    return 2;
  }
}



/*
 * 气压解算为高度值(cm)
 */
float Alt_offset_Pa;
double paOffsetNum = 0;
uint16_t  paInitCnt=0;
uint8_t paOffsetInited=0;
#define PA_OFFSET_INIT_NUM 10
uint16 MS5611_Cnter=0;
void Read_MS5611_Offset(void)
{
   uint16 i=0;
    while(MS5611_Cnter<=200)
    {
    MS5611_Cnter++;
    Baro_update();
    delay_ms(10);
    }

    for(i=0;i<PA_OFFSET_INIT_NUM*2;i++)
   {
      if(Baro_update()==2)
      paOffsetNum+=baroPressure;
      paInitCnt++;
      delay_ms(10);
   }
   Alt_offset_Pa=paOffsetNum/PA_OFFSET_INIT_NUM;
}



volatile double Tempbaro=0;
volatile double Temptmp=0;

float getEstimatedAltitude(float baroPress)
{
    Tempbaro=(float)(baroPress/Alt_offset_Pa)*1.0;
    Altitude = 4433000.0f * (1 - powf((float)(Tempbaro),0.190295f));
    return Altitude;
}

#define LENGTH  3
float MS5611_Rec[LENGTH];
float Min5611,Max5611;
float Max_Min5611(float *Data)
{
      unsigned int i=0;
      float Sum=0;
      Min5611=Data[0];
      Max5611=Data[0];
      Sum=Data[0];
      for(i=LENGTH-1;i>0;i--)
      {
        if(Data[i]>=Max5611)  Max5611=Data[i];
        if(Data[i]<=Min5611)  Min5611=Data[i];
        Sum+=Data[i];
      }
      //return ((Sum-(Min5611+Max5611))/(LENGTH-2));
      return (float)((Min5611+Max5611)/2.0);
}


static int16_t MS5611_status = 0;
unsigned int MS5611_ReadyCnt=0;
float Last_AirPresure_Altitude=0,AirPresure_Altitude=0,AirPresure_Altitude_Origion=0;
uint16 MS5611_Update=0;
uint16 MS5611_Update_finished=0;
void MS5611_StateMachine_20ms(void)
{
	 MS5611_status++;
         MS5611_ReadyCnt++;
         if(MS5611_status == 1)
	 {
          i2c_MS561101BA_UT_Read();
          i2c_MS561101BA_UP_Start();
	 }
         else   if(MS5611_status == 2)
         {

         }
         else   if(MS5611_status == 3)
         {

         }
         else   if(MS5611_status == 4)
         {
         i2c_MS561101BA_UP_Read();
         i2c_MS561101BA_UT_Start();
         }
         else   if(MS5611_status == 6)
         {
           i2c_MS561101BA_Calculate();
           Last_AirPresure_Altitude=AirPresure_Altitude;
           Baro=getEstimatedAltitude(baroPressure);
           AirPresure_Altitude_Origion=Baro;//原始气压高度
           AirPresure_Altitude=LPButter_BaroAlt(Baro);//滤波后气压高度
           MS5611_status = 0;
           MS5611_Update_finished=1;
           MS5611_Update=1;
           Baro_Climbrate=(AirPresure_Altitude-Last_AirPresure_Altitude)/0.024;
         }

          if(MS5611_ReadyCnt==2000) //500*8ms=4s
         {
             NamelessQuad.Position[_YAW]=AirPresure_Altitude;
             High_Okay_flag=1;
         }
}

void MS5611_StateMachine(void)
{
	 MS5611_status++;
         MS5611_ReadyCnt++;
         if(MS5611_status == 1)
	 {
          i2c_MS561101BA_UT_Read();
          i2c_MS561101BA_UP_Start();
	 }
         else   if(MS5611_status == 2)
         {
         i2c_MS561101BA_UP_Read();
         i2c_MS561101BA_UT_Start();
         }
         else   if(MS5611_status == 3)
         {
           i2c_MS561101BA_Calculate();
           Last_AirPresure_Altitude=AirPresure_Altitude;
           Baro=getEstimatedAltitude(baroPressure);
           AirPresure_Altitude_Origion=Baro;//原始气压高度
           AirPresure_Altitude=LPButter_BaroAlt(Baro);//滤波后气压高度
           MS5611_status = 0;
           MS5611_Update_finished=1;
           MS5611_Update=1;
          /**************气压计得到的攀爬速度************/
           //Baro_Climbrate=(AirPresure_Altitude-Last_AirPresure_Altitude)/0.024;
         }
          if(MS5611_ReadyCnt==2000) //500*8ms=4s
         {
             NamelessQuad.Position[_YAW]=AirPresure_Altitude;
             High_Okay_flag=1;
         }
}


