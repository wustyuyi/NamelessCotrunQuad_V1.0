/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ¿ªÔ´²¢²»µÈÓÚÃâ·Ñ£¬ÏÈÇýÕßµÄÀúÊ·ÒÑ¾­Ö¤Ã÷£¬ÔÚ¹úÄÚÕâ¸ö»·¾³ÏÂ£¬ºÁÎÞÊÕÒæµÄ¿ªÔ´£¬µ¥¿¿·»¼ä¸öÈË°®ºÃÕß£¬×Ô·¢µØ²ÎÓëÏî
								Ä¿ÍêÉÆµÄ·½Ê½ÐÐ²»Í¨£¬ºÃµÄ¿ªÔ´ÏîÄ¿ÐèÒªÇë×¨Ö°ÈËÔ±×öºÃÊÛºó·þÎñ¡¢ÊÖ°ÑÊÖ½ÌÑ§¡¢Í³¼ÆÓÃ»§·´À¡ÐèÇó¡¢ÔÚÊµ¼ùÖÐÍê³É¶Ô²ú
								Æ·µÄÒ»´Î´ÎÍêÉÆÓëµü´úÉý¼¶¡£¾­¹ý×ÛºÏ¿¼ÂÇ£¬ÎÞÃû·É¿Ø¿ªÔ´´úÂëÖÐ£¬³ÌÐò½ö±£Áô¹«Ë¾Õý°æ¼¤»î¹¦ÄÜ´úÂë£¬°æ±¾¼¤»îÎÞÊµ¼Ê
								¹¦ÄÜ£¬ÊôÓÚ¹«Ë¾²úÆ·³£¹æ³ö³§²Ù×÷£¬²»Ó°Ïì¿Í»§Ñ§Ï°£¬ÆäÓà´úÂëÈ«²¿¿ª·Å¸ø¿Í»§Ñ§Ï°£¬¿Í»§ÒÆÖ²ºÍ¶þ´Î¿ª·¢´úÂëÇë±£Áô´ú
								Âë°æÈ¨¡£
