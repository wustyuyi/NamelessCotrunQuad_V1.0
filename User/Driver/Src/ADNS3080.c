#include "Headfile.h"
#include "ADNS3080.h"
#include "srom.h"

#define H  200 //����
void ADNS_3080_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //�������
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void ADNS3080_reset(void)  //ADNS3080 ��λ���ߣ�
{
  GPIO_ResetBits(GPIOC,GPIO_Pin_7); 
  delay_ms(5);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  delay_ms(5);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);//�����ź�
}

void Write_srom(void)
{
 int i;
 ON_CS(); 
 writr_register(0x20,0x44);
 delay_us(51);
 writr_register(0x23,0x07);
  delay_us(51);
 writr_register(0x24,0x88);
 delay_us(51);
  OFF_CS();  //ͻ��_дģʽ
  delay_us(340);//�ȴ�����1֡ʱ��
  ON_CS(); 
  writr_register(SROM_Enable,0x18);
  OFF_CS();  //ͻ��_дģʽ
 delay_us(41);//  >40us
  ON_CS();
  for(i=0;i<=1985;i++)
  {
     writr_register(0x60,SROM[i]);
     delay_us(11);// >10us
  }
 OFF_CS();
 delay_us(105);	//>104us
}
void ADNS3080_Init(void)
{	  
  ADNS_3080_GPIO_Configuration();
  SPI_init(128);  //�ı��ٶȣ�2��256��Ƶ��
  ADNS3080_reset(); //��λ
  GPIO_SetBits(GPIOC,GPIO_Pin_6);  //����NPD,��˯��
  delay_ms(10);
  Write_srom();
  ADNS_Configuration();
 //printf("%d   Data is Okay\n",read_register(0x1f));	 //�鿴�Ƿ����سɹ�
}

void ADNS_Configuration(void)
{
	 ON_CS(); 
	 writr_register(Configuration_bits,0x10);		//���÷ֱ��� 1600	 //��Bit 4Ϊ0����Ϊ400��ÿӢ��
	 delay_ms(3);
	 writr_register(Extended_Config,0x01);
	 delay_ms(3);
 if(read_busy()!=1)
 {  							      //��Ϊ3000֡ÿ��
    OFF_CS();  //ͻ��_дģʽ
	delay_ms(2);
	ON_CS();	
 	SPI_SendReceive(Frame_Period_Max_Bound_Lower+0x80);	//����֡�� //��д��λ��д��λ
    SPI_SendReceive(0x40); //   C0 5000֡��	   
	SPI_SendReceive(Frame_Period_Max_Bound_Upper+0x80);
	SPI_SendReceive(0x1f);	 // 12
 } 
 clear_motion();
 OFF_CS();
}

u8 read_register(u8 adress)
{
u8 temp;
ON_CS();
temp=SPI_SendReceive(adress+0x00);	//��
delay_us(75);
temp=SPI_SendReceive(0xff);	//�ṩʱ���ź�_��
OFF_CS();
return temp;
}

void writr_register(u8 adress,u8 vlue)
{
ON_CS();
 SPI_SendReceive(adress+0x80);
 SPI_SendReceive(vlue);
OFF_CS();
delay_us(51);
}

u8 read_busy(void)//д֡�ʵ���æ  ==1æ
{
u8 temp;
ON_CS();
temp=SPI_SendReceive(Extended_Config+0x00);
delay_us(75);
temp=SPI_SendReceive(0xff);
temp&=0x80;
OFF_CS();
return temp;
}

void clear_motion(void)
{
ON_CS();
 SPI_SendReceive(Motion_Clear+0x80);
 SPI_SendReceive(0xff);	//���X Y����
OFF_CS();
}


