#include "Headfile.h"
#include "tofsense.h"


Testime tofsense_t;
tofsense tofsense_data;
void tofsense_receive_anl(uint8_t *data_buf,uint8_t num)
{
  uint8_t sum = 0;
  for(uint8_t i=0;i<(num-1);i++)  sum+=*(data_buf+i);
  if(!(sum==*(data_buf+num-1))) 	return;//不满足和校验条件
  if(!(*(data_buf)==0x57 && *(data_buf+1)==0x00))return;//不满足帧头条件
	Test_Period(&tofsense_t);
	
	tofsense_data.frame_header=data_buf[0];
	tofsense_data.function_mark=data_buf[1];
	tofsense_data.id=data_buf[3];
	tofsense_data.system_time=data_buf[4]|(data_buf[5]<<8)|(data_buf[6]<<16)|(data_buf[7]<<24);
	tofsense_data.dis=(int32_t)(data_buf[8]<< 8|data_buf[9]<<16|data_buf[10]<<24)/256;
	tofsense_data.dis_status=data_buf[11];
	tofsense_data.signal_strength=data_buf[12]|(data_buf[13]<<8);
	tofsense_data.range_precision=data_buf[14];
	
	tofsense_data.distance=tofsense_data.dis/10.0f;//cm		
	tofsense_data.update_flag=1;
	if(tofsense_data.dis_status==1&&tofsense_data.distance<450) tofsense_data.valid=1;
	else tofsense_data.valid=0;
	tofsense_data.period_ms=124;
	
	HC_SR04_Distance=tofsense_data.distance;
	if(HC_SR04_Distance<=400&&HC_SR04_Distance>0)  Sensor_Flag.Hcsr04_Health=1;
	else  Sensor_Flag.Hcsr04_Health=0; 
	HCSR_04_Update_Flag=1;	
	
	for(int16_t i=20-1;i>0;i--)//历史位置观测值
	{
		tofsense_data.height_backups[i]=tofsense_data.height_backups[i-1];
	}
	tofsense_data.height_backups[0]=tofsense_data.distance;
}


void tofsense_prase(uint8_t data)
{
	static uint8_t buf[16];
  static uint8_t data_len = 0,data_cnt = 0;
  static uint8_t state = 0;
  if(state==0&&data==0x57)//判断帧头1
  {
    state=1;
    buf[0]=data;
  }
  else if(state==1&&data==0x00)//判断帧头2
  {
    state=2;
    buf[1]=data;
  }
  else if(state==2&&data==0xff)//功能字节
  {
    state=3;
    buf[2]=data;
  }
  else if(state==3&&data<=0xff)//id
  {
    state = 4;
    buf[3]=data;
    data_len = 11;
    data_cnt = 0;
  }
  else if(state==4&&data_len>0)//数据接收
  {
    data_len--;
    buf[4+data_cnt++]=data;
    if(data_len==0)  state = 5;
  }
  else if(state==5)//和校验
  {
    state = 0;
    buf[4+data_cnt++]=data;
		tofsense_receive_anl(buf,16);
  }
  else state = 0;
}


