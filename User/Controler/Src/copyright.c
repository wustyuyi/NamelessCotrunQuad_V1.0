/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               �޸�����:2020/10/25
*               �汾���۷��ߡ���V1.0.1
*               ��Ȩ���У�����ؾ���
*               Copyright(C) �人�Ƽ���ѧ�����ƴ��Ŷ� 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "w25qxx.h"


void W25QXX_Init(void);
u16  W25QXX_ReadID(void);  	    		//��ȡFLASH ID
u8 W25QXX_ReadSR(u8 regno);             //��ȡ״̬�Ĵ��� 
void W25QXX_4ByteAddr_Enable(void);     //ʹ��4�ֽڵ�ַģʽ
void W25QXX_Write_SR(u8 regno,u8 sr);   //д״̬�Ĵ���
void W25QXX_Write_Enable(void);  		//дʹ�� 
void W25QXX_Write_Disable(void);		//д����
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void W25QXX_Erase_Chip(void);    	  	//��Ƭ����
void W25QXX_Erase_Sector(u32 Dst_Addr);	//��������
void W25QXX_Wait_Busy(void);           	//�ȴ�����
void W25QXX_PowerDown(void);        	//�������ģʽ
void W25QXX_WAKEUP(void);				//����
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);

void W25QXX_Write_Data(float *data,uint32_t addr);
void W25QXX_Read_Float(float *data,uint32_t addr);
//0x000000~0x800000
u16 W25QXX_TYPE;//W25Q80;	//Ĭ����W25Q128
//ÿһҳΪ256 byte,һ��������16ҳ
//4KbytesΪһ��Sector����
//16������Ϊ1��Block����
//W25Q80
//����Ϊ8M�ֽ�,����128��Block����,2048��Sector���� 											 
//��ʼ��SPI FLASH��IO��
void W25QXX_Init(void)
{ 
  u8 temp;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  W25QXX_CS=1;			             				//SPI FLASH��ѡ��
  
//	SPI2_Configuration();		   			    //��ʼ��SPI
//	W25QXX_Erase_Chip();
//	W25QXX_Erase_Sector(0x00);
  
  W25QXX_PowerDown();
  Delay_Ms(10);
  W25QXX_WAKEUP();
  Delay_Ms(10);
  
  
  W25QXX_TYPE=W25QXX_ReadID();	        //��ȡFLASH ID.
  if(W25QXX_TYPE==W25Q256)              //SPI FLASHΪW25Q256
  {
    temp=W25QXX_ReadSR(3);              //��ȡ״̬�Ĵ���3���жϵ�ַģʽ
    if((temp&0X01)==0)			        		//�������4�ֽڵ�ַģʽ,�����4�ֽڵ�ַģʽ
    {
      W25QXX_CS=0; 			        				//ѡ��
      SPI2_ReadWriteByte(W25X_Enable4ByteAddr);//���ͽ���4�ֽڵ�ַģʽָ��   
      W25QXX_CS=1;       		        		//ȡ��Ƭѡ   
    }
  }
}  

/*************************************************
��ȡW25QXX��״̬�Ĵ�����W25QXXһ����3��״̬�Ĵ���
״̬�Ĵ���1��
BIT7  6   5   4   3   2   1   0
SPR   RV  TB BP2 BP1 BP0 WEL BUSY
SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
TB,BP2,BP1,BP0:FLASH����д��������
WEL:дʹ������
BUSY:æ���λ(1,æ;0,����)
Ĭ��:0x00

״̬�Ĵ���2��
BIT7  6   5   4   3   2   1   0
SUS   CMP LB3 LB2 LB1 (R) QE  SRP1


״̬�Ĵ���3��
BIT7      6    5    4   3   2   1   0
HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
regno:״̬�Ĵ����ţ���:1~3
����ֵ:״̬�Ĵ���ֵ
*************************************************/

u8 W25QXX_ReadSR(u8 regno)   
{  
  u8 byte=0,command=0; 
  switch(regno)
  {
  case 1:
    command=W25X_ReadStatusReg1;    //��״̬�Ĵ���1ָ��
    break;
  case 2:
    command=W25X_ReadStatusReg2;    //��״̬�Ĵ���2ָ��
    break;
  case 3:
    command=W25X_ReadStatusReg3;    //��״̬�Ĵ���3ָ��
    break;
  default:
    command=W25X_ReadStatusReg1;    
    break;
  }    
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(command);            //���Ͷ�ȡ״̬�Ĵ�������    
  byte=SPI2_ReadWriteByte(0Xff);          //��ȡһ���ֽ�  
  W25QXX_CS=1;                            //ȡ��Ƭѡ     
  return byte;   
} 
//дW25QXX״̬�Ĵ���
void W25QXX_Write_SR(u8 regno,u8 sr)   
{   
  u8 command=0;
  switch(regno)
  {
  case 1:
    command=W25X_WriteStatusReg1;    //д״̬�Ĵ���1ָ��
    break;
  case 2:
    command=W25X_WriteStatusReg2;    //д״̬�Ĵ���2ָ��
    break;
  case 3:
    command=W25X_WriteStatusReg3;    //д״̬�Ĵ���3ָ��
    break;
  default:
    command=W25X_WriteStatusReg1;    
    break;
  }   
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(command);            //����дȡ״̬�Ĵ�������    
  SPI2_ReadWriteByte(sr);                 //д��һ���ֽ�  
  W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
}   
//W25QXXдʹ��	
//��WEL��λ   
void W25QXX_Write_Enable(void)   
{
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_WriteEnable);   //����дʹ��  
  W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 
