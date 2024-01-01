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
*               修改日期:2020/10/25
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "w25qxx.h"


void W25QXX_Init(void);
u16  W25QXX_ReadID(void);  	    		//读取FLASH ID
u8 W25QXX_ReadSR(u8 regno);             //读取状态寄存器 
void W25QXX_4ByteAddr_Enable(void);     //使能4字节地址模式
void W25QXX_Write_SR(u8 regno,u8 sr);   //写状态寄存器
void W25QXX_Write_Enable(void);  		//写使能 
void W25QXX_Write_Disable(void);		//写保护
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//写入flash
void W25QXX_Erase_Chip(void);    	  	//整片擦除
void W25QXX_Erase_Sector(u32 Dst_Addr);	//扇区擦除
void W25QXX_Wait_Busy(void);           	//等待空闲
void W25QXX_PowerDown(void);        	//进入掉电模式
void W25QXX_WAKEUP(void);				//唤醒
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);

void W25QXX_Write_Data(float *data,uint32_t addr);
void W25QXX_Read_Float(float *data,uint32_t addr);
//0x000000~0x800000
u16 W25QXX_TYPE;//W25Q80;	//默认是W25Q128
//每一页为256 byte,一个扇区有16页
//4Kbytes为一个Sector扇区
//16个扇区为1个Block区块
//W25Q80
//容量为8M字节,共有128个Block区块,2048个Sector扇区 											 
//初始化SPI FLASH的IO口
void W25QXX_Init(void)
{ 
  u8 temp;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  W25QXX_CS=1;			             				//SPI FLASH不选中
  
//	SPI2_Configuration();		   			    //初始化SPI
//	W25QXX_Erase_Chip();
//	W25QXX_Erase_Sector(0x00);
  
  W25QXX_PowerDown();
  Delay_Ms(10);
  W25QXX_WAKEUP();
  Delay_Ms(10);
  
  
  W25QXX_TYPE=W25QXX_ReadID();	        //读取FLASH ID.
  if(W25QXX_TYPE==W25Q256)              //SPI FLASH为W25Q256
  {
    temp=W25QXX_ReadSR(3);              //读取状态寄存器3，判断地址模式
    if((temp&0X01)==0)			        		//如果不是4字节地址模式,则进入4字节地址模式
    {
      W25QXX_CS=0; 			        				//选中
      SPI2_ReadWriteByte(W25X_Enable4ByteAddr);//发送进入4字节地址模式指令   
      W25QXX_CS=1;       		        		//取消片选   
    }
  }
}  

/*************************************************
读取W25QXX的状态寄存器，W25QXX一共有3个状态寄存器
状态寄存器1：
BIT7  6   5   4   3   2   1   0
SPR   RV  TB BP2 BP1 BP0 WEL BUSY
SPR:默认0,状态寄存器保护位,配合WP使用
TB,BP2,BP1,BP0:FLASH区域写保护设置
WEL:写使能锁定
BUSY:忙标记位(1,忙;0,空闲)
默认:0x00

状态寄存器2：
BIT7  6   5   4   3   2   1   0
SUS   CMP LB3 LB2 LB1 (R) QE  SRP1


状态寄存器3：
BIT7      6    5    4   3   2   1   0
HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
regno:状态寄存器号，范:1~3
返回值:状态寄存器值
*************************************************/

