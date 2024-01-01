#include "up_flow.h"

#define LIMIT( x,min,max ) ( ((x) < (min)) ? (min) : ( ((x) > (max))? (max) :(x) ) )
#define LPF_1_(hz,t,in,out) ((out) += ( 1 / ( 1 + 1 / ( (hz) *3.14f *(t) ) ) )*( (in) - (out) )) //һ�׵�ͨ�˲�
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0)?(safe_value) : ((numerator)/(denominator)) )
void filter_1(float base_hz,float gain_hz,float dT,float in,_filter_1_st *f1)//��̬�����˲���ֹƵ�ʵ�һ���˲�
{
  LPF_1_(gain_hz,dT,(in - f1->out),f1->a); //��ͨ��ı仯��
  f1->b = my_pow(in - f1->out); //��һ����ƽ������
  f1->e_nr = LIMIT(safe_div(my_pow(f1->a),((f1->b) + my_pow(f1->a)),0),0,1);
  //�仯������Ч�ʣ� LIMIT ������������ 0-1 ֮�䣬 safe_div Ϊ��ȫ����
  LPF_1_(base_hz *f1->e_nr,dT,in,f1->out); //��ͨ����
} 
_xyz_f_st heading_coordinate_acc;
_xyz_f_st heading_coordinate_speed_fus;
_xyz_f_st heading_coordinate_speed_err_i;
float fx_gyro_fix,fy_gyro_fix;
float fx_o,fy_o;
float f_out_x,f_out_y;
float gyro_lpf_x,gyro_lpf_y;
_filter_1_st f1_fx;
_filter_1_st f1_fy;
float f1_b,f1_g;
//flow_dat.qual�� x�� y �����������Ч�� 255�� x ��Ч�� 2�� y ��Ч�� 1�� ����Ч�� 0��
float gyro_x,gyro_y;
void flow_fusion(float dT,float fx,float fy,s32 flow_height,u8 pos_hold)
{
  float flow_t1 = 1.0,flow_t2 = 1.0;
  fx_o = fx *10 *flow_height; //fx�� fy��rad/s�� -->flow speed (mm/s)
  fy_o = fy *10 *flow_height;
  u32 use_height=100;
  if(flow_height<200) //input height (cm/s)
  {
    use_height = 100;
  } 
  else if(flow_height<300)
  {
    use_height = 150;
  } 
  else if(flow_height<400)
  {
    use_height = 200;
  } 
  else if(flow_height<500)
  {
    use_height = 250;
  } 
  else if(flow_height<600)
  {
    use_height = 300;
  } 
  else if(flow_height<1000)
  {
    use_height = 350;
  } 
  else
  {
    use_height = 400;
  } i
    f( pos_hold == 1) //in pose hold mode
    {
      gyro_y = (((s16)sensor.Gyro_deg.y/2 )*2 ); //degree per second
      gyro_x = (((s16)sensor.Gyro_deg.x/2 )*2 );
      LPF_1_(3.0f,dT,gyro_y,gyro_lpf_y); //gyro low pass filter
      (delay) for fitting flow data()
        LPF_1_(3.0f,dT,gyro_x,gyro_lpf_x);
       fx_gyro_fix = ((fx + LIMIT(((gyro_lpf_y)/57.3f),-flow_t1,flow_t1))
                      *10 *use_height ) ; //rotation compensation
       fy_gyro_fix = ((fy - LIMIT(((gyro_lpf_x)/57.3f),-flow_t2,flow_t2))
                      *10 *use_height ) ;
       vec_3d_transition(&imu_data.z_vec, &imu_data.a_acc,
                         &heading_coordinate_acc); //��������ϵ�¼��ٶȵ�ˮƽ���庽������ϵ(������
       ˮƽ���ã� û��ƫ���ǣ�
         //���ּ��ٶ������û��ƫ�������Ӱ��)
         f1_fx.out += ((s32)heading_coordinate_acc.x/10 *10 ) *dT;
       //integrated acceleration for speed
       f1_fy.out += ((s32)heading_coordinate_acc.y/10 *10 ) *dT;
       f1_g = 2.5f;
       if(flow_dat.qual <3) //����Ч������ʱ
       {
         f1_b = 0.5f;
       } e
         lse
         {
           if(f1_b<1.2f)
           {
             f1_b += 0.02f;
           }
         } 
       filter_1(f1_b,f1_g,dT,fx_gyro_fix,&f1_fx); //flow_data with acc
       integrated data complementary filtering
         filter_1(f1_b,f1_g,dT,fy_gyro_fix,&f1_fy);
       heading_coordinate_speed_fus.x = f1_fx.out; //�ں��ٶ�
       heading_coordinate_speed_fus.y = f1_fy.out;
       f_out_x = heading_coordinate_speed_fus.x + 0.1f
         *heading_coordinate_speed_err_i.x; //�ں��ٶȶ��������� ����������
       f_out_y = heading_coordinate_speed_fus.y + 0.1f
         *heading_coordinate_speed_err_i.y;
       heading_coordinate_speed_err_i.x += (fx_gyro_fix - f_out_x) *dT;
       heading_coordinate_speed_err_i.y += (fy_gyro_fix - f_out_y) *dT;
    } 
}