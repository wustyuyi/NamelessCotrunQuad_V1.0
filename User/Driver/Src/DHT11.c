#include "Headfile.h"
#include "DHT11.h"
#define DHT11_PORT GPIO_Pin_5
#define DHT11_PORT_H         GPIO_SetBits(GPIOC , GPIO_Pin_5)   
#define DHT11_PORT_L         GPIO_ResetBits(GPIOC , GPIO_Pin_5) 
#define DHT11_PORT_Read      GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_5)
#define DHT11_DQ_OUT PCout(5) //���ݶ˿�   PG11   
#define DHT11_DQ_IN  PCin(5)  //���ݶ˿�   PG11 



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



//��λDHT11  
void Dht11Rst(void)      
{                   
    DHT11_IO_OUT();     //SET OUTPUT  
    DHT11_DQ_OUT=0;     //����DQ  
    delay_ms(20);        //��������18ms  
    DHT11_DQ_OUT=1;     //DQ=1   
    delay_us(30);        //��������20~40us  
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
    DHT11_DQ_OUT=0;     //����DQ
    }
    if(DHT11_TimeCnt>=5)
    {
      DHT11_DQ_OUT=1;     //DQ=1   
      delay_us(30);        //��������20~40us 
      if(Dht11Check()==0)  
      {  
        for(i=0;i<5;i++)//��ȡ40λ����  
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


  
  
  
//�ȴ�DHT11�Ļ�Ӧ  
//����1:δ��⵽DHT11�Ĵ���  
//����0:����  
u8 Dht11Check(void)          
{     
    u8 retry=0;  
    DHT11_IO_IN();//SET INPUT      
    while (DHT11_DQ_IN&&retry<100)//DHT11������40~80us  
    {  
        retry++;  
        delay_us(1);  
    };     
    if(retry>=100)return 1;  
    else retry=0;  
    while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~80us  
    {  
        retry++;  
        delay_us(1);  
    };  
    if(retry>=100)return 1;        
    return 0;  
}  
  
  
  
//��DHT11��ȡһ��λ  
//����ֵ��1/0  
u8 Dht11ReadBit(void)              
{  
    u8 retry=0;  
    while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ  
    {  
        retry++;  
        delay_us(1);  
    }  
    retry=0;  
    while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ  
    {  
        retry++;  
        delay_us(1);  
    }  
    delay_us(40);//�ȴ�40us  
    if(DHT11_DQ_IN)return 1;  
    else return 0;           
}  
  
  
  
//��DHT11��ȡһ���ֽ�  
//����ֵ������������  
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
  
  
  
//��DHT11��ȡһ������  
//temp:�¶�ֵ(��Χ:0~50��)  
//humi:ʪ��ֵ(��Χ:20%~90%)  
//����ֵ��0,����;1,��ȡʧ��  
u8 Dht11ReadData(u8 *temp,u8 *humi)      
{          
    u8 buf[5];  
    u8 i;  
    Dht11Rst();  
    if(Dht11Check()==0)  
    {  
        for(i=0;i<5;i++)//��ȡ40λ����  
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
  
  
  
//��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���  
//����1:������  
//����0:����           
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
        printf("�¶� %d ʪ�� %d \r\n",temp,humi);  
    }  
}  



