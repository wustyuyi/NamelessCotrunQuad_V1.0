#ifndef _DHT11_H_
#define _DHT11_H_


u8 Dht11Init(void);//初始化DHT11  
  
u8 Dht11ReadData(u8 *temp,u8 *humi);//读取温湿度  
  
u8 Dht11ReadByte(void);//读出一个字节  
  
u8 Dht11ReadBit(void);//读出一个位  
  
  
u8 Dht11Check(void);//检测是否存在DHT11  
  
  
void Dht11Rst(void);//复位DHT11    
  
void Dht11Show(void); 
void DHT11_TimeRead(void);

extern float DHT11_Data[2];
#endif