u16 read_zhenlv(void) //��֡��
{  
  u16 Frame_Period_Max_Bound_Lower1,Frame_Period_Max_Bound_Upper1;
  ON_CS();
  Frame_Period_Max_Bound_Upper1=SPI_SendReceive(Frame_Period_Uppe+0x00);
  Frame_Period_Max_Bound_Upper1=SPI_SendReceive(0xff);//���ո�λ��֡��
  delay_ms(5);
  Frame_Period_Max_Bound_Lower1=SPI_SendReceive(Frame_Period_Lower+0x00);
  Frame_Period_Max_Bound_Lower1=SPI_SendReceive(0xff); //���յ�λ��֡��
  OFF_CS();
  return ((Frame_Period_Max_Bound_Upper1 << 8) | Frame_Period_Max_Bound_Lower1);
}
 

float SumX,SumY;
uint8 Move_Flag=0;
float sum_x,sum_y;
void Read_Data_burst(void)
{


  unsigned char move=0;
  int  x=0;
  int  y=0;
  ON_CS();
  SPI_SendReceive(0x50);   
  delay_us(100);//75
  move=SPI_SendReceive(0xFF);
  x=SPI_SendReceive(0xFF);
  y=SPI_SendReceive(0xFF);
  if(x&0x80)
    {
  //x�Ķ�����ת��	
    x -= 1;
    x = ~x;	
    x=(-1)*x;
    x-=256;
    }
  if(y&0x80)
    {
    //y�Ķ�����ת��	
    y -= 1;
    y = ~y;	
    y=(-1)*y;
    y-=256;
    } 
	SumX=SumX+x;    //�ۼ�X������ƶ�����
	SumY=SumY+y;	//�ۼ�Y������ƶ�����
	OFF_CS();
	delay_us(4);
	OFF_CS();
        sum_x=(25.4*(float)SumX *H)/(12*1600);//����=d_x*(25.4/1600)*n   ����n=���:���=8����:�ﳤ
        sum_y=(25.4*(float)SumY *H)/(12*1600);
 
if(move&0x10!=1)	
if(move&0x80) Move_Flag=1;//printf("X:%f,Y:%f\n",sum_x,sum_y);
else Move_Flag=0;
}

float  read_average_pixel(void)	  //��ƽ������
{
  float temp;
  ON_CS();
  temp=SPI_SendReceive(Pixel_Sum);
  delay_us(76);
  temp=SPI_SendReceive(0xff);
  temp=temp*256/900;
  OFF_CS();
  return temp;
}

void read_pixel(void)
{
   u8 i,j ,regValue, pixelValue,test=1;	 
  writr_register(Frame_Capture,0x83); 
  delay_us(1010);//�ȴ�3֡ (1/3000)*1000000*3+10 =1010us
  //��ʾ����  30*30=900
  for(i=0;i<30;i++)//��
  {
	  for(j=0;j<30;j++) //�� 
	  {
	   regValue=read_register(Frame_Capture);  //������
	    if( test && ((regValue&0x40)==0)) //�Ҳ�����һ������
		{
	 printf("Read pixel fail");		    
		}
						    test=0;
	                        pixelValue =(regValue<<2);
							//while(!(USART1->SR&(1<<6)));
	  						//USART1->DR=pixelValue;                               
	                        delay_us(50);
	  }
   }
  ADNS3080_reset();//��������
}



    
#define CMD_Image    1
uint8 cmdh[2] = {CMD_Image, ~CMD_Image};   
uint8 cmdl[2] = {~CMD_Image, CMD_Image};

void read_pixel_burst(void)//������ͼ��
{
int i,j;
writr_register(Frame_Capture,0x83); 
delay_us(1010);//�ȴ�3֡(1/3000)*1000000*3+10=1010us//��ʼburst��
ON_CS();
SPI_SendReceive(0x40);   
delay_us(75);
//UART1_Send(cmdh[0]);
//UART1_Send(cmdh[1]);
for(i=0;i<30;i++)
{
	for(j=0;j<30;j++)
	{
	//while(!(USART1->SR&(1<<6)));
	//USART1->DR=
          //UART1_Send((SPI_SendReceive(0xFF)<<2)); 
    //delay_us(10);
	}
}

//UART1_Send(cmdl[0]);
//UART1_Send(cmdl[1]); 

OFF_CS();
delay_us(4);
OFF_CS();            
}
