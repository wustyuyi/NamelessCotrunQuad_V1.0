///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.60.1.11101/W32 for ARM      03/Dec/2017  17:09:22
// Copyright 1999-2016 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Src\MPU6050.c
//    Command line =
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Src\MPU6050.c -D
//        USE_STDPERIPH_DRIVER -D STM32F10X_HD -D ARM_MATH_CM3 -lC
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Debug\List -lA
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Debug\List -o
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Debug\Obj --no_cse --no_unroll
//        --no_inline --no_code_motion --no_tbaa --no_clustering
//        --no_scheduling --debug --endian=little --cpu=Cortex-M3 -e --fpu=None
//        --dlib_config "D:\Program Files (x86)\IAR Systems\Embedded Workbench
//        7.4\arm\INC\c\DLib_Config_Full.h" -I
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Chip\inc\ -I
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Chip\CMSIS\ -I
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\ -I
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Inc\ -I
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Controler\Inc\ -I
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\AHRS\ -Ol
//        --use_c++_inline -I "D:\Program Files (x86)\IAR Systems\Embedded
//        Workbench 7.4\arm\CMSIS\Include\" -D ARM_MATH_CM3
//    Locale       =  C
//    List file    =
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Debug\List\MPU6050.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_file_descriptor", "1"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN Acce_Control_Filter
        EXTERN Cos_Pitch
        EXTERN Cos_Roll
        EXTERN Cos_Yaw
        EXTERN FilterBefore_NamelessQuad
        EXTERN LPButterworth
        EXTERN Sin_Pitch
        EXTERN Sin_Roll
        EXTERN Sin_Yaw
        EXTERN Single_ReadI2C
        EXTERN Single_WriteI2C
        EXTERN __aeabi_cfcmple
        EXTERN __aeabi_d2f
        EXTERN __aeabi_ddiv
        EXTERN __aeabi_dmul
        EXTERN __aeabi_f2d
        EXTERN __aeabi_f2iz
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fdiv
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub
        EXTERN __aeabi_i2f
        EXTERN __aeabi_ui2f
        EXTERN atan
        EXTERN delay_ms
        EXTERN sqrt

        PUBLIC ACCE_X
        PUBLIC ACCE_Y
        PUBLIC ACCE_Z
        PUBLIC Acce_Correct
        PUBLIC Acce_Correct_Filter
        PUBLIC Acce_Correct_Update_Flag
        PUBLIC Angle_Calculate
        PUBLIC Angle_X
        PUBLIC Angle_Y
        PUBLIC Angle_Z
        PUBLIC `B`
        PUBLIC Butter_1HZ_Parameter_Acce
        PUBLIC Butter_Buffer_Correct
        PUBLIC Data_X_g
        PUBLIC Data_Y_g
        PUBLIC Data_Z_g
        PUBLIC GET_ACC_DATA
        PUBLIC GET_GYRO
        PUBLIC GET_GYRO_DATA
        PUBLIC GET_MPU_DATA
        PUBLIC GYRO_LPF
        PUBLIC GetData
        PUBLIC GildeAverageValueFilter
        PUBLIC Gyro_BufferData
        PUBLIC Gyro_Parameter
        PUBLIC Gyro_X
        PUBLIC Gyro_Y
        PUBLIC Gyro_Z
        PUBLIC IMU_Calibration
        PUBLIC IMU_Filter
        PUBLIC InitMPU6050_GY86
        PUBLIC K
        PUBLIC X_Origion
        PUBLIC X_g
        PUBLIC X_g_av
        PUBLIC X_g_off
        PUBLIC X_w
        PUBLIC X_w_av
        PUBLIC X_w_off
        PUBLIC Y_Origion
        PUBLIC Y_g
        PUBLIC Y_g_av
        PUBLIC Y_g_off
        PUBLIC Y_w
        PUBLIC Y_w_av
        PUBLIC Y_w_off
        PUBLIC Z_Origion
        PUBLIC Z_g
        PUBLIC Z_g_av
        PUBLIC Z_g_off
        PUBLIC Z_w
        PUBLIC Z_w_av
        PUBLIC Z_w_off
        PUBLIC accButter
        PUBLIC g_Gyro_xoffset
        PUBLIC g_Gyro_yoffset
        PUBLIC g_Gyro_zoffset
        PUBLIC gyroButter
        PUBLIC imu
        PUBLIC invSqrt

          CFI Names cfiNames0
          CFI StackFrame CFA R13 DATA
          CFI Resource R0:32, R1:32, R2:32, R3:32, R4:32, R5:32, R6:32, R7:32
          CFI Resource R8:32, R9:32, R10:32, R11:32, R12:32, R13:32, R14:32
          CFI EndNames cfiNames0

          CFI Common cfiCommon0 Using cfiNames0
          CFI CodeAlign 2
          CFI DataAlign 4
          CFI ReturnAddress R14 CODE
          CFI CFA R13+0
          CFI R0 Undefined
          CFI R1 Undefined
          CFI R2 Undefined
          CFI R3 Undefined
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI R8 SameValue
          CFI R9 SameValue
          CFI R10 SameValue
          CFI R11 SameValue
          CFI R12 Undefined
          CFI R14 SameValue
          CFI EndCommon cfiCommon0

