#ifndef _TOFSENSE_H
#define _TOFSENSE_H


typedef struct
{
	uint8_t frame_header;
	uint8_t function_mark;
	uint8_t reserved1;
	uint8_t id;
	uint32_t system_time;
	uint32_t dis;
	uint8_t dis_status;      //0��Ч��1��Ч
	uint16_t signal_strength;//��ֵԽ����������ź�Խǿ
	uint8_t range_precision; //��ֵԽС��������Խ��
	uint8_t sum_check;
	
	float distance;
	uint8_t update_flag;
	uint8_t valid;
  uint16_t period_ms;
	
	uint8_t init;
	float height_backups[20];
	float height_standard_deviation;
	float average;
}tofsense;


void tofsense_prase(uint8_t data);


#endif


