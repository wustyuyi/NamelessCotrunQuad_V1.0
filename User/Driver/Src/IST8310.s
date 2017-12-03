///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.60.1.11101/W32 for ARM      03/Dec/2017  17:09:19
// Copyright 1999-2016 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Src\IST8310.c
//    Command line =  
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Src\IST8310.c -D
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
//        D:\STM32_Maple\NamelessCotrunQuad_V1.5\Debug\List\IST8310.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_file_descriptor", "1"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN Cos_Pitch
        EXTERN Cos_Roll
        EXTERN DataMag
        EXTERN Mag_Offset
        EXTERN Sin_Pitch
        EXTERN Sin_Roll
        EXTERN Single_ReadI2C
        EXTERN Single_WriteI2C
        EXTERN __aeabi_d2f
        EXTERN __aeabi_dmul
        EXTERN __aeabi_f2d
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub
        EXTERN __aeabi_i2f
        EXTERN atan2

        PUBLIC Get_Mag_IST8310
        PUBLIC IST8310_Init
        PUBLIC Mag_IST8310
        
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
        
// D:\STM32_Maple\NamelessCotrunQuad_V1.5\User\Driver\Src\IST8310.c
//    1 #include "Headfile.h"
//    2 #include "IST8310.h"
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
//   27 #define MAG_REVERSE_SIDE

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function IST8310_Init
        THUMB
//   28 void IST8310_Init(void)
//   29 {
IST8310_Init:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//   30   Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x41,0x24);//开启16x内部平均
        MOVS     R2,#+36
        MOVS     R1,#+65
        MOVS     R0,#+28
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
//   31   Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x42,0xC0);//Set/Reset内部平均
        MOVS     R2,#+192
        MOVS     R1,#+66
        MOVS     R0,#+28
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
//   32 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock0
//   33 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   34 IST8310 Mag_IST8310;
Mag_IST8310:
        DS8 44

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function Get_Mag_IST8310
        THUMB
