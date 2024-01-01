/* Copyright (c)  2018-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               公司官网:www.nameless.tech
*               修改日期:2019/4/12
*               版本：躺赢者——CarryPilot_V1.0
*               版权所有，盗版必究。
*               Copyright(C) 2017-2025 武汉无名创新科技有限公司 
*               All rights reserved
*               重要提示：
*               正常淘宝咸鱼转手的飞控、赠送朋友、传给学弟的都可以进售后群学习交流，
*               不得直接在网上销售无名创新资料，无名创新代码有声明版权，他人不得将
*               资料代码传网上供他人下载，不得以谋利为目的销售资料代码，发现有此操
*               作者，公司会提前告知，请1天内及时处理，否则你的学校、单位、姓名、电
*               话、地址信息会被贴出在公司官网、官方微信公众平台、官方技术博客、知乎
*               专栏以及淘宝店铺首页予以公示公告，此种所作所为，会成为个人污点，影响
*               升学、找工作、社会声誉、很快就很在无人机界出名，后果很严重。
*               因此行为给公司造成重大损失者，会以法律途径解决，感谢您的合作，谢谢！！！
----------------------------------------------------------------------------------------------------------------------*/
#ifndef __QMC5883_H
#define __QMC5883_H

#define QMC5883L_DATA_READ_X_LSB	0x00
#define QMC5883L_DATA_READ_X_MSB	0x01
#define QMC5883L_DATA_READ_Y_LSB	0x02
#define QMC5883L_DATA_READ_Y_MSB	0x03
#define QMC5883L_DATA_READ_Z_LSB	0x04
#define QMC5883L_DATA_READ_Z_MSB	0x05
#define QMC5883L_TEMP_READ_LSB		0x07
#define QMC5883L_TEMP_READ_MSB		0x08 
#define QMC5883L_STATUS		        0x06 // DOR | OVL | DRDY
#define QMC5883L_CONFIG_1					0x09 // OSR | RNG | ODR | MODE
#define QMC5883L_CONFIG_2					0x0A // SOFT_RST | ROL_PNT | INT_ENB
#define QMC5883L_CONFIG_3					0x0B // SET/RESET Period FBR [7:0]
#define QMC5883L_ID								0x0D



#define QMC5883L_WR_ADDRESS  				(0x0D<<1)
#define QMC5883L_RD_ADDRESS  				(0x0D<<1)

#ifndef M_PI 
#define M_PI 3.14159265358979323846264338327950288f 
#endif 

#define QMC5883L_SCALE_FACTOR 		0.732421875f
#define QMC5883L_CONVERT_GAUSS_2G 	12000.0f
#define QMC5883L_CONVERT_GAUSS_8G 	3000.0f
#define QMC5883L_CONVERT_MICROTESLA 	100
#define QMC5883L_DECLINATION_ANGLE	93.67/1000  // radian, Tekirdag/Turkey

typedef enum STATUS_VARIABLES
{
NORMAL,
NO_NEW_DATA,
NEW_DATA_IS_READY,
DATA_OVERFLOW,
DATA_SKIPPED_FOR_READING
}_qmc5883l_status;

typedef enum MODE_VARIABLES
{
MODE_CONTROL_STANDBY=0x00,
MODE_CONTROL_CONTINUOUS=0x01
}_qmc5883l_MODE;

typedef enum ODR_VARIABLES
{
OUTPUT_DATA_RATE_10HZ=0x00,
OUTPUT_DATA_RATE_50HZ=0x04,
OUTPUT_DATA_RATE_100HZ=0x08,
OUTPUT_DATA_RATE_200HZ=0x0C
}_qmc5883l_ODR;

typedef enum RNG_VARIABLES
{
FULL_SCALE_2G=0x00,
FULL_SCALE_8G=0x10
}_qmc5883l_RNG;


typedef enum OSR_VARIABLES
{
OVER_SAMPLE_RATIO_512=0x00,
OVER_SAMPLE_RATIO_256=0x40,
OVER_SAMPLE_RATIO_128=0x80,
OVER_SAMPLE_RATIO_64=0xC0
}_qmc5883l_OSR;



typedef enum INTTERRUPT_VARIABLES
{
INTERRUPT_DISABLE,INTERRUPT_ENABLE
}_qmc5883l_INT;

static float Xmin,Xmax,Ymin,Ymax;
static int16_t X,Y,Z;

extern uint8_t 					QMC5883L_Read_Reg(uint8_t reg);
extern void 						QMC5883L_Write_Reg(uint8_t reg, uint8_t data);
extern _qmc5883l_status QMC5883L_DataIsReady(void);
extern _qmc5883l_status QMC5883L_DataIsOverflow(void);
extern _qmc5883l_status QMC5883L_DataIsSkipped(void);
extern int16_t 					QMC5883L_Read_Temperature(void);
extern void 						QMC5883L_Read_Data(int16_t *MagX,int16_t *MagY,int16_t *MagZ);
extern void 						QMC5883L_Initialize(_qmc5883l_MODE MODE,_qmc5883l_ODR ODR,_qmc5883l_RNG RNG,_qmc5883l_OSR OSR);
extern void							QMC5883L_Reset(void);
extern void 						QMC5883L_InterruptConfig(_qmc5883l_INT INT);
extern void 		        QMC5883L_ResetCalibration(void); 
extern float 		        QMC5883L_Heading(int16_t Xraw,int16_t Yraw,int16_t Zraw);
extern void 		        QMC5883L_Scale(int16_t *X,int16_t *Y,int16_t *Z);

void QMC5883L_StateMachine(void);
void QMC5883L_Init(void);
#endif /*_QMC5883L_H_*/
