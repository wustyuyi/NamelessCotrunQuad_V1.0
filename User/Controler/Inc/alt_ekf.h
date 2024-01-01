/*
*	ekf for altitude
* states: pos vel acc_bias
* input ：acc
* measurement： -baro_alt -gps_alt gps_veld
* direction: down is positive
* by -----
* 20171219
*/
#ifndef  __ALT_EKF_H
#define  __ALT_EKF_H

#define VEKF_STATE_DIM 3						//pos vel acc_bias
#define VEKF_MEASUREMENT_NUM 3 			//-baro -gps_alt gps_veld		down

/*
eg:180ug/vHz => s=180*9.80665e-6*v1000=0.05578m/s^1.5  sigma^2=0.003111696m^2/s^3
*/
#define VEKF_U_ACC_SIGMA 		0.033f
#define VEKF_U_ACC_BIAS_SIGMA		3.1e-4f

#define VEKF_R_BARO_SIGMA 2.f				//Measurement noise SD

//need to tune
#define VEKF_R_GPSP_SIGMA 50.f      //
#define VEKF_R_GPSV_SIGMA 0.5f			//Initial position uncertainty


typedef struct
{
bool update;
float alt;
Vector3f ned;
Vector3f vel;
}EKF_SINS_Update;

struct vkef_def
{
	float P[VEKF_STATE_DIM][VEKF_STATE_DIM];
	float Q[VEKF_STATE_DIM][VEKF_STATE_DIM];
	float R[VEKF_MEASUREMENT_NUM];
	float F[VEKF_STATE_DIM][VEKF_STATE_DIM];
	float K[VEKF_STATE_DIM];	//for simple
	float Z;
	//state vector
	float X[VEKF_STATE_DIM];
	//measurement vector
};

void vekfinit(float alt);
void vekfupdate(float acc, float dt);

#endif	// ALT_EKF_H
