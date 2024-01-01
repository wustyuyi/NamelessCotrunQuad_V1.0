/**
  ******************************************************************************
  * @file    memory.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Memory management layer
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

#include "memory.h"
#include "usb_scsi.h"
#include "usb_bot.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "hw_config.h"
#include "mass_mal.h"
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Block_Read_count = 0;
__IO uint32_t Block_offset;
__IO uint32_t Counter = 0;
uint32_t  Idx;
uint8_t TransferState = TXFR_IDLE;
/* Extern variables ----------------------------------------------------------*/
u32 *Data_Buffer;			//�ⲿ������malloc���� BULK_MAX_PACKET_SIZE*2*4 ��ô���ֽڵ��ڴ档
extern u8 *Bulk_Data_Buff;	//��usb_bot.c����������

extern uint16_t Data_Len;
extern uint8_t Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;

 ////////////////////////////�Լ������һ�����USB״̬�ļĴ���///////////////////
//bit0:��ʾ����������SD��д������
//bit1:��ʾ��������SD����������
//bit2:SD��д���ݴ����־λ
//bit3:SD�������ݴ����־λ
//bit4:1,��ʾ��������ѯ����(�������ӻ�������)
vu8 USB_STATUS_REG=0;

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Read_Memory(uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length)
{
	static uint64_t Offset, Length;//Ҫ֧�ִ���4G��SD��,����ʹ��long long(64λ)��������
	u8 STA;//����һ������

	if (TransferState == TXFR_IDLE )
	{
		Offset = (long long)Memory_Offset * Mass_Block_Size[lun];
		Length = (long long)Transfer_Length * Mass_Block_Size[lun];
		TransferState = TXFR_ONGOING;
	}

	if (TransferState == TXFR_ONGOING )
	{
		if (!Block_Read_count)
		{
			STA=MAL_Read(lun ,Offset,Data_Buffer,Mass_Block_Size[lun]);
			if(STA)USB_STATUS_REG|=0X08;//SD��������!


			USB_SIL_Write(EP1_IN, (uint8_t *)Data_Buffer, BULK_MAX_PACKET_SIZE);

			Block_Read_count = Mass_Block_Size[lun] - BULK_MAX_PACKET_SIZE;
			Block_offset = BULK_MAX_PACKET_SIZE;
		}else
		{
			USB_SIL_Write(EP1_IN, (uint8_t *)Data_Buffer + Block_offset, BULK_MAX_PACKET_SIZE);

			Block_Read_count -= BULK_MAX_PACKET_SIZE;
			Block_offset += BULK_MAX_PACKET_SIZE;
		}

		SetEPTxCount(ENDP1, BULK_MAX_PACKET_SIZE);
		SetEPTxStatus(ENDP1, EP_TX_VALID);  
		Offset += BULK_MAX_PACKET_SIZE;
		Length -= BULK_MAX_PACKET_SIZE;

		CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;
		//Led_RW_ON();
	}
	if (Length == 0)
	{
		Block_Read_count = 0;
		Block_offset = 0;
		Offset = 0;
		Bot_State = BOT_DATA_IN_LAST;
		TransferState = TXFR_IDLE;
		//Led_RW_OFF();
	}
}

/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Write_Memory (uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length)
{

	static uint64_t W_Offset, W_Length;//Ҫ֧�ִ���4G��SD��,����ʹ��long long(64λ)��������
	u8 STA;//����һ������

	uint32_t temp =  Counter + 64;

	if (TransferState == TXFR_IDLE )
	{
		W_Offset = (long long)Memory_Offset * Mass_Block_Size[lun];
		W_Length = (long long)Transfer_Length * Mass_Block_Size[lun];
		TransferState = TXFR_ONGOING;
	} 
	if (TransferState == TXFR_ONGOING )
	{

		for (Idx = 0 ; Counter < temp; Counter++)
		{
			*((uint8_t *)Data_Buffer + Counter) = Bulk_Data_Buff[Idx++];
		}

		W_Offset += Data_Len;
		W_Length -= Data_Len;

		if (!(W_Length % Mass_Block_Size[lun]))
		{
			Counter = 0;
			STA=MAL_Write(lun,W_Offset - Mass_Block_Size[lun],Data_Buffer,Mass_Block_Size[lun]);
			if(STA)USB_STATUS_REG|=0X04;//SD��д����!

		} 
		CSW.dDataResidue -= Data_Len;
		SetEPRxStatus(ENDP2, EP_RX_VALID); /* enable the next transaction*/   
		//Led_RW_ON();
	}

	if ((W_Length == 0) || (Bot_State == BOT_CSW_Send))
	{
		Counter = 0;
		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
		TransferState = TXFR_IDLE;
		//Led_RW_OFF();
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