//W25QXXд��ֹ	
//��WEL����  
void W25QXX_Write_Disable(void)   
{  
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_WriteDisable);  //����д��ָֹ��    
  W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 

//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
//0XEF18,��ʾоƬ�ͺ�ΪW25Q256
u16 W25QXX_ReadID(void)
{
  u16 Temp = 0;	  
  W25QXX_CS=0;				    
  SPI2_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
  SPI2_ReadWriteByte(0x00); 	    
  SPI2_ReadWriteByte(0x00); 	    
  SPI2_ReadWriteByte(0x00); 	 			   
  Temp|=SPI2_ReadWriteByte(0xFF)<<8;  
  Temp|=SPI2_ReadWriteByte(0xFF);	 
  W25QXX_CS=1;				    
  return Temp;
}   		    
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
  u16 i;   										    
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_ReadData);      //���Ͷ�ȡ����  
  if(W25QXX_TYPE==W25Q256)                //�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
  {
    SPI2_ReadWriteByte((u8)((ReadAddr)>>24));    
  }
  SPI2_ReadWriteByte((u8)((ReadAddr)>>16));   //����24bit��ַ    
  SPI2_ReadWriteByte((u8)((ReadAddr)>>8));   
  SPI2_ReadWriteByte((u8)ReadAddr);   
  for(i=0;i<NumByteToRead;i++)
  { 
    pBuffer[i]=SPI2_ReadWriteByte(0XFF);    //ѭ������  
  }
  W25QXX_CS=1;  				    	      
}  
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
  u16 i;  
  W25QXX_Write_Enable();                  //SET WEL 
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_PageProgram);   //����дҳ����   
  if(W25QXX_TYPE==W25Q256)                //�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
  {
    SPI2_ReadWriteByte((u8)((WriteAddr)>>24)); 
  }
  SPI2_ReadWriteByte((u8)((WriteAddr)>>16)); //����24bit��ַ    
  SPI2_ReadWriteByte((u8)((WriteAddr)>>8));   
  SPI2_ReadWriteByte((u8)WriteAddr);   
  for(i=0;i<NumByteToWrite;i++)	SPI2_ReadWriteByte(pBuffer[i]);//ѭ��д��  
  W25QXX_CS=1;                            //ȡ��Ƭѡ 
  W25QXX_Wait_Busy();					   					//�ȴ�д�����
} 
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
  u16 pageremain;	   
  pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
  if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
  while(1)
  {	   
    W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
    if(NumByteToWrite==pageremain)break;//д�������
    else //NumByteToWrite>pageremain
    {
      pBuffer+=pageremain;
      WriteAddr+=pageremain;	
      
      NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
      if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
      else pageremain=NumByteToWrite; 	  //����256���ֽ���
    }
  }	    
} 
//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)   
u8 W25QXX_BUFFER[4096];		 
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
  u32 secpos;
  u16 secoff;
  u16 secremain;	   
  u16 i;    
  u8 * W25QXX_BUF;	  
  W25QXX_BUF=W25QXX_BUFFER;	     
  secpos=WriteAddr/4096;//������ַ  
  secoff=WriteAddr%4096;//�������ڵ�ƫ��
  secremain=4096-secoff;//����ʣ��ռ��С   
  //printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
  if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
  while(1) 
  {	
    W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//������������������
    for(i=0;i<secremain;i++)//У������
    {
      if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
    }
    if(i<secremain)//��Ҫ����
    {
      W25QXX_Erase_Sector(secpos); //�����������
      for(i=0;i<secremain;i++)	   //����
      {
        W25QXX_BUF[i+secoff]=pBuffer[i];	  
      }
      W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//д����������  
      
    }
    else W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
    if(NumByteToWrite==secremain)break;//д�������
    else//д��δ����
    {
      secpos++;//������ַ��1
      secoff=0;//ƫ��λ��Ϊ0 	 
      
      pBuffer+=secremain;  //ָ��ƫ��
      WriteAddr+=secremain;//д��ַƫ��	   
      NumByteToWrite-=secremain;				//�ֽ����ݼ�
      if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
      else secremain=NumByteToWrite;					//��һ����������д����
    }	 
  };	 
}
//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{                                   
  W25QXX_Write_Enable();                  //SET WEL 
  W25QXX_Wait_Busy();   
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_ChipErase);     //����Ƭ��������  
  W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
  W25QXX_Wait_Busy();   				          //�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ������������ʱ��:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
  //����falsh�������,������   
  //printf("fe:%x\r\n",Dst_Addr);	  
  Dst_Addr*=4096;
  W25QXX_Write_Enable();                  //SET WEL 	 
  W25QXX_Wait_Busy();   
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_SectorErase);   //������������ָ�� 
  if(W25QXX_TYPE==W25Q256)                //�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
  {
    SPI2_ReadWriteByte((u8)((Dst_Addr)>>24)); 
  }
  SPI2_ReadWriteByte((u8)((Dst_Addr)>>16));  //����24bit��ַ    
  SPI2_ReadWriteByte((u8)((Dst_Addr)>>8));   
  SPI2_ReadWriteByte((u8)Dst_Addr);  
  W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
  W25QXX_Wait_Busy();   				    //�ȴ��������
}  
//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   
  while((W25QXX_ReadSR(1)&0x01)==0x01);   // �ȴ�BUSYλ���
}  
//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
  W25QXX_CS=0;                            //ʹ������   
  SPI2_ReadWriteByte(W25X_PowerDown);     //���͵�������  
  W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
  delay_us(3);                            //�ȴ�TPD  
}   
//����
void W25QXX_WAKEUP(void)   
{  
  W25QXX_CS=0;                                //ʹ������   
  SPI2_ReadWriteByte(W25X_ReleasePowerDown);  //send W25X_PowerDown command 0xAB    
  W25QXX_CS=1;                                //ȡ��Ƭѡ     	      
  delay_us(3);                                //�ȴ�TRES1
}   