//   35 void Get_Mag_IST8310(void)
//   36 {
Get_Mag_IST8310:
        PUSH     {R1-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+24
//   37   static uint16_t IST8310_Sample_Cnt=0;
//   38   float MagTemp[3]={0};
        MOV      R0,SP
        MOVS     R1,#+0
        MOVS     R2,#+0
        MOVS     R3,#+0
        STM      R0!,{R1-R3}
        SUBS     R0,R0,#+12
//   39   IST8310_Sample_Cnt++;
        LDR.N    R0,??DataTable0
        LDRH     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable0
        STRH     R0,[R1, #+0]
//   40   if(IST8310_Sample_Cnt==1)
        LDR.N    R0,??DataTable0
        LDRH     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Get_Mag_IST8310_0
//   41   {
//   42   Single_WriteI2C(IST8310_SLAVE_ADDRESS,IST8310_REG_CNTRL1,0x01);//Single Measurement Mode
        MOVS     R2,#+1
        MOVS     R1,#+10
        MOVS     R0,#+28
          CFI FunCall Single_WriteI2C
        BL       Single_WriteI2C
        B.N      ??Get_Mag_IST8310_1
//   43   }
//   44   else if(IST8310_Sample_Cnt==3)//至少间隔6ms,此处为8ms
??Get_Mag_IST8310_0:
        LDR.N    R0,??DataTable0
        LDRH     R0,[R0, #+0]
        CMP      R0,#+3
        BNE.N    ??Get_Mag_IST8310_1
//   45   {
//   46     Mag_IST8310.Buf[0]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x03);//OUT_X_L_A
        MOVS     R1,#+3
        MOVS     R0,#+28
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        LDR.N    R1,??DataTable0_1
        STRB     R0,[R1, #+0]
//   47     Mag_IST8310.Buf[1]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x04);//OUT_X_H_A
        MOVS     R1,#+4
        MOVS     R0,#+28
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        LDR.N    R1,??DataTable0_1
        STRB     R0,[R1, #+1]
//   48     Mag_IST8310.Buf[2]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x05);//OUT_Y_L_A
        MOVS     R1,#+5
        MOVS     R0,#+28
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        LDR.N    R1,??DataTable0_1
        STRB     R0,[R1, #+2]
//   49     Mag_IST8310.Buf[3]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x06);//OUT_Y_H_A
        MOVS     R1,#+6
        MOVS     R0,#+28
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        LDR.N    R1,??DataTable0_1
        STRB     R0,[R1, #+3]
//   50     Mag_IST8310.Buf[4]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x07);//OUT_Z_L_A
        MOVS     R1,#+7
        MOVS     R0,#+28
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        LDR.N    R1,??DataTable0_1
        STRB     R0,[R1, #+4]
//   51     Mag_IST8310.Buf[5]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x08);//OUT_Z_H_A
        MOVS     R1,#+8
        MOVS     R0,#+28
          CFI FunCall Single_ReadI2C
        BL       Single_ReadI2C
        LDR.N    R1,??DataTable0_1
        STRB     R0,[R1, #+5]
//   52     /*****************合成三轴磁力计数据******************/
//   53     Mag_IST8310.Mag_Data[0]=(Mag_IST8310.Buf[1]<<8)|Mag_IST8310.Buf[0];
        LDR.N    R0,??DataTable0_1
        LDRB     R0,[R0, #+1]
        LDR.N    R1,??DataTable0_1
        LDRB     R1,[R1, #+0]
        ORRS     R0,R1,R0, LSL #+8
        LDR.N    R1,??DataTable0_1
        STRH     R0,[R1, #+6]
//   54     Mag_IST8310.Mag_Data[1]=(Mag_IST8310.Buf[3]<<8)|Mag_IST8310.Buf[2];
        LDR.N    R0,??DataTable0_1
        LDRB     R0,[R0, #+3]
        LDR.N    R1,??DataTable0_1
        LDRB     R1,[R1, #+2]
        ORRS     R0,R1,R0, LSL #+8
        LDR.N    R1,??DataTable0_1
        STRH     R0,[R1, #+8]
//   55     Mag_IST8310.Mag_Data[2]=(Mag_IST8310.Buf[5]<<8)|Mag_IST8310.Buf[4];
        LDR.N    R0,??DataTable0_1
        LDRB     R0,[R0, #+5]
        LDR.N    R1,??DataTable0_1
        LDRB     R1,[R1, #+4]
        ORRS     R0,R1,R0, LSL #+8
        LDR.N    R1,??DataTable0_1
        STRH     R0,[R1, #+10]
//   56     IST8310_Sample_Cnt=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable0
        STRH     R0,[R1, #+0]
//   57   }
//   58 #ifdef MAG_REVERSE_SIDE//重新映射磁力计三轴数据
//   59    Mag_IST8310.x = Mag_IST8310.Mag_Data[0];
??Get_Mag_IST8310_1:
        LDR.N    R0,??DataTable0_1
        LDRH     R0,[R0, #+6]
        LDR.N    R1,??DataTable0_1
        STRH     R0,[R1, #+32]
//   60    Mag_IST8310.y = -Mag_IST8310.Mag_Data[1];
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+8]
        RSBS     R0,R0,#+0
        LDR.N    R1,??DataTable0_1
        STRH     R0,[R1, #+34]
//   61    Mag_IST8310.z = Mag_IST8310.Mag_Data[2];
        LDR.N    R0,??DataTable0_1
        LDRH     R0,[R0, #+10]
        LDR.N    R1,??DataTable0_1
        STRH     R0,[R1, #+36]
//   62 #else
//   63    Mag_IST8310.x = Mag_IST8310.Mag_Data[0];
//   64    Mag_IST8310.y = Mag_IST8310.Mag_Data[1];
//   65    Mag_IST8310.z = Mag_IST8310.Mag_Data[2];
//   66 #endif
//   67    DataMag.x=Mag_IST8310.x;
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+32]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable0_2
        STR      R0,[R1, #+0]
//   68    DataMag.y=Mag_IST8310.y;
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+34]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable0_2
        STR      R0,[R1, #+4]
//   69    DataMag.z=Mag_IST8310.z;
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+36]
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable0_2
        STR      R0,[R1, #+8]
//   70 
//   71    MagTemp[0]=Mag_IST8310.x-Mag_Offset[0];
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+32]
        LDR.N    R1,??DataTable0_3
        LDRSH    R1,[R1, #+0]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        STR      R0,[SP, #+0]
//   72    MagTemp[1]=Mag_IST8310.y-Mag_Offset[1];
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+34]
        LDR.N    R1,??DataTable0_3
        LDRSH    R1,[R1, #+2]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        STR      R0,[SP, #+4]
//   73    MagTemp[2]=Mag_IST8310.z-Mag_Offset[2];
        LDR.N    R0,??DataTable0_1
        LDRSH    R0,[R0, #+36]
        LDR.N    R1,??DataTable0_3
        LDRSH    R1,[R1, #+4]
        SUBS     R0,R0,R1
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        STR      R0,[SP, #+8]
//   74 
//   75    Mag_IST8310.Mag_Data_Correct[0]=MagTemp[0];
        LDR      R0,[SP, #+0]
        LDR.N    R1,??DataTable0_1
        STR      R0,[R1, #+12]
//   76    Mag_IST8310.Mag_Data_Correct[1]=MagTemp[1];
        LDR      R0,[SP, #+4]
        LDR.N    R1,??DataTable0_1
        STR      R0,[R1, #+16]
//   77    Mag_IST8310.Mag_Data_Correct[2]=MagTemp[2];
        LDR      R0,[SP, #+8]
        LDR.N    R1,??DataTable0_1
        STR      R0,[R1, #+20]
//   78    /************磁力计倾角补偿*****************/
//   79    Mag_IST8310.thx = MagTemp[0] * Cos_Roll+ MagTemp[2] * Sin_Roll;
        LDR      R0,[SP, #+0]
        LDR.N    R1,??DataTable0_4
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR      R0,[SP, #+8]
        LDR.N    R1,??DataTable0_5
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        LDR.N    R1,??DataTable0_1
        STR      R0,[R1, #+24]
//   80    Mag_IST8310.thy = MagTemp[0] * Sin_Pitch*Sin_Roll
//   81                     +MagTemp[1] * Cos_Pitch
//   82                     -MagTemp[2] * Cos_Roll*Sin_Pitch;
        LDR      R0,[SP, #+0]
        LDR.N    R1,??DataTable0_6
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable0_5
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R4,R0
        LDR      R0,[SP, #+4]
        LDR.N    R1,??DataTable0_7
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fadd
        BL       __aeabi_fadd
        MOVS     R4,R0
        LDR      R0,[SP, #+8]
        LDR.N    R1,??DataTable0_4
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable0_6
        LDR      R1,[R1, #+0]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R4
          CFI FunCall __aeabi_fsub
        BL       __aeabi_fsub
        LDR.N    R1,??DataTable0_1
        STR      R0,[R1, #+28]
//   83    /***********反正切得到磁力计观测角度*********/
//   84    Mag_IST8310.Angle_Mag=atan2(Mag_IST8310.thx,Mag_IST8310.thy)*57.296;
        LDR.N    R0,??DataTable0_1
        LDR      R0,[R0, #+28]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,R0
        MOVS     R3,R1
        MOVS     R4,R2
        MOVS     R5,R3
        LDR.N    R0,??DataTable0_1
        LDR      R0,[R0, #+24]
          CFI FunCall __aeabi_f2d
        BL       __aeabi_f2d
        MOVS     R2,R4
        MOVS     R3,R5
          CFI FunCall atan2
        BL       atan2
        LDR.N    R2,??DataTable0_8  ;; 0x53f7ced9
        LDR.N    R3,??DataTable0_9  ;; 0x404ca5e3
          CFI FunCall __aeabi_dmul
        BL       __aeabi_dmul
          CFI FunCall __aeabi_d2f
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable0_1
        STR      R0,[R1, #+40]
//   85 }
        POP      {R0-R2,R4,R5,PC}  ;; return
          CFI EndBlock cfiBlock1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0:
        DC32     `Get_Mag_IST8310::IST8310_Sample_Cnt`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_1:
        DC32     Mag_IST8310

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_2:
        DC32     DataMag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_3:
        DC32     Mag_Offset

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_4:
        DC32     Cos_Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_5:
        DC32     Sin_Roll

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_6:
        DC32     Sin_Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_7:
        DC32     Cos_Pitch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_8:
        DC32     0x53f7ced9

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable0_9:
        DC32     0x404ca5e3

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
        DATA
`Get_Mag_IST8310::IST8310_Sample_Cnt`:
        DS8 2

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
        DATA
        DC32 0H
        DC8 0, 0, 0, 0, 0, 0, 0, 0

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   86 
// 
//  46 bytes in section .bss
//  12 bytes in section .rodata
// 544 bytes in section .text
// 
// 544 bytes of CODE  memory
//  12 bytes of CONST memory
//  46 bytes of DATA  memory
//
//Errors: none
//Warnings: none
