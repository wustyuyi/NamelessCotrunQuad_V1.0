#ifndef __BH1750_H
#define __BH1750_H

void Single_Write_BH1750(unsigned char REG_Address);
void BH1750_Init(void);
void BH1750_Read(void);

extern float LightValue;
#endif