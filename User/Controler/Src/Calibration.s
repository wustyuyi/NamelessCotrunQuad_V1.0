///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.60.1.11101/W32 for ARM      03/Dec/2017  16:54:43
// Copyright 1999-2016 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Controler\Src\Calibration.c
//    Command line =  
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Controler\Src\Calibration.c
//        -D USE_STDPERIPH_DRIVER -D STM32F10X_HD -D ARM_MATH_CM3 -lC
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
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Debug\List\Calibration.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_file_descriptor", "1"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN Acce_Correct
        EXTERN Acce_Correct_Update_Flag
        EXTERN `B`
        EXTERN Bling_Mode
        EXTERN Bling_Set
        EXTERN Gyro_Length
        EXTERN K
        EXTERN Light_1
        EXTERN Light_2
        EXTERN Light_3
        EXTERN Page_Number
        EXTERN Pitch_Control
        EXTERN ReadFlashThreeFloat
        EXTERN Roll_Control
        EXTERN Throttle_Control
        EXTERN WriteFlashNineFloat
        EXTERN Yaw_Control
        EXTERN __aeabi_cfcmpeq
        EXTERN __aeabi_cfcmple
        EXTERN __aeabi_cfrcmple
        EXTERN __aeabi_d2f
        EXTERN __aeabi_ddiv
        EXTERN __aeabi_f2iz
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fdiv
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub
        EXTERN __aeabi_i2d
        EXTERN __aeabi_i2f
        EXTERN __aeabi_memclr4
        EXTERN __aeabi_memcpy4
        EXTERN __aeabi_ui2f

        PUBLIC Accel_Calibartion
        PUBLIC Accel_Calibration_All_Finished
        PUBLIC Accel_Calibration_Check
        PUBLIC Accel_Calibration_Finished
        PUBLIC Accel_Calibration_Flag
        PUBLIC Accel_Calibration_Makesure_Cnt
        PUBLIC Accel_Offset_Read
        PUBLIC Accel_Scale_Read
        PUBLIC Accel_flight_direction_cnt
        PUBLIC Aoc
        PUBLIC Aoco
        PUBLIC Cal_Flag
        PUBLIC Calibrate_Find_Delta
        PUBLIC Calibrate_Reset_Matrices
        PUBLIC Calibrate_Update_Matrices
        PUBLIC Calibrate_accel
        PUBLIC Calibrationer
        PUBLIC DataMag
        PUBLIC Flash_Buf
        PUBLIC Mag
        PUBLIC Mag_360_Flag
        PUBLIC Mag_360_define
        PUBLIC Mag_Calibartion
        PUBLIC Mag_Calibration_All_Finished
        PUBLIC Mag_Calibration_Check
        PUBLIC Mag_Calibration_Cnt
        PUBLIC Mag_Calibration_Finished
        PUBLIC Mag_Calibration_Flag
        PUBLIC Mag_Calibration_Makesure_Cnt
        PUBLIC Mag_Calibration_Mode
        PUBLIC Mag_Data
        PUBLIC Mag_Is_Okay_Flag
        PUBLIC Mag_Offset
        PUBLIC Mag_Offset_Read
        PUBLIC Parameter_Init
        PUBLIC Parameter_Read_Flag
        PUBLIC Reset_Accel_Calibartion
        PUBLIC Reset_Mag_Calibartion
        PUBLIC acce_sample
        PUBLIC flight_direction
        PUBLIC new_offset
        PUBLIC new_scales
        
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
        
// D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Controler\Src\Calibration.c
//    1 #include "Headfile.h"
//    2 #include "Calibration.h"
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

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   27 int16_t Mag_Offset[3]={0,0,0};
Mag_Offset:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   28 float Mag_Data[3]={0};
Mag_Data:
        DS8 12
//   29 
//   30 /***************加速度计6面矫正，参考APM代码，配合遥控器进行现场矫正**************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function Calibrate_Reset_Matrices
          CFI NoCalls
        THUMB
//   31 void Calibrate_Reset_Matrices(float dS[6], float JS[6][6])
//   32 {
Calibrate_Reset_Matrices:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//   33     int16_t j,k;
//   34     for( j=0; j<6; j++ )
        MOVS     R2,#+0
        B.N      ??Calibrate_Reset_Matrices_0
