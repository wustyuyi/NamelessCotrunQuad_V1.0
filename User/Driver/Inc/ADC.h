#ifndef __DAC_H
#define __DAC_H


void Chip_ADC_Init(void);
float calculate_MCU_temperate (float Value);


extern unsigned short average; 
extern unsigned short ADC_Value[10];

#endif