u8 W25QXX_ReadSR(u8 regno)   
{  
  u8 byte=0,command=0; 
  switch(regno)
  {
  case 1:
    command=W25X_ReadStatusReg1;    //读状态寄存器1指令
    break;
  case 2:
    command=W25X_ReadStatusReg2;    //读状态寄存器2指令
    break;
  case 3:
    command=W25X_ReadStatusReg3;    //读状态寄存器3指令
    break;
  default:
    command=W25X_ReadStatusReg1;    
    break;
  }    
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(command);            //发送读取状态寄存器命令    
  byte=SPI2_ReadWriteByte(0Xff);          //读取一个字节  
  W25QXX_CS=1;                            //取消片选     
  return byte;   
} 
//写W25QXX状态寄存器
void W25QXX_Write_SR(u8 regno,u8 sr)   
{   
  u8 command=0;
  switch(regno)
  {
  case 1:
    command=W25X_WriteStatusReg1;    //写状态寄存器1指令
    break;
  case 2:
    command=W25X_WriteStatusReg2;    //写状态寄存器2指令
    break;
  case 3:
    command=W25X_WriteStatusReg3;    //写状态寄存器3指令
    break;
  default:
    command=W25X_WriteStatusReg1;    
    break;
  }   
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(command);            //发送写取状态寄存器命令    
  SPI2_ReadWriteByte(sr);                 //写入一个字节  
  W25QXX_CS=1;                            //取消片选     	      
}   
//W25QXX写使能	
//将WEL置位   
void W25QXX_Write_Enable(void)   
{
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_WriteEnable);   //发送写使能  
  W25QXX_CS=1;                            //取消片选     	      
} 
//W25QXX写禁止	
//将WEL清零  
void W25QXX_Write_Disable(void)   
{  
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_WriteDisable);  //发送写禁止指令    
  W25QXX_CS=1;                            //取消片选     	      
} 