void W25QXX_Write_Data(float *data,uint32_t addr)
{
	uint8_t tempwr[4];
  tempwr[0]=(*(uint32_t *)(data))&0xff;
  tempwr[1]=(*(uint32_t *)(data))>>8;
  tempwr[2]=(*(uint32_t *)(data))>>16;
  tempwr[3]=(*(uint32_t *)(data))>>24;
  W25QXX_Write_Page(tempwr,addr,4);
}


void W25QXX_Write_Data_Uint32_t(uint32_t *data,uint32_t addr)
{
	uint8_t tempwr[4];
  tempwr[0]=(*(uint32_t *)(data))&0xff;
  tempwr[1]=(*(uint32_t *)(data))>>8;
  tempwr[2]=(*(uint32_t *)(data))>>16;
  tempwr[3]=(*(uint32_t *)(data))>>24;
  W25QXX_Write_Page(tempwr,addr,4);
}



void W25QXX_Read_Float(float *data,uint32_t addr)
{
  Float_2_Byte temp;
  W25QXX_Read(temp.Bdata,addr,4);
  //uint8_t temp[4];*data=*(float *)(temp);
  *data=temp.Fdata;
}

void W25QXX_Read_Uint32_t(uint32_t *data,uint32_t addr)
{
  Float_2_Byte temp;
  W25QXX_Read(temp.Bdata,addr,4);
  //uint8_t temp[4];*data=*(float *)(temp);
  *data=temp.Idata;
}


int W25QXX_Read_N_Data(uint32_t ReadAddress,uint32_t *ReadBuf,int32_t ReadNum)
{
//	Float_2_Byte temp;
//	for(uint16_t i=0;i<ReadNum;i++)
//	{
//		W25QXX_Read(temp.Bdata,ReadAddress+4*i,4);
//		*(ReadBuf+i)=temp.Fdata;
//	}
	for(uint16_t i=0;i<ReadNum;i++)
	{
    W25QXX_Read_Uint32_t((ReadBuf+i),ReadAddress+4*i);
	}
	return 1;
}

void W25QXX_Write_N_Data(uint32_t WriteAddress,uint32_t *Buf,int32_t length)
{
//uint8_t tempwr[4];
//	for(uint16_t i=0;i<length;i++)
//	{
//		tempwr[0]=(*(uint32_t *)(Buf+i))&0xff;
//		tempwr[1]=(*(uint32_t *)(Buf+i))>>8;
//		tempwr[2]=(*(uint32_t *)(Buf+i))>>16;
//		tempwr[3]=(*(uint32_t *)(Buf+i))>>24;
//		W25QXX_Write_Page(tempwr,WriteAddress+4*i,4);
//	}
	for(uint16_t i=0;i<length;i++)
	{
		W25QXX_Write_Data_Uint32_t((Buf+i),WriteAddress+4*i);
	}
}




/*******************************************************************************
* Function Name : void USB_Config(void)
* Description   : USBϵͳ��ʼ��
* Input         :
* Output        :
* Other         :
* Date          : 2014.11.28
*******************************************************************************/
void USB_Config(void)
{
    Set_System();
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
}


void System_Init(uint16_t clock)
{
  SystemInit();        //ϵͳʼ�ճ�ʼ��
  cycleCounterInit();  
  delay_init(clock);      //�δ���ʱ��ʼ��
  OLED_Init();         //��ʾ����ʼ��
  USB_Config();        //USB���⴮�ڳ�ʼ��
  SPI2_Configuration();
  W25QXX_Init();	
  Soft_I2C_Init();     //���ģ��I2C��ʼ��
  spl0601_init();	
}