-----------------------------------------------------------------------------------------------------------------------/
*               ±¾³ÌÐòÖ»¹©¹ºÂòÕßÑ§Ï°Ê¹ÓÃ£¬°æÈ¨Öø×÷È¨ÊôÓÚÎÞÃû¿Æ´´ÍÅ¶Ó£¬ÎÞÃû¿Æ´´ÍÅ¶Ó½«·É¿Ø³ÌÐòÔ´ÂëÌá¹©¸ø¹ºÂòÕß£¬
*               ¹ºÂòÕßÒªÎªÎÞÃû¿Æ´´ÍÅ¶ÓÌá¹©±£»¤£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃ½«Ô´´úÂëÌá¹©¸øËûÈË£¬²»µÃ½«Ô´´úÂë·Åµ½ÍøÉÏ¹©ËûÈËÃâ·ÑÏÂÔØ£¬ 
*               ¸ü²»ÄÜÒÔ´ËÏúÊÛÄ²Àû£¬Èç·¢ÏÖÉÏÊöÐÐÎª£¬ÎÞÃû¿Æ´´ÍÅ¶Ó½«ËßÖ®ÒÔ·¨ÂÉ½â¾ö£¡£¡£¡
-----------------------------------------------------------------------------------------------------------------------
*                                                 ÎªÊ²Ã´Ñ¡ÔñÎÞÃû´´ÐÂ£¿
*                                         ¸Ð¶¯ÈËÐÄ¼Û¸ñºñµÀ£¬×î¿¿Æ×µÄ¿ªÔ´·É¿Ø£»
*                                         ¹úÄÚÒµ½çÁ¼ÐÄÖ®×÷£¬×î¾«ÖÂµÄÊÛºó·þÎñ£»
*                                         ×·Çó¼«ÖÂÓÃ»§ÌåÑé£¬¸ßÐ§½ø½×Ñ§Ï°Ö®Â·£»
*                                         ÃÈÐÂ²»ÔÙ¹Âµ¥ÇóË÷£¬ºÏÀí°ÑÎÕ¿ªÔ´³ß¶È£»
*                                         ÏìÓ¦¹ú¼Ò·öÆ¶ºÅÕÙ£¬´Ù½ø½ÌÓýÌåÖÆ¹«Æ½£»
*                                         ÐÂÊ±´ú·Ü¶·×î³ö²Ê£¬½¨ÈËÀàÃüÔË¹²Í¬Ìå¡£ 
-----------------------------------------------------------------------------------------------------------------------
*               ÉúÃü²»Ï¢¡¢·Ü¶·²»Ö¹£»Ç°ÈËÔÔÊ÷£¬ºóÈË³ËÁ¹£¡£¡£¡
*               ¿ªÔ´²»Ò×£¬ÇÒÑ§ÇÒÕäÏ§£¬×£ÔçÈÕÄæÏ®¡¢½ø½×³É¹¦£¡£¡£¡
*               Ñ§Ï°ÓÅÐãÕß£¬¼òÀú¿ÉÍÆ¼öµ½DJI¡¢ZEROTECH¡¢XAG¡¢AEE¡¢GDU¡¢AUTEL¡¢EWATT¡¢HIGH GREATµÈ¹«Ë¾¾ÍÒµ
*               ÇóÖ°¼òÀúÇë·¢ËÍ£º15671678205@163.com£¬Ðè±¸×¢ÇóÖ°ÒâÏòµ¥Î»¡¢¸ÚÎ»¡¢´ýÓöµÈ
*               ÎÞÃû¿Æ´´¿ªÔ´·É¿ØQQÈº£º2ºÅÈº465082224¡¢1ºÅÈº540707961£¨ÈËÔ±ÒÑÂú£©
*               CSDN²©¿Í£ºhttp://blog.csdn.net/u011992534
*               ÓÅ¿áID£ºNamelessCotrunÎÞÃûÐ¡¸ç
*               BÕ¾½ÌÑ§ÊÓÆµ£ºhttps://space.bilibili.com/67803559/#/video
*               ¿Í»§Ê¹ÓÃÐÄµÃ¡¢¸Ä½øÒâ¼ûÕ÷¼¯Ìù£ºhttp://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               ÌÔ±¦µêÆÌ£ºhttps://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               °Ù¶ÈÌù°É:ÎÞÃû¿Æ´´¿ªÔ´·É¿Ø
*               ¹«Ë¾¹ÙÍø:www.nameless.tech
*               ÎÞÃû´´ÐÂ¹úÄÚÊ×¿îTI¿ªÔ´·É¿ØÉè¼Æ³õÖÔ¡¢Öªºõ×¨À¸:https://zhuanlan.zhihu.com/p/54471146
*               ÐÞ¸ÄÈÕÆÚ:2019/11/27                    
*               °æ±¾£º»Û·ÉÕßPRO¡ª¡ªWisdomPilot_Pro_V1.0.0
*               °æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
*               Copyright(C) 2019-2025 ÎäººÎÞÃû´´ÐÂ¿Æ¼¼ÓÐÏÞ¹«Ë¾ 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               ÖØÒªÌáÊ¾£º
*               Õý³£ÌÔ±¦ÏÌÓã×ªÊÖµÄ·É¿Ø¡¢ÔùËÍÅóÓÑ¡¢´«¸øÑ§µÜµÄ¶¼¿ÉÒÔ½øÊÛºóÈºÑ§Ï°½»Á÷£¬
*               ²»µÃÖ±½ÓÔÚÍøÉÏÏúÊÛÎÞÃû´´ÐÂ×ÊÁÏ£¬ÎÞÃû´´ÐÂ´úÂëÓÐÉùÃ÷°æÈ¨£¬ËûÈË²»µÃ½«
*               ×ÊÁÏ´úÂë´«ÍøÉÏ¹©ËûÈËÏÂÔØ£¬²»µÃÒÔÄ±ÀûÎªÄ¿µÄÏúÊÛ×ÊÁÏ´úÂë£¬·¢ÏÖÓÐ´Ë²Ù
*               ×÷Õß£¬¹«Ë¾»áÌáÇ°¸æÖª£¬Çë1ÌìÄÚ¼°Ê±´¦Àí£¬·ñÔòÄãµÄÑ§Ð£¡¢µ¥Î»¡¢ÐÕÃû¡¢µç
*               »°¡¢µØÖ·ÐÅÏ¢»á±»Ìù³öÔÚ¹«Ë¾¹ÙÍø¡¢¹Ù·½Î¢ÐÅ¹«ÖÚÆ½Ì¨¡¢¹Ù·½¼¼Êõ²©¿Í¡¢Öªºõ
*               ×¨À¸ÒÔ¼°ÌÔ±¦µêÆÌÊ×Ò³ÓèÒÔ¹«Ê¾¹«¸æ£¬´ËÖÖËù×÷ËùÎª£¬»á³ÉÎª¸öÈËÎÛµã£¬Ó°Ïì
*               ÉýÑ§¡¢ÕÒ¹¤×÷¡¢Éç»áÉùÓþ¡¢ºÜ¿ì¾ÍºÜÔÚÎÞÈË»ú½ç³öÃû£¬ºó¹ûºÜÑÏÖØ¡£
*               Òò´ËÐÐÎª¸ø¹«Ë¾Ôì³ÉÖØ´óËðÊ§Õß£¬»áÒÔ·¨ÂÉÍ¾¾¶½â¾ö£¬¸ÐÐ»ÄúµÄºÏ×÷£¬Ð»Ð»£¡£¡£¡
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "OpticalFlow_LC306.h"