// D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Src\MPU6050.c
//    1 #include "Headfile.h"
//    2 #include "MPU6050.h"
//    3 /*----------------------------------------------------------------------------------------------------------------------/
//    4         *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
//    5         *               无名科创团队将飞控程序源码提供给购买者，
//    6         *               购买者要为无名科创团队提供保护，
//    7         *               未经作者许可，不得将源代码提供给他人
//    8         *               不得将源代码放到网上供他人免费下载，
//    9         *               更不能以此销售牟利，如发现上述行为，
//   10         *               无名科创团队将诉之以法律解决！！！
//   11 -----------------------------------------------------------------------------------------------------------------------/
//   12         *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
//   13         *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
//   14 -----------------------------------------------------------------------------------------------------------------------/
//   15 	*		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
//   16 	*		CSDN博客: http://blog.csdn.net/u011992534
//   17 	*               优酷ID：NamelessCotrun无名小哥
//   18 	*               无名科创开源飞控QQ群：540707961
//   19         *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
//   20         *               百度贴吧:无名科创开源飞控
//   21         *               修改日期:2017/10/30
//   22         *               版本：V1.1
//   23         *               版权所有，盗版必究。
//   24         *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
//   25         *               All rights reserved
//   26 ----------------------------------------------------------------------------------------------------------------------*/

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//   27 float  Y_g_off = -100,X_g_off = 40,Z_g_off =0;
Y_g_off:
        DC32 0C2C80000H

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
X_g_off:
        DC32 42200000H

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_g_off:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   28 float  X_w_off =0,Y_w_off =0,Z_w_off =0;
X_w_off:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_w_off:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_w_off:
        DS8 4

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//   29 float K[3]={1.0,1.0,1.0};//默认标度误差
K:
        DC32 3F800000H, 3F800000H, 3F800000H

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   30 float B[3]={0,0,0};//默认零位误差
`B`:
        DS8 12
//   31 //********************************************************

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   32 float  X_g,Y_g,Z_g;
X_g:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_g:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_g:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   33 float  X_w,Y_w,Z_w;
X_w:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_w:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_w:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   34 float  X_g_av,Y_g_av,Z_g_av;//可用的加速度计值
X_g_av:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_g_av:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_g_av:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   35 float  X_w_av,Y_w_av,Z_w_av;//可用的陀螺仪值
X_w_av:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_w_av:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_w_av:
        DS8 4
//   36
//   37 //200_30z

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
//   38 const static float b_acc[3] ={0.1311064399166,   0.2622128798333,   0.1311064399166};
b_acc:
        DC32 3E0640C4H, 3E8640C4H, 3E0640C4H

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
//   39 const static float a_acc[3] ={1,  -0.7477891782585,    0.272214937925};
a_acc:
        DC32 3F800000H, 0BF3F6F1DH, 3E8B5FC2H
//   40 struct _ButterWorth2d_Acc_Tag
//   41 {
//   42 	int16_t input[3];
//   43 	int16_t output[3];
//   44 };
//   45

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   46 struct _ButterWorth2d_Acc_Tag accButter[3] =
accButter:
        DS8 36
//   47 {
//   48 	/* input[3] output[3] */
//   49 	{0, 0, 0, 0, 0, 0},		// X-axis
//   50 	{0, 0, 0, 0, 0, 0},		// Y-axis
//   51 	{0, 0, 0, 0, 0, 0},		// Z-axis
//   52 };
//   53

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   54 struct _ButterWorth2d_Acc_Tag gyroButter[3] =
gyroButter:
        DS8 36
//   55 {
//   56 	/* input[3] output[3] */
//   57 	{0, 0, 0, 0, 0, 0},		// X-axis
//   58 	{0, 0, 0, 0, 0, 0},		// Y-axis
//   59 	{0, 0, 0, 0, 0, 0},		// Z-axis
//   60 };
//   61

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   62 _IMU_Tag imu;
imu:
        DS8 48
//   63 void IMU_Filter(void);

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function invSqrt
        THUMB
//   64 float invSqrt(float x)
//   65 {
invSqrt:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//   66   float halfx = 0.5f * x;
        MOVS     R0,#+1056964608
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
//   67   float y = x;
//   68   long i = *(long*)&y;
//   69
//   70   i = 0x5f3759df - (i>>1);
        LDR.W    R1,??DataTable7  ;; 0x5f3759df
        SUBS     R4,R1,R4, ASR #+1
//   71   y = *(float*)&i;
//   72   y = y * (1.5f - (halfx * y * y));
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,#+1069547520
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
//   73
//   74   return y;
        MOVS     R0,R4
        POP      {R4,PC}          ;; return
//   75 }
          CFI EndBlock cfiBlock0
//   76
//   77
//   78 //**************************************
//   79 //MPU6050
//   80 //**************************************

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function InitMPU6050_GY86
        THUMB
//   81 void InitMPU6050_GY86(void)
//   82 {
InitMPU6050_GY86:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//   83 	Single_WriteI2C(0xD0,PWR_MGMT_1  , 0x00);//关闭所有中断,解除休眠
        MOVS     R2,#+0
        MOVS     R1,#+107
        MOVS     R0,#+208
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
        MOVS     R2,#+0
        MOVS     R1,#+25
        MOVS     R0,#+208
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
        MOVS     R2,#+2
        MOVS     R1,#+26
        MOVS     R0,#+208
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
        MOVS     R2,#+24
        MOVS     R1,#+27
        MOVS     R0,#+208
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
        MOVS     R2,#+16
        MOVS     R1,#+28
        MOVS     R0,#+208
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock1
        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function GetData
        THUMB
GetData:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R1,R4
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+208
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        MOVS     R5,R0
//  100 	Ld=Single_ReadI2C(0xD0,REG_Address+1);
        ADDS     R1,R4,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+208
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
//  101 	return (Hd<<8)+Ld;
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        ADDS     R0,R0,R5, LSL #+8
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        POP      {R1,R4,R5,PC}    ;; return
//  102 }
          CFI EndBlock cfiBlock2
        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  107 float Data_X_g[N];
