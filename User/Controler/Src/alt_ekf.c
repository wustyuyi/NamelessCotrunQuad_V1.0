/*
*ekf for altitude
* states: pos vel acc_bias
* direction: down is positive
* by -----
* 20171219
* 75行是气压更行标记，101行清除标记 77行是获取气压高度值（测量值）
* 104行是GPS更新标记，146行清除标记 107行、127行是过去gps垂直方向高度，速度测量值
* 该算法中所有变量符号均为向下为正方向，使用需要注意
*/
#include "Headfile.h"
#include "alt_ekf.h"
struct vkef_def vekf = {0};
EKF_SINS_Update baro,gps;
void vekfinit(float alt)
{
	struct vkef_def *ekf = &vekf;
	ekf->X[0] = -alt;
	ekf->X[1] = 0;
	ekf->X[2] = 0;
	ekf->P[0][0] = 5.f;	ekf->P[0][1] = 0.f;	ekf->P[0][2] = 0.f;
	ekf->P[1][0] = 0.f;	ekf->P[1][1] = 2.f;	ekf->P[1][2] = 0.f;
	ekf->P[2][0] = 0.f;	ekf->P[2][1] = 0.f;	ekf->P[2][2] = 0.01f;
}


void vekfupdate(float acc, float dt)
{
	struct vkef_def *ekf = &vekf;
	float (*F)[VEKF_STATE_DIM] = ekf->F, (*P)[VEKF_STATE_DIM] = ekf->P, (*Q)[VEKF_STATE_DIM] = ekf->Q;
	float *X = ekf->X, *R = ekf->R, *K = ekf->K, Z = ekf->Z;
	float tmP[VEKF_STATE_DIM][VEKF_STATE_DIM] = {0};
	float Y;
	float accel;

	float Sa = (float)VEKF_U_ACC_SIGMA * (float)VEKF_U_ACC_SIGMA;
	float Sab = (float)VEKF_U_ACC_BIAS_SIGMA * (float)VEKF_U_ACC_BIAS_SIGMA;

//	static float posk1,velk1,acck1;
//	float pos,vel,acc;
	if(dt < 1e-3f || dt > 0.1f)
		return;

//update ekf
//	pos = X[0];		vel = X[1];
//	acc = 0.5f * (acck1 + accel);
//	vel += acc * dt;
//	pos += 0.5f * (velk1 + vel) * dt + 0.5f * acc * dt * dt;
//	posk1 = pos;	velk1 = vel;	acck1 = accel;
	accel = acc - X[2];

	X[0] += X[1] * dt + 0.5f * accel * dt * dt;
	X[1] += accel * dt;
	//X[2] = X[2];

	F[0][0] = 1.f;	F[0][1] = dt;	F[0][2] = -dt*dt;
	F[1][0] = 0;	F[1][1] = 1.f;	F[1][2] = -dt;
	F[2][0] = 0;	F[2][1] = 0;	F[2][2] = 1.f;

	Q[0][0] = 0.5f * dt * dt * Sa;	Q[0][1] = 0;	        Q[0][2] = 0;
	Q[1][0] = 0;			Q[1][1] = dt * Sa;	Q[1][2] = 0;
	Q[2][0] = 0;			Q[2][1] = 0;		Q[2][2] = Sab;

	//P(k|k-1) = FP(k-1|k-1)F'+Q
	tmP[0][0] = P[0][0] + dt * (P[0][1] + P[1][0] + dt * P[1][1]);		tmP[0][1] = P[0][1] + dt * (P[1][1] - P[0][2] - dt * P[1][2]);	tmP[0][2] = P[0][2] + dt * P[1][2];
	tmP[1][0] = P[1][0] + dt * (-P[2][0] + P[1][1] - dt * P[2][1]);		tmP[1][1] = P[1][1] + dt * (-P[2][1] - P[1][2] + dt * P[2][2]);	tmP[1][2] = P[1][2] - dt * P[2][2];
	tmP[2][0] = P[2][0] + dt * P[2][1];					tmP[2][1] = P[2][1] - dt * P[2][2];	                        tmP[2][2] = P[2][2];

	P[0][0]	=tmP[0][0] + Q[0][0];	P[0][1]	=tmP[0][1] + Q[0][1];	P[0][2]	=tmP[0][2] + Q[0][2];
	P[1][0]	=tmP[1][0] + Q[1][0];	P[1][1]	=tmP[1][1] + Q[1][1];	P[1][2]	=tmP[1][2] + Q[1][2];
	P[2][0]	=tmP[2][0] + Q[2][0];	P[2][1]	=tmP[2][1] + Q[2][1];	P[2][2]	=tmP[2][2] + Q[2][2];

	if(baro.update)
	{
		Z = -baro.alt;
		Y = Z - X[0];
		R[0] = (float)VEKF_R_BARO_SIGMA * (float)VEKF_R_BARO_SIGMA;

		//H = [1 0 0]
		//K = PH'/(HPH'+R)
		K[0] = P[0][0] / (P[0][0]+ R[0]);
		K[1] = P[1][0] / (P[0][0]+ R[0]);
		K[2] = P[2][0] / (P[0][0]+ R[0]);


		X[0] += K[0] * Y;
		X[1] += K[1] * Y;
		X[2] += K[2] * Y;

		//P = (I - KH)P = P - KHP
		tmP[0][0] = P[0][0] - K[0]*P[0][0];tmP[0][1] = P[0][1] - K[0]*P[0][1];tmP[0][2] = P[0][2] - K[0]*P[0][2];
		tmP[1][0] = P[1][0] - K[1]*P[0][0];tmP[1][1] = P[1][1] - K[1]*P[0][1];tmP[1][2] = P[1][2] - K[1]*P[0][2];
		tmP[2][0] = P[2][0] - K[2]*P[0][0];tmP[2][1] = P[2][1] - K[2]*P[0][1];tmP[2][2] = P[2][2] - K[2]*P[0][2];

		P[0][0]	=tmP[0][0];	P[0][1]	=tmP[0][1];	P[0][2]	=tmP[0][2];
		P[1][0]	=tmP[1][0];	P[1][1]	=tmP[1][1];	P[1][2]	=tmP[1][2];
		P[2][0]	=tmP[2][0];	P[2][1]	=tmP[2][1];	P[2][2]	=tmP[2][2];

		baro.update = false;
	}

	if(gps.update)
	{
		//position correct
		Z = gps.ned.z;
		Y = Z - X[0];
		R[1] = (float)VEKF_R_GPSP_SIGMA * (float)VEKF_R_GPSP_SIGMA;

		//H = [1 0 0]
		//K = PH'/(HPH'+R)
		K[0] = P[0][0] / (P[0][0]+ R[1]);
		K[1] = P[1][0] / (P[0][0]+ R[1]);
		K[2] = P[2][0] / (P[0][0]+ R[1]);

		X[0] += K[0] * Y;
		X[1] += K[1] * Y;
		X[2] += K[2] * Y;

		//P = (I - KH)P = P - KHP
		tmP[0][0] = P[0][0] - K[0]*P[0][0];	tmP[0][1] = P[0][1] - K[0]*P[0][1];	tmP[0][2] = P[0][2] - K[0]*P[0][2];
		tmP[1][0] = P[1][0] - K[1]*P[0][0];	tmP[1][1] = P[1][1] - K[1]*P[0][1];	tmP[1][2] = P[1][2] - K[1]*P[0][2];
		tmP[2][0] = P[2][0] - K[2]*P[0][0];	tmP[2][1] = P[2][1] - K[2]*P[0][1];	tmP[2][2] = P[2][2] - K[2]*P[0][2];

		//velocity correct
		Z = gps.vel.z;//
		Y = Z - X[1];
		R[2] = (float)VEKF_R_GPSV_SIGMA * (float)VEKF_R_GPSV_SIGMA;

		//H = [0 1 0]
		//K = PH'/(HPH'+R)
		K[0] = P[0][1] / (P[1][1]+ R[2]);
		K[1] = P[1][1] / (P[1][1]+ R[2]);
		K[2] = P[2][1] / (P[1][1]+ R[2]);

		X[0] += K[0] * Y;
		X[1] += K[1] * Y;
		X[2] += K[2] * Y;

		//P = (I - KH)P = P - KHP
		P[0][0] = tmP[0][0] - K[0]*tmP[1][0];	P[0][1] = tmP[0][1] - K[0]*tmP[1][1];	P[0][2] = tmP[0][2] - K[0]*tmP[1][2];
		P[1][0] = tmP[1][0] - K[1]*tmP[1][0];	P[1][1] = tmP[1][1] - K[1]*tmP[1][1];	P[1][2] = tmP[1][2] - K[1]*tmP[1][2];
		P[2][0] = tmP[2][0] - K[2]*tmP[1][0];	P[2][1] = tmP[2][1] - K[2]*tmP[1][1];	P[2][2] = tmP[2][2] - K[2]*tmP[1][2];

		gps.update = false;
	}

//	data[0] = baro.alt*100;
//	data[1] = -ekf->X[0]*100;
//	data[2] = -ekf->X[1]*100;
//	data[3] = -acc*100;
//	data[4] = -accel*100;
}
