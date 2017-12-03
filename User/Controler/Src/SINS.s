///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.60.1.11101/W32 for ARM      03/Dec/2017  16:05:29
// Copyright 1999-2016 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =
        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_file_descriptor", "1"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN Acce_Control
        EXTERN GPS_Quality
        EXTERN GPS_Sate_Num
        EXTERN GPS_Speed_Resolve
        EXTERN GPS_Update_finished_Correct_Flag
        EXTERN Latitude_Origion
        EXTERN Longitude_Origion
        EXTERN Pitch
        EXTERN Roll
        EXTERN SPL06_001_Filter_high
        EXTERN Test_Period
        EXTERN Yaw
        EXTERN __aeabi_cfcmple
        EXTERN __aeabi_d2f
        EXTERN __aeabi_dadd
        EXTERN __aeabi_ddiv
        EXTERN __aeabi_dmul
        EXTERN __aeabi_dsub
        EXTERN __aeabi_f2d
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fdiv
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub
        EXTERN __aeabi_i2f
        EXTERN __aeabi_memclr4
        EXTERN cos
        EXTERN cosf
        EXTERN sin
        EXTERN sqrt
        EXTERN sqrtf

        PUBLIC Acce_Bias
        PUBLIC Acce_Bias_Gain
        PUBLIC Acce_bias
        PUBLIC Accel_Correction_BF
        PUBLIC Accel_Correction_EF
        PUBLIC Acceleration_Length
        PUBLIC Altitude_Dealt
        PUBLIC Altitude_Estimate
        PUBLIC Baro_Climbrate
        PUBLIC Body_Frame_To_XYZ
        PUBLIC Cos_Pitch
        PUBLIC Cos_Roll
        PUBLIC Cos_Yaw
        PUBLIC Delta_T
        PUBLIC Earth_Frame_To_XYZ
        PUBLIC FilterAfter_NamelessQuad
        PUBLIC FilterBefore_NamelessQuad
        PUBLIC Filter_Feedback_NamelessQuad
        PUBLIC Filter_Horizontal
        PUBLIC GPSData_Sort
        PUBLIC GPSData_To_XY_Home
        PUBLIC GPS_Home
        PUBLIC GPS_Home_Set
        PUBLIC GPS_Pos_Delay_Cnt
        PUBLIC GPS_Position_Cnt
        PUBLIC GPS_Present
        PUBLIC GPS_SINS_Delay_Cnt
        PUBLIC GPS_Save_Period_Cnt
        PUBLIC GPS_Vel_Delay_Cnt
        PUBLIC High_Delay_Cnt
        PUBLIC Horizontal_Delta_T
        PUBLIC K_GPS
        PUBLIC KalmanFilter
        PUBLIC KalmanFilter_Horizontal_GPS
        PUBLIC NamelessQuad
        PUBLIC Origion_NamelessQuad
        PUBLIC Pos_Err_On_Accel
        PUBLIC Position_History
        PUBLIC Pre_conv
        PUBLIC Pre_conv_GPS
        PUBLIC Q
        PUBLIC Q_GPS
        PUBLIC R
        PUBLIC R_Acce_bias
        PUBLIC R_GPS
        PUBLIC SINS_Accel_Body
        PUBLIC SINS_High_Delta
        PUBLIC SINS_Horizontal_Delta
        PUBLIC SINS_Prepare
        PUBLIC Set_GPS_Home
        PUBLIC Sin_Pitch
        PUBLIC Sin_Roll
        PUBLIC Sin_Yaw
        PUBLIC SpeedDealt
        PUBLIC Strapdown_INS_High
        PUBLIC Strapdown_INS_High_Kalman
        PUBLIC Strapdown_INS_Horizontal
        PUBLIC Strapdown_INS_Reset
        PUBLIC TIME_CONTANST_ZER
        PUBLIC Vel_History
        PUBLIC X_Delta
        PUBLIC Y_Delta
        PUBLIC acc_correction
        PUBLIC constrain_float
        PUBLIC get_distance
        PUBLIC location_diff
        PUBLIC longitude_scale
        PUBLIC pos_correction
        PUBLIC pythagorous2
        PUBLIC pythagorous3
        PUBLIC sq
        PUBLIC vel_correction

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

// D:\STM32_Maple\NamelessCotrunQuad_V1.4\User\Controler\Src\SINS.c
//    1 #include "Headfile.h"
//    2 #include "SINS.h"
//    3 #include "math.h"
//    4 /*----------------------------------------------------------------------------------------------------------------------/
//    5         *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
//    6         *               无名科创团队将飞控程序源码提供给购买者，
//    7         *               购买者要为无名科创团队提供保护，
//    8         *               未经作者许可，不得将源代码提供给他人
//    9         *               不得将源代码放到网上供他人免费下载，
//   10         *               更不能以此销售牟利，如发现上述行为，
//   11         *               无名科创团队将诉之以法律解决！！！
//   12 -----------------------------------------------------------------------------------------------------------------------/
//   13         *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
//   14         *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
//   15 -----------------------------------------------------------------------------------------------------------------------/
//   16 	*		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
//   17 	*		CSDN博客: http://blog.csdn.net/u011992534
//   18 	*               优酷ID：NamelessCotrun无名小哥
//   19 	*               无名科创开源飞控QQ群：540707961
//   20         *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
//   21         *               百度贴吧:无名科创开源飞控
//   22         *               修改日期:2017/10/30
//   23         *               版本：V1.1
//   24         *               版权所有，盗版必究。
//   25         *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
//   26         *               All rights reserved
//   27 ----------------------------------------------------------------------------------------------------------------------*/
//   28

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   29 SINS NamelessQuad;
NamelessQuad:
        DS8 1272

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   30 SINS Origion_NamelessQuad;
Origion_NamelessQuad:
        DS8 1272

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   31 SINS FilterBefore_NamelessQuad;
FilterBefore_NamelessQuad:
        DS8 1272

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   32 SINS FilterAfter_NamelessQuad;
FilterAfter_NamelessQuad:
        DS8 1272

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   33 SINS Filter_Feedback_NamelessQuad;
Filter_Feedback_NamelessQuad:
        DS8 1272

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   34 float SpeedDealt[3]={0};
SpeedDealt:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   35 float Sin_Pitch=0,Sin_Roll=0,Sin_Yaw=0;
Sin_Pitch:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Sin_Roll:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Sin_Yaw:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   36 float Cos_Pitch=0,Cos_Roll=0,Cos_Yaw=0;
Cos_Pitch:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Cos_Roll:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Cos_Yaw:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   37 float Baro_Climbrate=0;
Baro_Climbrate:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   38 float Acceleration_Length=0;
Acceleration_Length:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   39 Vector2f SINS_Accel_Body={0,0};
SINS_Accel_Body:
        DS8 8
//   40

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function SINS_Prepare
        THUMB
//   41 void  SINS_Prepare(void)
//   42 {
SINS_Prepare:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
//   43       Vector2f SINS_Accel_Earth={0,0};
        LDR.W    R0,??DataTable8
        LDRD     R4,R5,[R0, #+0]
//   44       Sin_Pitch=sin(Pitch* DEG2RAD);
        LDR.W    R0,??DataTable8_1
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable8_2  ;; 0xa2529d44
        LDR.W    R3,??DataTable8_3  ;; 0x3f91df46
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall sin
        BL       sin
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_4
        STR      R0,[R1, #+0]
//   45       Cos_Pitch=cos(Pitch* DEG2RAD);
        LDR.W    R0,??DataTable8_1
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable8_2  ;; 0xa2529d44
        LDR.W    R3,??DataTable8_3  ;; 0x3f91df46
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall cos
        BL       cos
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_5
        STR      R0,[R1, #+0]
//   46       Sin_Roll=sin(Roll* DEG2RAD);
        LDR.W    R0,??DataTable8_6
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable8_2  ;; 0xa2529d44
        LDR.W    R3,??DataTable8_3  ;; 0x3f91df46
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall sin
        BL       sin
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_7
        STR      R0,[R1, #+0]
//   47       Cos_Roll=cos(Roll* DEG2RAD);
        LDR.W    R0,??DataTable8_6
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable8_2  ;; 0xa2529d44
        LDR.W    R3,??DataTable8_3  ;; 0x3f91df46
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall cos
        BL       cos
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_8
        STR      R0,[R1, #+0]
//   48       Sin_Yaw=sin(Yaw* DEG2RAD);
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable8_2  ;; 0xa2529d44
        LDR.W    R3,??DataTable8_3  ;; 0x3f91df46
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall sin
        BL       sin
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_10
        STR      R0,[R1, #+0]
//   49       Cos_Yaw=cos(Yaw* DEG2RAD);
        LDR.W    R0,??DataTable8_9
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable8_2  ;; 0xa2529d44
        LDR.W    R3,??DataTable8_3  ;; 0x3f91df46
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall cos
        BL       cos
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_11
        STR      R0,[R1, #+0]
//   50       /*Z-Y-X欧拉角转方向余弦矩阵
//   51         //Pitch Roll  Yaw 分别对应Φ θ Ψ
//   52
//   53              X轴旋转矩阵
//   54              R（Φ）
//   55         {1      0        0    }
//   56         {0      cosΦ    sinΦ}
//   57         {0    -sinΦ    cosΦ }
//   58
//   59              Y轴旋转矩阵
//   60              R（θ）
//   61         {cosθ     0        -sinθ}
//   62         {0         1        0     }
//   63         {sinθ     0        cosθ}
//   64
//   65              Z轴旋转矩阵
//   66              R（θ）
//   67         {cosΨ      sinΨ       0}
//   68         {-sinΨ     cosΨ       0}
//   69         {0          0           1 }
//   70
//   71         由Z-Y-X顺规有:
//   72       载体坐标系到导航坐标系下旋转矩阵R(b2n)
//   73       R(b2n) =R(Ψ)^T*R(θ)^T*R(Φ)^T
//   74
//   75       R=
//   76         {cosΨ*cosθ     -cosΦ*sinΨ+sinΦ*sinθ*cosΨ        sinΨ*sinΦ+cosΦ*sinθ*cosΨ}
//   77         {cosθ*sinΨ     cosΦ*cosΨ +sinΦ*sinθ*sinΨ       -cosΨ*sinΦ+cosΦ*sinθ*sinΨ}
//   78         {-sinθ          cosθsin Φ                          cosθcosΦ                   }
//   79       */
//   80
//   81       Origion_NamelessQuad.Acceleration[_YAW] =
//   82                             -Sin_Roll* Acce_Control[0]
//   83                               + Sin_Pitch *Cos_Roll * Acce_Control[1]
//   84                                  + Cos_Pitch * Cos_Roll *Acce_Control[2];
        LDR.W    R0,??DataTable8_7
        LDR      R1,[R0, #+0]
        EORS     R1,R1,#0x80000000
        LDR.W    R0,??DataTable8_12
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_4
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_8
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_5
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_8
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+24]
//   85
//   86       Origion_NamelessQuad.Acceleration[_PITCH]=
//   87                          Cos_Yaw* Cos_Roll * Acce_Control[0]
//   88                               +(Sin_Pitch*Sin_Roll*Cos_Yaw-Cos_Pitch * Sin_Yaw) * Acce_Control[1]
//   89                                 +(Sin_Pitch * Sin_Yaw+Cos_Pitch * Sin_Roll * Cos_Yaw)*Acce_Control[2];
        LDR.W    R0,??DataTable8_11
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_8
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_4
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_11
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R7,R0
        LDR.W    R0,??DataTable8_5
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_10
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R7
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_4
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_10
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R7,R0
        LDR.W    R0,??DataTable8_5
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_11
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R7
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+28]
//   90
//   91       Origion_NamelessQuad.Acceleration[_ROLL]=
//   92                          Sin_Yaw* Cos_Roll * Acce_Control[0]
//   93                               +(Sin_Pitch * Sin_Roll * Sin_Yaw +Cos_Pitch * Cos_Yaw) * Acce_Control[1]
//   94                                 + (Cos_Pitch * Sin_Roll * Sin_Yaw - Sin_Pitch * Cos_Yaw)*Acce_Control[2];
        LDR.W    R0,??DataTable8_10
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_8
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_4
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_10
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R7,R0
        LDR.W    R0,??DataTable8_5
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_11
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R7
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_5
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_10
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R7,R0
        LDR.W    R0,??DataTable8_4
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable8_11
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R7
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable8_12
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+32]
//   95
//   96
//   97       /*
//   98       Origion_NamelessQuad.Acceleration[_YAW]=rMat[2][0]*Acce_Control[0]
//   99                                               +rMat[2][1]*Acce_Control[1]
//  100                                                 +rMat[2][2]*Acce_Control[2];
//  101
//  102       Origion_NamelessQuad.Acceleration[_PITCH]=rMat[0][0]*Acce_Control[0]
//  103                                               +rMat[0][1]*Acce_Control[1]
//  104                                                 +rMat[0][2]*Acce_Control[2];
//  105
//  106       Origion_NamelessQuad.Acceleration[_ROLL]=rMat[1][0]*Acce_Control[0]
//  107                                               +rMat[1][1]*Acce_Control[1]
//  108                                              +rMat[1][2]*Acce_Control[2];
//  109
//  110       */
//  111
//  112       Origion_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+24]
        LDR.W    R0,??DataTable8_14  ;; 0x3b1ccccd
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+24]
//  113       Origion_NamelessQuad.Acceleration[_YAW]-=AcceGravity;//减去重力加速度
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+24]
        LDR.W    R0,??DataTable8_15  ;; 0xc11ccccd
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+24]
//  114       Origion_NamelessQuad.Acceleration[_YAW]*=100;//加速度cm/s^2
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+24]
        LDR.W    R0,??DataTable8_16  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+24]
