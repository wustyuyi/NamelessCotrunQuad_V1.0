#include "Headfile.h"
#include "BH1750.h"


#define	  SlaveAddress   0x46



void Single_Write_BH1750(unsigned char REG_Address)
{
    I2C_Start();                 
    I2C_SendByte(SlaveAddress);  
    I2C_SendByte(REG_Address); 
  //  BH1750_SendByte(REG_data);    
    I2C_Stop();                
}


void BH1750_SendACK(uint8 ack)
{
    SDA_IOOUT();
    if(ack==1)  SDA_H;
    else SDA_L;                
    SCL_H;                  
    delay_us(5);                
    SCL_L;                  
    delay_us(5);                 
}


void BH1750_Init()
{
Single_Write_BH1750(0x01); 
}
uint8 BH1750_Buf[8];
void Multiple_read_BH1750(void)
{   uint8 i;	
    I2C_Start();                    
    I2C_SendByte(SlaveAddress+1);        
	
	 for (i=0; i<3; i++)                      
    {
        BH1750_Buf[i] = I2C_RecvByte();         
        if (i == 3)
        {

           BH1750_SendACK(1);               
        }
        else
        {		
          BH1750_SendACK(0);         
        }
   }
    I2C_Stop();                
}

uint16  BH1750_Cnt=0;
int16 BH1750_Data;
float LightValue=0;
void BH1750_Read()//
{
    BH1750_Cnt++;
    if(BH1750_Cnt==1)
    {
    Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode
    }
    
    if(BH1750_Cnt>=45)
    {
    Multiple_read_BH1750();
    BH1750_Cnt=0;
    BH1750_Data=BH1750_Buf[0];
    BH1750_Data=(BH1750_Data<<8)+BH1750_Buf[1];
    LightValue=(float)BH1750_Data/1.2;
    } 

    
}