#define OPTICALFLOW_UART UART4
#define SENSOR_IIC_ADDR 0xdc
const static u8 tab_focus[4] = {0x96,0x26,0xbc,0x50};		
const static u8 Sensor_cfg[]={
  //µØÖ·, Êý¾Ý
  0x12, 0x80, 
  0x11, 0x30, 
  0x1b, 0x06, 
  0x6b, 0x43, 
  0x12, 0x20, 
  0x3a, 0x00, 
  0x15, 0x02, 
  0x62, 0x81, 
  0x08, 0xa0, 
  0x06, 0x68, 
  0x2b, 0x20, 
  0x92, 0x25, 
  0x27, 0x97, 
  0x17, 0x01, 
  0x18, 0x79, 
  0x19, 0x00, 
  0x1a, 0xa0, 
  0x03, 0x00, 
  0x13, 0x00, 
  0x01, 0x13, 
  0x02, 0x20, 
  0x87, 0x16, 
  0x8c, 0x01, 
  0x8d, 0xcc, 
  0x13, 0x07, 
  0x33, 0x10, 
  0x34, 0x1d, 
  0x35, 0x46, 
  0x36, 0x40, 
  0x37, 0xa4, 
  0x38, 0x7c, 
  0x65, 0x46, 
  0x66, 0x46, 
  0x6e, 0x20, 
  0x9b, 0xa4, 
  0x9c, 0x7c, 
  0xbc, 0x0c, 
  0xbd, 0xa4, 
  0xbe, 0x7c, 
  0x20, 0x09, 
  0x09, 0x03, 
  0x72, 0x2f, 
  0x73, 0x2f, 
  0x74, 0xa7, 
  0x75, 0x12, 
  0x79, 0x8d, 
  0x7a, 0x00, 
  0x7e, 0xfa, 
  0x70, 0x0f, 
  0x7c, 0x84, 
  0x7d, 0xba, 
  0x5b, 0xc2, 
  0x76, 0x90, 
  0x7b, 0x55, 
  0x71, 0x46, 
  0x77, 0xdd, 
  0x13, 0x0f, 
  0x8a, 0x10, 
  0x8b, 0x20, 
  0x8e, 0x21, 
  0x8f, 0x40, 
  0x94, 0x41, 
  0x95, 0x7e, 
  0x96, 0x7f, 
  0x97, 0xf3, 
  0x13, 0x07, 
  0x24, 0x58, 
  0x97, 0x48, 
  0x25, 0x08, 
  0x94, 0xb5, 
  0x95, 0xc0, 
  0x80, 0xf4, 
  0x81, 0xe0, 
  0x82, 0x1b, 
  0x83, 0x37, 
  0x84, 0x39, 
  0x85, 0x58, 
  0x86, 0xff, 
  0x89, 0x15, 
  0x8a, 0xb8, 
  0x8b, 0x99, 
  0x39, 0x98, 
  0x3f, 0x98, 
  0x90, 0xa0, 
  0x91, 0xe0, 
  0x40, 0x20, 
  0x41, 0x28, 
  0x42, 0x26, 
  0x43, 0x25, 
  0x44, 0x1f, 
  0x45, 0x1a, 
  0x46, 0x16, 
  0x47, 0x12, 
  0x48, 0x0f, 
  0x49, 0x0d, 
  0x4b, 0x0b, 
  0x4c, 0x0a, 
  0x4e, 0x08, 
  0x4f, 0x06, 
  0x50, 0x06, 
  0x5a, 0x56, 
  0x51, 0x1b, 
  0x52, 0x04, 
  0x53, 0x4a, 
  0x54, 0x26, 
  0x57, 0x75, 
  0x58, 0x2b, 
  0x5a, 0xd6, 
  0x51, 0x28, 
  0x52, 0x1e, 
  0x53, 0x9e, 
  0x54, 0x70, 
  0x57, 0x50, 
  0x58, 0x07, 
  0x5c, 0x28, 
  0xb0, 0xe0, 
  0xb1, 0xc0, 
  0xb2, 0xb0, 
  0xb3, 0x4f, 
  0xb4, 0x63, 
  0xb4, 0xe3, 
  0xb1, 0xf0, 
  0xb2, 0xa0, 
  0x55, 0x00, 
  0x56, 0x40, 
  0x96, 0x50, 
  0x9a, 0x30, 
  0x6a, 0x81, 
  0x23, 0x33, 
  0xa0, 0xd0, 
  0xa1, 0x31, 
  0xa6, 0x04, 
  0xa2, 0x0f, 
  0xa3, 0x2b, 
  0xa4, 0x0f, 
  0xa5, 0x2b, 
  0xa7, 0x9a, 
  0xa8, 0x1c, 
  0xa9, 0x11, 
  0xaa, 0x16, 
  0xab, 0x16, 
  0xac, 0x3c, 
  0xad, 0xf0, 
  0xae, 0x57, 
  0xc6, 0xaa, 
  0xd2, 0x78, 
  0xd0, 0xb4, 
  0xd1, 0x00, 
  0xc8, 0x10, 
  0xc9, 0x12, 
  0xd3, 0x09, 
  0xd4, 0x2a, 
  0xee, 0x4c, 
  0x7e, 0xfa, 
  0x74, 0xa7, 
  0x78, 0x4e, 
  0x60, 0xe7, 
  0x61, 0xc8, 
  0x6d, 0x70, 
  0x1e, 0x39, 
  0x98, 0x1a
};

