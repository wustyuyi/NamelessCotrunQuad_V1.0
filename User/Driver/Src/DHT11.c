#include "Headfile.h"
#include "DHT11.h"
#define DHT11_PORT GPIO_Pin_5
#define DHT11_PORT_H         GPIO_SetBits(GPIOC , GPIO_Pin_5)   
#define DHT11_PORT_L         GPIO_ResetBits(GPIOC , GPIO_Pin_5) 
#define DHT11_PORT_Read      GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_5)
#define DHT11_DQ_OUT PCout(5) //数据端口   PG11   
#define DHT11_DQ_IN  PCin(5)  //数据端口   PG11 



void DHT11_IO_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DHT11_PORT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
  GPIO_Init(GPIOC,&GPIO_InitStructure);
}
void DHT11_IO_IN(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DHT11_PORT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
}



//复位DHT11  
void Dht11Rst(void)      
{                   
    DHT11_IO_OUT();     //SET OUTPUT  
    DHT11_DQ_OUT=0;     //拉低DQ  
    delay_ms(20);        //拉低至少18ms  
    DHT11_DQ_OUT=1;     //DQ=1   
    delay_us(30);        //主机拉高20~40us  
} 

uint16 DHT11_TimeCnt=0;
float DHT11_Data[2];
  u8 buf[5];  
  void DHT11_TimeRead(void)      
{                   
  
    u8 i;  

    DHT11_TimeCnt++;
    if(DHT11_TimeCnt==1)
    {  
    DHT11_IO_OUT();     //SET OUTPUT  
    DHT11_DQ_OUT=0;     //拉低DQ
    }
    if(DHT11_TimeCnt>=5)
    {
      DHT11_DQ_OUT=1;     //DQ=1   
      delay_us(30);        //主机拉高20~40us 
      if(Dht11Check()==0)  
      {  
        for(i=0;i<5;i++)//读取40位数据  
        {  
            buf[i]=Dht11ReadByte();  
        }  
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])  
        {  
            DHT11_Data[0]=buf[0];  
            DHT11_Data[1]=buf[2];  
        }  
      }
      
      DHT11_TimeCnt=0;
    }
   
}  


  
  
  
//等待DHT11的回应  
//返回1:未检测到DHT11的存在  
//返回0:存在  
u8 Dht11Check(void)          
{     
    u8 retry=0;  
    DHT11_IO_IN();//SET INPUT      
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us  
    {  
        retry++;  
        delay_us(1);  
    };     
    if(retry>=100)return 1;  
    else retry=0;  
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us  
    {  
        retry++;  
        delay_us(1);  
    };  
    if(retry>=100)return 1;        
    return 0;  
}  
  
  
  
//从DHT11读取一个位  
//返回值：1/0  
u8 Dht11ReadBit(void)              
{  
    u8 retry=0;  
    while(DHT11_DQ_IN&&retry<100)//等待变为低电平  
    {  
        retry++;  
        delay_us(1);  
    }  
    retry=0;  
    while(!DHT11_DQ_IN&&retry<100)//等待变高电平  
    {  
        retry++;  
        delay_us(1);  
    }  
    delay_us(40);//等待40us  
    if(DHT11_DQ_IN)return 1;  
    else return 0;           
}  
  
  
  
//从DHT11读取一个字节  
//返回值：读到的数据  
u8 Dht11ReadByte(void)      
{          
    u8 i,dat;  
    dat=0;  
    for (i=0;i<8;i++)   
    {  
        dat<<=1;   
        dat|=Dht11ReadBit();  
    }                             
    return dat;  
}  
  
  
  
//从DHT11读取一次数据  
//temp:温度值(范围:0~50°)  
//humi:湿度值(范围:20%~90%)  
//返回值：0,正常;1,读取失败  
u8 Dht11ReadData(u8 *temp,u8 *humi)      
{          
    u8 buf[5];  
    u8 i;  
    Dht11Rst();  
    if(Dht11Check()==0)  
    {  
        for(i=0;i<5;i++)//读取40位数据  
        {  
            buf[i]=Dht11ReadByte();  
        }  
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])  
        {  
            *humi=buf[0];  
            *temp=buf[2];  
        }  
    }
    else return 1;  
    
return 0;         
}  
  
  
  
//初始化DHT11的IO口 DQ 同时检测DHT11的存在  
//返回1:不存在  
//返回0:存在           
u8 Dht11Init(void)  
{  
    DHT11_IO_OUT();
    
    DHT11_PORT_H;  
      
    Dht11Rst();  
      
    return Dht11Check();  
}  
  
void Dht11Show(void)  
{  
    u8 temp,humi;  
    if(Dht11ReadData(&temp,&humi))  
    {  
        printf("DHT11 read failed\r\n");  
    }  
    else  
    {  
        printf("温度 %d 湿度 %d \r\n",temp,humi);  
    }  
}  