//  115
//  116       Origion_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+28]
        LDR.W    R0,??DataTable8_14  ;; 0x3b1ccccd
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+28]
//  117       Origion_NamelessQuad.Acceleration[_PITCH]*=100;//加速度cm/s^2
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+28]
        LDR.W    R0,??DataTable8_16  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+28]
//  118
//  119       Origion_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+32]
        LDR.W    R0,??DataTable8_14  ;; 0x3b1ccccd
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+32]
//  120       Origion_NamelessQuad.Acceleration[_ROLL]*=100;//加速度cm/s^2
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+32]
        LDR.W    R0,??DataTable8_16  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+32]
//  121
//  122
//  123       Acceleration_Length=sqrt(Origion_NamelessQuad.Acceleration[_YAW]*Origion_NamelessQuad.Acceleration[_YAW]
//  124                                +Origion_NamelessQuad.Acceleration[_PITCH]*Origion_NamelessQuad.Acceleration[_PITCH]
//  125                                  +Origion_NamelessQuad.Acceleration[_ROLL]*Origion_NamelessQuad.Acceleration[_ROLL]);
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+24]
        LDR.W    R0,??DataTable8_13
        LDR      R0,[R0, #+24]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+28]
        LDR.W    R0,??DataTable8_13
        LDR      R0,[R0, #+28]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R6,R0
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+32]
        LDR.W    R0,??DataTable8_13
        LDR      R0,[R0, #+32]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
          CFI FunCall sqrt
        BL       sqrt
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_17
        STR      R0,[R1, #+0]
//  126
//  127    /******************************************************************************/
//  128    //将无人机在导航坐标系下的沿着正东、正北方向的运动加速度旋转到当前航向的运动加速度:机头(俯仰)+横滚
//  129
//  130       SINS_Accel_Earth.x=Origion_NamelessQuad.Acceleration[_PITCH];//沿地理坐标系，正东方向运动加速度,单位为CM
        LDR.W    R0,??DataTable8_13
        LDR      R0,[R0, #+28]
        MOVS     R4,R0
//  131       SINS_Accel_Earth.y=Origion_NamelessQuad.Acceleration[_ROLL];//沿地理坐标系，正北方向运动加速度,单位为CM
        LDR.W    R0,??DataTable8_13
        LDR      R0,[R0, #+32]
        MOVS     R5,R0
//  132
//  133
//  134       SINS_Accel_Body.x=SINS_Accel_Earth.x*Cos_Yaw+SINS_Accel_Earth.y*Sin_Yaw;  //横滚正向运动加速度  X轴正向
        MOVS     R1,R4
        LDR.W    R0,??DataTable8_11
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        MOVS     R1,R5
        LDR.W    R0,??DataTable8_10
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10
        STR      R0,[R1, #+0]
//  135       SINS_Accel_Body.y=-SINS_Accel_Earth.x*Sin_Yaw+SINS_Accel_Earth.y*Cos_Yaw; //机头正向运动加速度  Y轴正向
        MOVS     R1,R4
        EORS     R1,R1,#0x80000000
        LDR.W    R0,??DataTable8_10
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        MOVS     R1,R5
        LDR.W    R0,??DataTable8_11
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R6
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10
        STR      R0,[R1, #+4]
//  136
//  137 }
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_0:
        DC32 0H, 0H
//  138
//  139
//  140 /******************************************
//  141 原始运动加速度方向为东北天方向
//  142 Origion_NamelessQuad.Acceleration[_ROLL]
//  143     为载体沿着正北方向的运动加速度
//  144 Origion_NamelessQuad.Acceleration[_PITCH]
//  145     为载体沿着正东方向的运动加速度
//  146 Origion_NamelessQuad.Acceleration[_YAW]
//  147     为载体沿着‘天’方向的运动加速度
//  148
//  149 载体沿着正东（E）、正北（N）、正天（U）运动时，加速度方向为正
//  150         U（正天、气压高度、_YAW）
//  151         *
//  152         *
//  153         *
//  154         *
//  155         *
//  156         *
//  157         * * * * * * * * * *N（正北、纬线方向、_ROLL）
//  158          *
//  159            *
//  160              *
//  161                *
//  162                  *
//  163                    *
//  164                      E（正东、经线方向、_PITCH）
//  165 */
//  166
//  167
//  168

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  169 float pos_correction[3]={0,0,0};
pos_correction:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  170 float acc_correction[3]={0,0,0};
acc_correction:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  171 float vel_correction[3]={0,0,0};
vel_correction:
        DS8 12
//  172 /****气压计三阶互补滤波方案——参考开源飞控APM****/
//  173 //#define TIME_CONTANST_ZER       1.5f

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  174 float TIME_CONTANST_ZER=3.0f;
TIME_CONTANST_ZER:
        DC32 40400000H
//  175 #define K_ACC_ZER 	        (1.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER * TIME_CONTANST_ZER))
//  176 #define K_VEL_ZER	        (3.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER))//20															// XY????·′à??μêy,3.0
//  177 #define K_POS_ZER               (3.0f / TIME_CONTANST_ZER)
//  178 //#define High_Delay_Cnt  5 //20ms
//  179 #ifdef IMU_BOARD_GY86
//  180     uint16 High_Delay_Cnt=10;
//  181 #endif
//  182 #ifdef IMU_BOARD_NC686

        SECTION `.data`:DATA:REORDER:NOROOT(1)
        DATA
//  183     uint16 High_Delay_Cnt=30;//150ms
High_Delay_Cnt:
        DC16 30
//  184 #endif
//  185 #ifdef IMU_BOARD_NC683
//  186     uint16 High_Delay_Cnt=10;
//  187 #endif

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  188 float Altitude_Dealt=0;
Altitude_Dealt:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  189 float Altitude_Estimate=0;
Altitude_Estimate:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  190 Testime SINS_High_Delta;
SINS_High_Delta:
        DS8 16

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  191 float Delta_T;
Delta_T:
        DS8 4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function Strapdown_INS_High
        THUMB
//  192  void Strapdown_INS_High()
//  193 {
Strapdown_INS_High:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
//  194       uint16 Cnt=0;
        MOVS     R0,#+0
//  195       static uint16_t Save_Cnt=0;
//  196       Save_Cnt++;//数据存储周期
        LDR.W    R0,??DataTable10_1
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable10_1
        STRH     R0,[R1, #+0]
//  197       Test_Period(&SINS_High_Delta);
        LDR.W    R0,??DataTable9
          CFI FunCall Test_Period
        BL       Test_Period
//  198       Delta_T=SINS_High_Delta.Time_Delta/1000.0;
        LDR.W    R0,??DataTable9
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        LDR.W    R3,??DataTable9_1  ;; 0x408f4000
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable9_2
        STR      R0,[R1, #+0]
//  199 #ifdef  IMU_BOARD_GY86
//  200       Altitude_Estimate=AirPresure_Altitude;//高度观测量
//  201 #endif
//  202 #ifdef  IMU_BOARD_NC686
//  203       Altitude_Estimate=SPL06_001_Filter_high;//高度观测量
        LDR.W    R0,??DataTable9_3
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable9_4
        STR      R0,[R1, #+0]
//  204 #endif
//  205 #ifdef  IMU_BOARD_NC683
//  206       Altitude_Estimate=FBM320_Filter_high;//高度观测量
//  207 #endif
//  208 #ifdef  HC_SR04
//  209       Altitude_Estimate=HC_SR04_Distance;//高度观测量
//  210 #endif
//  211       //由观测量（气压计）得到状态误差
//  212       Altitude_Dealt=Altitude_Estimate-NamelessQuad.Pos_History[_YAW][High_Delay_Cnt];//气压计(超声波)与SINS估计量的差，单位cm
        LDR.W    R0,??DataTable9_4
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable10_2
        LDR.W    R2,??DataTable9_5
        LDRH     R2,[R2, #+0]
        ADD      R1,R1,R2, LSL #+2
        LDR      R1,[R1, #+36]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable9_6
        STR      R0,[R1, #+0]
//  213       //三路积分反馈量修正惯导
//  214       acc_correction[_YAW] +=Altitude_Dealt* K_ACC_ZER*Delta_T ;//加速度矫正量
        LDR.W    R0,??DataTable9_7
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable9_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable9_7
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,#+1065353216
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        LDR.W    R1,??DataTable9_6
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable9_2
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_3
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10_3
        STR      R0,[R1, #+0]
//  215       vel_correction[_YAW] +=Altitude_Dealt* K_VEL_ZER*Delta_T ;//速度矫正量
        LDR.W    R0,??DataTable9_7
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable9_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR.W    R0,??DataTable10_4  ;; 0x40400000
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        LDR.W    R1,??DataTable9_6
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable9_2
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_5
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10_5
        STR      R0,[R1, #+0]
//  216       pos_correction[_YAW] +=Altitude_Dealt* K_POS_ZER*Delta_T ;//位置矫正量
        LDR.W    R0,??DataTable10_4  ;; 0x40400000
        LDR.W    R1,??DataTable9_7
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        LDR.W    R1,??DataTable9_6
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable9_2
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_6
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10_6
        STR      R0,[R1, #+0]
//  217       //加速度计矫正后更新
//  218       NamelessQuad.Last_Acceleration[_YAW]=NamelessQuad.Acceleration[_YAW];//上一次加速度量
        LDR.W    R0,??DataTable10_2
        LDR      R0,[R0, #+24]
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+1248]
//  219       NamelessQuad.Acceleration[_YAW]=Origion_NamelessQuad.Acceleration[_YAW]+acc_correction[_YAW];
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+24]
        LDR.W    R0,??DataTable10_3
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+24]
//  220       //速度增量矫正后更新，用于更新位置,由于步长h=0.005,相对较长，
//  221       //这里采用二阶龙格库塔法更新微分方程，不建议用更高阶段，因为加速度信号非平滑
//  222       SpeedDealt[_YAW]=+(NamelessQuad.Last_Acceleration[_YAW]
//  223                          +NamelessQuad.Acceleration[_YAW])*Delta_T/2.0;
        LDR.W    R0,??DataTable10_2
        LDR      R1,[R0, #+1248]
        LDR.W    R0,??DataTable10_2
        LDR      R0,[R0, #+24]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable9_2
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable10_7
        STR      R0,[R1, #+0]
//  224       //原始位置更新
//  225       Origion_NamelessQuad.Position[_YAW]+=(NamelessQuad.Speed[_YAW]+0.5*SpeedDealt[_YAW])*Delta_T;
        LDR.W    R0,??DataTable8_13
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R6,R0
        MOVS     R7,R1
        LDR.W    R0,??DataTable10_2
        LDR      R0,[R0, #+12]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.W    R0,??DataTable10_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        LDR.W    R3,??DataTable10_8  ;; 0x3fe00000
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.W    R0,??DataTable9_2
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R6
        MOVS     R3,R7
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+0]
//  226       //位置矫正后更新
//  227       NamelessQuad.Position[_YAW]=Origion_NamelessQuad.Position[_YAW]+pos_correction[_YAW];
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable10_6
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+0]
//  228       //原始速度更新
//  229       Origion_NamelessQuad.Speed[_YAW]+=SpeedDealt[_YAW];
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+12]
        LDR.W    R0,??DataTable10_7
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable8_13
        STR      R0,[R1, #+12]
//  230       //速度矫正后更新
//  231       NamelessQuad.Speed[_YAW]=Origion_NamelessQuad.Speed[_YAW]+vel_correction[_YAW];
        LDR.W    R0,??DataTable8_13
        LDR      R1,[R0, #+12]
        LDR.W    R0,??DataTable10_5
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+12]
//  232
//  233       if(Save_Cnt>=1)//20ms
        LDR.W    R0,??DataTable10_1
        LDRH     R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??Strapdown_INS_High_0
//  234       {
//  235         for(Cnt=Num-1;Cnt>0;Cnt--)//20ms滑动一次
        MOVS     R0,#+49
        B.N      ??Strapdown_INS_High_1
//  236         {
//  237         NamelessQuad.Pos_History[_YAW][Cnt]=NamelessQuad.Pos_History[_YAW][Cnt-1];
??Strapdown_INS_High_2:
        LDR.W    R1,??DataTable10_2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #+32]
        LDR.W    R2,??DataTable10_2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0, LSL #+2
        STR      R1,[R2, #+36]
//  238         }
        SUBS     R0,R0,#+1
??Strapdown_INS_High_1:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+0
        BNE.N    ??Strapdown_INS_High_2
//  239         NamelessQuad.Pos_History[_YAW][0]=NamelessQuad.Position[_YAW];
        LDR.W    R0,??DataTable10_2
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+36]
//  240         Save_Cnt=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable10_1
        STRH     R0,[R1, #+0]
//  241       }
//  242 }
??Strapdown_INS_High_0:
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock1

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
`Strapdown_INS_High::Save_Cnt`:
        DS8 2
//  243
//  244
//  245

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  246 float R[2]={5.0e-4f,3.0e-4f};//{5.0e-4f,3.0e-4f}
R:
        DC32 3A03126FH, 399D4952H

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  247 float Q=50;//50
Q:
        DC32 42480000H

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  248 float Acce_Bias_Gain[3]={
Acce_Bias_Gain:
        DC32 3A83126FH, 3A83126FH, 3A83126FH
//  249   0.001,//0.001
//  250   0.001,
//  251   0.001
//  252 };

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  253 float Pre_conv[4]=
Pre_conv:
        DC32 3A83126FH, 0H, 0H, 3A83126FH
//  254 {
//  255   0.001,0,
//  256   0,0.001
//  257 };//上一次协方差

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function KalmanFilter
        THUMB
//  258 void  KalmanFilter(float Observation,//位置观测量
//  259                     uint16 Pos_Delay_Cnt,//观测传感器延时量
//  260                     SINS *Ins_Kf,//惯导结构体
//  261                     float System_drive,//系统原始驱动量，惯导加速度
//  262                     float *R,
//  263                     float Q,
//  264                     float dt,
//  265                     uint16 N)
//  266 {
KalmanFilter:
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
        SUB      SP,SP,#+36
          CFI CFA R13+72
        MOV      R8,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R7,R3
//  267         uint16 Cnt=0;
        MOVS     R0,#+0
//  268         float Temp_conv[4]={0};//先验协方差
        ADD      R0,SP,#+16
        MOVS     R1,#+16
          CFI FunCall __aeabi_memclr4
        BL       __aeabi_memclr4
//  269         float Conv_Z=0,Z_Cor=0;
        MOVS     R9,#+0
        MOVS     R9,#+0
//  270         float k[2]={0};//增益矩阵
        ADD      R0,SP,#+8
        MOVS     R1,#+0
        MOVS     R2,#+0
        STRD     R1,R2,[R0, #+0]
//  271         float Ctemp=0;
        MOVS     R9,#+0
        LDR      R4,[SP, #+84]
//  272         //先验状态
//  273         Ins_Kf->Acceleration[N]=System_drive;
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R0,R6,R4, LSL #+2
        STR      R7,[R0, #+24]
//  274         Ins_Kf->Acceleration[N]=Ins_Kf->Acce_Bias[N]+Ins_Kf->Acceleration[N];
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R0,R6,R4, LSL #+2
        LDR      R1,[R0, #+1236]
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R0,R6,R4, LSL #+2
        LDR      R0,[R0, #+24]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        STR      R0,[R1, #+24]
        LDR      R7,[SP, #+80]
//  275         Ins_Kf->Position[N] +=Ins_Kf->Speed[N]*dt+(Ins_Kf->Acceleration[N]*dt*dt)/2.0;
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        LDR      R0,[R6, R4, LSL #+2]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        STRD     R0,R1,[SP, #+0]
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R0,R6,R4, LSL #+2
        LDR      R0,[R0, #+12]
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R10,R0
        MOV      R11,R1
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R0,R6,R4, LSL #+2
        LDR      R0,[R0, #+24]
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
        MOV      R2,R10
        MOV      R3,R11
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        LDRD     R2,R3,[SP, #+0]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        STR      R0,[R6, R4, LSL #+2]
//  276         Ins_Kf->Speed[N]+=Ins_Kf->Acceleration[N]*dt;
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R0,R6,R4, LSL #+2
        LDR      R0,[R0, #+24]
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        LDR      R1,[R1, #+12]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        STR      R0,[R1, #+12]
//  277         //先验协方差
//  278         Ctemp=Pre_conv[1]+Pre_conv[3]*dt;
        LDR.W    R0,??DataTable10_9
        LDR      R0,[R0, #+12]
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_9
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
        LDR      R10,[SP, #+72]
//  279         Temp_conv[0]=Pre_conv[0]+Pre_conv[2]*dt+Ctemp*dt+R[0];
        LDR.W    R0,??DataTable10_9
        LDR      R0,[R0, #+8]
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_9
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R11,R0
        MOV      R0,R9
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOV      R1,R11
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR      R1,[R10, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        STR      R0,[SP, #+16]
//  280         Temp_conv[1]=Ctemp;
        STR      R9,[SP, #+20]
//  281         Temp_conv[2]=Pre_conv[2]+Pre_conv[3]*dt;;
        LDR.W    R0,??DataTable10_9
        LDR      R0,[R0, #+12]
        MOVS     R1,R7
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_9
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        STR      R0,[SP, #+24]
//  282         Temp_conv[3]=Pre_conv[3]+R[1];
        LDR.W    R0,??DataTable10_9
        LDR      R1,[R0, #+12]
        LDR      R0,[R10, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        STR      R0,[SP, #+28]
//  283         //计算卡尔曼增益
//  284         Conv_Z=Temp_conv[0]+Q;
        LDR      R1,[SP, #+16]
        LDR      R0,[SP, #+76]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOV      R9,R0
//  285         k[0]=Temp_conv[0]/Conv_Z;
        LDR      R0,[SP, #+16]
        MOV      R1,R9
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        STR      R0,[SP, #+8]
//  286         k[1]=Temp_conv[2]/Conv_Z;
        LDR      R0,[SP, #+24]
        MOV      R1,R9
          CFI FunCall __aeabi_fdiv
        BL       __aeabi_fdiv
        STR      R0,[SP, #+12]
//  287         //融合数据输出
//  288         Z_Cor=Observation-Ins_Kf->Pos_History[N][Pos_Delay_Cnt];
        MOV      R0,R8
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R1,#+200
        MUL      R1,R1,R4
        ADD      R1,R6,R1
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        ADD      R1,R1,R5, LSL #+2
        LDR      R1,[R1, #+36]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        MOV      R9,R0
//  289         //Z_Cor=Positional-*Position;
//  290         Ins_Kf->Position[N] +=k[0]*Z_Cor;
        LDR      R0,[SP, #+8]
        MOV      R1,R9
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        LDR      R1,[R6, R4, LSL #+2]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        STR      R0,[R6, R4, LSL #+2]
//  291         Ins_Kf->Speed[N] +=k[1]*Z_Cor;
        LDR      R0,[SP, #+12]
        MOV      R1,R9
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        LDR      R1,[R1, #+12]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        STR      R0,[R1, #+12]
//  292         Ins_Kf->Acce_Bias[N]+=Acce_Bias_Gain[_YAW]*Z_Cor;
        LDR.W    R0,??DataTable10_10
        LDR      R0,[R0, #+0]
        MOV      R1,R9
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        LDR      R1,[R1, #+1236]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R1,R6,R4, LSL #+2
        STR      R0,[R1, #+1236]
//  293         //更新状态协方差矩阵
//  294         Pre_conv[0]=(1-k[0])*Temp_conv[0];
        MOVS     R0,#+1065353216
        LDR      R1,[SP, #+8]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR      R1,[SP, #+16]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_9
        STR      R0,[R1, #+0]
//  295         Pre_conv[1]=(1-k[0])*Temp_conv[1];
        MOVS     R0,#+1065353216
        LDR      R1,[SP, #+8]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR      R1,[SP, #+20]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_9
        STR      R0,[R1, #+4]
//  296         Pre_conv[2]=Temp_conv[2]-k[1]*Temp_conv[0];
        LDR      R1,[SP, #+12]
        LDR      R0,[SP, #+16]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR      R0,[SP, #+24]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable10_9
        STR      R0,[R1, #+8]
//  297         Pre_conv[3]=Temp_conv[3]-k[1]*Temp_conv[1];
        LDR      R1,[SP, #+12]
        LDR      R0,[SP, #+20]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR      R0,[SP, #+28]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable10_9
        STR      R0,[R1, #+12]
//  298
//  299         for(Cnt=Num-1;Cnt>0;Cnt--)//4ms滑动一次
        MOVS     R0,#+49
        B.N      ??KalmanFilter_0
//  300         {
//  301           Ins_Kf->Pos_History[N][Cnt]=Ins_Kf->Pos_History[N][Cnt-1];
??KalmanFilter_1:
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R1,#+200
        MUL      R1,R1,R4
        ADD      R1,R6,R1
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R2,#+200
        MUL      R2,R2,R4
        ADD      R2,R6,R2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0, LSL #+2
        LDR      R2,[R2, #+32]
        STR      R2,[R1, #+36]
//  302         }
        SUBS     R0,R0,#+1
??KalmanFilter_0:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+0
        BNE.N    ??KalmanFilter_1
//  303           Ins_Kf->Pos_History[N][0]=Ins_Kf->Position[N];
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        LDR      R0,[R6, R4, LSL #+2]
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        MOVS     R1,#+200
        MUL      R1,R1,R4
        ADD      R1,R6,R1
        STR      R0,[R1, #+36]
//  304 }
        ADD      SP,SP,#+36
          CFI CFA R13+36
        POP      {R4-R11,PC}      ;; return
          CFI EndBlock cfiBlock2

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0
//  305
//  306

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function Strapdown_INS_High_Kalman
        THUMB
//  307 void Strapdown_INS_High_Kalman(void)
//  308 {
Strapdown_INS_High_Kalman:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
        SUB      SP,SP,#+20
          CFI CFA R13+24
//  309 #ifdef  IMU_BOARD_GY86
//  310       Altitude_Estimate=AirPresure_Altitude;//高度观测量
//  311 #endif
//  312 #ifdef  IMU_BOARD_NC686
//  313       Altitude_Estimate=SPL06_001_Filter_high;//高度观测量
        LDR.W    R0,??DataTable9_3
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable9_4
        STR      R0,[R1, #+0]
//  314 #endif
//  315 #ifdef  IMU_BOARD_NC683
//  316       Altitude_Estimate=FBM320_Filter_high;//高度观测量
//  317 #endif
//  318
//  319          KalmanFilter(Altitude_Estimate,//位置观测量
//  320                       High_Delay_Cnt,//观测传感器延时量
//  321                       &NamelessQuad,//惯导结构体
//  322                       Origion_NamelessQuad.Acceleration[_YAW],//系统原始驱动量，惯导加速度
//  323                       R,
//  324                       Q,
//  325                       0.005f,
//  326                       _YAW);
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
        LDR.W    R0,??DataTable10_11  ;; 0x3ba3d70a
        STR      R0,[SP, #+8]
        LDR.W    R0,??DataTable10_12
        LDR      R0,[R0, #+0]
        STR      R0,[SP, #+4]
        LDR.W    R0,??DataTable10_13
        STR      R0,[SP, #+0]
        LDR.N    R0,??DataTable8_13
        LDR      R3,[R0, #+24]
        LDR.W    R2,??DataTable10_2
        LDR.W    R0,??DataTable9_5
        LDRH     R1,[R0, #+0]
        LDR.W    R0,??DataTable9_4
        LDR      R0,[R0, #+0]
          CFI FunCall KalmanFilter
        BL       KalmanFilter
//  327 }
        ADD      SP,SP,#+20
          CFI CFA R13+4
        POP      {PC}             ;; return
          CFI EndBlock cfiBlock3
//  328
//  329 /*************************以下计算球面投影距离内容源于APM3.2 AP.Math.c文件******************************/
//  330 // radius of earth in meters
//  331 #define RADIUS_OF_EARTH 6378100
//  332 // scaling factor from 1e-7 degrees to meters at equater
//  333 // == 1.0e-7 * DEG_TO_RAD * RADIUS_OF_EARTH
//  334 #define LOCATION_SCALING_FACTOR 0.011131884502145034f
//  335 // inverse of LOCATION_SCALING_FACTOR
//  336 #define LOCATION_SCALING_FACTOR_INV 89.83204953368922f
//  337 // constrain a value

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function constrain_float
        THUMB
//  338 float constrain_float(float amt, float low, float high){
constrain_float:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        MOVS     R3,R0
//  339   return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
        MOVS     R0,R3
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??constrain_float_0
        MOVS     R3,R1
        B.N      ??constrain_float_1
??constrain_float_0:
        MOVS     R0,R2
        MOVS     R1,R3
          CFI FunCall __aeabi_cfcmple
        BL       __aeabi_cfcmple
        BCS.N    ??constrain_float_2
        MOVS     R3,R2
        B.N      ??constrain_float_1
??constrain_float_2:
??constrain_float_1:
        MOVS     R0,R3
        POP      {R1,PC}          ;; return
//  340 }
          CFI EndBlock cfiBlock4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function longitude_scale
        THUMB
//  341 float longitude_scale(Location loc)
//  342 {
longitude_scale:
        PUSH     {R0-R2,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+16
//  343     static int32_t last_lat;
//  344     static float scale = 1.0;
//  345     //比较两次纬度相差值，避免重复运算余弦函数
//  346     if (ABS(last_lat - loc.lat) < 100000) {
        LDR.W    R0,??DataTable10_14
        LDR      R0,[R0, #+0]
        LDR      R1,[SP, #+4]
        SUBS     R0,R0,R1
        CMP      R0,#+1
        BLT.N    ??longitude_scale_0
        LDR.W    R0,??DataTable10_14
        LDR      R0,[R0, #+0]
        LDR      R1,[SP, #+4]
        SUBS     R0,R0,R1
        B.N      ??longitude_scale_1
??longitude_scale_0:
        LDR      R0,[SP, #+4]
        LDR.W    R1,??DataTable10_14
        LDR      R1,[R1, #+0]
        SUBS     R0,R0,R1
??longitude_scale_1:
        LDR.W    R1,??DataTable11  ;; 0x186a0
        CMP      R0,R1
        BGE.N    ??longitude_scale_2
//  347     // we are within 0.01 degrees (about 1km) of the
//  348     // same latitude. We can avoid the cos() and return
//  349     // the same scale factor.
//  350         return scale;
        LDR.W    R0,??DataTable11_1
        LDR      R0,[R0, #+0]
        B.N      ??longitude_scale_3
//  351     }
//  352     scale = cosf(loc.lat * 1.0e-7f * DEG_TO_RAD);
??longitude_scale_2:
        LDR      R0,[SP, #+4]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable11_2  ;; 0x33d6bf95
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable11_3  ;; 0x3c8efa35
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall cosf
        BL       cosf
        LDR.W    R1,??DataTable11_1
        STR      R0,[R1, #+0]
//  353     scale = constrain_float(scale, 0.01f, 1.0f);
        MOVS     R2,#+1065353216
        LDR.W    R1,??DataTable11_4  ;; 0x3c23d70a
        LDR.W    R0,??DataTable11_1
        LDR      R0,[R0, #+0]
          CFI FunCall constrain_float
        BL       constrain_float
        LDR.W    R1,??DataTable11_1
        STR      R0,[R1, #+0]
//  354     last_lat = loc.lat;
        LDR      R0,[SP, #+4]
        LDR.W    R1,??DataTable10_14
        STR      R0,[R1, #+0]
//  355     return scale;
        LDR.W    R0,??DataTable11_1
        LDR      R0,[R0, #+0]
??longitude_scale_3:
        POP      {R1-R3,PC}       ;; return
//  356 }
          CFI EndBlock cfiBlock5

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
`longitude_scale::last_lat`:
        DS8 4

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
`longitude_scale::scale`:
        DC32 3F800000H
//  357 /*
//  358   return the distance in meters in North/East plane as a N/E vector
//  359   from loc1 to loc2
//  360  */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function location_diff
        THUMB
//  361 Vector2f location_diff(Location loc1,Location loc2)
//  362 {
location_diff:
        PUSH     {R1-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+32
        MOVS     R7,R0
//  363   Vector2f Location_Delta;
//  364   Location_Delta.x=(loc2.lat - loc1.lat) * LOCATION_SCALING_FACTOR;//距离单位为m
        LDR      R0,[SP, #+36]
        LDR      R1,[SP, #+4]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable11_5  ;; 0x3c366282
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
//  365   Location_Delta.y=(loc2.lng - loc1.lng) * LOCATION_SCALING_FACTOR * longitude_scale(loc1);//距离单位为mm
        LDR      R0,[SP, #+40]
        LDR      R1,[SP, #+8]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.W    R1,??DataTable11_5  ;; 0x3c366282
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R6,R0
        MOV      R0,SP
        LDM      R0,{R0-R2}
          CFI FunCall longitude_scale
        BL       longitude_scale
        MOVS     R1,R6
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R5,R0
//  366   return Location_Delta;
        STRD     R4,R5,[R7, #+0]
        POP      {R1-R7,PC}       ;; return
//  367 }
          CFI EndBlock cfiBlock6
//  368 // square

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function sq
        THUMB
//  369 float sq(float v) {return v*v;}
sq:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        MOVS     R1,R0
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        POP      {R1,PC}          ;; return
          CFI EndBlock cfiBlock7
//  370 // 2D vector length

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function pythagorous2
        THUMB
//  371 float pythagorous2(float a, float b) {	return sqrtf(sq(a)+sq(b));}
pythagorous2:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R1
          CFI FunCall sq
        BL       sq
        MOVS     R5,R0
        MOVS     R0,R4
          CFI FunCall sq
        BL       sq
        MOVS     R1,R5
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall sqrtf
        BL       sqrtf
        POP      {R1,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock8
//  372 // 3D vector length

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function pythagorous3
        THUMB
//  373 float pythagorous3(float a, float b, float c) {return sqrtf(sq(a)+sq(b)+sq(c));}
pythagorous3:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R4,R1
        MOVS     R5,R2
          CFI FunCall sq
        BL       sq
        MOVS     R6,R0
        MOVS     R0,R4
          CFI FunCall sq
        BL       sq
        MOVS     R4,R0
        MOVS     R0,R5
          CFI FunCall sq
        BL       sq
        MOVS     R5,R0
        MOVS     R0,R6
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R1,R5
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
          CFI FunCall sqrtf
        BL       sqrtf
        POP      {R4-R6,PC}       ;; return
          CFI EndBlock cfiBlock9
//  374 // return distance in meters between two locations

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function get_distance
        THUMB
//  375 float get_distance(Location loc1,Location loc2){
get_distance:
        PUSH     {R0-R3}
          CFI CFA R13+16
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -20)
          CFI R5 Frame(CFA, -24)
          CFI R4 Frame(CFA, -28)
          CFI CFA R13+32
//  376     float dlat              = (float)(loc2.lat - loc1.lat);
        LDR      R0,[SP, #+32]
        LDR      R1,[SP, #+20]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R4,R0
//  377     float dlong             = ((float)(loc2.lng - loc1.lng)) * longitude_scale(loc2);
        LDR      R0,[SP, #+36]
        LDR      R1,[SP, #+24]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        MOVS     R5,R0
        ADD      R0,SP,#+28
        LDM      R0,{R0-R2}
          CFI FunCall longitude_scale
        BL       longitude_scale
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
//  378     return pythagorous2(dlat, dlong) * LOCATION_SCALING_FACTOR;
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall pythagorous2
        BL       pythagorous2
        LDR.W    R1,??DataTable11_5  ;; 0x3c366282
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        POP      {R1,R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+20
        LDR      PC,[SP], #+20    ;; return
//  379 }
          CFI EndBlock cfiBlock10
//  380 /*************************以上计算球面投影距离内容源于APM3.2 AP.Math.c文件******************************/
//  381

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  382 Vector2i GPSData_To_XY_Home={1143637460,306276000};//经、纬度
GPSData_To_XY_Home:
        DC32 1143637460, 306276000

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  383 Location GPS_Home;//初始定位成功点信息
GPS_Home:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  384 Location GPS_Present;//当前位置点信息
GPS_Present:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
//  385 uint8 GPS_Home_Set=0;
GPS_Home_Set:
        DS8 1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function Set_GPS_Home
        THUMB
//  386 void Set_GPS_Home(void)//设置Home点
//  387 {
Set_GPS_Home:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  388       if(GPS_Home_Set==0
//  389          &&GPS_Sate_Num>=9)//全程只设置一次
        LDR.W    R0,??DataTable11_6
        LDRB     R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??Set_GPS_Home_0
        LDR.W    R0,??DataTable11_7
        LDRH     R0,[R0, #+0]
        CMP      R0,#+9
        BLT.N    ??Set_GPS_Home_0
//  390       {
//  391           GPSData_To_XY_Home.x=Longitude_Origion;//Longitude;
        LDR.W    R0,??DataTable11_8
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable11_9
        STR      R0,[R1, #+0]
//  392           GPSData_To_XY_Home.y=Latitude_Origion;//Latitude;
        LDR.W    R0,??DataTable11_10
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable11_9
        STR      R0,[R1, #+4]
//  393           GPS_Home_Set=1;//设定返航点
        MOVS     R0,#+1
        LDR.W    R1,??DataTable11_6
        STRB     R0,[R1, #+0]
//  394           GPS_Home.lng=GPSData_To_XY_Home.x;
        LDR.W    R0,??DataTable11_9
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable11_11
        STR      R0,[R1, #+8]
//  395           GPS_Home.lat=GPSData_To_XY_Home.y;
        LDR.W    R0,??DataTable11_9
        LDR      R0,[R0, #+4]
        LDR.W    R1,??DataTable11_11
        STR      R0,[R1, #+4]
//  396
//  397           Strapdown_INS_Reset(&NamelessQuad,_PITCH,Earth_Frame_To_XYZ.E,0);//复位惯导融合
        MOVS     R3,#+0
        LDR.W    R0,??DataTable11_12
        LDR      R2,[R0, #+0]
        MOVS     R1,#+1
        LDR.W    R0,??DataTable10_2
          CFI FunCall Strapdown_INS_Reset
        BL       Strapdown_INS_Reset
//  398           Strapdown_INS_Reset(&NamelessQuad,_ROLL,Earth_Frame_To_XYZ.E,0);//复位惯导融合
        MOVS     R3,#+0
        LDR.W    R0,??DataTable11_12
        LDR      R2,[R0, #+0]
        MOVS     R1,#+2
        LDR.W    R0,??DataTable10_2
          CFI FunCall Strapdown_INS_Reset
        BL       Strapdown_INS_Reset
//  399
//  400
//  401       }
//  402
//  403 }
??Set_GPS_Home_0:
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock11
//  404
//  405

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  406 float Body_Frame_To_XYZ[3]={0,0,0};//导航（地理）坐标系，机体横滚(Y正)、俯仰(X正)方向位置偏移
Body_Frame_To_XYZ:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  407 Vector3_Nav Earth_Frame_To_XYZ={0,0,0};//导航（地理）坐标系，天 、正北、正东方向上位置偏移
Earth_Frame_To_XYZ:
        DS8 12

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function GPSData_Sort
        THUMB
//  408 void GPSData_Sort()
//  409 {
GPSData_Sort:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        SUB      SP,SP,#+24
          CFI CFA R13+32
//  410    Vector2f location_delta={0,0};
        LDR.W    R0,??DataTable11_13
        LDRD     R2,R3,[R0, #+0]
        STRD     R2,R3,[SP, #+12]
//  411    GPS_Present.lng=Longitude_Origion;//更新当前经纬度
        LDR.W    R0,??DataTable11_8
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable11_14
        STR      R0,[R1, #+8]
//  412    GPS_Present.lat=Latitude_Origion;
        LDR.W    R0,??DataTable11_10
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable11_14
        STR      R0,[R1, #+4]
//  413    location_delta=location_diff(GPS_Home,GPS_Present);//根据当前GPS定位信息与Home点位置信息计算正北、正东方向位置偏移
        LDR.W    R0,??DataTable11_14
        MOV      R2,SP
        LDM      R0!,{R1,R3}
        STM      R2!,{R1,R3}
        LDR      R3,[R0, #0]
        STR      R3,[R2, #+0]
        SUBS     R0,R0,#+8
        SUBS     R2,R2,#+8
        LDR.W    R0,??DataTable11_11
        LDM      R0,{R1-R3}
        ADD      R0,SP,#+12
          CFI FunCall location_diff
        BL       location_diff
//  414    /***********************************************************************************
//  415    明确下导航系方向，这里正北、正东为正方向:
//  416      沿着正东，经度增加,当无人机相对home点，往正东向移动时，此时GPS_Present.lng>GPS_Home.lng，得到的location_delta.x大于0;
//  417      沿着正北，纬度增加,当无人机相对home点，往正北向移动时，此时GPS_Present.lat>GPS_Home.lat，得到的location_delta.y大于0;
//  418    ******************************************************************************/
//  419    location_delta.x*=100;//沿地理坐标系，正东方向位置偏移,单位为CM
        LDR      R1,[SP, #+12]
        LDR.N    R0,??DataTable8_16  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[SP, #+12]
//  420    location_delta.y*=100;//沿地理坐标系，正北方向位置偏移,单位为CM
        LDR      R1,[SP, #+16]
        LDR.N    R0,??DataTable8_16  ;; 0x42c80000
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[SP, #+16]
//  421    Earth_Frame_To_XYZ.E=location_delta.y;//地理系下相对Home点正东位置偏移，单位为CM
        LDR      R0,[SP, #+16]
        LDR.W    R1,??DataTable11_12
        STR      R0,[R1, #+0]
//  422    Earth_Frame_To_XYZ.N=location_delta.x;//地理系下相对Home点正北位置偏移，单位为CM
        LDR      R0,[SP, #+12]
        LDR.W    R1,??DataTable11_12
        STR      R0,[R1, #+4]
//  423    //将无人机在导航坐标系下的沿着正东、正北方向的位置偏移旋转到当前航向的位置偏移:机头(俯仰)+横滚
//  424    Body_Frame_To_XYZ[_PITCH]=-location_delta.x*Sin_Yaw+location_delta.y*Cos_Yaw;//机头正向位置偏移  Y轴正向
        LDR      R1,[SP, #+12]
        EORS     R1,R1,#0x80000000
        LDR.N    R0,??DataTable8_10
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR      R1,[SP, #+16]
        LDR.N    R0,??DataTable8_11
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12
        STR      R0,[R1, #+4]
//  425    Body_Frame_To_XYZ[_ROLL]=location_delta.x*Cos_Yaw+location_delta.y*Sin_Yaw;  //横滚正向位置偏移  X轴正向
        LDR      R1,[SP, #+12]
        LDR.N    R0,??DataTable8_11
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR      R1,[SP, #+16]
        LDR.N    R0,??DataTable8_10
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12
        STR      R0,[R1, #+8]
//  426 }
        ADD      SP,SP,#+24
          CFI CFA R13+8
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock12

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_1:
        DC32     Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_2:
        DC32     0xa2529d44

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_3:
        DC32     0x3f91df46

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_4:
        DC32     Sin_Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_5:
        DC32     Cos_Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_6:
        DC32     Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_7:
        DC32     Sin_Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_8:
        DC32     Cos_Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_9:
        DC32     Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_10:
        DC32     Sin_Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_11:
        DC32     Cos_Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_12:
        DC32     Acce_Control

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_13:
        DC32     Origion_NamelessQuad

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_14:
        DC32     0x3b1ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_15:
        DC32     0xc11ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_16:
        DC32     0x42c80000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_17:
        DC32     Acceleration_Length

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
?_3:
        DC32 0H, 0H
//  427
//  428 #define TIME_CONTANST_XY      2.5f
//  429 #define K_ACC_XY	     (1.0f / (TIME_CONTANST_XY * TIME_CONTANST_XY * TIME_CONTANST_XY))
//  430 #define K_VEL_XY             (3.0f / (TIME_CONTANST_XY * TIME_CONTANST_XY))															// XY????·′à??μêy,3.0
//  431 #define K_POS_XY             (3.0f / TIME_CONTANST_XY)

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  432 float X_Delta=0,Y_Delta=0;
X_Delta:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
Y_Delta:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  433 uint16_t GPS_Save_Period_Cnt=0;
GPS_Save_Period_Cnt:
        DS8 2

        SECTION `.data`:DATA:REORDER:NOROOT(1)
        DATA
//  434 uint16_t GPS_SINS_Delay_Cnt=20;//100ms
GPS_SINS_Delay_Cnt:
        DC16 20
//  435 Testime SINS_Horizontal_Delta;

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  436 Vector2_Body Pos_Err_On_Accel={0};
Pos_Err_On_Accel:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  437 Vector2_Body  Accel_Correction_BF={0};
Accel_Correction_BF:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  438 Vector2_Earth Accel_Correction_EF={0};
Accel_Correction_EF:
        DS8 8

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function Strapdown_INS_Horizontal
        THUMB
//  439 void Strapdown_INS_Horizontal()
//  440 {
Strapdown_INS_Horizontal:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
//  441       uint16 Cnt=0;
        MOVS     R0,#+0
//  442       GPSData_Sort();//获取相对home的水平偏移
          CFI FunCall GPSData_Sort
        BL       GPSData_Sort
//  443       GPS_Save_Period_Cnt++;
        LDR.W    R0,??DataTable11_15
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable11_15
        STRH     R0,[R1, #+0]
//  444       if(GPS_Save_Period_Cnt>=1)//5ms
        LDR.W    R0,??DataTable11_15
        LDRH     R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??Strapdown_INS_Horizontal_0
//  445       {
//  446             for(Cnt=Num-1;Cnt>0;Cnt--)//10ms滑动一次
        MOVS     R0,#+49
        B.N      ??Strapdown_INS_Horizontal_1
//  447             {
//  448               NamelessQuad.Pos_History[_PITCH][Cnt]=NamelessQuad.Pos_History[_PITCH][Cnt-1];
??Strapdown_INS_Horizontal_2:
        LDR.W    R1,??DataTable10_2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #+232]
        LDR.W    R2,??DataTable10_2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0, LSL #+2
        STR      R1,[R2, #+236]
//  449               NamelessQuad.Pos_History[_ROLL][Cnt]=NamelessQuad.Pos_History[_ROLL][Cnt-1];
        LDR.W    R1,??DataTable10_2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #+432]
        LDR.W    R2,??DataTable10_2
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0, LSL #+2
        STR      R1,[R2, #+436]
//  450             }
        SUBS     R0,R0,#+1
??Strapdown_INS_Horizontal_1:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+0
        BNE.N    ??Strapdown_INS_Horizontal_2
//  451               NamelessQuad.Pos_History[_PITCH][0]=NamelessQuad.Position[_PITCH];
        LDR.W    R0,??DataTable10_2
        LDR      R0,[R0, #+4]
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+236]
//  452               NamelessQuad.Pos_History[_ROLL][0]=NamelessQuad.Position[_ROLL];
        LDR.W    R0,??DataTable10_2
        LDR      R0,[R0, #+8]
        LDR.W    R1,??DataTable10_2
        STR      R0,[R1, #+436]
//  453               GPS_Save_Period_Cnt=0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable11_15
        STRH     R0,[R1, #+0]
//  454       }
//  455       //GPS导航坐标系下，正北、正东方向位置偏移与SINS估计量的差，单位cm
//  456       X_Delta=Earth_Frame_To_XYZ.E-NamelessQuad.Pos_History[_PITCH][GPS_SINS_Delay_Cnt];
??Strapdown_INS_Horizontal_0:
        LDR.W    R0,??DataTable11_12
        LDR      R0,[R0, #+0]
        LDR.W    R1,??DataTable10_2
        LDR.W    R2,??DataTable12_1
        LDRH     R2,[R2, #+0]
        ADD      R1,R1,R2, LSL #+2
        LDR      R1,[R1, #+236]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable12_2
        STR      R0,[R1, #+0]
//  457       Y_Delta=Earth_Frame_To_XYZ.N-NamelessQuad.Pos_History[_ROLL][GPS_SINS_Delay_Cnt];
        LDR.W    R0,??DataTable11_12
        LDR      R0,[R0, #+4]
        LDR.W    R1,??DataTable10_2
        LDR.W    R2,??DataTable12_1
        LDRH     R2,[R2, #+0]
        ADD      R1,R1,R2, LSL #+2
        LDR      R1,[R1, #+436]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable12_3
        STR      R0,[R1, #+0]
//  458
//  459
//  460       Pos_Err_On_Accel.Rol=X_Delta*Cos_Yaw+Y_Delta*Sin_Yaw;//载体系Roll方向    X轴
        LDR.W    R0,??DataTable12_2
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_4
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable12_3
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_5
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_6
        STR      R0,[R1, #+4]
//  461       Pos_Err_On_Accel.Pit=-X_Delta*Sin_Yaw+Y_Delta*Cos_Yaw;//载体系Pitch方向  Y轴
        LDR.W    R0,??DataTable12_2
        LDR      R1,[R0, #+0]
        EORS     R1,R1,#0x80000000
        LDR.W    R0,??DataTable12_5
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable12_3
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_4
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_6
        STR      R0,[R1, #+0]
//  462
//  463       Accel_Correction_BF.Pit+=Pos_Err_On_Accel.Pit* K_ACC_XY*CNTLCYCLE;//在载体机头方向，加速度矫正量
        LDR.W    R0,??DataTable12_6
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_7  ;; 0x3d83126f
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable12_8
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_8
        STR      R0,[R1, #+0]
//  464       Accel_Correction_BF.Rol+=Pos_Err_On_Accel.Rol* K_ACC_XY*CNTLCYCLE;//在载体横滚方向，加速度矫正量
        LDR.W    R0,??DataTable12_6
        LDR      R1,[R0, #+4]
        LDR.W    R0,??DataTable12_7  ;; 0x3d83126f
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.W    R1,??DataTable12_8
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_8
        STR      R0,[R1, #+4]
//  465
//  466       Accel_Correction_EF.North=Accel_Correction_BF.Rol*Cos_Yaw+Accel_Correction_BF.Pit*Sin_Yaw;//将载体方向上加速度修正量，旋转至导航系北向  Y Axis
        LDR.W    R0,??DataTable12_8
        LDR      R1,[R0, #+4]
        LDR.W    R0,??DataTable12_4
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable12_8
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_5
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_9
        STR      R0,[R1, #+0]
//  467       Accel_Correction_EF.East=Accel_Correction_BF.Rol*Sin_Yaw-Accel_Correction_BF.Pit*Cos_Yaw;//将载体方向上加速度修正量，旋转至导航系动向   X axis
        LDR.W    R0,??DataTable12_8
        LDR      R1,[R0, #+4]
        LDR.W    R0,??DataTable12_5
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable12_8
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_4
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.W    R1,??DataTable12_9
        STR      R0,[R1, #+4]
//  468
//  469       acc_correction[_PITCH] += X_Delta*K_ACC_XY*CNTLCYCLE;//加速度矫正量
        LDR.W    R0,??DataTable12_2
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_7  ;; 0x3d83126f
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_3
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_3
        STR      R0,[R1, #+4]
//  470       //acc_correction[_PITCH]  = Accel_Correction_EF.East;//加速度矫正量
//  471       vel_correction[_PITCH] += X_Delta* K_VEL_XY*CNTLCYCLE;//速度矫正量
        LDR.W    R0,??DataTable12_2
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_10  ;; 0x3ef5c28f
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_5
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_5
        STR      R0,[R1, #+4]
//  472       pos_correction[_PITCH] += X_Delta* K_POS_XY*CNTLCYCLE;//位置矫正量
        LDR.W    R0,??DataTable12_2
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_11  ;; 0x3f99999a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_6
        LDR      R1,[R1, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_6
        STR      R0,[R1, #+4]
//  473
//  474       //acc_correction[_ROLL]  = Accel_Correction_EF.North;//加速度矫正量
//  475       acc_correction[_ROLL] += Y_Delta* K_ACC_XY*CNTLCYCLE;//加速度矫正量
        LDR.W    R0,??DataTable12_3
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_7  ;; 0x3d83126f
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_3
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_3
        STR      R0,[R1, #+8]
//  476       vel_correction[_ROLL] += Y_Delta* K_VEL_XY*CNTLCYCLE;//速度矫正量
        LDR.W    R0,??DataTable12_3
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_10  ;; 0x3ef5c28f
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_5
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_5
        STR      R0,[R1, #+8]
//  477       pos_correction[_ROLL] += Y_Delta* K_POS_XY*CNTLCYCLE;//位置矫正量
        LDR.W    R0,??DataTable12_3
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_11  ;; 0x3f99999a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_6
        LDR      R1,[R1, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_6
        STR      R0,[R1, #+8]
//  478
//  479       /*************************************************************/
//  480       //水平运动加速度计校正
//  481       NamelessQuad.Acceleration[_PITCH]=Origion_NamelessQuad.Acceleration[_PITCH]+acc_correction[_PITCH];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+28]
        LDR.N    R0,??DataTable10_3
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_2
        STR      R0,[R1, #+28]
//  482       //速度增量矫正后更新，用于更新位置
//  483       SpeedDealt[_PITCH]=NamelessQuad.Acceleration[_PITCH]*CNTLCYCLE;
        LDR.N    R0,??DataTable10_2
        LDR      R1,[R0, #+28]
        LDR.N    R0,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_7
        STR      R0,[R1, #+4]
//  484       //原始位置更新
//  485       Origion_NamelessQuad.Position[_PITCH]+=(NamelessQuad.Speed[_PITCH]+0.5*SpeedDealt[_PITCH])*CNTLCYCLE;
        LDR.W    R0,??DataTable12_12
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R6,R0
        MOVS     R7,R1
        LDR.N    R0,??DataTable10_2
        LDR      R0,[R0, #+16]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.N    R0,??DataTable10_7
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        LDR.N    R3,??DataTable10_8  ;; 0x3fe00000
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,#+1073741824
        LDR.W    R3,??DataTable12_13  ;; 0x3f747ae1
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R6
        MOVS     R3,R7
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable12_12
        STR      R0,[R1, #+4]
//  486       //位置矫正后更新
//  487       NamelessQuad.Position[_PITCH]=Origion_NamelessQuad.Position[_PITCH]+pos_correction[_PITCH];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+4]
        LDR.N    R0,??DataTable10_6
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_2
        STR      R0,[R1, #+4]
//  488       //原始速度更新
//  489       Origion_NamelessQuad.Speed[_PITCH]+=SpeedDealt[_PITCH];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+16]
        LDR.N    R0,??DataTable10_7
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_12
        STR      R0,[R1, #+16]
//  490       //速度矫正后更新
//  491       NamelessQuad.Speed[_PITCH]=Origion_NamelessQuad.Speed[_PITCH]+vel_correction[_PITCH];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+16]
        LDR.N    R0,??DataTable10_5
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_2
        STR      R0,[R1, #+16]
//  492
//  493       /*************************************************************/
//  494       //水平运动加速度计校正
//  495       NamelessQuad.Acceleration[_ROLL]=Origion_NamelessQuad.Acceleration[_ROLL]+acc_correction[_ROLL];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+32]
        LDR.N    R0,??DataTable10_3
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_2
        STR      R0,[R1, #+32]
//  496       //速度增量矫正后更新，用于更新位置
//  497       SpeedDealt[_ROLL]=NamelessQuad.Acceleration[_ROLL]*CNTLCYCLE;
        LDR.N    R0,??DataTable10_2
        LDR      R1,[R0, #+32]
        LDR.N    R0,??DataTable10_11  ;; 0x3ba3d70a
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable10_7
        STR      R0,[R1, #+8]
//  498       //原始位置更新
//  499       Origion_NamelessQuad.Position[_ROLL]+=(NamelessQuad.Speed[_ROLL]+0.5*SpeedDealt[_ROLL])*CNTLCYCLE;
        LDR.W    R0,??DataTable12_12
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R6,R0
        MOVS     R7,R1
        LDR.N    R0,??DataTable10_2
        LDR      R0,[R0, #+20]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.N    R0,??DataTable10_7
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        LDR.N    R3,??DataTable10_8  ;; 0x3fe00000
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,#+1073741824
        LDR.W    R3,??DataTable12_13  ;; 0x3f747ae1
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R6
        MOVS     R3,R7
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.W    R1,??DataTable12_12
        STR      R0,[R1, #+8]
//  500       //位置矫正后更新
//  501       NamelessQuad.Position[_ROLL]=Origion_NamelessQuad.Position[_ROLL]+pos_correction[_ROLL];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+8]
        LDR.N    R0,??DataTable10_6
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_2
        STR      R0,[R1, #+8]
//  502       //原始速度更新
//  503       Origion_NamelessQuad.Speed[_ROLL]+=SpeedDealt[_ROLL];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+20]
        LDR.N    R0,??DataTable10_7
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_12
        STR      R0,[R1, #+20]
//  504       //速度矫正后更新
//  505       NamelessQuad.Speed[_ROLL]=Origion_NamelessQuad.Speed[_ROLL]+vel_correction[_ROLL];
        LDR.W    R0,??DataTable12_12
        LDR      R1,[R0, #+20]
        LDR.N    R0,??DataTable10_5
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable10_2
        STR      R0,[R1, #+20]
//  506 }
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock13

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9:
        DC32     SINS_High_Delta

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_1:
        DC32     0x408f4000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_2:
        DC32     Delta_T

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_3:
        DC32     SPL06_001_Filter_high

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_4:
        DC32     Altitude_Estimate

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_5:
        DC32     High_Delay_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_6:
        DC32     Altitude_Dealt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_7:
        DC32     TIME_CONTANST_ZER
//  507
//  508
//  509

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock14 Using cfiCommon0
          CFI Function Strapdown_INS_Reset
          CFI NoCalls
        THUMB
//  510 void Strapdown_INS_Reset(SINS *Ins,uint8_t Axis,float Pos_Target,float Vel_Target)
//  511 {
Strapdown_INS_Reset:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//  512       uint16_t Cnt=0;
        MOVS     R4,#+0
//  513       Ins->Position[Axis]=Pos_Target;//位置重置
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        STR      R2,[R0, R1, LSL #+2]
//  514       Ins->Speed[Axis]=Vel_Target;//速度重置
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        ADD      R4,R0,R1, LSL #+2
        STR      R3,[R4, #+12]
//  515       Ins->Acceleration[Axis]=0.0f;//加速度清零
        MOVS     R4,#+0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        ADD      R5,R0,R1, LSL #+2
        STR      R4,[R5, #+24]
//  516       Ins->Acce_Bias[Axis]=0.0f;
        MOVS     R4,#+0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        ADD      R5,R0,R1, LSL #+2
        STR      R4,[R5, #+1236]
//  517       for(Cnt=Num-1;Cnt>0;Cnt--)//历史位置值，全部装载为当前观测值
        MOVS     R4,#+49
        B.N      ??Strapdown_INS_Reset_0
//  518       {
//  519          Ins->Pos_History[Axis][Cnt]=Pos_Target;
??Strapdown_INS_Reset_1:
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R5,#+200
        MUL      R5,R5,R1
        ADD      R5,R0,R5
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R5,R5,R4, LSL #+2
        STR      R2,[R5, #+36]
//  520       }
        SUBS     R4,R4,#+1
??Strapdown_INS_Reset_0:
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        CMP      R4,#+0
        BNE.N    ??Strapdown_INS_Reset_1
//  521          Ins->Pos_History[Axis][0]=Pos_Target;
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R4,#+200
        MUL      R4,R4,R1
        ADD      R4,R0,R4
        STR      R2,[R4, #+36]
//  522       for(Cnt=Num-1;Cnt>0;Cnt--)//历史速度值，全部装载为当前观测值
        MOVS     R4,#+49
        B.N      ??Strapdown_INS_Reset_2
//  523       {
//  524          Ins->Vel_History[Axis][Cnt]=Vel_Target;
??Strapdown_INS_Reset_3:
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R2,#+200
        MUL      R2,R2,R1
        ADD      R2,R0,R2
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADD      R2,R2,R4, LSL #+2
        STR      R3,[R2, #+636]
//  525       }
        SUBS     R4,R4,#+1
??Strapdown_INS_Reset_2:
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        CMP      R4,#+0
        BNE.N    ??Strapdown_INS_Reset_3
//  526          Ins->Vel_History[Axis][0]=Vel_Target;
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R2,#+200
        MUL      R2,R2,R1
        ADD      R0,R0,R2
        STR      R3,[R0, #+636]
//  527       pos_correction[Axis]=0;//清空惯导融合量
        MOVS     R0,#+0
        LDR.N    R2,??DataTable10_6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        STR      R0,[R2, R1, LSL #+2]
//  528       acc_correction[Axis]=0;
        MOVS     R0,#+0
        LDR.N    R2,??DataTable10_3
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        STR      R0,[R2, R1, LSL #+2]
//  529       vel_correction[Axis]=0;
        MOVS     R0,#+0
        LDR.N    R2,??DataTable10_5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        STR      R0,[R2, R1, LSL #+2]
//  530 }
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock14

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10:
        DC32     SINS_Accel_Body

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_1:
        DC32     `Strapdown_INS_High::Save_Cnt`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_2:
        DC32     NamelessQuad

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_3:
        DC32     acc_correction

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_4:
        DC32     0x40400000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_5:
        DC32     vel_correction

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_6:
        DC32     pos_correction

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_7:
        DC32     SpeedDealt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_8:
        DC32     0x3fe00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_9:
        DC32     Pre_conv

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_10:
        DC32     Acce_Bias_Gain

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_11:
        DC32     0x3ba3d70a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_12:
        DC32     Q

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_13:
        DC32     R

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_14:
        DC32     `longitude_scale::last_lat`
//  531
//  532
//  533 //float R_GPS[2]={0.01f,0.005f};
//  534 //float Q_GPS[2]={0.5,3};
//  535 //float R_Acce_bias[2]={0.0001,0.00001};
//  536

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  537 float R_GPS[2]={0.05f,0.005f};
R_GPS:
        DC32 3D4CCCCDH, 3BA3D70AH

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  538 float Q_GPS[2]={2,3};
Q_GPS:
        DC32 40000000H, 40400000H

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//  539 float R_Acce_bias[2]={0.0001,0.00001};
R_Acce_bias:
        DC32 38D1B717H, 3727C5ACH

        SECTION `.data`:DATA:REORDER:NOROOT(3)
        DATA
//  540 double Pre_conv_GPS[2][4]=
Pre_conv_GPS:
        DC32 0EB1C432DH, 3F1A36E2H, 88E368F1H, 3EE4F8B5H, 88E368F1H, 3EE4F8B5H
        DC32 0BC6A7EFAH, 3F689374H, 0EB1C432DH, 3F1A36E2H, 88E368F1H, 3EE4F8B5H
        DC32 88E368F1H, 3EE4F8B5H, 0BC6A7EFAH, 3F689374H
//  541 {
//  542   0.0001 ,    0.00001,  0.00001    , 0.003,
//  543   0.0001 ,    0.00001,  0.00001    , 0.003,
//  544 };//上一次协方差

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//  545 double K_GPS[2][2]={0};//增益矩阵
K_GPS:
        DS8 32

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  546 float Acce_Bias[2];
Acce_Bias:
        DS8 8

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock15 Using cfiCommon0
          CFI Function KalmanFilter_Horizontal_GPS
        THUMB
//  547 void   KalmanFilter_Horizontal_GPS(float Position_GPS,float Vel_GPS,float Position_Last,float Vel_Last,
//  548                                    float *Position,float *Vel,
//  549                                    float *Acce,float *R,
//  550                                    float *Q,float dt,uint8_t Axis)
//  551 {
KalmanFilter_Horizontal_GPS:
        PUSH     {R0-R2,R4-R11,LR}
          CFI R14 Frame(CFA, -4)
          CFI R11 Frame(CFA, -8)
          CFI R10 Frame(CFA, -12)
          CFI R9 Frame(CFA, -16)
          CFI R8 Frame(CFA, -20)
          CFI R7 Frame(CFA, -24)
          CFI R6 Frame(CFA, -28)
          CFI R5 Frame(CFA, -32)
          CFI R4 Frame(CFA, -36)
          CFI CFA R13+48
        SUB      SP,SP,#+48
          CFI CFA R13+96
        MOV      R11,R3
//  552       float Conv_Z=0;
        MOVS     R4,#+0
//  553       float Z_Delta[2]={0};
        ADD      R0,SP,#+8
        MOVS     R1,#+0
        MOVS     R2,#+0
        STRD     R1,R2,[R0, #+0]
//  554       float Conv_Temp=0;
        MOVS     R4,#+0
//  555       double Temp_conv[4]={0};//先验协方差
        ADD      R0,SP,#+16
        MOVS     R1,#+32
          CFI FunCall __aeabi_memclr4
        BL       __aeabi_memclr4
//  556       uint8 Label=0;
        MOVS     R6,#+0
//  557       if(Axis=='X') Label=0;
        LDR      R0,[SP, #+120]
        CMP      R0,#+88
        BNE.N    ??KalmanFilter_Horizontal_GPS_0
        MOVS     R6,#+0
        B.N      ??KalmanFilter_Horizontal_GPS_1
//  558       else Label=1;
??KalmanFilter_Horizontal_GPS_0:
        MOVS     R6,#+1
??KalmanFilter_Horizontal_GPS_1:
        LDR      R10,[SP, #+96]
        LDR      R7,[SP, #+100]
        LDR      R4,[SP, #+104]
        LDR      R5,[SP, #+116]
//  559       //先验状态
//  560       *Position +=*Vel*dt+((*Acce+Acce_Bias[Label])*dt*dt)/2.0;
        LDR      R0,[R10, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        STRD     R0,R1,[SP, #+0]
        LDR      R0,[R7, #+0]
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R8,R0
        MOV      R9,R1
        LDR      R0,[R4, #+0]
        LDR.W    R1,??DataTable12_14
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LDR      R1,[R1, R6, LSL #+2]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        LDRD     R2,R3,[SP, #+0]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        STR      R0,[R10, #+0]
//  561       *Vel+=*Acce*dt;
        LDR      R0,[R4, #+0]
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR      R1,[R7, #+0]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        STR      R0,[R7, #+0]
//  562       //先验协方差
//  563       Conv_Temp=Pre_conv_GPS[Label][1]+Pre_conv_GPS[Label][3]*dt;
        MOVS     R0,R5
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R4,R2,R3
        LDRD     R2,R3,[R4, #+24]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R4,R2,R3
        LDRD     R2,R3,[R4, #+8]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        MOVS     R4,R0
//  564       Temp_conv[0]=Pre_conv_GPS[Label][0]+Pre_conv_GPS[Label][2]*dt+Conv_Temp*dt+R_GPS[0];
        MOVS     R0,R5
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R12,R2,R3
        LDRD     R2,R3,[R12, #+16]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R12,R2,R3
        LDRD     R2,R3,[R12, #+0]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOV      R8,R0
        MOV      R9,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOV      R8,R0
        MOV      R9,R1
        LDR.W    R0,??DataTable12_16
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        STRD     R0,R1,[SP, #+16]
//  565       Temp_conv[1]=Conv_Temp;
        MOVS     R0,R4
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        STRD     R0,R1,[SP, #+24]
//  566       Temp_conv[2]=Pre_conv_GPS[Label][2]+Pre_conv_GPS[Label][3]*dt;
        MOVS     R0,R5
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R4,R2,R3
        LDRD     R2,R3,[R4, #+24]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R4,R2,R3
        LDRD     R2,R3,[R4, #+16]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        STRD     R0,R1,[SP, #+32]
//  567       //Temp_conv[1]=Conv_Temp+R_GPS[0]*0.5*0.00001;
//  568       //Temp_conv[2]=Temp_conv[1];
//  569       Temp_conv[3]=Pre_conv_GPS[Label][3]+R_GPS[1];
        LDR.W    R0,??DataTable12_16
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R4,R2,R3
        LDRD     R2,R3,[R4, #+24]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        STRD     R0,R1,[SP, #+40]
//  570       //计算卡尔曼增益
//  571       Conv_Z=1.0/(Temp_conv[0]+Q_GPS[0]*GPS_Quality)*(Temp_conv[3]+Q_GPS[1]*GPS_Quality)-Temp_conv[1]*Temp_conv[2];
        LDR.W    R0,??DataTable12_17
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_18
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDRD     R2,R3,[SP, #+16]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,#+0
        LDR.W    R1,??DataTable12_19  ;; 0x3ff00000
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.W    R0,??DataTable12_17
        LDR      R1,[R0, #+4]
        LDR.W    R0,??DataTable12_18
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDRD     R2,R3,[SP, #+40]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDRD     R2,R3,[SP, #+24]
        LDRD     R0,R1,[SP, #+32]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        MOVS     R4,R0
//  572       //K_GPS[0][0]=( Temp_conv[0]*(Temp_conv[3]+Q_GPS[1])-Temp_conv[1]*Temp_conv[2])*Conv_Z;
//  573       //K_GPS[0][1]=(-Temp_conv[0]*Temp_conv[1]+Temp_conv[1]*(Temp_conv[0]+Q_GPS[0]))*Conv_Z;
//  574       //K_GPS[1][0]=( Temp_conv[2]*(Temp_conv[3]+Q_GPS[1])-Temp_conv[2]*Temp_conv[3])*Conv_Z;
//  575       //K_GPS[1][1]=(-Temp_conv[1]*Temp_conv[2]+Temp_conv[3]*(Temp_conv[0]+Q_GPS[0]))*Conv_Z;
//  576       //化简如下
//  577       K_GPS[0][0]=( Temp_conv[0]*(Temp_conv[3]+Q_GPS[1]*GPS_Quality)-Temp_conv[1]*Temp_conv[2])*Conv_Z;
        LDR.W    R0,??DataTable12_17
        LDR      R1,[R0, #+4]
        LDR.W    R0,??DataTable12_18
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDRD     R2,R3,[SP, #+40]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        LDRD     R2,R3,[SP, #+16]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R8,R0
        MOV      R9,R1
        LDRD     R2,R3,[SP, #+24]
        LDRD     R0,R1,[SP, #+32]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOV      R0,R8
        MOV      R1,R9
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        MOV      R8,R0
        MOV      R9,R1
        MOVS     R0,R4
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_20
        STRD     R0,R1,[R2, #+0]
//  578       K_GPS[0][1]=(Temp_conv[1]*Q_GPS[0]*GPS_Quality)*Conv_Z;
        LDR.W    R0,??DataTable12_17
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDRD     R2,R3,[SP, #+24]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R8,R0
        MOV      R9,R1
        LDR.W    R0,??DataTable12_18
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R8,R0
        MOV      R9,R1
        MOVS     R0,R4
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_20
        STRD     R0,R1,[R2, #+8]
//  579       K_GPS[1][0]=(Temp_conv[2]*Q_GPS[1]*GPS_Quality)*Conv_Z;
        LDR.W    R0,??DataTable12_17
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDRD     R2,R3,[SP, #+32]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R8,R0
        MOV      R9,R1
        LDR.W    R0,??DataTable12_18
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R8,R0
        MOV      R9,R1
        MOVS     R0,R4
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_20
        STRD     R0,R1,[R2, #+16]
//  580       K_GPS[1][1]=(-Temp_conv[1]*Temp_conv[2]+Temp_conv[3]*(Temp_conv[0]+Q_GPS[0]*GPS_Quality))*Conv_Z;
        LDRD     R2,R3,[SP, #+24]
        EORS     R3,R3,#0x80000000
        LDRD     R0,R1,[SP, #+32]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R8,R0
        MOV      R9,R1
        LDR.W    R0,??DataTable12_17
        LDR      R1,[R0, #+0]
        LDR.W    R0,??DataTable12_18
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDRD     R2,R3,[SP, #+16]
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        LDRD     R2,R3,[SP, #+40]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOV      R8,R0
        MOV      R9,R1
        MOVS     R0,R4
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R2,R8
        MOV      R3,R9
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        LDR.W    R2,??DataTable12_20
        STRD     R0,R1,[R2, #+24]
//  581       //融合数据输出
//  582       //Z_Delta[0]=Position_GPS-*Position;
//  583       //Z_Delta[1]=Vel_GPS-*Vel;
//  584       Z_Delta[0]=Position_GPS-Position_Last;
        LDR      R0,[SP, #+48]
        LDR      R1,[SP, #+56]
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        STR      R0,[SP, #+8]
//  585       Z_Delta[1]=Vel_GPS-Vel_Last;
        LDR      R0,[SP, #+52]
        MOV      R1,R11
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        STR      R0,[SP, #+12]
//  586       *Position +=K_GPS[0][0]*Z_Delta[0]
//  587                  +K_GPS[0][1]*Z_Delta[1];
        LDR      R0,[R10, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R8,R0
        MOV      R9,R1
        LDR      R0,[SP, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R4,??DataTable12_20
        LDRD     R2,R3,[R4, #+0]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDR      R0,[SP, #+12]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R12,??DataTable12_20
        LDRD     R2,R3,[R12, #+8]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,R0
        MOVS     R3,R1
        MOV      R0,R8
        MOV      R1,R9
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        STR      R0,[R10, #+0]
//  588       *Vel +=K_GPS[1][0]*Z_Delta[0]
//  589             +K_GPS[1][1]*Z_Delta[1];
        LDR      R0,[R7, #+0]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOV      R8,R0
        MOV      R9,R1
        LDR      R0,[SP, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R4,??DataTable12_20
        LDRD     R2,R3,[R4, #+16]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDR      R0,[SP, #+12]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        LDR.W    R12,??DataTable12_20
        LDRD     R2,R3,[R12, #+24]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,R0
        MOVS     R3,R1
        MOV      R0,R8
        MOV      R1,R9
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        STR      R0,[R7, #+0]
//  590       Acce_Bias[Label]=R_Acce_bias[0]*Z_Delta[0]
//  591                        +R_Acce_bias[1]*Z_Delta[1];
        LDR.W    R0,??DataTable12_21
        LDR      R1,[R0, #+0]
        LDR      R0,[SP, #+8]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR.W    R0,??DataTable12_21
        LDR      R1,[R0, #+4]
        LDR      R0,[SP, #+12]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.W    R1,??DataTable12_14
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        STR      R0,[R1, R6, LSL #+2]
//  592       //更新状态协方差矩阵
//  593       Pre_conv_GPS[Label][0]=(1-K_GPS[0][0])*Temp_conv[0]-K_GPS[0][1]*Temp_conv[2];
        MOVS     R0,#+0
        LDR.W    R1,??DataTable12_19  ;; 0x3ff00000
        LDR.W    R4,??DataTable12_20
        LDRD     R2,R3,[R4, #+0]
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDRD     R2,R3,[SP, #+16]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.W    R2,??DataTable12_20
        LDRD     R0,R1,[R2, #+8]
        LDRD     R2,R3,[SP, #+32]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R2,R2,R3
        STRD     R0,R1,[R2, #+0]
//  594       Pre_conv_GPS[Label][1]=(1-K_GPS[0][0])*Temp_conv[1]-K_GPS[0][1]*Temp_conv[3];
        MOVS     R0,#+0
        LDR.W    R1,??DataTable12_19  ;; 0x3ff00000
        LDR.W    R4,??DataTable12_20
        LDRD     R2,R3,[R4, #+0]
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDRD     R2,R3,[SP, #+24]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.W    R2,??DataTable12_20
        LDRD     R0,R1,[R2, #+8]
        LDRD     R2,R3,[SP, #+40]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDR.W    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R2,R2,R3
        STRD     R0,R1,[R2, #+8]
//  595       Pre_conv_GPS[Label][2]=(1-K_GPS[1][1])*Temp_conv[2]-K_GPS[1][0]*Temp_conv[0];
        MOVS     R0,#+0
        LDR.W    R1,??DataTable12_19  ;; 0x3ff00000
        LDR.W    R4,??DataTable12_20
        LDRD     R2,R3,[R4, #+24]
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDRD     R2,R3,[SP, #+32]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.W    R2,??DataTable12_20
        LDRD     R0,R1,[R2, #+16]
        LDRD     R2,R3,[SP, #+16]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDR.N    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R2,R2,R3
        STRD     R0,R1,[R2, #+16]
//  596       Pre_conv_GPS[Label][3]=(1-K_GPS[1][1])*Temp_conv[3]-K_GPS[1][0]*Temp_conv[1];
        MOVS     R0,#+0
        LDR.N    R1,??DataTable12_19  ;; 0x3ff00000
        LDR.N    R4,??DataTable12_20
        LDRD     R2,R3,[R4, #+24]
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDRD     R2,R3,[SP, #+40]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.N    R2,??DataTable12_20
        LDRD     R0,R1,[R2, #+16]
        LDRD     R2,R3,[SP, #+24]
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R0,R4
        MOVS     R1,R5
          CFI FunCall __aeabi_dsub
        BL       __aeabi_dsub
        LDR.N    R2,??DataTable12_15
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        LSLS     R3,R6,#+5
        ADD      R2,R2,R3
        STRD     R0,R1,[R2, #+24]
//  597 }
        ADD      SP,SP,#+60
          CFI CFA R13+36
        POP      {R4-R11,PC}      ;; return
          CFI EndBlock cfiBlock15

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11:
        DC32     0x186a0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_1:
        DC32     `longitude_scale::scale`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_2:
        DC32     0x33d6bf95

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_3:
        DC32     0x3c8efa35

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_4:
        DC32     0x3c23d70a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_5:
        DC32     0x3c366282

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_6:
        DC32     GPS_Home_Set

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_7:
        DC32     GPS_Sate_Num

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_8:
        DC32     Longitude_Origion

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_9:
        DC32     GPSData_To_XY_Home

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_10:
        DC32     Latitude_Origion

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_11:
        DC32     GPS_Home

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_12:
        DC32     Earth_Frame_To_XYZ

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_13:
        DC32     ?_3

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_14:
        DC32     GPS_Present

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable11_15:
        DC32     GPS_Save_Period_Cnt

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(3)
        DATA
        DC32 0H, 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0
//  598
//  599
//  600 #define X_Axis  0
//  601 #define Y_Axis  1

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  602 float Position_History[2][100]={0};
Position_History:
        DS8 800

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  603 float Vel_History[2][100]={0};
Vel_History:
        DS8 800

        SECTION `.data`:DATA:REORDER:NOROOT(1)
        DATA
//  604 uint16 GPS_Vel_Delay_Cnt=5;//50ms
GPS_Vel_Delay_Cnt:
        DC16 5

        SECTION `.data`:DATA:REORDER:NOROOT(1)
        DATA
//  605 uint16 GPS_Pos_Delay_Cnt=10;//100ms
GPS_Pos_Delay_Cnt:
        DC16 10

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
//  606 int16 GPS_Position_Cnt=0;
GPS_Position_Cnt:
        DS8 2

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  607 float Acce_bias[2]={0};
Acce_bias:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  608 Testime SINS_Horizontal_Delta;
SINS_Horizontal_Delta:
        DS8 16

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//  609 float Horizontal_Delta_T=0;
Horizontal_Delta_T:
        DS8 4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock16 Using cfiCommon0
          CFI Function Filter_Horizontal
        THUMB
//  610 void Filter_Horizontal(void)
//  611 {
Filter_Horizontal:
        PUSH     {R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+20
        SUB      SP,SP,#+28
          CFI CFA R13+48
//  612 int16 i=0;
        MOVS     R0,#+0
//  613 GPSData_Sort();
          CFI FunCall GPSData_Sort
        BL       GPSData_Sort
//  614 Test_Period(&SINS_Horizontal_Delta);
        LDR.N    R0,??DataTable12_22
          CFI FunCall Test_Period
        BL       Test_Period
//  615 Horizontal_Delta_T=SINS_Horizontal_Delta.Time_Delta/1000.0;
        LDR.N    R0,??DataTable12_22
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        LDR.N    R3,??DataTable12_23  ;; 0x408f4000
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable12_24
        STR      R0,[R1, #+0]
//  616
//  617 GPS_Position_Cnt++;
        LDR.N    R0,??DataTable12_25
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable12_25
        STRH     R0,[R1, #+0]
//  618 if(GPS_Position_Cnt>=2)//每10ms保存一次
        LDR.N    R0,??DataTable12_25
        LDRSH    R0,[R0, #+0]
        CMP      R0,#+2
        BLT.N    ??Filter_Horizontal_0
//  619 {
//  620 for(i=99;i>0;i--)
        MOVS     R0,#+99
        B.N      ??Filter_Horizontal_1
//  621 {
//  622  Position_History[X_Axis][i]=Position_History[X_Axis][i-1];
??Filter_Horizontal_2:
        LDR.N    R1,??DataTable12_26
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #-4]
        LDR.N    R2,??DataTable12_26
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        STR      R1,[R2, R0, LSL #+2]
//  623  Position_History[Y_Axis][i]=Position_History[Y_Axis][i-1];
        LDR.N    R1,??DataTable12_26
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #+396]
        LDR.N    R2,??DataTable12_26
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0, LSL #+2
        STR      R1,[R2, #+400]
//  624
//  625  Vel_History[X_Axis][i]=Vel_History[X_Axis][i-1];
        LDR.N    R1,??DataTable12_27
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #-4]
        LDR.N    R2,??DataTable12_27
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        STR      R1,[R2, R0, LSL #+2]
//  626  Vel_History[Y_Axis][i]=Vel_History[Y_Axis][i-1];
        LDR.N    R1,??DataTable12_27
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        ADD      R1,R1,R0, LSL #+2
        LDR      R1,[R1, #+396]
        LDR.N    R2,??DataTable12_27
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        ADD      R2,R2,R0, LSL #+2
        STR      R1,[R2, #+400]
//  627 }
        SUBS     R0,R0,#+1
??Filter_Horizontal_1:
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        CMP      R0,#+1
        BGE.N    ??Filter_Horizontal_2
//  628  Position_History[X_Axis][0]=NamelessQuad.Position[_PITCH];
        LDR.N    R0,??DataTable12_28
        LDR      R0,[R0, #+4]
        LDR.N    R1,??DataTable12_26
        STR      R0,[R1, #+0]
//  629  Position_History[Y_Axis][0]=NamelessQuad.Position[_ROLL];
        LDR.N    R0,??DataTable12_28
        LDR      R0,[R0, #+8]
        LDR.N    R1,??DataTable12_26
        STR      R0,[R1, #+400]
//  630
//  631  Vel_History[X_Axis][0]=NamelessQuad.Speed[_PITCH];
        LDR.N    R0,??DataTable12_28
        LDR      R0,[R0, #+16]
        LDR.N    R1,??DataTable12_27
        STR      R0,[R1, #+0]
//  632  Vel_History[Y_Axis][0]=NamelessQuad.Speed[_ROLL];
        LDR.N    R0,??DataTable12_28
        LDR      R0,[R0, #+20]
        LDR.N    R1,??DataTable12_27
        STR      R0,[R1, #+400]
//  633
//  634  GPS_Position_Cnt=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable12_25
        STRH     R0,[R1, #+0]
//  635 }
//  636 NamelessQuad.Acceleration[_PITCH]=FilterAfter_NamelessQuad.Acceleration[_PITCH];
??Filter_Horizontal_0:
        LDR.N    R0,??DataTable12_29
        LDR      R0,[R0, #+28]
        LDR.N    R1,??DataTable12_28
        STR      R0,[R1, #+28]
//  637 NamelessQuad.Acceleration[_ROLL]=FilterAfter_NamelessQuad.Acceleration[_ROLL];
        LDR.N    R0,??DataTable12_29
        LDR      R0,[R0, #+32]
        LDR.N    R1,??DataTable12_28
        STR      R0,[R1, #+32]
//  638
//  639
//  640
//  641 if(GPS_Update_finished_Correct_Flag==1)
        LDR.N    R0,??DataTable12_30
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Filter_Horizontal_3
//  642 {
//  643 KalmanFilter_Horizontal_GPS(Earth_Frame_To_XYZ.E,
//  644                             GPS_Speed_Resolve[1],
//  645                             Position_History[X_Axis][GPS_Pos_Delay_Cnt],
//  646                             Vel_History[X_Axis][GPS_Vel_Delay_Cnt],
//  647                             &NamelessQuad.Position[_PITCH],
//  648                             &NamelessQuad.Speed[_PITCH],
//  649                             &Origion_NamelessQuad.Acceleration[_PITCH],
//  650                             R_GPS,Q_GPS,Horizontal_Delta_T,'X');
        MOVS     R0,#+88
        STR      R0,[SP, #+24]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
        STR      R0,[SP, #+20]
        LDR.N    R0,??DataTable12_17
        STR      R0,[SP, #+16]
        LDR.N    R0,??DataTable12_16
        STR      R0,[SP, #+12]
        LDR.N    R0,??DataTable12_31
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable12_32
        STR      R0,[SP, #+4]
        LDR.N    R0,??DataTable12_33
        STR      R0,[SP, #+0]
        LDR.N    R0,??DataTable12_27
        LDR.N    R1,??DataTable12_34
        LDRH     R1,[R1, #+0]
        LDR      R3,[R0, R1, LSL #+2]
        LDR.N    R0,??DataTable12_26
        LDR.N    R1,??DataTable12_35
        LDRH     R1,[R1, #+0]
        LDR      R2,[R0, R1, LSL #+2]
        LDR.N    R0,??DataTable12_36
        LDR      R1,[R0, #+4]
        LDR.N    R0,??DataTable12_37
        LDR      R0,[R0, #+0]
          CFI FunCall KalmanFilter_Horizontal_GPS
        BL       KalmanFilter_Horizontal_GPS
//  651
//  652
//  653 KalmanFilter_Horizontal_GPS(Earth_Frame_To_XYZ.N,
//  654                             GPS_Speed_Resolve[0],
//  655                             Position_History[Y_Axis][GPS_Pos_Delay_Cnt],
//  656                             Vel_History[Y_Axis][GPS_Vel_Delay_Cnt],
//  657                             &NamelessQuad.Position[_ROLL],
//  658                             &NamelessQuad.Speed[_ROLL],
//  659                             &Origion_NamelessQuad.Acceleration[_ROLL],
//  660                             R_GPS,Q_GPS,Horizontal_Delta_T,'Y');
        MOVS     R0,#+89
        STR      R0,[SP, #+24]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
        STR      R0,[SP, #+20]
        LDR.N    R0,??DataTable12_17
        STR      R0,[SP, #+16]
        LDR.N    R0,??DataTable12_16
        STR      R0,[SP, #+12]
        LDR.N    R0,??DataTable12_38
        STR      R0,[SP, #+8]
        LDR.N    R0,??DataTable12_39
        STR      R0,[SP, #+4]
        LDR.N    R0,??DataTable12_40
        STR      R0,[SP, #+0]
        LDR.N    R0,??DataTable12_27
        LDR.N    R1,??DataTable12_34
        LDRH     R1,[R1, #+0]
        ADD      R0,R0,R1, LSL #+2
        LDR      R3,[R0, #+400]
        LDR.N    R0,??DataTable12_26
        LDR.N    R1,??DataTable12_35
        LDRH     R1,[R1, #+0]
        ADD      R0,R0,R1, LSL #+2
        LDR      R2,[R0, #+400]
        LDR.N    R0,??DataTable12_36
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable12_37
        LDR      R0,[R0, #+4]
          CFI FunCall KalmanFilter_Horizontal_GPS
        BL       KalmanFilter_Horizontal_GPS
//  661 GPS_Update_finished_Correct_Flag=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable12_30
        STRH     R0,[R1, #+0]
        B.N      ??Filter_Horizontal_4
//  662 }
//  663 else
//  664 {
//  665   NamelessQuad.Position[_PITCH] +=NamelessQuad.Speed[_PITCH]*Horizontal_Delta_T
//  666                                 +((NamelessQuad.Acceleration[_PITCH])*Horizontal_Delta_T*Horizontal_Delta_T)/2.0;
??Filter_Horizontal_3:
        LDR.N    R0,??DataTable12_28
        LDR      R0,[R0, #+4]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R6,R0
        MOVS     R7,R1
        LDR.N    R0,??DataTable12_28
        LDR      R1,[R0, #+16]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.N    R0,??DataTable12_28
        LDR      R1,[R0, #+28]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable12_24
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,R6
        MOVS     R3,R7
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable12_28
        STR      R0,[R1, #+4]
//  667   NamelessQuad.Speed[_PITCH]+=((NamelessQuad.Acceleration[_PITCH]))*Horizontal_Delta_T;
        LDR.N    R0,??DataTable12_28
        LDR      R1,[R0, #+28]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable12_28
        LDR      R1,[R1, #+16]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable12_28
        STR      R0,[R1, #+16]
//  668
//  669   NamelessQuad.Position[_ROLL] +=NamelessQuad.Speed[_ROLL]*Horizontal_Delta_T
//  670                                 +((NamelessQuad.Acceleration[_ROLL])*Horizontal_Delta_T*Horizontal_Delta_T)/2.0;
        LDR.N    R0,??DataTable12_28
        LDR      R0,[R0, #+8]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R6,R0
        MOVS     R7,R1
        LDR.N    R0,??DataTable12_28
        LDR      R1,[R0, #+20]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.N    R0,??DataTable12_28
        LDR      R1,[R0, #+32]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable12_24
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
          CFI FunCall __aeabi_ddiv
        BL       __aeabi_ddiv
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
        MOVS     R2,R6
        MOVS     R3,R7
          CFI FunCall __aeabi_dadd
        BL       __aeabi_dadd
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable12_28
        STR      R0,[R1, #+8]
//  671   NamelessQuad.Speed[_ROLL]+=(NamelessQuad.Acceleration[_ROLL])*Horizontal_Delta_T;
        LDR.N    R0,??DataTable12_28
        LDR      R1,[R0, #+32]
        LDR.N    R0,??DataTable12_24
        LDR      R0,[R0, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable12_28
        LDR      R1,[R1, #+20]
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable12_28
        STR      R0,[R1, #+20]
//  672 }
//  673
//  674 }
??Filter_Horizontal_4:
        ADD      SP,SP,#+28
          CFI CFA R13+20
        POP      {R4-R7,PC}       ;; return
          CFI EndBlock cfiBlock16

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12:
        DC32     Body_Frame_To_XYZ

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_1:
        DC32     GPS_SINS_Delay_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_2:
        DC32     X_Delta

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_3:
        DC32     Y_Delta

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_4:
        DC32     Cos_Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_5:
        DC32     Sin_Yaw

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_6:
        DC32     Pos_Err_On_Accel

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_7:
        DC32     0x3d83126f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_8:
        DC32     Accel_Correction_BF

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_9:
        DC32     Accel_Correction_EF

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_10:
        DC32     0x3ef5c28f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_11:
        DC32     0x3f99999a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_12:
        DC32     Origion_NamelessQuad

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_13:
        DC32     0x3f747ae1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_14:
        DC32     Acce_Bias

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_15:
        DC32     Pre_conv_GPS

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_16:
        DC32     R_GPS

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_17:
        DC32     Q_GPS

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_18:
        DC32     GPS_Quality

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_19:
        DC32     0x3ff00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_20:
        DC32     K_GPS

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_21:
        DC32     R_Acce_bias

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_22:
        DC32     SINS_Horizontal_Delta

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_23:
        DC32     0x408f4000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_24:
        DC32     Horizontal_Delta_T

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_25:
        DC32     GPS_Position_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_26:
        DC32     Position_History

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_27:
        DC32     Vel_History

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_28:
        DC32     NamelessQuad

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_29:
        DC32     FilterAfter_NamelessQuad

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_30:
        DC32     GPS_Update_finished_Correct_Flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_31:
        DC32     Origion_NamelessQuad+0x1C

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_32:
        DC32     NamelessQuad+0x10

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_33:
        DC32     NamelessQuad+0x4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_34:
        DC32     GPS_Vel_Delay_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_35:
        DC32     GPS_Pos_Delay_Cnt

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_36:
        DC32     GPS_Speed_Resolve

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_37:
        DC32     Earth_Frame_To_XYZ

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_38:
        DC32     Origion_NamelessQuad+0x20

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_39:
        DC32     NamelessQuad+0x14

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable12_40:
        DC32     NamelessQuad+0x8

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
// 8 235 bytes in section .bss
//   152 bytes in section .data
//    80 bytes in section .rodata
// 6 466 bytes in section .text
//
// 6 466 bytes of CODE  memory
//    80 bytes of CONST memory
// 8 387 bytes of DATA  memory
//
//Errors: none
//Warnings: none