Data_X_g:
        DS8 120

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  108 float Data_Y_g[N];
Data_Y_g:
        DS8 120

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  109 float Data_Z_g[N];
Data_Z_g:
        DS8 120

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function GildeAverageValueFilter
        THUMB
//  110 float GildeAverageValueFilter(float NewValue,float *Data)
//  111 {
GildeAverageValueFilter:
        PUSH     {R4-R8,LR}
          CFI R14 Frame(CFA, -4)
          CFI R8 Frame(CFA, -8)
          CFI R7 Frame(CFA, -12)
          CFI R6 Frame(CFA, -16)
          CFI R5 Frame(CFA, -20)
          CFI R4 Frame(CFA, -24)
          CFI CFA R13+24
        MOVS     R4,R1
//  112 	float max,min;
//  113 	float sum;
//  114 	unsigned char i;
//  115 	Data[0]=NewValue;
        STR      R0,[R4, #+0]
//  116 	max=Data[0];
        LDR      R5,[R4, #+0]
//  117 	min=Data[0];
        LDR      R6,[R4, #+0]
//  118 	sum=Data[0];
        LDR      R7,[R4, #+0]
//  119 	for(i=N-1;i!=0;i--)
        MOVS     R8,#+29
        B.N      ??GildeAverageValueFilter_0
//  120 	{
//  121 	  if(Data[i]>max) max=Data[i];
//  122 	  else if(Data[i]<min) min=Data[i];
??GildeAverageValueFilter_1:
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        LDR      R0,[R4, R8, LSL #+2]
        MOVS     R1,R6
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??GildeAverageValueFilter_2
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        LDR      R6,[R4, R8, LSL #+2]
//  123 	  sum+=Data[i];
??GildeAverageValueFilter_2:
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        LDR      R0,[R4, R8, LSL #+2]
        MOVS     R1,R7
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R7,R0
//  124 	  Data[i]=Data[i-1];
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        ADD      R0,R4,R8, LSL #+2
        LDR      R0,[R0, #-4]
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        STR      R0,[R4, R8, LSL #+2]
        SUBS     R8,R8,#+1
??GildeAverageValueFilter_0:
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        CMP      R8,#+0
        BEQ.N    ??GildeAverageValueFilter_3
        MOVS     R0,R5
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        LDR      R1,[R4, R8, LSL #+2]
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??GildeAverageValueFilter_1
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        LDR      R5,[R4, R8, LSL #+2]
        B.N      ??GildeAverageValueFilter_2
//  125 	}
//  126 	 i=N-2;
??GildeAverageValueFilter_3:
        MOVS     R8,#+28
//  127 	 sum=sum-max-min;
        MOVS     R0,R7
        MOVS     R1,R5
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R1,R6
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R7,R0
//  128 	 sum=sum/i;
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        MOV      R0,R8
          CFI FunCall __aeabi_ui2f
        BL       __aeabi_ui2f
        MOVS     R1,R0
        MOVS     R0,R7
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOVS     R7,R0
//  129 	 return(sum);
        MOVS     R0,R7
        POP      {R4-R8,PC}       ;; return
//  130 }
          CFI EndBlock cfiBlock3
//  131
//  132 /**********************************
//  133 函数名：void IMU_Calibration(void)
//  134 说明：MPU6050标定
//  135 入口：无
//  136 出口：无
//  137 备注：用来开机时设定陀螺仪的零值
//  138 **********************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function GET_GYRO
        THUMB
//  139 void GET_GYRO(void)
//  140 {
GET_GYRO:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  141 	X_w  = GetData(GYRO_XOUT_H);
        MOVS     R0,#+67
          CFI FunCall GetData
        BL       GetData
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_1
        STR      R0,[R1, #+0]
//  142 	Y_w  = GetData(GYRO_YOUT_H);
        MOVS     R0,#+69
          CFI FunCall GetData
        BL       GetData
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_2
        STR      R0,[R1, #+0]
//  143 	Z_w  = GetData(GYRO_ZOUT_H);
        MOVS     R0,#+71
          CFI FunCall GetData
        BL       GetData
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_3
        STR      R0,[R1, #+0]
//  144 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  145 s32 g_Gyro_xoffset = 0, g_Gyro_yoffset = 0, g_Gyro_zoffset = 0;
g_Gyro_xoffset:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
g_Gyro_yoffset:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
g_Gyro_zoffset:
        DS8 4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function IMU_Calibration
        THUMB
//  146 void IMU_Calibration(void)
//  147 {
IMU_Calibration:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//  148 	u8 i;
//  149 	for (i = 0; i < 100; i++)			//连续采样30次，一共耗时30*3=90ms
        MOVS     R4,#+0
        B.N      ??IMU_Calibration_0
//  150 	{
//  151 		GET_GYRO();						//读取MPU6050的值
??IMU_Calibration_1:
          CFI FunCall GET_GYRO
        BL       GET_GYRO
//  152 		g_Gyro_xoffset +=X_w;
        LDR.W    R0,??DataTable7_4
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_1
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable7_4
        STR      R0,[R1, #+0]
//  153 		g_Gyro_yoffset +=Y_w;
        LDR.W    R0,??DataTable7_5
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_2
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable7_5
        STR      R0,[R1, #+0]
//  154 		g_Gyro_zoffset +=Z_w;
        LDR.W    R0,??DataTable7_6
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_3
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable7_6
        STR      R0,[R1, #+0]
//  155 		delay_ms(5);
        MOVS     R0,#+5
          CFI FunCall delay_ms
        BL       delay_ms
//  156 	}
        ADDS     R4,R4,#+1
??IMU_Calibration_0:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+100
        BLT.N    ??IMU_Calibration_1
//  157 	X_w_off =g_Gyro_xoffset/100;//得到标定偏移
        LDR.W    R0,??DataTable7_4
        LDR      R0,[R0, #+0]
        MOVS     R1,#+100
        SDIV     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_7
        STR      R0,[R1, #+0]
//  158 	Y_w_off =g_Gyro_yoffset/100;
        LDR.W    R0,??DataTable7_5
        LDR      R0,[R0, #+0]
        MOVS     R1,#+100
        SDIV     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_8
        STR      R0,[R1, #+0]
//  159 	Z_w_off =g_Gyro_zoffset/100;
        LDR.W    R0,??DataTable7_6
        LDR      R0,[R0, #+0]
        MOVS     R1,#+100
        SDIV     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_9
        STR      R0,[R1, #+0]
//  160 }
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock5
//  161

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function GET_ACC_DATA
        THUMB
//  162 void GET_ACC_DATA(void)
//  163 {
GET_ACC_DATA:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  164 	X_g    = GetData(ACCEL_XOUT_H)-X_g_off;
        MOVS     R0,#+59
          CFI FunCall GetData
        BL       GetData
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_10
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_11
        STR      R0,[R1, #+0]
//  165 	X_g_av = GildeAverageValueFilter(X_g,Data_X_g);
        LDR.W    R1,??DataTable7_12
        LDR.W    R0,??DataTable7_11
        LDR      R0,[R0, #+0]
          CFI FunCall GildeAverageValueFilter
        BL       GildeAverageValueFilter
        LDR.W    R1,??DataTable7_13
        STR      R0,[R1, #+0]
//  166 	Y_g    = GetData(ACCEL_YOUT_H)-Y_g_off;
        MOVS     R0,#+61
          CFI FunCall GetData
        BL       GetData
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_14
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_15
        STR      R0,[R1, #+0]
//  167 	Y_g_av = GildeAverageValueFilter(Y_g,Data_Y_g);
        LDR.W    R1,??DataTable7_16
        LDR.W    R0,??DataTable7_15
        LDR      R0,[R0, #+0]
          CFI FunCall GildeAverageValueFilter
        BL       GildeAverageValueFilter
        LDR.W    R1,??DataTable7_17
        STR      R0,[R1, #+0]
//  168 	Z_g    = GetData(ACCEL_ZOUT_H)-Z_g_off;
        MOVS     R0,#+63
          CFI FunCall GetData
        BL       GetData
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_18
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_19
        STR      R0,[R1, #+0]
//  169 	Z_g_av = GildeAverageValueFilter(Z_g,Data_Z_g);
        LDR.W    R1,??DataTable7_20
        LDR.W    R0,??DataTable7_19
        LDR      R0,[R0, #+0]
          CFI FunCall GildeAverageValueFilter
        BL       GildeAverageValueFilter
        LDR.W    R1,??DataTable7_21
        STR      R0,[R1, #+0]
//  170 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock6
//  171
//  172
//  173

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  174 Butter_Parameter Gyro_Parameter={
Gyro_Parameter:
        DC32 3F800000H, 3EBD32B1H, 3E4883EAH, 3EC85D2AH, 3F485D2AH, 3EC85D2AH
//  175 //200hz---30hz
//  176 //1,  -0.7477891782585,    0.272214937925,
//  177 //0.1311064399166,   0.2622128798333,   0.1311064399166
//  178   //200hz---60hz
//  179 1,   0.3695273773512,   0.1958157126558,
//  180 0.3913357725018,   0.7826715450035,   0.3913357725018
//  181
//  182
//  183 };

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  184 Butter_BufferData Gyro_BufferData[3];
Gyro_BufferData:
        DS8 72

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function GYRO_LPF
        THUMB
//  185 float GYRO_LPF(float curr_inputer,
//  186                Butter_BufferData *Buffer,
//  187                Butter_Parameter *Parameter)
//  188 {
GYRO_LPF:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R4,R1
        MOVS     R5,R2
//  189         /* 加速度计Butterworth滤波 */
//  190 	/* 获取最新x(n) */
//  191         Buffer->Input_Butter[2]=curr_inputer;
        STR      R0,[R4, #+8]
//  192 	/* Butterworth滤波 */
//  193         Buffer->Output_Butter[2]=
//  194          Parameter->b[0] * Buffer->Input_Butter[2]
//  195         +Parameter->b[1] * Buffer->Input_Butter[1]
//  196 	+Parameter->b[2] * Buffer->Input_Butter[0]
//  197         -Parameter->a[1] * Buffer->Output_Butter[1]
//  198         -Parameter->a[2] * Buffer->Output_Butter[0];
        LDR      R1,[R5, #+12]
        LDR      R0,[R4, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        LDR      R1,[R5, #+16]
        LDR      R0,[R4, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R6,R0
        LDR      R1,[R5, #+20]
        LDR      R0,[R4, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R6,R0
        LDR      R1,[R5, #+4]
        LDR      R0,[R4, #+16]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R6
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R6,R0
        LDR      R1,[R5, #+8]
        LDR      R0,[R4, #+12]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R6
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        STR      R0,[R4, #+20]
//  199 	/* x(n) 序列保存 */
//  200         Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
        LDR      R0,[R4, #+4]
        STR      R0,[R4, #+0]
//  201         Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
        LDR      R0,[R4, #+8]
        STR      R0,[R4, #+4]
//  202 	/* y(n) 序列保存 */
//  203         Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
        LDR      R0,[R4, #+16]
        STR      R0,[R4, #+12]
//  204         Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
        LDR      R0,[R4, #+20]
        STR      R0,[R4, #+16]
//  205         return (Buffer->Output_Butter[2]);
        LDR      R0,[R4, #+20]
        POP      {R4-R6,PC}       ;; return
//  206 }
          CFI EndBlock cfiBlock7
//  207
//  208

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function GET_GYRO_DATA
        THUMB
//  209 void GET_GYRO_DATA(void)//角速度低通滤波后用于姿态解算
//  210 {
GET_GYRO_DATA:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  211 	X_w  = GetData(GYRO_XOUT_H)-X_w_off;
        MOVS     R0,#+67
          CFI FunCall GetData
        BL       GetData
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_7
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_1
        STR      R0,[R1, #+0]
//  212 	Y_w  = GetData(GYRO_YOUT_H)-Y_w_off;
        MOVS     R0,#+69
          CFI FunCall GetData
        BL       GetData
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_8
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_2
        STR      R0,[R1, #+0]
//  213 	Z_w  = GetData(GYRO_ZOUT_H)-Z_w_off;
        MOVS     R0,#+71
          CFI FunCall GetData
        BL       GetData
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_9
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_3
        STR      R0,[R1, #+0]
//  214         X_w_av=GYRO_LPF(X_w,
//  215                         &Gyro_BufferData[0],
//  216                         &Gyro_Parameter
//  217                         );
        LDR.W    R2,??DataTable7_22
        LDR.W    R1,??DataTable7_23
        LDR.W    R0,??DataTable7_1
        LDR      R0,[R0, #+0]
          CFI FunCall GYRO_LPF
        BL       GYRO_LPF
        LDR.W    R1,??DataTable7_24
        STR      R0,[R1, #+0]
//  218         Y_w_av=GYRO_LPF(Y_w,
//  219                         &Gyro_BufferData[1],
//  220                         &Gyro_Parameter
//  221                         );
        LDR.W    R2,??DataTable7_22
        LDR.W    R1,??DataTable7_25
        LDR.W    R0,??DataTable7_2
        LDR      R0,[R0, #+0]
          CFI FunCall GYRO_LPF
        BL       GYRO_LPF
        LDR.W    R1,??DataTable7_26
        STR      R0,[R1, #+0]
//  222         Z_w_av=GYRO_LPF(Z_w,
//  223                         &Gyro_BufferData[2],
//  224                         &Gyro_Parameter
//  225                         );
        LDR.W    R2,??DataTable7_22
        LDR.W    R1,??DataTable7_27
        LDR.W    R0,??DataTable7_3
        LDR      R0,[R0, #+0]
          CFI FunCall GYRO_LPF
        BL       GYRO_LPF
        LDR.W    R1,??DataTable7_28
        STR      R0,[R1, #+0]
//  226 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock8
//  227

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function GET_MPU_DATA
        THUMB
//  228 void GET_MPU_DATA(void)
//  229 {
GET_MPU_DATA:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  230   //GET_ACC_DATA();
//  231   IMU_Filter();
          CFI FunCall IMU_Filter
        BL       IMU_Filter
//  232   GET_GYRO_DATA();
          CFI FunCall GET_GYRO_DATA
        BL       GET_GYRO_DATA
//  233
//  234 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock9
//  235

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  236 float Gyro_X,Gyro_Y,Gyro_Z;
Gyro_X:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Gyro_Y:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Gyro_Z:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  237 float Angle_X,Angle_Y,Angle_Z;
Angle_X:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Angle_Y:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Angle_Z:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  238 float ACCE_X,ACCE_Y,ACCE_Z;
ACCE_X:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
ACCE_Y:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
ACCE_Z:
        DS8 4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function Angle_Calculate
        THUMB
//  239 void Angle_Calculate(void)//角度计算
//  240 {
Angle_Calculate:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
//  241 float ACCE_X_TEMP,ACCE_Y_TEMP,ACCE_Z_TEMP;
//  242 ACCE_X_TEMP=ACCE_X=X_g_av;
        LDR.W    R0,??DataTable7_13
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable7_29
        STR      R0,[R1, #+0]
        LDR.W    R0,??DataTable7_29
        LDR      R4,[R0, #+0]
//  243 ACCE_Y_TEMP=ACCE_Y=Y_g_av;
        LDR.W    R0,??DataTable7_17
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable7_30
        STR      R0,[R1, #+0]
        LDR.W    R0,??DataTable7_30
        LDR      R5,[R0, #+0]
//  244 ACCE_Z_TEMP=ACCE_Z=Z_g_av;
        LDR.W    R0,??DataTable7_21
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable7_31
        STR      R0,[R1, #+0]
        LDR.W    R0,??DataTable7_31
        LDR      R6,[R0, #+0]
//  245 ACCE_X=-57.3*atan(ACCE_X_TEMP*invSqrt(ACCE_Y_TEMP*ACCE_Y_TEMP+ACCE_Z_TEMP*ACCE_Z_TEMP));
        MOVS     R0,R5
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R7,R0
        MOVS     R0,R6
        MOVS     R1,R6
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R7
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall invSqrt
        BL       invSqrt
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
          CFI FunCall atan
        BL       atan
        MOVS     R2,#+1717986918
        LDR.W    R3,??DataTable7_32  ;; 0xc04ca666
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable7_29
        STR      R0,[R1, #+0]
//  246 ACCE_Y=57.3*atan(ACCE_Y_TEMP*invSqrt(ACCE_X_TEMP*ACCE_X_TEMP+ACCE_Z_TEMP*ACCE_Z_TEMP));
        MOVS     R0,R4
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R7,R0
        MOVS     R0,R6
        MOVS     R1,R6
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R7
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall invSqrt
        BL       invSqrt
        MOVS     R1,R0
        MOVS     R0,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
          CFI FunCall atan
        BL       atan
        MOVS     R2,#+1717986918
        LDR.W    R3,??DataTable7_33  ;; 0x404ca666
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable7_30
        STR      R0,[R1, #+0]
//  247 ACCE_Z=57.3*atan(sqrt(ACCE_X_TEMP*ACCE_X_TEMP+ACCE_Y_TEMP*ACCE_Y_TEMP)/ACCE_Z_TEMP);
        MOVS     R0,R4
        MOVS     R1,R4
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        MOVS     R0,R5
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
          CFI FunCall sqrt
        BL       sqrt
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,R6
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall atan
        BL       atan
        MOVS     R2,#+1717986918
        LDR.W    R3,??DataTable7_33  ;; 0x404ca666
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable7_31
        STR      R0,[R1, #+0]
//  248 }
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock10
//  249
//  250

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  251 int16_t Acce_Correct[3]={0};//用于矫正加速度量，截至频率很低
Acce_Correct:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  252 uint8_t Acce_Correct_Update_Flag=0;
Acce_Correct_Update_Flag:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  253 Butter_BufferData Butter_Buffer_Correct[3];
Butter_Buffer_Correct:
        DS8 72

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  254 Butter_Parameter Butter_1HZ_Parameter_Acce={
Butter_1HZ_Parameter_Acce:
        DC32 3F800000H, 0BFFA5063H, 3F74E00CH, 397D1554H, 39FD1554H, 397D1554H
//  255   //200hz---1hz
//  256   1,   -1.955578240315,   0.9565436765112,
//  257   0.000241359049042, 0.000482718098084, 0.000241359049042
//  258 };

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function Acce_Correct_Filter
        THUMB
//  259 void Acce_Correct_Filter()
//  260 {
Acce_Correct_Filter:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  261    Acce_Correct[0]=Int_Sort(LPButterworth(imu.accelRaw[0],
//  262                     &Butter_Buffer_Correct[0],&Butter_1HZ_Parameter_Acce));
        LDR.W    R2,??DataTable7_34
        LDR.W    R1,??DataTable7_35
        LDR.W    R0,??DataTable7_36
        LDR      R0,[R0, #+0]
          CFI FunCall LPButterworth
        BL       LPButterworth
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable7_37
        STRH     R0,[R1, #+0]
//  263    Acce_Correct[1]=Int_Sort(LPButterworth(imu.accelRaw[1]
//  264                     ,&Butter_Buffer_Correct[1],&Butter_1HZ_Parameter_Acce));
        LDR.W    R2,??DataTable7_34
        LDR.W    R1,??DataTable7_38
        LDR.W    R0,??DataTable7_36
        LDR      R0,[R0, #+4]
          CFI FunCall LPButterworth
        BL       LPButterworth
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable7_37
        STRH     R0,[R1, #+2]
//  265    Acce_Correct[2]=Int_Sort(LPButterworth(imu.accelRaw[2]
//  266                     ,&Butter_Buffer_Correct[2],&Butter_1HZ_Parameter_Acce));
        LDR.W    R2,??DataTable7_34
        LDR.W    R1,??DataTable7_39
        LDR.W    R0,??DataTable7_36
        LDR      R0,[R0, #+8]
          CFI FunCall LPButterworth
        BL       LPButterworth
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable7_37
        STRH     R0,[R1, #+4]
//  267    Acce_Correct_Update_Flag=1;
        MOVS     R0,#+1
        LDR.W    R1,??DataTable7_40
        STRB     R0,[R1, #+0]
//  268 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock11
//  269
//  270

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  271 float X_Origion,Y_Origion,Z_Origion;
X_Origion:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_Origion:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Z_Origion:
        DS8 4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function IMU_Filter
        THUMB
//  272 void IMU_Filter(void)
//  273 {
IMU_Filter:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
//  274 	uint8_t axis;
//  275         imu.accelRaw[0] = GetData(ACCEL_XOUT_H);
        MOVS     R0,#+59
          CFI FunCall GetData
        BL       GetData
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_36
        STR      R0,[R1, #+0]
//  276         imu.accelRaw[1] = GetData(ACCEL_YOUT_H);
        MOVS     R0,#+61
          CFI FunCall GetData
        BL       GetData
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_36
        STR      R0,[R1, #+4]
//  277         imu.accelRaw[2] = GetData(ACCEL_ZOUT_H);
        MOVS     R0,#+63
          CFI FunCall GetData
        BL       GetData
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable7_36
        STR      R0,[R1, #+8]
//  278         Acce_Correct_Filter();
          CFI FunCall Acce_Correct_Filter
        BL       Acce_Correct_Filter
//  279
//  280         X_Origion=K[0]*imu.accelRaw[0]-B[0]*One_G_TO_Accel;//经过椭球校正后的三轴加速度量
        LDR.W    R0,??DataTable7_41
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_36
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_42
        LDR      R1,[R0, #+0]
        MOVS     R0,#+1166016512
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_43  ;; 0x411ce80a
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_44
        STR      R0,[R1, #+0]
//  281         Y_Origion=K[1]*imu.accelRaw[1]-B[1]*One_G_TO_Accel;
        LDR.W    R0,??DataTable7_41
        LDR      R1,[R0, #+4]
        LDR.W    R0,??DataTable7_36
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_42
        LDR      R1,[R0, #+4]
        MOVS     R0,#+1166016512
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_43  ;; 0x411ce80a
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_45
        STR      R0,[R1, #+0]
//  282         Z_Origion=K[2]*imu.accelRaw[2]-B[2]*One_G_TO_Accel;
        LDR.W    R0,??DataTable7_41
        LDR      R1,[R0, #+8]
        LDR.W    R0,??DataTable7_36
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_42
        LDR      R1,[R0, #+8]
        MOVS     R0,#+1166016512
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_43  ;; 0x411ce80a
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_46
        STR      R0,[R1, #+0]
//  283
//  284         FilterBefore_NamelessQuad.Acceleration[_YAW]=
//  285                       -Sin_Roll* X_Origion
//  286                         + Sin_Pitch *Cos_Roll *Y_Origion
//  287                            + Cos_Pitch * Cos_Roll *Z_Origion;
        LDR.W    R0,??DataTable7_47
        LDR      R1,[R0, #+0]
        EORS     R1,R1,#0x80000000
        LDR.W    R0,??DataTable7_44
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_48
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_49
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_45
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_50
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_49
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_46
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable7_51
        STR      R0,[R1, #+24]
//  288         FilterBefore_NamelessQuad.Acceleration[_PITCH]=
//  289                    Cos_Yaw* Cos_Roll * X_Origion
//  290                         +(Sin_Pitch*Sin_Roll*Cos_Yaw-Cos_Pitch * Sin_Yaw) * Y_Origion
//  291                           +(Sin_Pitch * Sin_Yaw+Cos_Pitch * Sin_Roll * Cos_Yaw) * Z_Origion;
        LDR.W    R0,??DataTable7_52
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_49
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_44
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_48
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_47
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_52
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR.W    R0,??DataTable7_50
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_53
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R5
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable7_45
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R4,R0
        LDR.W    R0,??DataTable7_48
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_53
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR.W    R0,??DataTable7_50
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable7_47
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable7_52
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R5
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable7_46
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable7_51
        STR      R0,[R1, #+28]
//  292         FilterBefore_NamelessQuad.Acceleration[_ROLL]=
//  293                    Sin_Yaw* Cos_Roll * X_Origion
//  294                         +(Sin_Pitch * Sin_Roll * Sin_Yaw +Cos_Pitch * Cos_Yaw) * Y_Origion
//  295                           + (Cos_Pitch * Sin_Roll * Sin_Yaw - Sin_Pitch * Cos_Yaw) * Z_Origion;
        LDR.W    R0,??DataTable7_53
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable7_49
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_44
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.N    R0,??DataTable7_48
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable7_47
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_53
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR.N    R0,??DataTable7_50
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable7_52
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R5
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable7_45
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R4,R0
        LDR.N    R0,??DataTable7_50
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable7_47
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_53
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR.N    R0,??DataTable7_48
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable7_52
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R5
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.N    R1,??DataTable7_46
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+32]
//  296
//  297
//  298         FilterBefore_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+24]
        LDR.N    R0,??DataTable7_54  ;; 0x3b1ccccd
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+24]
//  299         FilterBefore_NamelessQuad.Acceleration[_YAW]-=AcceGravity;
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+24]
        LDR.N    R0,??DataTable7_55  ;; 0xc11ccccd
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+24]
//  300         FilterBefore_NamelessQuad.Acceleration[_YAW]*=100;//加速度cm/s^2
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+24]
        LDR.N    R0,??DataTable7_56  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+24]
//  301         FilterBefore_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+28]
        LDR.N    R0,??DataTable7_54  ;; 0x3b1ccccd
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+28]
//  302         FilterBefore_NamelessQuad.Acceleration[_PITCH]*=100;//加速度cm/s^2
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+28]
        LDR.N    R0,??DataTable7_56  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+28]
//  303         FilterBefore_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+32]
        LDR.N    R0,??DataTable7_54  ;; 0x3b1ccccd
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+32]
//  304         FilterBefore_NamelessQuad.Acceleration[_ROLL]*=100;//加速度cm/s^2
        LDR.N    R0,??DataTable7_51
        LDR      R1,[R0, #+32]
        LDR.N    R0,??DataTable7_56  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable7_51
        STR      R0,[R1, #+32]
//  305
//  306
//  307         Acce_Control_Filter();//加速度滤波，用于惯导、加速度控制反馈量
          CFI FunCall Acce_Control_Filter
        BL       Acce_Control_Filter
//  308
//  309 	/* 加速度计Butterworth滤波 */
//  310 	/* 获取最新x(n) */
//  311 	accButter[0].input[2] =Int_Sort(X_Origion);
        LDR.N    R0,??DataTable7_44
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable7_57
        STRH     R0,[R1, #+4]
//  312         accButter[1].input[2] =Int_Sort(Y_Origion);
        LDR.N    R0,??DataTable7_45
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable7_57
        STRH     R0,[R1, #+16]
//  313         accButter[2].input[2] =Int_Sort(Z_Origion);
        LDR.N    R0,??DataTable7_46
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable7_57
        STRH     R0,[R1, #+28]
//  314 	/* Butterworth滤波 */
//  315 	for (axis = 0; axis < 3; axis++)
        MOVS     R4,#+0
        B.N      ??IMU_Filter_0
//  316 	{
//  317 	accButter[axis].output[2] =
//  318                  Int_Sort(b_acc[0] * accButter[axis].input[2]
//  319                   + b_acc[1] * accButter[axis].input[1]
//  320                     + b_acc[2] * accButter[axis].input[0]
//  321                       - a_acc[1] * accButter[axis].output[1]
//  322                         - a_acc[2] * accButter[axis].output[0]);
??IMU_Filter_1:
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+4]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable7_58
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+2]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable7_58
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R5
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R5,R0
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        LDRSH    R0,[R0, R1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable7_58
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R5
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R5,R0
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+8]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable7_59
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R5
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R5,R0
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+6]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable7_59
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R5
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+12
        MUL      R2,R2,R4
        ADD      R1,R1,R2
        STRH     R0,[R1, #+10]
//  323 		imu.accelFilter[axis] = accButter[axis].output[2];
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+10]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable7_36
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        ADD      R1,R1,R4, LSL #+2
        STR      R0,[R1, #+24]
//  324 	}
        ADDS     R4,R4,#+1
??IMU_Filter_0:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+3
        BLT.N    ??IMU_Filter_1
//  325 	for (axis = 0; axis < 3; axis++)
        MOVS     R4,#+0
        B.N      ??IMU_Filter_2
//  326 	{
//  327 		/* x(n) 序列保存 */
//  328 		accButter[axis].input[0] = accButter[axis].input[1];
??IMU_Filter_3:
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRH     R0,[R0, #+2]
        LDR.N    R1,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+12
        MUL      R2,R2,R4
        STRH     R0,[R1, R2]
//  329 		accButter[axis].input[1] = accButter[axis].input[2];
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRH     R0,[R0, #+4]
        LDR.N    R1,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+12
        MUL      R2,R2,R4
        ADD      R1,R1,R2
        STRH     R0,[R1, #+2]
//  330 		/* y(n) 序列保存 */
//  331 		accButter[axis].output[0] = accButter[axis].output[1];
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRH     R0,[R0, #+8]
        LDR.N    R1,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+12
        MUL      R2,R2,R4
        ADD      R1,R1,R2
        STRH     R0,[R1, #+6]
//  332 		accButter[axis].output[1] = accButter[axis].output[2];
        LDR.N    R0,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDRH     R0,[R0, #+10]
        LDR.N    R1,??DataTable7_57
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+12
        MUL      R2,R2,R4
        ADD      R1,R1,R2
        STRH     R0,[R1, #+8]
//  333 	}
        ADDS     R4,R4,#+1
??IMU_Filter_2:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+3
        BLT.N    ??IMU_Filter_3
//  334        X_g_av=imu.accelFilter[0];
        LDR.N    R0,??DataTable7_36
        LDR      R0,[R0, #+24]
        LDR.N    R1,??DataTable7_13
        STR      R0,[R1, #+0]
//  335        Y_g_av=imu.accelFilter[1];
        LDR.N    R0,??DataTable7_36
        LDR      R0,[R0, #+28]
        LDR.N    R1,??DataTable7_17
        STR      R0,[R1, #+0]
//  336        Z_g_av=imu.accelFilter[2];
        LDR.N    R0,??DataTable7_36
        LDR      R0,[R0, #+32]
        LDR.N    R1,??DataTable7_21
        STR      R0,[R1, #+0]
//  337 }
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock12

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DC32     0x5f3759df

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DC32     X_w

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DC32     Y_w

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_3:
        DC32     Z_w

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_4:
        DC32     g_Gyro_xoffset

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_5:
        DC32     g_Gyro_yoffset

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_6:
        DC32     g_Gyro_zoffset

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_7:
        DC32     X_w_off

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_8:
        DC32     Y_w_off

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_9:
        DC32     Z_w_off

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_10:
        DC32     X_g_off

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_11:
        DC32     X_g

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_12:
        DC32     Data_X_g

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_13:
        DC32     X_g_av

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_14:
        DC32     Y_g_off

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_15:
        DC32     Y_g

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_16:
        DC32     Data_Y_g

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_17:
        DC32     Y_g_av

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_18:
        DC32     Z_g_off

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_19:
        DC32     Z_g

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_20:
        DC32     Data_Z_g

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_21:
        DC32     Z_g_av

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_22:
        DC32     Gyro_Parameter

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_23:
        DC32     Gyro_BufferData

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_24:
        DC32     X_w_av

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_25:
        DC32     Gyro_BufferData+0x18

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_26:
        DC32     Y_w_av

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_27:
        DC32     Gyro_BufferData+0x30

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_28:
        DC32     Z_w_av

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_29:
        DC32     ACCE_X

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_30:
        DC32     ACCE_Y

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_31:
        DC32     ACCE_Z

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_32:
        DC32     0xc04ca666

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_33:
        DC32     0x404ca666

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_34:
        DC32     Butter_1HZ_Parameter_Acce

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_35:
        DC32     Butter_Buffer_Correct

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_36:
        DC32     imu

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_37:
        DC32     Acce_Correct

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_38:
        DC32     Butter_Buffer_Correct+0x18

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_39:
        DC32     Butter_Buffer_Correct+0x30

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_40:
        DC32     Acce_Correct_Update_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_41:
        DC32     K

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_42:
        DC32     `B`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_43:
        DC32     0x411ce80a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_44:
        DC32     X_Origion

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_45:
        DC32     Y_Origion

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_46:
        DC32     Z_Origion

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_47:
        DC32     Sin_Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_48:
        DC32     Sin_Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_49:
        DC32     Cos_Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_50:
        DC32     Cos_Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_51:
        DC32     FilterBefore_NamelessQuad

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_52:
        DC32     Cos_Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_53:
        DC32     Sin_Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_54:
        DC32     0x3b1ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_55:
        DC32     0xc11ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_56:
        DC32     0x42c80000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_57:
        DC32     accButter

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_58:
        DC32     b_acc

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_59:
        DC32     a_acc

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//
//   769 bytes in section .bss
//    68 bytes in section .data
//    24 bytes in section .rodata
// 2 716 bytes in section .text
//
// 2 716 bytes of CODE  memory
//    24 bytes of CONST memory
//   837 bytes of DATA  memory
//
//Errors: none
//Warnings: none