static void SensorConfig_UartSend(u8 dat)
{
  while(USART_GetFlagStatus(OPTICALFLOW_UART, USART_FLAG_TXE)==RESET);
  USART_SendData(OPTICALFLOW_UART, dat);	
}

uint16_t LC306_Ready_Cnt=0;
/**************************************************/		
uint8_t Config_Init_Uart()
{
  u16 i;
  u16 len ;
  u8 recv[3];
  int recv_cnt;		
  delay_ms(100);		
  len = sizeof(Sensor_cfg);	
  SensorConfig_UartSend(0xAA);//0xAAÖ¸Áî
  SensorConfig_UartSend(0xAB);//0xABÖ¸Áî		 
  SensorConfig_UartSend(tab_focus[0]);		
  SensorConfig_UartSend(tab_focus[1]);
  SensorConfig_UartSend(tab_focus[2]);
  SensorConfig_UartSend(tab_focus[3]);
  SensorConfig_UartSend(tab_focus[0]^tab_focus[1]^tab_focus[2]^tab_focus[3]);			 		 
  recv_cnt = 0;
  LC306_Ready_Cnt=65535;
  while(recv_cnt<3)  //Èç½ÓÊÕ²»µ½Ä£¿é·µ»ØµÄÈý¸öÊý£¬¿ÉÑÓÊ±10ms´Ó0xAAÖ¸Áî¿ªÊ¼ÖØÐÂÅäÖÃ
  {
    while(USART_GetFlagStatus(OPTICALFLOW_UART, USART_FLAG_RXNE)==RESET)
    {
      LC306_Ready_Cnt--;
      if(LC306_Ready_Cnt==0) return 0;
    };
    recv[recv_cnt++] = USART_ReceiveData(OPTICALFLOW_UART);							
  }			
  if(((recv[0]^recv[1]) == recv[2]) & (recv[1] == 0x00)) ;
  //printf("AB Command configuration successconfig succefful\n");		
  
  for(i=0;i<len;i+=2)//0xBBÖ  ¸Áî
  {
    SensorConfig_UartSend(0xBB);		 
    SensorConfig_UartSend(SENSOR_IIC_ADDR);		
    SensorConfig_UartSend(Sensor_cfg[i]);
    SensorConfig_UartSend(Sensor_cfg[i+1]);
    SensorConfig_UartSend(SENSOR_IIC_ADDR^Sensor_cfg[i]^Sensor_cfg[i+1]);	 
    recv_cnt = 0;
    while(recv_cnt<3)  //Èç½ÓÊÕ²»µ½Ä£¿é·µ»ØµÄÈý¸öÊý£¬¿ÉÑÓÊ±1msÖØÐÂ·¢ËÍ0xBBÖ¸Áî
    {
      while(USART_GetFlagStatus(OPTICALFLOW_UART, USART_FLAG_RXNE)==RESET){};
      recv[recv_cnt++] = USART_ReceiveData(OPTICALFLOW_UART);							
    }			
    if(((recv[0]^recv[1]) == recv[2]) & (recv[1] == 0x00));
    //printf("BB Command configuration successconfig succefful\n");								 
  }	 		 
  SensorConfig_UartSend(0xDD);//0xDD		
  //printf("Configuration success\n");
  return 1;
}			 


