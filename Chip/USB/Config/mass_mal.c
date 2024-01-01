/**
  ******************************************************************************
  * @file    mass_mal.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Medium Access Layer interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "mass_mal.h"
#include "mmc_sd.h"
#include "flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
long long Mass_Memory_Size[MAX_LUN+1];//超过4G的SD卡，必须用long long表示其容量！！
u32 Mass_Block_Size[MAX_LUN+1];
u32 Mass_Block_Count[MAX_LUN+1];

#if defined(USE_STM3210E_EVAL) || defined(USE_STM32L152D_EVAL)
SD_CardInfo mSDCardInfo;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{ 
	u16 Status=MAL_OK;   
	switch (lun)
	{
		case 0://磁盘0为 SPI FLASH
			 break; 			   
		case 1://磁盘1为 SD卡
			break; 		  
		default://非法值
			return MAL_FAIL;
	}
	return Status;
}

/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint64_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
	u8 STA;
	switch (lun)		//这里,根据lun的值确定所要操作的磁盘
	{
		case 0:	 //磁盘0为 SPI FLASH盘	
			STA=0;
			SPI_Flash_Write((u8*)Writebuff, Memory_Offset, Transfer_Length); 
			//Mini板为：SPI_Flash_Write
			break; 
		case 1:	//磁盘1为SD卡		  
			STA=SD_WriteDisk((u8*)Writebuff,Memory_Offset>>9, Transfer_Length>>9);  
			break;					
		default:
			return MAL_FAIL;
	}
	if(STA!=0)return MAL_FAIL;
	return MAL_OK; 
}




/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint64_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
	u8 STA;
	switch (lun)		//这里,根据lun的值确定所要操作的磁盘
	{
		case 0:			//磁盘0为 SPI FLASH盘	 
			STA=0;
			SPI_Flash_Read((u8*)Readbuff, Memory_Offset, Transfer_Length); 
			//Mini板为:SPI_Flash_Read
			break;	  
		case 1:			//磁盘1为SD卡		    
			STA=SD_ReadDisk((u8*)Readbuff, Memory_Offset>>9, Transfer_Length>>9);   
			break;			    
		default:
			return MAL_FAIL;
	}
	if(STA!=0)return MAL_FAIL;
	return MAL_OK;
}



/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
	switch(lun)
	{
		case 0:
			return MAL_OK;
		case 1:
			return MAL_OK; 
		default:
			return MAL_FAIL;
	} 
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

