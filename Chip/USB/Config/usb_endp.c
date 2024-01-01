/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
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
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
#include "Queue.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t txBuffter[VIRTUAL_COM_PORT_DATA_SIZE] = {0};
static volatile uint8_t txFlg = 0;
static volatile uint32_t FrameCount = 0;



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)
{
    uint16_t len = 0;

    if (1 == txFlg)
    {
        len = USB_TxRead(txBuffter, sizeof(txBuffter));

        if (len > 0)
        {
            UserToPMABufferCopy(txBuffter, ENDP1_TXADDR, len);
            SetEPTxCount(ENDP1, len);
            SetEPTxValid(ENDP1);
            FrameCount = 0;
        }
        else
        {
            txFlg = 0;
        }
    }
}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
/*
void EP3_OUT_Callback(void)
{
  static uint8_t buffter[VIRTUAL_COM_PORT_DATA_SIZE] = {0};
  uint16_t USB_Rx_Cnt;
  //Get the received data buffer and update the counter
  USB_Rx_Cnt = USB_SIL_Read(EP3_OUT, buffter);
  //USB data will be immediately processed, this allow next USB traffic being
  //NAKed till the end of the USART Xfer
  USB_RxWrite(buffter, USB_Rx_Cnt);
  USB_ReceiveFlg = true;
  //Enable the receive of data on EP3
  SetEPRxValid(ENDP3);

}
*/
void EP3_OUT_Callback(void)
{
  PMAToUserBufferCopy(Hid_RxData, ENDP3_RXADDR,64);
  USB_ReceiveFlg = true;
  SetEPRxStatus(ENDP3, EP_RX_VALID);
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SOF_Callback(void)
{
    uint16_t len = 0;
    if(bDeviceState == CONFIGURED)
    {
        if (0 == txFlg)
        {
            if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
            {
                /* Reset the frame counter */
                FrameCount = 0;
                /* Check the data to be sent through IN pipe */
                len = USB_TxRead(txBuffter, sizeof(txBuffter));
                if (len > 0)
                {
                    UserToPMABufferCopy(txBuffter, ENDP1_TXADDR, len);
                    SetEPTxCount(ENDP1, len);
                    SetEPTxValid(ENDP1);
                    txFlg = 1;
                }
            }
        }
    }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

