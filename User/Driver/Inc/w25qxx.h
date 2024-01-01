#ifndef __W25QXX_H
#define __W25QXX_H
#include "Headfile.h"


//W25X系列/Q系列芯片列表	   
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17
#define W25Q256 0XEF18

extern u16 W25QXX_TYPE;					//定义W25QXX芯片型号		   

#define	W25QXX_CS 		PAout(15)  		//W25QXX的片选信号

////////////////////////////////////////////////////////////////////////////////// 
//指令表
#define W25X_WriteEnable				0x06 
#define W25X_WriteDisable				0x04 
#define W25X_ReadStatusReg1			0x05 
#define W25X_ReadStatusReg2			0x35 
#define W25X_ReadStatusReg3			0x15 
#define W25X_WriteStatusReg1    0x01 
#define W25X_WriteStatusReg2    0x31 
#define W25X_WriteStatusReg3    0x11 
#define W25X_ReadData						0x03 
#define W25X_FastReadData				0x0B 
#define W25X_FastReadDual				0x3B 
#define W25X_PageProgram				0x02 
#define W25X_BlockErase					0xD8 
#define W25X_SectorErase				0x20 
#define W25X_ChipErase					0xC7 
#define W25X_PowerDown					0xB9 
#define W25X_ReleasePowerDown		0xAB 
#define W25X_DeviceID						0xAB 
#define W25X_ManufactDeviceID		0x90 
#define W25X_JedecDeviceID			0x9F 
#define W25X_Enable4ByteAddr    0xB7
#define W25X_Exit4ByteAddr      0xE9



void W25QXX_Write_Data(float *data,uint32_t addr);
void W25QXX_Read_Float(float *data,uint32_t addr);


void W25QXX_Write_N_Data(uint32_t WriteAddress,uint32_t *Buf,int32_t length);	
int W25QXX_Read_N_Data(uint32_t ReadAddress,uint32_t *ReadBuf,int32_t ReadNum);

#endif