//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128 	  
//0XEF18,表示芯片型号为W25Q256
u16 W25QXX_ReadID(void)
{
  u16 Temp = 0;	  
  W25QXX_CS=0;				    
  SPI2_ReadWriteByte(0x90);//发送读取ID命令	    
  SPI2_ReadWriteByte(0x00); 	    
  SPI2_ReadWriteByte(0x00); 	    
  SPI2_ReadWriteByte(0x00); 	 			   
  Temp|=SPI2_ReadWriteByte(0xFF)<<8;  
  Temp|=SPI2_ReadWriteByte(0xFF);	 
  W25QXX_CS=1;				    
  return Temp;
}   		    
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
  u16 i;   										    
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_ReadData);      //发送读取命令  
  if(W25QXX_TYPE==W25Q256)                //如果是W25Q256的话地址为4字节的，要发送最高8位
  {
    SPI2_ReadWriteByte((u8)((ReadAddr)>>24));    
  }
  SPI2_ReadWriteByte((u8)((ReadAddr)>>16));   //发送24bit地址    
  SPI2_ReadWriteByte((u8)((ReadAddr)>>8));   
  SPI2_ReadWriteByte((u8)ReadAddr);   
  for(i=0;i<NumByteToRead;i++)
  { 
    pBuffer[i]=SPI2_ReadWriteByte(0XFF);    //循环读数  
  }
  W25QXX_CS=1;  				    	      
}  
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
void W25QXX_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
  u16 i;  
  W25QXX_Write_Enable();                  //SET WEL 
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_PageProgram);   //发送写页命令   
  if(W25QXX_TYPE==W25Q256)                //如果是W25Q256的话地址为4字节的，要发送最高8位
  {
    SPI2_ReadWriteByte((u8)((WriteAddr)>>24)); 
  }
  SPI2_ReadWriteByte((u8)((WriteAddr)>>16)); //发送24bit地址    
  SPI2_ReadWriteByte((u8)((WriteAddr)>>8));   
  SPI2_ReadWriteByte((u8)WriteAddr);   
  for(i=0;i<NumByteToWrite;i++)	SPI2_ReadWriteByte(pBuffer[i]);//循环写数  
  W25QXX_CS=1;                            //取消片选 
  W25QXX_Wait_Busy();					   					//等待写入结束
} 
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
  u16 pageremain;	   
  pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
  if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
  while(1)
  {	   
    W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
    if(NumByteToWrite==pageremain)break;//写入结束了
    else //NumByteToWrite>pageremain
    {
      pBuffer+=pageremain;
      WriteAddr+=pageremain;	
      
      NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
      if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
      else pageremain=NumByteToWrite; 	  //不够256个字节了
    }
  }	    
} 
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)						
//NumByteToWrite:要写入的字节数(最大65535)   
u8 W25QXX_BUFFER[4096];		 
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
  u32 secpos;
  u16 secoff;
  u16 secremain;	   
  u16 i;    
  u8 * W25QXX_BUF;	  
  W25QXX_BUF=W25QXX_BUFFER;	     
  secpos=WriteAddr/4096;//扇区地址  
  secoff=WriteAddr%4096;//在扇区内的偏移
  secremain=4096-secoff;//扇区剩余空间大小   
  //printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//测试用
  if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
  while(1) 
  {	
    W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//读出整个扇区的内容
    for(i=0;i<secremain;i++)//校验数据
    {
      if(W25QXX_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
    }
    if(i<secremain)//需要擦除
    {
      W25QXX_Erase_Sector(secpos); //擦除这个扇区
      for(i=0;i<secremain;i++)	   //复制
      {
        W25QXX_BUF[i+secoff]=pBuffer[i];	  
      }
      W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//写入整个扇区  
      
    }
    else W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
    if(NumByteToWrite==secremain)break;//写入结束了
    else//写入未结束
    {
      secpos++;//扇区地址增1
      secoff=0;//偏移位置为0 	 
      
      pBuffer+=secremain;  //指针偏移
      WriteAddr+=secremain;//写地址偏移	   
      NumByteToWrite-=secremain;				//字节数递减
      if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
      else secremain=NumByteToWrite;					//下一个扇区可以写完了
    }	 
  };	 
}
//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip(void)   
{                                   
  W25QXX_Write_Enable();                  //SET WEL 
  W25QXX_Wait_Busy();   
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_ChipErase);     //发送片擦除命令  
  W25QXX_CS=1;                            //取消片选     	      
  W25QXX_Wait_Busy();   				          //等待芯片擦除结束
}   
//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个扇区的最少时间:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
  //监视falsh擦除情况,测试用   
  //printf("fe:%x\r\n",Dst_Addr);	  
  Dst_Addr*=4096;
  W25QXX_Write_Enable();                  //SET WEL 	 
  W25QXX_Wait_Busy();   
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_SectorErase);   //发送扇区擦除指令 
  if(W25QXX_TYPE==W25Q256)                //如果是W25Q256的话地址为4字节的，要发送最高8位
  {
    SPI2_ReadWriteByte((u8)((Dst_Addr)>>24)); 
  }
  SPI2_ReadWriteByte((u8)((Dst_Addr)>>16));  //发送24bit地址    
  SPI2_ReadWriteByte((u8)((Dst_Addr)>>8));   
  SPI2_ReadWriteByte((u8)Dst_Addr);  
  W25QXX_CS=1;                            //取消片选     	      
  W25QXX_Wait_Busy();   				    //等待擦除完成
}  
//等待空闲
void W25QXX_Wait_Busy(void)   
{   
  while((W25QXX_ReadSR(1)&0x01)==0x01);   // 等待BUSY位清空
}  
//进入掉电模式
void W25QXX_PowerDown(void)   
{ 
  W25QXX_CS=0;                            //使能器件   
  SPI2_ReadWriteByte(W25X_PowerDown);     //发送掉电命令  
  W25QXX_CS=1;                            //取消片选     	      
  delay_us(3);                            //等待TPD  
}   
//唤醒
void W25QXX_WAKEUP(void)   
{  
  W25QXX_CS=0;                                //使能器件   
  SPI2_ReadWriteByte(W25X_ReleasePowerDown);  //send W25X_PowerDown command 0xAB    
  W25QXX_CS=1;                                //取消片选     	      
  delay_us(3);                                //等待TRES1
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
* Description   : USB系统初始化
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
  SystemInit();        //系统始终初始化
  cycleCounterInit();  
  delay_init(clock);      //滴答延时初始化
  OLED_Init();         //显示屏初始化
  USB_Config();        //USB虚拟串口初始化
  SPI2_Configuration();
  W25QXX_Init();	
  Soft_I2C_Init();     //软件模拟I2C初始化
  spl0601_init();	
}

