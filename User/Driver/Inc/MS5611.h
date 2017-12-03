#ifndef __MS5611_H_
#define __MS5611_H_

uint8_t i2c_readAck(void);
uint8_t i2c_readNak(void);


void  Baro_init(void);
uint8_t Baro_update(void);
void Read_MS5611_Offset(void);

extern float Alt_offset_Pa,AirPresure_Altitude_Origion;
extern int32_t baroPressure;
extern float Baro;
float getEstimatedAltitude(float baroPress);

void MS5611_StateMachine_20ms(void);

extern uint16 MS5611_Update_finished,MS5611_Update;
void MS5611_StateMachine(void);

#endif