//   35     {
//   36         dS[j] = 0.0f;
//   37         for( k=0; k<6; k++ )
//   38         {
//   39             JS[j][k] = 0.0f;
??Calibrate_Reset_Matrices_1:
        SXTH     R2,R2            ;; SignExt  R2,R2,#+16,#+16
        MOVS     R4,#+24
        MUL      R4,R4,R2
        ADD      R4,R1,R4
        SXTH     R3,R3            ;; SignExt  R3,R3,#+16,#+16
        MOVS     R5,#+0
        STR      R5,[R4, R3, LSL #+2]
//   40         }
        ADDS     R3,R3,#+1
??Calibrate_Reset_Matrices_2:
        SXTH     R3,R3            ;; SignExt  R3,R3,#+16,#+16
        CMP      R3,#+6
        BLT.N    ??Calibrate_Reset_Matrices_1
        ADDS     R2,R2,#+1
??Calibrate_Reset_Matrices_0:
        SXTH     R2,R2            ;; SignExt  R2,R2,#+16,#+16
        CMP      R2,#+6
        BGE.N    ??Calibrate_Reset_Matrices_3
        MOVS     R3,#+0
        SXTH     R2,R2            ;; SignExt  R2,R2,#+16,#+16
        STR      R3,[R0, R2, LSL #+2]
        MOVS     R3,#+0
        B.N      ??Calibrate_Reset_Matrices_2
//   41     }
//   42 }
??Calibrate_Reset_Matrices_3:
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock0
//   43 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function Calibrate_Find_Delta
        THUMB
//   44 void Calibrate_Find_Delta(float dS[6], float JS[6][6], float delta[6])
//   45 {
Calibrate_Find_Delta:
        PUSH     {R3-R11,LR}
          CFI R14 Frame(CFA, -4)
          CFI R11 Frame(CFA, -8)
          CFI R10 Frame(CFA, -12)
          CFI R9 Frame(CFA, -16)
          CFI R8 Frame(CFA, -20)
          CFI R7 Frame(CFA, -24)
          CFI R6 Frame(CFA, -28)
          CFI R5 Frame(CFA, -32)
          CFI R4 Frame(CFA, -36)
          CFI CFA R13+40
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   46     //Solve 6-d matrix equation JS*x = dS
//   47     //first put in upper triangular form
//   48     int16_t i,j,k;
//   49     float mu;
//   50     //make upper triangular
//   51     for( i=0; i<6; i++ ) {
        MOVS     R7,#+0
        B.N      ??Calibrate_Find_Delta_0
??Calibrate_Find_Delta_1:
        ADDS     R7,R7,#+1
??Calibrate_Find_Delta_0:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        CMP      R7,#+6
        BGE.N    ??Calibrate_Find_Delta_2
//   52         //eliminate all nonzero entries below JS[i][i]
//   53         for( j=i+1; j<6; j++ ) {
        ADDS     R8,R7,#+1
        B.N      ??Calibrate_Find_Delta_3
//   54             mu = JS[i][j]/JS[i][i];
//   55             if( mu != 0.0f ) {
//   56                 dS[j] -= mu*dS[i];
//   57                 for( k=j; k<6; k++ ) {
//   58                     JS[k][j] -= mu*JS[k][i];
??Calibrate_Find_Delta_4:
        SXTH     R9,R9            ;; SignExt  R9,R9,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R9
        ADD      R11,R5,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        SXTH     R9,R9            ;; SignExt  R9,R9,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R9
        ADD      R0,R5,R0
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R0, R7, LSL #+2]
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        SXTH     R9,R9            ;; SignExt  R9,R9,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R9
        ADD      R0,R5,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R0,[R0, R8, LSL #+2]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        STR      R0,[R11, R8, LSL #+2]
//   59                 }
        ADDS     R9,R9,#+1
??Calibrate_Find_Delta_5:
        SXTH     R9,R9            ;; SignExt  R9,R9,#+16,#+16
        CMP      R9,#+6
        BLT.N    ??Calibrate_Find_Delta_4
??Calibrate_Find_Delta_6:
        ADDS     R8,R8,#+1
??Calibrate_Find_Delta_3:
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        CMP      R8,#+6
        BGE.N    ??Calibrate_Find_Delta_1
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R7
        ADD      R0,R5,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R0,[R0, R8, LSL #+2]
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R1,#+24
        MUL      R1,R1,R7
        ADD      R1,R5,R1
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R1,[R1, R7, LSL #+2]
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOV      R10,R0
        MOV      R0,R10
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfcmpeq
        BL       __aeabi_cfcmpeq
        BEQ.N    ??Calibrate_Find_Delta_6
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R4, R7, LSL #+2]
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R0,[R4, R8, LSL #+2]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        STR      R0,[R4, R8, LSL #+2]
        MOV      R9,R8
        B.N      ??Calibrate_Find_Delta_5
//   60             }
//   61         }
//   62     }
//   63     //back-substitute
//   64     for( i=5; i>=0; i-- ) {
??Calibrate_Find_Delta_2:
        MOVS     R7,#+5
        B.N      ??Calibrate_Find_Delta_7
//   65         dS[i] /= JS[i][i];
//   66         JS[i][i] = 1.0f;
//   67 
//   68         for( j=0; j<i; j++ ) {
//   69             mu = JS[i][j];
??Calibrate_Find_Delta_8:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R7
        ADD      R0,R5,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R10,[R0, R8, LSL #+2]
//   70             dS[j] -= mu*dS[i];
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R4, R7, LSL #+2]
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R0,[R4, R8, LSL #+2]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        STR      R0,[R4, R8, LSL #+2]
//   71             JS[i][j] = 0.0f;
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R7
        ADD      R0,R5,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        MOVS     R1,#+0
        STR      R1,[R0, R8, LSL #+2]
//   72         }
        ADDS     R8,R8,#+1
??Calibrate_Find_Delta_9:
        MOV      R0,R8
        MOVS     R1,R7
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        SXTH     R1,R1            ;; SignExt  R1,R1,#+16,#+16
        CMP      R0,R1
        BLT.N    ??Calibrate_Find_Delta_8
        SUBS     R7,R7,#+1
??Calibrate_Find_Delta_7:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        CMP      R7,#+0
        BMI.N    ??Calibrate_Find_Delta_10
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R4, R7, LSL #+2]
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R1,#+24
        MUL      R1,R1,R7
        ADD      R1,R5,R1
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R1,[R1, R7, LSL #+2]
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        STR      R0,[R4, R7, LSL #+2]
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R7
        ADD      R0,R5,R0
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R1,#+1065353216
        STR      R1,[R0, R7, LSL #+2]
        MOVS     R8,#+0
        B.N      ??Calibrate_Find_Delta_9
//   73     }
//   74     for( i=0; i<6; i++ ) {
??Calibrate_Find_Delta_10:
        MOVS     R7,#+0
        B.N      ??Calibrate_Find_Delta_11
//   75         delta[i] = dS[i];
??Calibrate_Find_Delta_12:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R4, R7, LSL #+2]
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        STR      R0,[R6, R7, LSL #+2]
//   76     }
        ADDS     R7,R7,#+1
??Calibrate_Find_Delta_11:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        CMP      R7,#+6
        BLT.N    ??Calibrate_Find_Delta_12
//   77 }
        POP      {R0,R4-R11,PC}   ;; return
          CFI EndBlock cfiBlock1
//   78 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function Calibrate_Update_Matrices
        THUMB
//   79 void Calibrate_Update_Matrices(float dS[6],
//   80                                float JS[6][6],
//   81                                float beta[6],
//   82                                float data[3])
//   83 {
Calibrate_Update_Matrices:
        PUSH     {R4-R11,LR}
          CFI R14 Frame(CFA, -4)
          CFI R11 Frame(CFA, -8)
          CFI R10 Frame(CFA, -12)
          CFI R9 Frame(CFA, -16)
          CFI R8 Frame(CFA, -20)
          CFI R7 Frame(CFA, -24)
          CFI R6 Frame(CFA, -28)
          CFI R5 Frame(CFA, -32)
          CFI R4 Frame(CFA, -36)
          CFI CFA R13+36
        SUB      SP,SP,#+28
          CFI CFA R13+64
        MOVS     R4,R0
        MOVS     R5,R1
        MOV      R8,R2
        MOV      R9,R3
//   84     int16_t j, k;
//   85     float dx, b;
//   86     float residual = 1.0;
        MOVS     R6,#+1065353216
//   87     float jacobian[6];
//   88     for(j=0;j<3;j++)
        MOVS     R7,#+0
        B.N      ??Calibrate_Update_Matrices_0
//   89     {
//   90         b = beta[3+j];
??Calibrate_Update_Matrices_1:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        ADD      R0,R8,R7, LSL #+2
        LDR      R10,[R0, #+12]
//   91         dx = (float)data[j] - beta[j];
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R9, R7, LSL #+2]
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R1,[R8, R7, LSL #+2]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOV      R11,R0
//   92         residual -= b*b*dx*dx;
        MOV      R0,R10
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R11
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R11
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R6
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R6,R0
//   93         jacobian[j] = 2.0f*b*b*dx;
        MOVS     R0,#+1073741824
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R11
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,SP
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        STR      R0,[R1, R7, LSL #+2]
//   94         jacobian[3+j] = -2.0f*b*dx*dx;
        MOVS     R0,#-1073741824
        MOV      R1,R10
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R11
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R11
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,SP
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        ADD      R1,R1,R7, LSL #+2
        STR      R0,[R1, #+12]
//   95     }
        ADDS     R7,R7,#+1
??Calibrate_Update_Matrices_0:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        CMP      R7,#+3
        BLT.N    ??Calibrate_Update_Matrices_1
//   96 
//   97     for(j=0;j<6;j++)
        MOVS     R7,#+0
        B.N      ??Calibrate_Update_Matrices_2
//   98     {
//   99         dS[j]+=jacobian[j]*residual;
//  100         for(k=0;k<6;k++)
//  101         {
//  102             JS[j][k]+=jacobian[j]*jacobian[k];
??Calibrate_Update_Matrices_3:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R0,#+24
        MUL      R0,R0,R7
        ADD      R9,R5,R0
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        MOV      R0,SP
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R0, R7, LSL #+2]
        MOV      R1,SP
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R1,[R1, R8, LSL #+2]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        MOVS     R1,#+24
        MUL      R1,R1,R7
        ADD      R1,R5,R1
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        LDR      R1,[R1, R8, LSL #+2]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        STR      R0,[R9, R8, LSL #+2]
//  103         }
        ADDS     R8,R8,#+1
??Calibrate_Update_Matrices_4:
        SXTH     R8,R8            ;; SignExt  R8,R8,#+16,#+16
        CMP      R8,#+6
        BLT.N    ??Calibrate_Update_Matrices_3
        ADDS     R7,R7,#+1
??Calibrate_Update_Matrices_2:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        CMP      R7,#+6
        BGE.N    ??Calibrate_Update_Matrices_5
        MOV      R0,SP
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R0,[R0, R7, LSL #+2]
        MOVS     R1,R6
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        LDR      R1,[R4, R7, LSL #+2]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        STR      R0,[R4, R7, LSL #+2]
        MOVS     R8,#+0
        B.N      ??Calibrate_Update_Matrices_4
//  104     }
//  105 }
??Calibrate_Update_Matrices_5:
        ADD      SP,SP,#+28
          CFI CFA R13+36
        POP      {R4-R11,PC}      ;; return
          CFI EndBlock cfiBlock2
//  106 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function Calibrate_accel
        THUMB
//  107 uint8 Calibrate_accel(Acce_Unit accel_sample[6],
//  108                       Acce_Unit *accel_offsets,
//  109                       Acce_Unit *accel_scale)
//  110 {
Calibrate_accel:
        PUSH     {R4-R11,LR}
          CFI R14 Frame(CFA, -4)
          CFI R11 Frame(CFA, -8)
          CFI R10 Frame(CFA, -12)
          CFI R9 Frame(CFA, -16)
          CFI R8 Frame(CFA, -20)
          CFI R7 Frame(CFA, -24)
          CFI R6 Frame(CFA, -28)
          CFI R5 Frame(CFA, -32)
          CFI R4 Frame(CFA, -36)
          CFI CFA R13+36
        SUB      SP,SP,#+228
          CFI CFA R13+264
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  111     int16_t i;
//  112     int16_t num_iterations = 0;
        MOVS     R7,#+0
//  113     float eps = 0.000000001;
        LDR.W    R8,??DataTable5  ;; 0x3089705f
//  114     float change = 100.0;
        LDR.W    R9,??DataTable5_1  ;; 0x42c80000
//  115     float data[3]={0};
        ADD      R0,SP,#+48
        MOVS     R1,#+0
        MOVS     R2,#+0
        MOVS     R3,#+0
        STM      R0!,{R1-R3}
        SUBS     R0,R0,#+12
//  116     float beta[6]={0};
        MOV      R0,SP
        MOVS     R1,#+24
          CFI FunCall __aeabi_memclr4
        BL       __aeabi_memclr4
//  117     float delta[6]={0};
        ADD      R0,SP,#+24
        MOVS     R1,#+24
          CFI FunCall __aeabi_memclr4
        BL       __aeabi_memclr4
//  118     float ds[6]={0};
        ADD      R0,SP,#+60
        MOVS     R1,#+24
          CFI FunCall __aeabi_memclr4
        BL       __aeabi_memclr4
//  119     float JS[6][6]={0};
        ADD      R0,SP,#+84
        MOVS     R1,#+144
          CFI FunCall __aeabi_memclr4
        BL       __aeabi_memclr4
//  120     bool success = true;
        MOVS     R10,#+1
//  121     // reset
//  122     beta[0] = beta[1] = beta[2] = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+8]
        STR      R0,[SP, #+4]
        STR      R0,[SP, #+0]
//  123     beta[3] = beta[4] = beta[5] = 1.0f/GRAVITY_MSS;
        LDR.W    R0,??DataTable5_2  ;; 0x3dd0d67f
        STR      R0,[SP, #+20]
        STR      R0,[SP, #+16]
        STR      R0,[SP, #+12]
//  124     while( num_iterations < 20 && change > eps ) {
??Calibrate_accel_0:
        SXTH     R7,R7            ;; SignExt  R7,R7,#+16,#+16
        CMP      R7,#+20
        BGE.W    ??Calibrate_accel_1
        MOV      R0,R8
        MOV      R1,R9
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.W    ??Calibrate_accel_1
//  125         num_iterations++;
        ADDS     R7,R7,#+1
//  126         Calibrate_Reset_Matrices(ds, JS);
        ADD      R1,SP,#+84
        ADD      R0,SP,#+60
          CFI FunCall Calibrate_Reset_Matrices
        BL       Calibrate_Reset_Matrices
//  127 
//  128         for( i=0; i<6; i++ ) {
        MOVS     R11,#+0
        B.N      ??Calibrate_accel_2
//  129             data[0] = accel_sample[i].x;
??Calibrate_accel_3:
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        MOVS     R0,#+12
        MUL      R0,R0,R11
        LDR      R0,[R4, R0]
        STR      R0,[SP, #+48]
//  130             data[1] = accel_sample[i].y;
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        MOVS     R0,#+12
        MUL      R0,R0,R11
        ADD      R0,R4,R0
        LDR      R0,[R0, #+4]
        STR      R0,[SP, #+52]
//  131             data[2] = accel_sample[i].z;
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        MOVS     R0,#+12
        MUL      R0,R0,R11
        ADD      R0,R4,R0
        LDR      R0,[R0, #+8]
        STR      R0,[SP, #+56]
//  132             Calibrate_Update_Matrices(ds, JS, beta, data);
        ADD      R3,SP,#+48
        MOV      R2,SP
        ADD      R1,SP,#+84
        ADD      R0,SP,#+60
          CFI FunCall Calibrate_Update_Matrices
        BL       Calibrate_Update_Matrices
//  133 
//  134         }
        ADDS     R11,R11,#+1
??Calibrate_accel_2:
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        CMP      R11,#+6
        BLT.N    ??Calibrate_accel_3
//  135         Calibrate_Find_Delta(ds, JS, delta);
        ADD      R2,SP,#+24
        ADD      R1,SP,#+84
        ADD      R0,SP,#+60
          CFI FunCall Calibrate_Find_Delta
        BL       Calibrate_Find_Delta
//  136         change =    delta[0]*delta[0] +
//  137                     delta[0]*delta[0] +
//  138                     delta[1]*delta[1] +
//  139                     delta[2]*delta[2] +
//  140                     delta[3]*delta[3] / (beta[3]*beta[3]) +
//  141                     delta[4]*delta[4] / (beta[4]*beta[4]) +
//  142                     delta[5]*delta[5] / (beta[5]*beta[5]);
        LDR      R0,[SP, #+24]
        LDR      R1,[SP, #+24]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R9,R0
        LDR      R0,[SP, #+24]
        LDR      R1,[SP, #+24]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R9
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
        LDR      R0,[SP, #+28]
        LDR      R1,[SP, #+28]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R9
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
        LDR      R0,[SP, #+32]
        LDR      R1,[SP, #+32]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R9
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
        LDR      R0,[SP, #+36]
        LDR      R1,[SP, #+36]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R11,R0
        LDR      R0,[SP, #+12]
        LDR      R1,[SP, #+12]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOV      R0,R11
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOV      R1,R9
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
        LDR      R0,[SP, #+40]
        LDR      R1,[SP, #+40]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R11,R0
        LDR      R0,[SP, #+16]
        LDR      R1,[SP, #+16]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOV      R0,R11
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOV      R1,R9
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
        LDR      R0,[SP, #+44]
        LDR      R1,[SP, #+44]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R11,R0
        LDR      R0,[SP, #+20]
        LDR      R1,[SP, #+20]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOV      R0,R11
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOV      R1,R9
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
//  143         for( i=0; i<6; i++ ) {
        MOVS     R11,#+0
??Calibrate_accel_4:
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        CMP      R11,#+6
        BGE.W    ??Calibrate_accel_0
//  144             beta[i] -= delta[i];
        MOV      R0,SP
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        LDR      R0,[R0, R11, LSL #+2]
        ADD      R1,SP,#+24
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        LDR      R1,[R1, R11, LSL #+2]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOV      R1,SP
        SXTH     R11,R11          ;; SignExt  R11,R11,#+16,#+16
        STR      R0,[R1, R11, LSL #+2]
//  145         }
        ADDS     R11,R11,#+1
        B.N      ??Calibrate_accel_4
//  146     }
//  147     // copy results out
//  148     accel_scale->x = beta[3] * GRAVITY_MSS;
??Calibrate_accel_1:
        LDR      R1,[SP, #+12]
        LDR.W    R0,??DataTable5_3  ;; 0x411ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R6, #+0]
//  149     accel_scale->y = beta[4] * GRAVITY_MSS;
        LDR      R1,[SP, #+16]
        LDR.W    R0,??DataTable5_3  ;; 0x411ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R6, #+4]
//  150     accel_scale->z = beta[5] * GRAVITY_MSS;
        LDR      R1,[SP, #+20]
        LDR.W    R0,??DataTable5_3  ;; 0x411ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R6, #+8]
//  151     accel_offsets->x = beta[0] * accel_scale->x;
        LDR      R1,[SP, #+0]
        LDR      R0,[R6, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R5, #+0]
//  152     accel_offsets->y = beta[1] * accel_scale->y;
        LDR      R1,[SP, #+4]
        LDR      R0,[R6, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R5, #+4]
//  153     accel_offsets->z = beta[2] * accel_scale->z;
        LDR      R1,[SP, #+8]
        LDR      R0,[R6, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R5, #+8]
//  154 
//  155     // sanity check scale
//  156     if(fabsf(accel_scale->x-1.0f) > 0.2f
//  157          || fabsf(accel_scale->y-1.0f) > 0.2f
//  158            || fabsf(accel_scale->z-1.0f) > 0.2f )
        LDR      R1,[R6, #+0]
        LDR.W    R0,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        BICS     R0,R0,#0x80000000
        LDR.W    R1,??DataTable5_5  ;; 0x3e4cccce
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Calibrate_accel_5
        LDR      R1,[R6, #+4]
        LDR.W    R0,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        BICS     R0,R0,#0x80000000
        LDR.W    R1,??DataTable5_5  ;; 0x3e4cccce
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Calibrate_accel_5
        LDR      R1,[R6, #+8]
        LDR.W    R0,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        BICS     R0,R0,#0x80000000
        LDR.W    R1,??DataTable5_5  ;; 0x3e4cccce
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Calibrate_accel_6
//  159     {
//  160         success = false;
??Calibrate_accel_5:
        MOVS     R10,#+0
//  161     }
//  162     // sanity check offsets (3.5 is roughly 3/10th of a G, 5.0 is roughly half a G)
//  163     if(fabsf(accel_offsets->x) > 3.5f
//  164          || fabsf(accel_offsets->y) > 3.5f
//  165            || fabsf(accel_offsets->z) > 3.5f )
??Calibrate_accel_6:
        LDR      R0,[R5, #+0]
        BICS     R0,R0,#0x80000000
        LDR.W    R1,??DataTable7  ;; 0x40600001
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Calibrate_accel_7
        LDR      R0,[R5, #+4]
        BICS     R0,R0,#0x80000000
        LDR.W    R1,??DataTable7  ;; 0x40600001
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Calibrate_accel_7
        LDR      R0,[R5, #+8]
        BICS     R0,R0,#0x80000000
        LDR.W    R1,??DataTable7  ;; 0x40600001
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Calibrate_accel_8
//  166     {
//  167         success = false;
??Calibrate_accel_7:
        MOVS     R10,#+0
//  168     }
//  169     // return success or failure
//  170     return success;
??Calibrate_accel_8:
        MOV      R0,R10
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        ADD      SP,SP,#+228
          CFI CFA R13+36
        POP      {R4-R11,PC}      ;; return
//  171 }
          CFI EndBlock cfiBlock3

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0
//  172 
//  173 
//  174 

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  175 float Aoco[6]={1,1,1};
Aoco:
        DC32 3F800000H, 3F800000H, 3F800000H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  176 float Aoc[6][6]={1,1,1};
Aoc:
        DC32 3F800000H, 3F800000H, 3F800000H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  177 Acce_Unit new_offset={
new_offset:
        DS8 12
//  178   0,0,0,
//  179 };

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  180 Acce_Unit new_scales={
new_scales:
        DC32 3F800000H, 3F800000H, 3F800000H
//  181   1.0,1.0,1.0,
//  182 };
//  183 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  184 Acce_Unit Accel_Offset_Read={
Accel_Offset_Read:
        DS8 12
//  185   0,0,0,
//  186 };

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  187 Acce_Unit Accel_Scale_Read={
Accel_Scale_Read:
        DS8 12
//  188   0,0,0,
//  189 };

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  190 uint8_t Cal_Flag=0;
Cal_Flag:
        DS8 1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function Calibrationer
        THUMB
//  191 void Calibrationer(void)
//  192 {
Calibrationer:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        SUB      SP,SP,#+72
          CFI CFA R13+80
//  193  uint16 i=0;
        MOVS     R4,#+0
//  194  Acce_Unit Test_Calibration[6]=
//  195 {
//  196 20,     21,    4152,
//  197 4062,  -24,      78,
//  198 -4082, 1,        -8,
//  199 -45,   -4071,   30,
//  200 20,    4035,    -8,
//  201 30,     -60,   -3980
//  202 };
        MOV      R0,SP
        LDR.W    R1,??DataTable5_6
        MOVS     R2,#+72
          CFI FunCall __aeabi_memcpy4
        BL       __aeabi_memcpy4
//  203  for(i=0;i<6;i++)
        MOVS     R4,#+0
        B.N      ??Calibrationer_0
//  204  {
//  205     Test_Calibration[i].x *=ACCEL_TO_1G;
??Calibrationer_1:
        MOV      R0,SP
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R1,#+12
        MUL      R1,R1,R4
        LDR      R0,[R0, R1]
        LDR.W    R1,??DataTable5_7  ;; 0x3b1ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,SP
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R2,#+12
        MUL      R2,R2,R4
        STR      R0,[R1, R2]
//  206     Test_Calibration[i].y *=ACCEL_TO_1G;
        MOV      R0,SP
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDR      R0,[R0, #+4]
        LDR.W    R1,??DataTable5_7  ;; 0x3b1ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,SP
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R2,#+12
        MUL      R2,R2,R4
        ADD      R1,R1,R2
        STR      R0,[R1, #+4]
//  207     Test_Calibration[i].z *=ACCEL_TO_1G;
        MOV      R0,SP
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R1,#+12
        MUL      R1,R1,R4
        ADD      R0,R0,R1
        LDR      R0,[R0, #+8]
        LDR.W    R1,??DataTable5_7  ;; 0x3b1ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,SP
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R2,#+12
        MUL      R2,R2,R4
        ADD      R1,R1,R2
        STR      R0,[R1, #+8]
//  208  }
        ADDS     R4,R4,#+1
??Calibrationer_0:
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        CMP      R4,#+6
        BLT.N    ??Calibrationer_1
//  209 
//  210  Cal_Flag=Calibrate_accel(Test_Calibration,
//  211                  &new_offset,
//  212                  &new_scales);
        LDR.W    R2,??DataTable5_8
        LDR.W    R1,??DataTable5_9
        MOV      R0,SP
          CFI FunCall Calibrate_accel
        BL       Calibrate_accel
        LDR.W    R1,??DataTable7_1
        STRB     R0,[R1, #+0]
//  213 }
        ADD      SP,SP,#+72
          CFI CFA R13+8
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock4

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_5:
        DC32 41A00000H, 41A80000H, 4581C000H, 457DE000H, 0C1C00000H, 429C0000H
        DC32 0C57F2000H, 3F800000H, 0C1000000H, 0C2340000H, 0C57E7000H
        DC32 41F00000H, 41A00000H, 457C3000H, 0C1000000H, 41F00000H, 0C2700000H
        DC32 0C578C000H
//  214 
//  215 

        SECTION `.data`:DATA:REORDER:NOROOT(0)
        DATA
//  216 uint8_t flight_direction=6;
flight_direction:
        DC8 6

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  217 uint8_t Accel_Calibration_Flag=0;//加速度计校准模式
Accel_Calibration_Flag:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  218 uint8_t Accel_Calibration_Finished[6]={0,0,0,0,0,0};//对应面校准完成标志位
Accel_Calibration_Finished:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  219 uint8_t Accel_Calibration_All_Finished=0;//6面校准全部校准完成标志位
Accel_Calibration_All_Finished:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  220 uint16_t Accel_Calibration_Makesure_Cnt=0;
Accel_Calibration_Makesure_Cnt:
        DS8 2

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  221 uint16_t Accel_flight_direction_cnt=0;
Accel_flight_direction_cnt:
        DS8 2

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function Accel_Calibration_Check
        THUMB
//  222 void Accel_Calibration_Check(void)
//  223 {
Accel_Calibration_Check:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
        SUB      SP,SP,#+20
          CFI CFA R13+24
//  224    uint16_t  i=0;
        MOVS     R0,#+0
//  225    if(Throttle_Control==1000&&Yaw_Control>=80&&Roll_Control<=-40&&Pitch_Control>=40)
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_0
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+80
        BLT.N    ??Accel_Calibration_Check_0
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMN      R0,#+39
        BGE.N    ??Accel_Calibration_Check_0
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Accel_Calibration_Check_0
//  226    {
//  227       Accel_Calibration_Makesure_Cnt++;
        LDR.W    R0,??DataTable6_3
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable6_3
        STRH     R0,[R1, #+0]
//  228    }
//  229    if(Throttle_Control==1000
//  230       &&Yaw_Control>=80
//  231         &&Roll_Control<=-40
//  232           &&Pitch_Control>=40
//  233             &&Accel_Calibration_Makesure_Cnt>=200*3)//持续三秒
??Accel_Calibration_Check_0:
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.W    ??Accel_Calibration_Check_1
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+80
        BLT.W    ??Accel_Calibration_Check_1
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMN      R0,#+39
        BGE.W    ??Accel_Calibration_Check_1
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.W    ??Accel_Calibration_Check_1
        LDR.W    R0,??DataTable6_3
        LDRH     R0,[R0, #+0]
        CMP      R0,#+600
        BLT.N    ??Accel_Calibration_Check_1
//  234   {
//  235       Bling_Mode=1;
        MOVS     R0,#+1
        LDR.W    R1,??DataTable7_3
        STRH     R0,[R1, #+0]
//  236       Accel_Calibration_Flag=1;//加速度校准模式
        MOVS     R0,#+1
        LDR.W    R1,??DataTable7_4
        STRB     R0,[R1, #+0]
//  237       Cal_Flag=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_1
        STRB     R0,[R1, #+0]
//  238       Bling_Set(&Light_1,1000,100,0.5,0,GPIOC,GPIO_Pin_4,1);
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
        MOVS     R0,#+16
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOVS     R2,#+100
        MOV      R1,#+1000
        LDR.W    R0,??DataTable7_6
          CFI FunCall Bling_Set
        BL       Bling_Set
//  239       Bling_Set(&Light_2,1000,100,0.5,0,GPIOC,GPIO_Pin_5,1);
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
        MOVS     R0,#+32
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOVS     R2,#+100
        MOV      R1,#+1000
        LDR.W    R0,??DataTable7_7
          CFI FunCall Bling_Set
        BL       Bling_Set
//  240       Bling_Set(&Light_3,1000,100,0.5,0,GPIOC,GPIO_Pin_10,1);
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
        MOV      R0,#+1024
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOVS     R2,#+100
        MOV      R1,#+1000
        LDR.W    R0,??DataTable7_8
          CFI FunCall Bling_Set
        BL       Bling_Set
//  241       flight_direction=6;
        MOVS     R0,#+6
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
//  242       Accel_Calibration_All_Finished=0;//全部校准完成标志位清零
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_10
        STRB     R0,[R1, #+0]
//  243       Accel_Calibration_Makesure_Cnt=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable6_3
        STRH     R0,[R1, #+0]
//  244       for(i=0;i<6;i++)
        MOVS     R0,#+0
        B.N      ??Accel_Calibration_Check_2
//  245       {
//  246         Accel_Calibration_Finished[i]=0;//对应面标志位清零
??Accel_Calibration_Check_3:
        MOVS     R1,#+0
        LDR.W    R2,??DataTable7_11
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        STRB     R1,[R2, R0]
//  247         acce_sample[i].x=0; //清空对应面的加速度计量
        MOVS     R1,#+0
        LDR.W    R2,??DataTable7_12
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVS     R3,#+12
        MUL      R3,R3,R0
        STR      R1,[R2, R3]
//  248         acce_sample[i].y=0; //清空对应面的加速度计量
        MOVS     R1,#+0
        LDR.W    R2,??DataTable7_12
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVS     R3,#+12
        MUL      R3,R3,R0
        ADD      R2,R2,R3
        STR      R1,[R2, #+4]
//  249         acce_sample[i].z=0; //清空对应面的加速度计量
        MOVS     R1,#+0
        LDR.W    R2,??DataTable7_12
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVS     R3,#+12
        MUL      R3,R3,R0
        ADD      R2,R2,R3
        STR      R1,[R2, #+8]
//  250       }
        ADDS     R0,R0,#+1
??Accel_Calibration_Check_2:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+6
        BLT.N    ??Accel_Calibration_Check_3
//  251       Page_Number=10;//OLED加速度计矫正页面
        MOVS     R0,#+10
        LDR.W    R1,??DataTable7_13
        STRH     R0,[R1, #+0]
//  252       Reset_Mag_Calibartion(1);
        MOVS     R0,#+1
          CFI FunCall Reset_Mag_Calibartion
        BL       Reset_Mag_Calibartion
//  253   }
//  254 
//  255   if(Accel_Calibration_Flag==1)
??Accel_Calibration_Check_1:
        LDR.W    R0,??DataTable7_4
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.W    ??Accel_Calibration_Check_4
//  256   {
//  257      if(Throttle_Control==1000&&Yaw_Control<=-80&&Roll_Control==0&&Pitch_Control==0)
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_5
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMN      R0,#+79
        BGE.N    ??Accel_Calibration_Check_5
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_5
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_5
//  258      {
//  259        Accel_flight_direction_cnt++;
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  260        if(Accel_flight_direction_cnt>=4*25)//100ms
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.W    ??Accel_Calibration_Check_6
//  261          flight_direction=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
        B.N      ??Accel_Calibration_Check_6
//  262 
//  263      }
//  264      else if(Throttle_Control==1000&&Yaw_Control==0&&Roll_Control>=40&&Pitch_Control==0)
??Accel_Calibration_Check_5:
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_7
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_7
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Accel_Calibration_Check_7
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_7
//  265      {
//  266        Accel_flight_direction_cnt++;
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  267        if(Accel_flight_direction_cnt>=4*25)//100ms
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.W    ??Accel_Calibration_Check_6
//  268          flight_direction=1;
        MOVS     R0,#+1
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
        B.N      ??Accel_Calibration_Check_6
//  269      }
//  270      else if(Throttle_Control==1000&&Yaw_Control==0&&Roll_Control<=-40&&Pitch_Control==0)
??Accel_Calibration_Check_7:
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_8
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_8
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMN      R0,#+39
        BGE.N    ??Accel_Calibration_Check_8
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_8
//  271      {
//  272        Accel_flight_direction_cnt++;
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  273        if(Accel_flight_direction_cnt>=4*25)//100ms
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.W    ??Accel_Calibration_Check_6
//  274          flight_direction=2;
        MOVS     R0,#+2
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
        B.N      ??Accel_Calibration_Check_6
//  275      }
//  276      else if(Throttle_Control==1000&&Yaw_Control==0&&Roll_Control==0&&Pitch_Control>=40)
??Accel_Calibration_Check_8:
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_9
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_9
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_9
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Accel_Calibration_Check_9
//  277      {
//  278        Accel_flight_direction_cnt++;
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  279        if(Accel_flight_direction_cnt>=4*25)//100ms
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.N    ??Accel_Calibration_Check_6
//  280          flight_direction=3;
        MOVS     R0,#+3
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
        B.N      ??Accel_Calibration_Check_6
//  281      }
//  282      else if(Throttle_Control==1000&&Yaw_Control==0&&Roll_Control==0&&Pitch_Control<=-40)
??Accel_Calibration_Check_9:
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_10
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_10
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_10
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMN      R0,#+39
        BGE.N    ??Accel_Calibration_Check_10
//  283      {
//  284        Accel_flight_direction_cnt++;
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  285        if(Accel_flight_direction_cnt>=4*25)//100ms
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.N    ??Accel_Calibration_Check_6
//  286          flight_direction=4;
        MOVS     R0,#+4
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
        B.N      ??Accel_Calibration_Check_6
//  287      }
//  288      else if(Throttle_Control==1000&&Yaw_Control>80&&Roll_Control==0&&Pitch_Control==0)
??Accel_Calibration_Check_10:
        LDR.W    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Accel_Calibration_Check_11
        LDR.W    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+81
        BLT.N    ??Accel_Calibration_Check_11
        LDR.W    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_11
        LDR.W    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Accel_Calibration_Check_11
//  289      {
//  290        Accel_flight_direction_cnt++;
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  291        if(Accel_flight_direction_cnt>=4*25)//100ms
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.N    ??Accel_Calibration_Check_6
//  292        flight_direction=5;
        MOVS     R0,#+5
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
        B.N      ??Accel_Calibration_Check_6
//  293      }
//  294      else
//  295      {
//  296        Accel_flight_direction_cnt/=2;
??Accel_Calibration_Check_11:
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        MOVS     R1,#+2
        SDIV     R0,R0,R1
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  297      }
//  298 
//  299    if(Accel_flight_direction_cnt>=200)  Accel_flight_direction_cnt=0;
??Accel_Calibration_Check_6:
        LDR.W    R0,??DataTable7_14
        LDRH     R0,[R0, #+0]
        CMP      R0,#+200
        BLT.N    ??Accel_Calibration_Check_4
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_14
        STRH     R0,[R1, #+0]
//  300 
//  301  }
//  302 
//  303 }
??Accel_Calibration_Check_4:
        ADD      SP,SP,#+20
          CFI CFA R13+4
        POP      {PC}             ;; return
          CFI EndBlock cfiBlock5
//  304 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  305 Acce_Unit acce_sample[6]={0};//三行6列，保存6面待矫正数据
acce_sample:
        DS8 72

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  306 uint8_t Flash_Buf[12]={0};
Flash_Buf:
        DS8 12
//  307 /***************************************************
//  308 函数名: void Accel_Calibartion()
//  309 说明:	加速度基本标定、利用遥控器直接进入
//  310 入口:	无
//  311 出口:	无
//  312 备注:	在主函数While(1)里面，利用中断空隙时间一直运行
//  313 ****************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function Accel_Calibartion
        THUMB
//  314 uint8_t Accel_Calibartion(void)
//  315 {
Accel_Calibartion:
        PUSH     {R4,R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+12
        SUB      SP,SP,#+28
          CFI CFA R13+40
//  316   uint16 i,j=0;
        MOVS     R5,#+0
//  317   float acce_sample_sum[3]={0,0,0};//加速度和数据
        MOV      R0,SP
        MOVS     R1,#+0
        MOVS     R2,#+0
        MOVS     R3,#+0
        STM      R0!,{R1-R3}
        SUBS     R0,R0,#+12
//  318 /*第一面飞控平放，Z轴正向朝着正上方，Z axis is about 1g,X、Y is about 0g*/
//  319 /*第二面飞控平放，X轴正向朝着正上方，X axis is about 1g,Y、Z is about 0g*/
//  320 /*第三面飞控平放，X轴正向朝着正下方，X axis is about -1g,Y、Z is about 0g*/
//  321 /*第四面飞控平放，Y轴正向朝着正下方，Y axis is about -1g,X、Z is about 0g*/
//  322 /*第五面飞控平放，Y轴正向朝着正上方，Y axis is about 1g,X、Z is about 0g*/
//  323 /*第六面飞控平放，Z轴正向朝着正下方，Z axis is about -1g,X、Y is about 0g*/
//  324 if(flight_direction<=5)//检测到对应面数据
        LDR.W    R0,??DataTable7_9
        LDRB     R0,[R0, #+0]
        CMP      R0,#+6
        BGE.N    ??Accel_Calibartion_0
//  325 {
//  326   uint16_t num_samples=0;
        MOVS     R4,#+0
        B.N      ??Accel_Calibartion_1
//  327   while(num_samples<1000)//采样200次
//  328   {
//  329     if(Gyro_Length<=20.0f
//  330        &&Acce_Correct_Update_Flag==1)//通过陀螺仪模长来确保机体静止
//  331     {
//  332        for(j=0;j<3;j++){
//  333           acce_sample_sum[j]+=Acce_Correct[j]*ACCEL_TO_1G;//加速度计转化为1g量程下
??Accel_Calibartion_2:
        LDR.W    R0,??DataTable7_15
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable5_3  ;; 0x411ce80a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,#+1166016512
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        MOV      R1,SP
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDR      R1,[R1, R5, LSL #+2]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R1,SP
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        STR      R0,[R1, R5, LSL #+2]
//  334        }
        ADDS     R5,R5,#+1
??Accel_Calibartion_3:
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        CMP      R5,#+3
        BLT.N    ??Accel_Calibartion_2
//  335        //delay_ms(4);//间隔10ms，1s内数据取平均
//  336        num_samples++;
        ADDS     R4,R4,#+1
//  337        Acce_Correct_Update_Flag=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_16
        STRB     R0,[R1, #+0]
//  338     }
//  339     Accel_Calibration_Finished[flight_direction]=1;//对应面校准完成标志位置1
??Accel_Calibartion_4:
        MOVS     R0,#+1
        LDR.W    R1,??DataTable7_11
        LDR.W    R2,??DataTable7_9
        LDRB     R2,[R2, #+0]
        STRB     R0,[R1, R2]
??Accel_Calibartion_1:
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        CMP      R4,#+1000
        BGE.N    ??Accel_Calibartion_5
        LDR.W    R0,??DataTable7_17
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable7_18  ;; 0x41a00001
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??Accel_Calibartion_4
        LDR.W    R0,??DataTable7_16
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Accel_Calibartion_4
        MOVS     R5,#+0
        B.N      ??Accel_Calibartion_3
//  340   }
//  341   acce_sample[flight_direction].x=acce_sample_sum[0]/num_samples; //保存对应面的加速度计量
??Accel_Calibartion_5:
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R0,R4
          CFI FunCall __aeabi_ui2f
        BL       __aeabi_ui2f
        MOVS     R1,R0
        LDR      R0,[SP, #+0]
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        LDR.W    R1,??DataTable7_12
        LDR.W    R2,??DataTable7_9
        LDRB     R2,[R2, #+0]
        MOVS     R3,#+12
        MULS     R2,R3,R2
        STR      R0,[R1, R2]
//  342   acce_sample[flight_direction].y=acce_sample_sum[1]/num_samples; //保存对应面的加速度计量
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R0,R4
          CFI FunCall __aeabi_ui2f
        BL       __aeabi_ui2f
        MOVS     R1,R0
        LDR      R0,[SP, #+4]
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        LDR.W    R1,??DataTable7_12
        LDR.W    R2,??DataTable7_9
        LDRB     R2,[R2, #+0]
        MOVS     R3,#+12
        MULS     R2,R3,R2
        ADD      R1,R1,R2
        STR      R0,[R1, #+4]
//  343   acce_sample[flight_direction].z=acce_sample_sum[2]/num_samples; //保存对应面的加速度计量
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R0,R4
          CFI FunCall __aeabi_ui2f
        BL       __aeabi_ui2f
        MOVS     R1,R0
        LDR      R0,[SP, #+8]
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        LDR.W    R1,??DataTable7_12
        LDR.W    R2,??DataTable7_9
        LDRB     R2,[R2, #+0]
        MOVS     R3,#+12
        MULS     R2,R3,R2
        ADD      R1,R1,R2
        STR      R0,[R1, #+8]
//  344   flight_direction=6;//单面矫正完毕
        MOVS     R0,#+6
        LDR.W    R1,??DataTable7_9
        STRB     R0,[R1, #+0]
//  345 }
//  346 
//  347   if((Accel_Calibration_Finished[0]
//  348     &Accel_Calibration_Finished[1]
//  349      &Accel_Calibration_Finished[2]
//  350        &Accel_Calibration_Finished[3]
//  351          &Accel_Calibration_Finished[4]
//  352            &Accel_Calibration_Finished[5])
//  353              &&Accel_Calibration_All_Finished==0)//6面全部校准完毕
??Accel_Calibartion_0:
        LDR.W    R0,??DataTable7_11
        LDRB     R0,[R0, #+0]
        LDR.W    R1,??DataTable7_11
        LDRB     R1,[R1, #+1]
        ANDS     R0,R1,R0
        LDR.W    R1,??DataTable7_11
        LDRB     R1,[R1, #+2]
        ANDS     R0,R1,R0
        LDR.W    R1,??DataTable7_11
        LDRB     R1,[R1, #+3]
        ANDS     R0,R1,R0
        LDR.W    R1,??DataTable7_11
        LDRB     R1,[R1, #+4]
        ANDS     R0,R1,R0
        LDR.W    R1,??DataTable7_11
        LDRB     R1,[R1, #+5]
        TST      R0,R1
        BEQ.W    ??Accel_Calibartion_6
        LDR.W    R0,??DataTable7_10
        LDRB     R0,[R0, #+0]
        CMP      R0,#+0
        BNE.W    ??Accel_Calibartion_6
//  354   {
//  355       Accel_Calibration_All_Finished=1;//加速度计6面校准完成标志
        MOVS     R0,#+1
        LDR.W    R1,??DataTable7_10
        STRB     R0,[R1, #+0]
//  356       Accel_Calibration_Flag=0;//加速度计校准结束，释放遥感操作
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_4
        STRB     R0,[R1, #+0]
//  357       Cal_Flag=Calibrate_accel(acce_sample,
//  358                                 &new_offset,
//  359                                   &new_scales);//将所得6面数据
        LDR.W    R2,??DataTable5_8
        LDR.W    R1,??DataTable5_9
        LDR.W    R0,??DataTable7_12
          CFI FunCall Calibrate_accel
        BL       Calibrate_accel
        LDR.W    R1,??DataTable7_1
        STRB     R0,[R1, #+0]
//  360       for(i=0;i<6;i++)
        MOVS     R0,#+0
        B.N      ??Accel_Calibartion_7
//  361       {
//  362         Accel_Calibration_Finished[i]=0;//对应面标志位清零
??Accel_Calibartion_8:
        MOVS     R1,#+0
        LDR.W    R2,??DataTable7_11
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        STRB     R1,[R2, R0]
//  363       }
        ADDS     R0,R0,#+1
??Accel_Calibartion_7:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+6
        BLT.N    ??Accel_Calibartion_8
//  364      if(Cal_Flag==true)//加速度计校准成功
        LDR.W    R0,??DataTable7_1
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Accel_Calibartion_9
//  365      {
//  366        WriteFlashNineFloat(Accel_Offset_Address,
//  367                         new_offset.x,
//  368                         new_offset.y,
//  369                         new_offset.z,
//  370                         new_scales.x,
//  371                         new_scales.y,
//  372                         new_scales.z,
//  373                         Mag_Offset_Read.x,
//  374                         Mag_Offset_Read.y,
//  375                         Mag_Offset_Read.z);//写入加速度零点偏执与磁力计中心偏执
        LDR.W    R0,??DataTable8
        LDR      R0,[R0, #+8]
        STR      R0,[SP, #+20]
        LDR.W    R0,??DataTable8
        LDR      R0,[R0, #+4]
        STR      R0,[SP, #+16]
        LDR.W    R0,??DataTable8
        LDR      R0,[R0, #+0]
        STR      R0,[SP, #+12]
        LDR.W    R0,??DataTable5_8
        LDR      R0,[R0, #+8]
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable5_8
        LDR      R0,[R0, #+4]
        STR      R0,[SP, #+4]
        LDR.W    R0,??DataTable5_8
        LDR      R0,[R0, #+0]
        STR      R0,[SP, #+0]
        LDR.W    R0,??DataTable5_9
        LDR      R3,[R0, #+8]
        LDR.W    R0,??DataTable5_9
        LDR      R2,[R0, #+4]
        LDR.W    R0,??DataTable5_9
        LDR      R1,[R0, #+0]
        MOVS     R0,#+0
          CFI FunCall WriteFlashNineFloat
        BL       WriteFlashNineFloat
//  376        Parameter_Init();//读取写入参数
          CFI FunCall Parameter_Init
        BL       Parameter_Init
//  377        Bling_Mode=0;//恢复正常指示模式
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_3
        STRH     R0,[R1, #+0]
//  378        Bling_Set(&Light_1,3000,1000,0.3,0,GPIOC,GPIO_Pin_4,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOVS     R0,#+16
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable8_1  ;; 0x3e99999a
        MOV      R2,#+1000
        MOVW     R1,#+3000
        LDR.W    R0,??DataTable7_6
          CFI FunCall Bling_Set
        BL       Bling_Set
//  379        Bling_Set(&Light_2,3000,1000,0.5,0,GPIOC,GPIO_Pin_5,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOVS     R0,#+32
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOV      R2,#+1000
        MOVW     R1,#+3000
        LDR.W    R0,??DataTable7_7
          CFI FunCall Bling_Set
        BL       Bling_Set
//  380        Bling_Set(&Light_3,3000,1000,0.8,0,GPIOC,GPIO_Pin_10,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOV      R0,#+1024
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable8_2  ;; 0x3f4ccccd
        MOV      R2,#+1000
        MOVW     R1,#+3000
        LDR.W    R0,??DataTable7_8
          CFI FunCall Bling_Set
        BL       Bling_Set
        B.N      ??Accel_Calibartion_10
//  381      }
//  382      else//加速度计校准失败
//  383      {
//  384         Bling_Mode=0;//恢复正常指示模式
??Accel_Calibartion_9:
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_3
        STRH     R0,[R1, #+0]
//  385         Bling_Set(&Light_1,5000,200,0.3,0,GPIOC,GPIO_Pin_4,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOVS     R0,#+16
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable8_1  ;; 0x3e99999a
        MOVS     R2,#+200
        MOVW     R1,#+5000
        LDR.W    R0,??DataTable7_6
          CFI FunCall Bling_Set
        BL       Bling_Set
//  386         Bling_Set(&Light_2,5000,200,0.5,0,GPIOC,GPIO_Pin_5,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOVS     R0,#+32
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOVS     R2,#+200
        MOVW     R1,#+5000
        LDR.W    R0,??DataTable7_7
          CFI FunCall Bling_Set
        BL       Bling_Set
//  387         Bling_Set(&Light_3,5000,200,0.8,0,GPIOC,GPIO_Pin_10,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOV      R0,#+1024
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable8_2  ;; 0x3f4ccccd
        MOVS     R2,#+200
        MOVW     R1,#+5000
        LDR.W    R0,??DataTable7_8
          CFI FunCall Bling_Set
        BL       Bling_Set
//  388         Page_Number=0;//OLED恢复首页
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_13
        STRH     R0,[R1, #+0]
//  389      }
//  390      return true;
??Accel_Calibartion_10:
        MOVS     R0,#+1
        B.N      ??Accel_Calibartion_11
//  391   }
//  392   return false;
??Accel_Calibartion_6:
        MOVS     R0,#+0
??Accel_Calibartion_11:
        ADD      SP,SP,#+28
          CFI CFA R13+12
        POP      {R4,R5,PC}       ;; return
//  393 }
          CFI EndBlock cfiBlock6

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H, 0H, 0H
//  394 
//  395 
//  396 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function Reset_Accel_Calibartion
          CFI NoCalls
        THUMB
//  397 void Reset_Accel_Calibartion(uint8_t Type)
//  398 {
Reset_Accel_Calibartion:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
//  399   uint16 i=0;
        MOVS     R1,#+0
//  400   for(i=0;i<6;i++)
        MOVS     R1,#+0
        B.N      ??Reset_Accel_Calibartion_0
//  401   {
//  402      Accel_Calibration_Finished[i]=0;//对应面标志位清零
??Reset_Accel_Calibartion_1:
        MOVS     R2,#+0
        LDR.W    R3,??DataTable7_11
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        STRB     R2,[R3, R1]
//  403      acce_sample[i].x=0; //清空对应面的加速度计量
        MOVS     R2,#+0
        LDR.W    R3,??DataTable7_12
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R4,#+12
        MUL      R4,R4,R1
        STR      R2,[R3, R4]
//  404      acce_sample[i].y=0; //清空对应面的加速度计量
        MOVS     R2,#+0
        LDR.W    R3,??DataTable7_12
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R4,#+12
        MUL      R4,R4,R1
        ADD      R3,R3,R4
        STR      R2,[R3, #+4]
//  405      acce_sample[i].z=0; //清空对应面的加速度计量
        MOVS     R2,#+0
        LDR.W    R3,??DataTable7_12
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R4,#+12
        MUL      R4,R4,R1
        ADD      R3,R3,R4
        STR      R2,[R3, #+8]
//  406   }
        ADDS     R1,R1,#+1
??Reset_Accel_Calibartion_0:
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        CMP      R1,#+6
        BLT.N    ??Reset_Accel_Calibartion_1
//  407   Accel_Calibration_All_Finished=0;//全部校准完成标志位清零
        MOVS     R1,#+0
        LDR.W    R2,??DataTable7_10
        STRB     R1,[R2, #+0]
//  408   if(Type==1)  Accel_Calibration_Flag=0;
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+1
        BNE.N    ??Reset_Accel_Calibartion_2
        MOVS     R0,#+0
        LDR.W    R1,??DataTable7_4
        STRB     R0,[R1, #+0]
//  409 }
??Reset_Accel_Calibartion_2:
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock7
//  410 
//  411 
//  412 typedef struct
//  413 {
//  414 uint8_t accel_off;
//  415 uint8_t accel_scale;
//  416 uint8_t mag;
//  417 }Parameter_Flag;
//  418 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  419 Parameter_Flag Parameter_Read_Flag;
Parameter_Read_Flag:
        DS8 4
//  420 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function Parameter_Init
        THUMB
//  421 bool Parameter_Init(void)
//  422 {
Parameter_Init:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//  423     bool success=true;
        MOVS     R4,#+1
//  424    /************加速度计零偏与标度值*******/
//  425     Parameter_Read_Flag.accel_off=ReadFlashThreeFloat(Accel_Offset_Address,
//  426                          &Accel_Offset_Read.x,
//  427                          &Accel_Offset_Read.y,
//  428                          &Accel_Offset_Read.z);
        LDR.W    R3,??DataTable8_3
        LDR.W    R2,??DataTable8_4
        LDR.W    R1,??DataTable8_5
        MOVS     R0,#+0
          CFI FunCall ReadFlashThreeFloat
        BL       ReadFlashThreeFloat
        LDR.W    R1,??DataTable8_6
        STRB     R0,[R1, #+0]
//  429 
//  430     Parameter_Read_Flag.accel_scale=ReadFlashThreeFloat(Accel_Scale_Address,
//  431                          &Accel_Scale_Read.x,
//  432                          &Accel_Scale_Read.y,
//  433                          &Accel_Scale_Read.z);
        LDR.W    R3,??DataTable8_7
        LDR.W    R2,??DataTable8_8
        LDR.W    R1,??DataTable8_9
        MOVS     R0,#+12
          CFI FunCall ReadFlashThreeFloat
        BL       ReadFlashThreeFloat
        LDR.W    R1,??DataTable8_6
        STRB     R0,[R1, #+1]
//  434     /************磁力计零偏****************/
//  435     Parameter_Read_Flag.mag=ReadFlashThreeFloat(Mag_Offset_Address,
//  436                          &Mag_Offset_Read.x,
//  437                          &Mag_Offset_Read.y,
//  438                          &Mag_Offset_Read.z);
        LDR.W    R3,??DataTable8_10
        LDR.W    R2,??DataTable8_11
        LDR.W    R1,??DataTable8
        MOVS     R0,#+24
          CFI FunCall ReadFlashThreeFloat
        BL       ReadFlashThreeFloat
        LDR.W    R1,??DataTable8_6
        STRB     R0,[R1, #+2]
//  439     // sanity check scale
//  440     if(ABS(Accel_Scale_Read.x-1.0f)>0.3f
//  441          || ABS(Accel_Scale_Read.y-1.0f)>0.3f
//  442            || ABS(Accel_Scale_Read.z-1.0f)>0.3f)
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Parameter_Init_0
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        B.N      ??Parameter_Init_1
??Parameter_Init_0:
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        EORS     R0,R0,#0x80000000
??Parameter_Init_1:
        LDR.W    R1,??DataTable8_12  ;; 0x3e99999b
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Parameter_Init_2
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+4]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Parameter_Init_3
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+4]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        B.N      ??Parameter_Init_4
??Parameter_Init_3:
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+4]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        EORS     R0,R0,#0x80000000
??Parameter_Init_4:
        LDR.W    R1,??DataTable8_12  ;; 0x3e99999b
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Parameter_Init_2
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+8]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Parameter_Init_5
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+8]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        B.N      ??Parameter_Init_6
??Parameter_Init_5:
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+8]
        LDR.N    R1,??DataTable5_4  ;; 0xbf800000
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        EORS     R0,R0,#0x80000000
??Parameter_Init_6:
        LDR.W    R1,??DataTable8_12  ;; 0x3e99999b
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Parameter_Init_7
//  443     {
//  444         success = false;
??Parameter_Init_2:
        MOVS     R4,#+0
//  445     }
//  446     // sanity check offsets (3.5 is roughly 3/10th of a G, 5.0 is roughly half a G)
//  447     if(ABS(Accel_Offset_Read.x) > 3.5f
//  448          || ABS(Accel_Offset_Read.y) > 3.5f
//  449            || ABS(Accel_Offset_Read.z) > 3.5f)
??Parameter_Init_7:
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+0]
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Parameter_Init_8
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+0]
        B.N      ??Parameter_Init_9
??Parameter_Init_8:
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+0]
        EORS     R0,R0,#0x80000000
??Parameter_Init_9:
        LDR.W    R1,??DataTable7  ;; 0x40600001
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Parameter_Init_10
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+4]
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Parameter_Init_11
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+4]
        B.N      ??Parameter_Init_12
??Parameter_Init_11:
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+4]
        EORS     R0,R0,#0x80000000
??Parameter_Init_12:
        LDR.W    R1,??DataTable7  ;; 0x40600001
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BLS.N    ??Parameter_Init_10
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+8]
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Parameter_Init_13
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+8]
        B.N      ??Parameter_Init_14
??Parameter_Init_13:
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+8]
        EORS     R0,R0,#0x80000000
??Parameter_Init_14:
        LDR.W    R1,??DataTable7  ;; 0x40600001
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Parameter_Init_15
//  450     {
//  451         success = false;
??Parameter_Init_10:
        MOVS     R4,#+0
//  452     }
//  453 
//  454 
//  455    if(success==true
//  456       &&Parameter_Read_Flag.accel_off!=0x07
//  457        &&Parameter_Read_Flag.accel_scale!=0x07)//Flash内数据正常，更新加速度校正值
??Parameter_Init_15:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+1
        BNE.N    ??Parameter_Init_16
        LDR.W    R0,??DataTable8_6
        LDRB     R0,[R0, #+0]
        CMP      R0,#+7
        BEQ.N    ??Parameter_Init_16
        LDR.W    R0,??DataTable8_6
        LDRB     R0,[R0, #+1]
        CMP      R0,#+7
        BEQ.N    ??Parameter_Init_16
//  458    {
//  459     B[0]=Accel_Offset_Read.x;//*One_G_TO_Accel;
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+0]
//  460     B[1]=Accel_Offset_Read.y;//*One_G_TO_Accel;
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+4]
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+4]
//  461     B[2]=Accel_Offset_Read.z;//*One_G_TO_Accel;
        LDR.W    R0,??DataTable8_5
        LDR      R0,[R0, #+8]
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+8]
//  462     K[0]=Accel_Scale_Read.x;
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable8_14
        STR      R0,[R1, #+0]
//  463     K[1]=Accel_Scale_Read.y;
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+4]
        LDR.W    R1,??DataTable8_14
        STR      R0,[R1, #+4]
//  464     K[2]=Accel_Scale_Read.z;
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+8]
        LDR.W    R1,??DataTable8_14
        STR      R0,[R1, #+8]
//  465    }
//  466    /**********磁力计中心偏执获取************/
//  467    if(Parameter_Read_Flag.mag!=0x07)
??Parameter_Init_16:
        LDR.W    R0,??DataTable8_6
        LDRB     R0,[R0, #+2]
        CMP      R0,#+7
        BEQ.N    ??Parameter_Init_17
//  468    {
//  469    Mag_Offset[0]=(int16_t)(Mag_Offset_Read.x);
        LDR.W    R0,??DataTable8
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable8_15
        STRH     R0,[R1, #+0]
//  470    Mag_Offset[1]=(int16_t)(Mag_Offset_Read.y);
        LDR.W    R0,??DataTable8
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable8_15
        STRH     R0,[R1, #+2]
//  471    Mag_Offset[2]=(int16_t)(Mag_Offset_Read.z);
        LDR.W    R0,??DataTable8
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable8_15
        STRH     R0,[R1, #+4]
//  472    }
//  473    return success;
??Parameter_Init_17:
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R4,PC}          ;; return
//  474 }
          CFI EndBlock cfiBlock8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5:
        DC32     0x3089705f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_1:
        DC32     0x42c80000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_2:
        DC32     0x3dd0d67f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_3:
        DC32     0x411ce80a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_4:
        DC32     0xbf800000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_5:
        DC32     0x3e4cccce

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_6:
        DC32     ?_5

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_7:
        DC32     0x3b1ce80a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_8:
        DC32     new_scales

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_9:
        DC32     new_offset
//  475 /************加速度计6面矫正结束***********************/
//  476 
//  477 
//  478 /***********磁力计中心矫正，取单轴最大、最小值平均******/

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  479 uint8_t Mag_Calibration_Flag=0,Mag_Calibration_All_Finished;
Mag_Calibration_Flag:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
Mag_Calibration_All_Finished:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  480 uint8_t Mag_Calibration_Finished[2]={0};
Mag_Calibration_Finished:
        DS8 2

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  481 uint16_t Mag_Calibration_Makesure_Cnt=0;
Mag_Calibration_Makesure_Cnt:
        DS8 2

        SECTION `.data`:DATA:REORDER:NOROOT(0)
        DATA
//  482 uint8_t  Mag_Calibration_Mode=2;
Mag_Calibration_Mode:
        DC8 2

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  483 uint16_t Mag_Calibration_Cnt=0;
Mag_Calibration_Cnt:
        DS8 2
//  484 /*********************************************/

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
//  485 const int16_t Mag_360_define[12]={
Mag_360_define:
        DC16 0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330
//  486 0,30,60,90,
//  487 120,150,180,210,
//  488 240,270,300,330
//  489 };//磁力计矫正遍历角度，确保数据采集充分

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  490 uint8_t Mag_360_Flag[2][12]={0};
Mag_360_Flag:
        DS8 24

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  491 uint16_t Mag_Is_Okay_Flag[2];
Mag_Is_Okay_Flag:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  492 Calibration Mag;
Mag:
        DS8 24

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  493 Mag_Unit DataMag;
DataMag:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  494 Mag_Unit Mag_Offset_Read={
Mag_Offset_Read:
        DS8 12
//  495   0,0,0,
//  496 };

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function Mag_Calibration_Check
        THUMB
//  497 void Mag_Calibration_Check(void)
//  498 {
Mag_Calibration_Check:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
        SUB      SP,SP,#+20
          CFI CFA R13+24
//  499    uint16_t  i=0,j=0;
        MOVS     R0,#+0
        MOVS     R1,#+0
//  500    if(Throttle_Control==1000&&Yaw_Control>=80&&Roll_Control>=40&&Pitch_Control>=40) Mag_Calibration_Makesure_Cnt++;
        LDR.N    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Mag_Calibration_Check_0
        LDR.N    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+80
        BLT.N    ??Mag_Calibration_Check_0
        LDR.N    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Mag_Calibration_Check_0
        LDR.N    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Mag_Calibration_Check_0
        LDR.W    R0,??DataTable8_16
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable8_16
        STRH     R0,[R1, #+0]
//  501    if(Throttle_Control==1000
//  502       &&Yaw_Control>=80
//  503         &&Roll_Control>=40
//  504           &&Pitch_Control>=40
//  505            &&Mag_Calibration_Makesure_Cnt>250*4//持续4S
//  506             )//进入磁力计校准模式
??Mag_Calibration_Check_0:
        LDR.N    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Mag_Calibration_Check_1
        LDR.N    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+80
        BLT.N    ??Mag_Calibration_Check_1
        LDR.N    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Mag_Calibration_Check_1
        LDR.N    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+40
        BLT.N    ??Mag_Calibration_Check_1
        LDR.W    R0,??DataTable8_16
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BLE.N    ??Mag_Calibration_Check_1
//  507   {
//  508       Bling_Mode=2;
        MOVS     R0,#+2
        LDR.N    R1,??DataTable7_3
        STRH     R0,[R1, #+0]
//  509       Mag_Calibration_Flag=1;//磁力计校准模式
        MOVS     R0,#+1
        LDR.W    R1,??DataTable8_17
        STRB     R0,[R1, #+0]
//  510       Mag_Calibration_Mode=2;
        MOVS     R0,#+2
        LDR.W    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
//  511       Bling_Set(&Light_1,1000,500,0.2,0,GPIOC,GPIO_Pin_4,1);
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
        MOVS     R0,#+16
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable8_19  ;; 0x3e4ccccd
        MOV      R2,#+500
        MOV      R1,#+1000
        LDR.N    R0,??DataTable7_6
          CFI FunCall Bling_Set
        BL       Bling_Set
//  512       Bling_Set(&Light_2,1000,500,0.5,0,GPIOC,GPIO_Pin_5,1);
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
        MOVS     R0,#+32
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOV      R2,#+500
        MOV      R1,#+1000
        LDR.N    R0,??DataTable7_7
          CFI FunCall Bling_Set
        BL       Bling_Set
//  513       Bling_Set(&Light_3,1000,500,0.7,0,GPIOC,GPIO_Pin_10,1);
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
        MOV      R0,#+1024
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable7_5  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable8_20  ;; 0x3f333333
        MOV      R2,#+500
        MOV      R1,#+1000
        LDR.N    R0,??DataTable7_8
          CFI FunCall Bling_Set
        BL       Bling_Set
//  514       Mag_Calibration_Makesure_Cnt=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable8_16
        STRH     R0,[R1, #+0]
//  515       Mag_Calibration_All_Finished=0;//全部校准完成标志位清零
        MOVS     R0,#+0
        LDR.W    R1,??DataTable8_21
        STRB     R0,[R1, #+0]
//  516       for(i=0;i<2;i++)
        MOVS     R0,#+0
        B.N      ??Mag_Calibration_Check_2
//  517       {
//  518         Mag_Calibration_Finished[i]=0;//对应面标志位清零
//  519         for(j=0;j<12;j++) {Mag_360_Flag[i][j]=0;}
??Mag_Calibration_Check_3:
        LDR.W    R2,??DataTable8_22
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVS     R3,#+12
        MUL      R3,R3,R0
        ADD      R2,R2,R3
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R3,#+0
        STRB     R3,[R2, R1]
        ADDS     R1,R1,#+1
??Mag_Calibration_Check_4:
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        CMP      R1,#+12
        BLT.N    ??Mag_Calibration_Check_3
        ADDS     R0,R0,#+1
??Mag_Calibration_Check_2:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+2
        BGE.N    ??Mag_Calibration_Check_5
        MOVS     R1,#+0
        LDR.W    R2,??DataTable8_23
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        STRB     R1,[R2, R0]
        MOVS     R1,#+0
        B.N      ??Mag_Calibration_Check_4
//  520       }
//  521       Page_Number=11;
??Mag_Calibration_Check_5:
        MOVS     R0,#+11
        LDR.N    R1,??DataTable7_13
        STRH     R0,[R1, #+0]
//  522       Reset_Accel_Calibartion(1);
        MOVS     R0,#+1
          CFI FunCall Reset_Accel_Calibartion
        BL       Reset_Accel_Calibartion
//  523   }
//  524 
//  525   if(Mag_Calibration_Flag==1)
??Mag_Calibration_Check_1:
        LDR.W    R0,??DataTable8_17
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Mag_Calibration_Check_6
//  526   {
//  527      if(Throttle_Control==1000
//  528         &&Yaw_Control<=-80
//  529           &&Roll_Control==0
//  530             &&Pitch_Control==0) //第一面矫正
        LDR.N    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Mag_Calibration_Check_7
        LDR.N    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMN      R0,#+79
        BGE.N    ??Mag_Calibration_Check_7
        LDR.N    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibration_Check_7
        LDR.N    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibration_Check_7
//  531      {
//  532          Mag_Calibration_Cnt++;
        LDR.W    R0,??DataTable8_24
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable8_24
        STRH     R0,[R1, #+0]
//  533          if(Mag_Calibration_Cnt>=4*25)
        LDR.W    R0,??DataTable8_24
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.N    ??Mag_Calibration_Check_8
//  534          {
//  535             Mag_Calibration_Mode=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
//  536             Mag_Is_Okay_Flag[1]=0;//单面数据采集完成标志位置0
        MOVS     R0,#+0
        LDR.W    R1,??DataTable8_25
        STRH     R0,[R1, #+2]
//  537             for(i=0;i<12;i++) Mag_360_Flag[1][i]=0;//清空采集角遍历数据点
        MOVS     R0,#+0
??Mag_Calibration_Check_9:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+12
        BGE.N    ??Mag_Calibration_Check_8
        MOVS     R1,#+0
        LDR.W    R2,??DataTable8_22
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0
        STRB     R1,[R2, #+12]
        ADDS     R0,R0,#+1
        B.N      ??Mag_Calibration_Check_9
//  538          }
//  539      }
//  540   else if(Throttle_Control==1000
//  541              &&Yaw_Control>80
//  542                &&Roll_Control==0
//  543                  &&Pitch_Control==0) //第二面矫正
??Mag_Calibration_Check_7:
        LDR.N    R0,??DataTable6
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1000
        BNE.N    ??Mag_Calibration_Check_10
        LDR.N    R0,??DataTable6_1
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+81
        BLT.N    ??Mag_Calibration_Check_10
        LDR.N    R0,??DataTable6_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibration_Check_10
        LDR.N    R0,??DataTable7_2
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibration_Check_10
//  544      {
//  545          Mag_Calibration_Cnt++;
        LDR.W    R0,??DataTable8_24
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable8_24
        STRH     R0,[R1, #+0]
//  546          if(Mag_Calibration_Cnt>=4*25)
        LDR.W    R0,??DataTable8_24
        LDRH     R0,[R0, #+0]
        CMP      R0,#+100
        BLT.N    ??Mag_Calibration_Check_8
//  547          {
//  548              Mag_Calibration_Mode=1;
        MOVS     R0,#+1
        LDR.W    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
//  549              Mag_Is_Okay_Flag[1]=0;//单面数据采集完成标志位置0
        MOVS     R0,#+0
        LDR.W    R1,??DataTable8_25
        STRH     R0,[R1, #+2]
//  550              for(i=0;i<12;i++) Mag_360_Flag[1][i]=0;//清空采集角遍历数据点
        MOVS     R0,#+0
??Mag_Calibration_Check_11:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+12
        BGE.N    ??Mag_Calibration_Check_8
        MOVS     R1,#+0
        LDR.W    R2,??DataTable8_22
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0
        STRB     R1,[R2, #+12]
        ADDS     R0,R0,#+1
        B.N      ??Mag_Calibration_Check_11
//  551          }
//  552      }
//  553   else
//  554   {
//  555     Mag_Calibration_Cnt/=2;
??Mag_Calibration_Check_10:
        LDR.W    R0,??DataTable8_24
        LDRH     R0,[R0, #+0]
        MOVS     R1,#+2
        SDIV     R0,R0,R1
        LDR.W    R1,??DataTable8_24
        STRH     R0,[R1, #+0]
//  556   }
//  557   if(Mag_Calibration_Cnt>=200)  Mag_Calibration_Cnt=200;
??Mag_Calibration_Check_8:
        LDR.W    R0,??DataTable8_24
        LDRH     R0,[R0, #+0]
        CMP      R0,#+200
        BLT.N    ??Mag_Calibration_Check_6
        MOVS     R0,#+200
        LDR.W    R1,??DataTable8_24
        STRH     R0,[R1, #+0]
//  558 
//  559   }
//  560 
//  561 }
??Mag_Calibration_Check_6:
        ADD      SP,SP,#+20
          CFI CFA R13+4
        POP      {PC}             ;; return
          CFI EndBlock cfiBlock9

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable6:
        DC32     Throttle_Control

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable6_1:
        DC32     Yaw_Control

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable6_2:
        DC32     Roll_Control

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable6_3:
        DC32     Accel_Calibration_Makesure_Cnt
//  562 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function Reset_Mag_Calibartion
          CFI NoCalls
        THUMB
//  563 void Reset_Mag_Calibartion(uint8_t Type)
//  564 {
//  565   uint16 i=0;
Reset_Mag_Calibartion:
        MOVS     R1,#+0
//  566   for(i=0;i<12;i++)
        MOVS     R1,#+0
        B.N      ??Reset_Mag_Calibartion_0
//  567   {
//  568     Mag_360_Flag[0][i]=0;//清空采集角点
??Reset_Mag_Calibartion_1:
        MOVS     R2,#+0
        LDR.W    R3,??DataTable8_22
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        STRB     R2,[R3, R1]
//  569     Mag_360_Flag[1][i]=0;//清空采集角点
        MOVS     R2,#+0
        LDR.W    R3,??DataTable8_22
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        ADD      R3,R3,R1
        STRB     R2,[R3, #+12]
//  570   }
        ADDS     R1,R1,#+1
??Reset_Mag_Calibartion_0:
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        CMP      R1,#+12
        BLT.N    ??Reset_Mag_Calibartion_1
//  571   Mag_Is_Okay_Flag[0]=0;
        MOVS     R1,#+0
        LDR.W    R2,??DataTable8_25
        STRH     R1,[R2, #+0]
//  572   Mag_Is_Okay_Flag[1]=0;
        MOVS     R1,#+0
        LDR.W    R2,??DataTable8_25
        STRH     R1,[R2, #+2]
//  573   Mag_Calibration_Mode=2;
        MOVS     R1,#+2
        LDR.W    R2,??DataTable8_18
        STRB     R1,[R2, #+0]
//  574   if(Type==1)  Mag_Calibration_Flag=0;
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+1
        BNE.N    ??Reset_Mag_Calibartion_2
        MOVS     R0,#+0
        LDR.W    R1,??DataTable8_17
        STRB     R0,[R1, #+0]
//  575 }
??Reset_Mag_Calibartion_2:
        BX       LR               ;; return
          CFI EndBlock cfiBlock10

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DC32     0x40600001

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DC32     Cal_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DC32     Pitch_Control

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_3:
        DC32     Bling_Mode

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_4:
        DC32     Accel_Calibration_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_5:
        DC32     0x40011000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_6:
        DC32     Light_1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_7:
        DC32     Light_2

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_8:
        DC32     Light_3

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_9:
        DC32     flight_direction

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_10:
        DC32     Accel_Calibration_All_Finished

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_11:
        DC32     Accel_Calibration_Finished

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_12:
        DC32     acce_sample

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_13:
        DC32     Page_Number

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_14:
        DC32     Accel_flight_direction_cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_15:
        DC32     Acce_Correct

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_16:
        DC32     Acce_Correct_Update_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_17:
        DC32     Gyro_Length

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_18:
        DC32     0x41a00001
//  576 
//  577 /***************************************************
//  578 函数名: Mag_Calibartion(Mag_Unit MagData,float MagAngle)
//  579 说明:	磁力计中心标定、利用遥控器直接进入
//  580 入口:	磁力计磁偏角、三轴磁力计原始值
//  581 出口:	无
//  582 备注:	在主函数While(1)里面，利用中断空隙时间一直运行
//  583 ****************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function Mag_Calibartion
        THUMB
//  584 uint8_t Mag_Calibartion(Mag_Unit MagData,float MagAngle)
//  585 {
Mag_Calibartion:
        PUSH     {R0-R2,R4,R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+24
        SUB      SP,SP,#+24
          CFI CFA R13+48
        MOVS     R4,R3
//  586   uint16 i=0;
        MOVS     R5,#+0
//  587 /********第一面Z轴正向朝着正上方，
//  588   开始绕竖直轴旋转，Z axis is about 1g,X、Y is about 0g*/
//  589 /********第二面Y轴正向朝着正上方，
//  590   开始绕竖直轴旋转，Y axis is about 1g,X、Z is about 0g*/
//  591 if(Mag_Calibration_Mode<2)//检测到对应面数据
        LDR.W    R0,??DataTable8_18
        LDRB     R0,[R0, #+0]
        CMP      R0,#+2
        BGE.W    ??Mag_Calibartion_0
//  592 {
//  593   for(i=0;i<12;i++)
        MOVS     R5,#+0
        B.N      ??Mag_Calibartion_1
//  594   {
//  595     if(ABS(MagAngle-Mag_360_define[i])<=10.0
//  596          &&Mag_Calibration_Mode==0
//  597           &&Acce_Correct[2]>=3500)//Z轴基本竖直
//  598     {
//  599       Mag_360_Flag[0][i]=1;
//  600     }
//  601 
//  602     if(ABS(MagAngle-Mag_360_define[i])<=10.0
//  603          &&Mag_Calibration_Mode==1
//  604           &&Acce_Correct[1]>=3500)//Y轴基本竖直
??Mag_Calibartion_2:
        LDR.W    R0,??DataTable8_26
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
??Mag_Calibartion_3:
        LDR.W    R1,??DataTable8_27  ;; 0x41200001
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??Mag_Calibartion_4
        LDR.W    R0,??DataTable8_18
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Mag_Calibartion_4
        LDR.W    R0,??DataTable8_28
        LDRSH    R0,[R0, #+2]
        MOVW     R1,#+3500
        CMP      R0,R1
        BLT.N    ??Mag_Calibartion_4
//  605     {
//  606       Mag_360_Flag[1][i]=1;
        MOVS     R0,#+1
        LDR.W    R1,??DataTable8_22
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        ADD      R1,R1,R5
        STRB     R0,[R1, #+12]
//  607     }
??Mag_Calibartion_4:
        ADDS     R5,R5,#+1
??Mag_Calibartion_1:
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        CMP      R5,#+12
        BGE.N    ??Mag_Calibartion_5
        LDR.W    R0,??DataTable8_26
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Mag_Calibartion_6
        LDR.W    R0,??DataTable8_26
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        B.N      ??Mag_Calibartion_7
??Mag_Calibartion_6:
        LDR.W    R0,??DataTable8_26
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
??Mag_Calibartion_7:
        LDR.W    R1,??DataTable8_27  ;; 0x41200001
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??Mag_Calibartion_8
        LDR.W    R0,??DataTable8_18
        LDRB     R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibartion_8
        LDR.W    R0,??DataTable8_28
        LDRSH    R0,[R0, #+4]
        MOVW     R1,#+3500
        CMP      R0,R1
        BLT.N    ??Mag_Calibartion_8
        MOVS     R0,#+1
        LDR.W    R1,??DataTable8_22
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        STRB     R0,[R1, R5]
??Mag_Calibartion_8:
        LDR.W    R0,??DataTable8_26
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOVS     R1,#+0
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BCS.N    ??Mag_Calibartion_2
        LDR.W    R0,??DataTable8_26
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LDRSH    R0,[R0, R5, LSL #+1]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        B.N      ??Mag_Calibartion_3
//  608   }
//  609   if(MagData.x >= Mag.x_max)   Mag.x_max = (int16_t)(MagData.x);
??Mag_Calibartion_5:
        LDR.W    R0,??DataTable8_29
        LDRSH    R0,[R0, #+0]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        LDR      R0,[SP, #+24]
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Mag_Calibartion_9
        LDR      R0,[SP, #+24]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable8_29
        STRH     R0,[R1, #+0]
//  610   if(MagData.x <  Mag.x_min)   Mag.x_min = (int16_t)(MagData.x);
??Mag_Calibartion_9:
        LDR.W    R0,??DataTable8_29
        LDRSH    R0,[R0, #+6]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        LDR      R0,[SP, #+24]
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??Mag_Calibartion_10
        LDR      R0,[SP, #+24]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.W    R1,??DataTable8_29
        STRH     R0,[R1, #+6]
//  611   if(MagData.y >= Mag.y_max)   Mag.y_max = (int16_t)(MagData.y);
??Mag_Calibartion_10:
        LDR.W    R0,??DataTable8_29
        LDRSH    R0,[R0, #+2]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        LDR      R0,[SP, #+28]
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Mag_Calibartion_11
        LDR      R0,[SP, #+28]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable8_29
        STRH     R0,[R1, #+2]
//  612   if(MagData.y <  Mag.y_min)   Mag.y_min = (int16_t)(MagData.y);
??Mag_Calibartion_11:
        LDR.N    R0,??DataTable8_29
        LDRSH    R0,[R0, #+8]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        LDR      R0,[SP, #+28]
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??Mag_Calibartion_12
        LDR      R0,[SP, #+28]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable8_29
        STRH     R0,[R1, #+8]
//  613   if(MagData.z >= Mag.z_max)   Mag.z_max = (int16_t)(MagData.z);
??Mag_Calibartion_12:
        LDR.N    R0,??DataTable8_29
        LDRSH    R0,[R0, #+4]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        LDR      R0,[SP, #+32]
          CFI FunCall __aeabi_cfrcmple
        BL       __aeabi_cfrcmple
        BHI.N    ??Mag_Calibartion_13
        LDR      R0,[SP, #+32]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable8_29
        STRH     R0,[R1, #+4]
//  614   if(MagData.z <  Mag.z_min)   Mag.z_min = (int16_t)(MagData.z);
??Mag_Calibartion_13:
        LDR.N    R0,??DataTable8_29
        LDRSH    R0,[R0, #+10]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R1,R0
        LDR      R0,[SP, #+32]
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??Mag_Calibartion_0
        LDR      R0,[SP, #+32]
          CFI FunCall __aeabi_f2iz
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable8_29
        STRH     R0,[R1, #+10]
//  615 }
//  616 if(Mag_360_Flag[0][0]&Mag_360_Flag[0][1]&Mag_360_Flag[0][2]
//  617     &Mag_360_Flag[0][3]&Mag_360_Flag[0][4]&Mag_360_Flag[0][5]
//  618      &Mag_360_Flag[0][6]&Mag_360_Flag[0][7]&Mag_360_Flag[0][8]
//  619       &Mag_360_Flag[0][9]&Mag_360_Flag[0][10]&Mag_360_Flag[0][11]
//  620      )
??Mag_Calibartion_0:
        LDR.N    R0,??DataTable8_22
        LDRB     R0,[R0, #+0]
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+1]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+2]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+3]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+4]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+5]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+6]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+7]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+8]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+9]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+10]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+11]
        TST      R0,R1
        BEQ.N    ??Mag_Calibartion_14
//  621 {
//  622   Mag_Is_Okay_Flag[0]=1;//单面数据采集完成标志位置1
        MOVS     R0,#+1
        LDR.N    R1,??DataTable8_25
        STRH     R0,[R1, #+0]
//  623   for(i=0;i<12;i++)  Mag_360_Flag[0][i]=0;//清空采集角点
        MOVS     R5,#+0
        B.N      ??Mag_Calibartion_15
??Mag_Calibartion_16:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_22
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        STRB     R0,[R1, R5]
        ADDS     R5,R5,#+1
??Mag_Calibartion_15:
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        CMP      R5,#+12
        BLT.N    ??Mag_Calibartion_16
//  624   if(Mag_Is_Okay_Flag[1]==0)//另外一面数据未完成
        LDR.N    R0,??DataTable8_25
        LDRH     R0,[R0, #+2]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibartion_17
//  625     Mag_Calibration_Mode=1;//自动进入下一面数据采集模式
        MOVS     R0,#+1
        LDR.N    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
        B.N      ??Mag_Calibartion_14
//  626   else Mag_Calibration_Mode=2;//
??Mag_Calibartion_17:
        MOVS     R0,#+2
        LDR.N    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
//  627 }
//  628 if(Mag_360_Flag[1][0]&Mag_360_Flag[1][1]&Mag_360_Flag[1][2]
//  629     &Mag_360_Flag[1][3]&Mag_360_Flag[1][4]&Mag_360_Flag[1][5]
//  630      &Mag_360_Flag[1][6]&Mag_360_Flag[1][7]&Mag_360_Flag[1][8]
//  631       &Mag_360_Flag[1][9]&Mag_360_Flag[1][10]&Mag_360_Flag[1][11]
//  632      )
??Mag_Calibartion_14:
        LDR.N    R0,??DataTable8_22
        LDRB     R0,[R0, #+12]
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+13]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+14]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+15]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+16]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+17]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+18]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+19]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+20]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+21]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+22]
        ANDS     R0,R1,R0
        LDR.N    R1,??DataTable8_22
        LDRB     R1,[R1, #+23]
        TST      R0,R1
        BEQ.N    ??Mag_Calibartion_18
//  633 {
//  634   Mag_Is_Okay_Flag[1]=1;//单面数据采集完成标志位置1
        MOVS     R0,#+1
        LDR.N    R1,??DataTable8_25
        STRH     R0,[R1, #+2]
//  635   for(i=0;i<12;i++) Mag_360_Flag[1][i]=0;//清空采集角点
        MOVS     R5,#+0
        B.N      ??Mag_Calibartion_19
??Mag_Calibartion_20:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_22
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        ADD      R1,R1,R5
        STRB     R0,[R1, #+12]
        ADDS     R5,R5,#+1
??Mag_Calibartion_19:
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        CMP      R5,#+12
        BLT.N    ??Mag_Calibartion_20
//  636   if(Mag_Is_Okay_Flag[0]==0)//另外一面数据未完成
        LDR.N    R0,??DataTable8_25
        LDRH     R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Mag_Calibartion_21
//  637     Mag_Calibration_Mode=0;//自动进入下一面数据采集模式
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
        B.N      ??Mag_Calibartion_18
//  638   else Mag_Calibration_Mode=2;
??Mag_Calibartion_21:
        MOVS     R0,#+2
        LDR.N    R1,??DataTable8_18
        STRB     R0,[R1, #+0]
//  639 }
//  640 
//  641   if(Mag_Is_Okay_Flag[0]==1
//  642      &&Mag_Is_Okay_Flag[1]==1)//两面数据全部采集完毕，计算磁力计零点
??Mag_Calibartion_18:
        LDR.N    R0,??DataTable8_25
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.W    ??Mag_Calibartion_22
        LDR.N    R0,??DataTable8_25
        LDRH     R0,[R0, #+2]
        CMP      R0,#+1
        BNE.W    ??Mag_Calibartion_22
//  643   {
//  644       Mag.x_offset=(Mag.x_min+Mag.x_max)/2.0;
        LDR.N    R0,??DataTable8_29
        LDRSH    R0,[R0, #+6]
        LDR.N    R1,??DataTable8_29
        LDRSH    R1,[R1, #+0]
        ADDS     R0,R1,R0
          CFI FunCall __aeabi_i2d
        BL       __aeabi_i2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable8_29
        STR      R0,[R1, #+12]
//  645       Mag.y_offset=(Mag.y_min+Mag.y_max)/2.0;
        LDR.N    R0,??DataTable8_29
        LDRSH    R0,[R0, #+8]
        LDR.N    R1,??DataTable8_29
        LDRSH    R1,[R1, #+2]
        ADDS     R0,R1,R0
          CFI FunCall __aeabi_i2d
        BL       __aeabi_i2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable8_29
        STR      R0,[R1, #+16]
//  646       Mag.z_offset=(Mag.z_min+Mag.z_max)/2.0;
        LDR.N    R0,??DataTable8_29
        LDRSH    R0,[R0, #+10]
        LDR.N    R1,??DataTable8_29
        LDRSH    R1,[R1, #+4]
        ADDS     R0,R1,R0
          CFI FunCall __aeabi_i2d
        BL       __aeabi_i2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable8_29
        STR      R0,[R1, #+20]
//  647       Mag_Offset_Read.x=Mag.x_offset;
        LDR.N    R0,??DataTable8_29
        LDR      R0,[R0, #+12]
        LDR.N    R1,??DataTable8
        STR      R0,[R1, #+0]
//  648       Mag_Offset_Read.y=Mag.y_offset;
        LDR.N    R0,??DataTable8_29
        LDR      R0,[R0, #+16]
        LDR.N    R1,??DataTable8
        STR      R0,[R1, #+4]
//  649       Mag_Offset_Read.z=Mag.z_offset;
        LDR.N    R0,??DataTable8_29
        LDR      R0,[R0, #+20]
        LDR.N    R1,??DataTable8
        STR      R0,[R1, #+8]
//  650       Mag_Is_Okay_Flag[0]=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_25
        STRH     R0,[R1, #+0]
//  651       Mag_Is_Okay_Flag[1]=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_25
        STRH     R0,[R1, #+2]
//  652       Mag_Calibration_Flag=0;//磁力计校准结束，释放遥感操作
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_17
        STRB     R0,[R1, #+0]
//  653       Bling_Mode=0;//恢复正常指示模式
        MOVS     R0,#+0
        LDR.N    R1,??DataTable8_30
        STRH     R0,[R1, #+0]
//  654       Bling_Set(&Light_1,5000,1000,0.3,0,GPIOC,GPIO_Pin_4,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOVS     R0,#+16
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable8_31  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.N    R3,??DataTable8_1  ;; 0x3e99999a
        MOV      R2,#+1000
        MOVW     R1,#+5000
        LDR.N    R0,??DataTable8_32
          CFI FunCall Bling_Set
        BL       Bling_Set
//  655       Bling_Set(&Light_2,5000,1000,0.5,0,GPIOC,GPIO_Pin_5,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOVS     R0,#+32
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable8_31  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+1056964608
        MOV      R2,#+1000
        MOVW     R1,#+5000
        LDR.N    R0,??DataTable8_33
          CFI FunCall Bling_Set
        BL       Bling_Set
//  656       Bling_Set(&Light_3,5000,1000,0.8,0,GPIOC,GPIO_Pin_10,0);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        MOV      R0,#+1024
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable8_31  ;; 0x40011000
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        LDR.N    R3,??DataTable8_2  ;; 0x3f4ccccd
        MOV      R2,#+1000
        MOVW     R1,#+5000
        LDR.N    R0,??DataTable8_34
          CFI FunCall Bling_Set
        BL       Bling_Set
//  657       WriteFlashNineFloat(Accel_Offset_Address,
//  658                         Accel_Offset_Read.x,
//  659                         Accel_Offset_Read.y,
//  660                         Accel_Offset_Read.z,
//  661                         Accel_Scale_Read.x,
//  662                         Accel_Scale_Read.y,
//  663                         Accel_Scale_Read.z,
//  664                         Mag.x_offset,
//  665                         Mag.y_offset,
//  666                         Mag.z_offset);//写入加速度零点偏执与磁力计中心偏执
        LDR.N    R0,??DataTable8_29
        LDR      R0,[R0, #+20]
        STR      R0,[SP, #+20]
        LDR.N    R0,??DataTable8_29
        LDR      R0,[R0, #+16]
        STR      R0,[SP, #+16]
        LDR.N    R0,??DataTable8_29
        LDR      R0,[R0, #+12]
        STR      R0,[SP, #+12]
        LDR.N    R0,??DataTable8_9
        LDR      R0,[R0, #+8]
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable8_9
        LDR      R0,[R0, #+4]
        STR      R0,[SP, #+4]
        LDR.N    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
        STR      R0,[SP, #+0]
        LDR.N    R0,??DataTable8_5
        LDR      R3,[R0, #+8]
        LDR.N    R0,??DataTable8_5
        LDR      R2,[R0, #+4]
        LDR.N    R0,??DataTable8_5
        LDR      R1,[R0, #+0]
        MOVS     R0,#+0
          CFI FunCall WriteFlashNineFloat
        BL       WriteFlashNineFloat
//  667       return true;
        MOVS     R0,#+1
        B.N      ??Mag_Calibartion_23
//  668   }
//  669 return false;
??Mag_Calibartion_22:
        MOVS     R0,#+0
??Mag_Calibartion_23:
        ADD      SP,SP,#+36
          CFI CFA R13+12
        POP      {R4,R5,PC}       ;; return
//  670 }
          CFI EndBlock cfiBlock11

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8:
        DC32     Mag_Offset_Read

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_1:
        DC32     0x3e99999a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_2:
        DC32     0x3f4ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_3:
        DC32     Accel_Offset_Read+0x8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_4:
        DC32     Accel_Offset_Read+0x4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_5:
        DC32     Accel_Offset_Read

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_6:
        DC32     Parameter_Read_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_7:
        DC32     Accel_Scale_Read+0x8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_8:
        DC32     Accel_Scale_Read+0x4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_9:
        DC32     Accel_Scale_Read

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_10:
        DC32     Mag_Offset_Read+0x8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_11:
        DC32     Mag_Offset_Read+0x4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_12:
        DC32     0x3e99999b

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_13:
        DC32     `B`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_14:
        DC32     K

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_15:
        DC32     Mag_Offset

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_16:
        DC32     Mag_Calibration_Makesure_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_17:
        DC32     Mag_Calibration_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_18:
        DC32     Mag_Calibration_Mode

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_19:
        DC32     0x3e4ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_20:
        DC32     0x3f333333

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_21:
        DC32     Mag_Calibration_All_Finished

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_22:
        DC32     Mag_360_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_23:
        DC32     Mag_Calibration_Finished

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_24:
        DC32     Mag_Calibration_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_25:
        DC32     Mag_Is_Okay_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_26:
        DC32     Mag_360_define

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_27:
        DC32     0x41200001

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_28:
        DC32     Acce_Correct

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_29:
        DC32     Mag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_30:
        DC32     Bling_Mode

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_31:
        DC32     0x40011000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_32:
        DC32     Light_1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_33:
        DC32     Light_2

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_34:
        DC32     Light_3

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
//   243 bytes in section .bss
//   182 bytes in section .data
//   336 bytes in section .rodata
// 5 824 bytes in section .text
// 
// 5 824 bytes of CODE  memory
//   336 bytes of CONST memory
//   425 bytes of DATA  memory
//
//Errors: none
//Warnings: none
