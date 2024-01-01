#ifndef _OPTICALFLOW_CONTROL_H
#define _OPTICALFLOW_CONTROL_H


#define OpticalFlow_Speed_Control_Mode 1
#define OpticalFlow_Speed_Control_Max  250


void OpticalFlow_Control_Pure(uint8_t force_brake_flag);
void OpticalFlow_Control(uint8_t force_brake_flag);
void OpticalFlow_SINS_Reset(void);
void OpticalFlow_Ctrl_Reset(void);
void OpticalFlow_Vel_Control(Vector2f target);
void OpticalFlow_Pos_Control(void);
void OpticalFlow_Y_Vel_Control(float target_y);

extern Vector2f OpticalFlow_Pos_Ctrl_Expect;
extern Vector2f OpticalFlow_Pos_Ctrl_Err;
extern Vector2f OpticalFlow_Pos_Ctrl_Integrate;
extern Vector2f OpticalFlow_Pos_Ctrl_Output;
extern Vector2f OpticalFlow_Ctrl_Err;
extern Vector2f OpticalFlow_Ctrl_Integrate;
extern Vector2f OpticalFlow_Ctrl_Output,OpticalFlow_Ctrl_Expect;


#endif
