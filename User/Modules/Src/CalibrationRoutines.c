/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
* calibrationRoutines.cpp
*
*  Created on: 30/set/2013
*      Author: Murtas Matteo
*/
/****************************************************************************
*
*   Copyright (C) 2012 PX4 Development Team. All rights reserved.
*   Author: Lorenz Meier <lm@inf.ethz.ch>
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name PX4 nor the names of its contributors may be
*    used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
#include "CalibrationRoutines.h"
#include <math.h>
#include <string.h>
int sphere_fit_least_squares(const float x[], const float y[], const float z[],
                             unsigned int size, unsigned int max_iterations, float delta, float *sphere_x, float *sphere_y, float *sphere_z, float *sphere_radius)
{
  
  float x_sumplain = 0.0f;
  float x_sumsq = 0.0f;
  float x_sumcube = 0.0f;
  
  float y_sumplain = 0.0f;
  float y_sumsq = 0.0f;
  float y_sumcube = 0.0f;
  
  float z_sumplain = 0.0f;
  float z_sumsq = 0.0f;
  float z_sumcube = 0.0f;
  
  float xy_sum = 0.0f;
  float xz_sum = 0.0f;
  float yz_sum = 0.0f;
  
  float x2y_sum = 0.0f;
  float x2z_sum = 0.0f;
  float y2x_sum = 0.0f;
  float y2z_sum = 0.0f;
  float z2x_sum = 0.0f;
  float z2y_sum = 0.0f;
  
  for (unsigned int i = 0; i < size; i++) {
    
    float x2 = x[i] * x[i];
    float y2 = y[i] * y[i];
    float z2 = z[i] * z[i];
    
    x_sumplain += x[i];
    x_sumsq += x2;
    x_sumcube += x2 * x[i];
    
    y_sumplain += y[i];
    y_sumsq += y2;
    y_sumcube += y2 * y[i];
    
    z_sumplain += z[i];
    z_sumsq += z2;
    z_sumcube += z2 * z[i];
    
    xy_sum += x[i] * y[i];
    xz_sum += x[i] * z[i];
    yz_sum += y[i] * z[i];
    
    x2y_sum += x2 * y[i];
    x2z_sum += x2 * z[i];
    
    y2x_sum += y2 * x[i];
    y2z_sum += y2 * z[i];
    
    z2x_sum += z2 * x[i];
    z2y_sum += z2 * y[i];
  }
  
  //
  //Least Squares Fit a sphere A,B,C with radius squared Rsq to 3D data
  //
  //    P is a structure that has been computed with the data earlier.
  //    P.npoints is the number of elements; the length of X,Y,Z are identical.
  //    P's members are logically named.
  //
  //    X[n] is the x component of point n
  //    Y[n] is the y component of point n
  //    Z[n] is the z component of point n
  //
  //    A is the x coordiante of the sphere
  //    B is the y coordiante of the sphere
  //    C is the z coordiante of the sphere
  //    Rsq is the radius squared of the sphere.
  //
  //This method should converge; maybe 5-100 iterations or more.
  //
  float x_sum = x_sumplain / size;        //sum( X[n] )
  float x_sum2 = x_sumsq / size;    //sum( X[n]^2 )
  float x_sum3 = x_sumcube / size;    //sum( X[n]^3 )
  float y_sum = y_sumplain / size;        //sum( Y[n] )
  float y_sum2 = y_sumsq / size;    //sum( Y[n]^2 )
  float y_sum3 = y_sumcube / size;    //sum( Y[n]^3 )
  float z_sum = z_sumplain / size;        //sum( Z[n] )
  float z_sum2 = z_sumsq / size;    //sum( Z[n]^2 )
  float z_sum3 = z_sumcube / size;    //sum( Z[n]^3 )
  
  float XY = xy_sum / size;        //sum( X[n] * Y[n] )
  float XZ = xz_sum / size;        //sum( X[n] * Z[n] )
  float YZ = yz_sum / size;        //sum( Y[n] * Z[n] )
  float X2Y = x2y_sum / size;    //sum( X[n]^2 * Y[n] )
  float X2Z = x2z_sum / size;    //sum( X[n]^2 * Z[n] )
  float Y2X = y2x_sum / size;    //sum( Y[n]^2 * X[n] )
  float Y2Z = y2z_sum / size;    //sum( Y[n]^2 * Z[n] )
  float Z2X = z2x_sum / size;    //sum( Z[n]^2 * X[n] )
  float Z2Y = z2y_sum / size;    //sum( Z[n]^2 * Y[n] )
  
  //Reduction of multiplications
  float F0 = x_sum2 + y_sum2 + z_sum2;
  float F1 =  0.5f * F0;
  float F2 = -8.0f * (x_sum3 + Y2X + Z2X);
  float F3 = -8.0f * (X2Y + y_sum3 + Z2Y);
  float F4 = -8.0f * (X2Z + Y2Z + z_sum3);
  
  //Set initial conditions:
  float A = x_sum;
  float B = y_sum;
  float C = z_sum;
  
  //First iteration computation:
  float A2 = A * A;
  float B2 = B * B;
  float C2 = C * C;
  float QS = A2 + B2 + C2;
  float QB = -2.0f * (A * x_sum + B * y_sum + C * z_sum);
  
  //Set initial conditions:
  float Rsq = F0 + QB + QS;
  
  //First iteration computation:
  float Q0 = 0.5f * (QS - Rsq);
  float Q1 = F1 + Q0;
  float Q2 = 8.0f * (QS - Rsq + QB + F0);
  float aA, aB, aC, nA, nB, nC, dA, dB, dC;
  
  //Iterate N times, ignore stop condition.
  unsigned int n = 0;
  
  while (n < max_iterations) {
    n++;
    
    //Compute denominator:
    aA = Q2 + 16.0f * (A2 - 2.0f * A * x_sum + x_sum2);
    aB = Q2 + 16.0f * (B2 - 2.0f * B * y_sum + y_sum2);
    aC = Q2 + 16.0f * (C2 - 2.0f * C * z_sum + z_sum2);
    aA = (aA == 0.0f) ? 1.0f : aA;
    aB = (aB == 0.0f) ? 1.0f : aB;
    aC = (aC == 0.0f) ? 1.0f : aC;
    
    //Compute next iteration
    nA = A - ((F2 + 16.0f * (B * XY + C * XZ + x_sum * (-A2 - Q0) + A * (x_sum2 + Q1 - C * z_sum - B * y_sum))) / aA);
    nB = B - ((F3 + 16.0f * (A * XY + C * YZ + y_sum * (-B2 - Q0) + B * (y_sum2 + Q1 - A * x_sum - C * z_sum))) / aB);
    nC = C - ((F4 + 16.0f * (A * XZ + B * YZ + z_sum * (-C2 - Q0) + C * (z_sum2 + Q1 - A * x_sum - B * y_sum))) / aC);
    
    //Check for stop condition
    dA = (nA - A);
    dB = (nB - B);
    dC = (nC - C);
    
    if ((dA * dA + dB * dB + dC * dC) <= delta) { break; }
    
    //Compute next iteration's values
    A = nA;
    B = nB;
    C = nC;
    A2 = A * A;
    B2 = B * B;
    C2 = C * C;
    QS = A2 + B2 + C2;
    QB = -2.0f * (A * x_sum + B * y_sum + C * z_sum);
    Rsq = F0 + QB + QS;
    Q0 = 0.5f * (QS - Rsq);
    Q1 = F1 + Q0;
    Q2 = 8.0f * (QS - Rsq + QB + F0);
  }
  
  *sphere_x = A;
  *sphere_y = B;
  *sphere_z = C;
  *sphere_radius = sqrtf(Rsq);
  
  return 0;
}





//original source of��https://github.com/stevenjiaweixie/vrgimbal
//https://github.com/stevenjiaweixie/vrgimbal/blob/master/Firmware/VRGimbal/calibrationRoutines.cpp
//��Դ�ڿ�Դ��̨��Ŀ��https://vrgimbal.wordpress.com/
Least_Squares_Intermediate_Variable Mag_LS;
void LS_Init(Least_Squares_Intermediate_Variable * pLSQ)
{
  memset(pLSQ, 0, sizeof(Least_Squares_Intermediate_Variable));
}

unsigned int LS_Accumulate(Least_Squares_Intermediate_Variable * pLSQ, float x, float y, float z)
{
  float x2 = x * x;
  float y2 = y * y;
  float z2 = z * z;
  
  pLSQ->x_sumplain += x;
  pLSQ->x_sumsq += x2;
  pLSQ->x_sumcube += x2 * x;
  
  pLSQ->y_sumplain += y;
  pLSQ->y_sumsq += y2;
  pLSQ->y_sumcube += y2 * y;
  
  pLSQ->z_sumplain += z;
  pLSQ->z_sumsq += z2;
  pLSQ->z_sumcube += z2 * z;
  
  pLSQ->xy_sum += x * y;
  pLSQ->xz_sum += x * z;
  pLSQ->yz_sum += y * z;
  
  pLSQ->x2y_sum += x2 * y;
  pLSQ->x2z_sum += x2 * z;
  
  pLSQ->y2x_sum += y2 * x;
  pLSQ->y2z_sum += y2 * z;
  
  pLSQ->z2x_sum += z2 * x;
  pLSQ->z2y_sum += z2 * y;
  
  pLSQ->size++;
  
  return pLSQ->size;
}


void LS_Calculate(Least_Squares_Intermediate_Variable * pLSQ,
                  unsigned int max_iterations,
                  float delta,
                  float *sphere_x, float *sphere_y, float *sphere_z,
                  float *sphere_radius)
{
  //
  //Least Squares Fit a sphere A,B,C with radius squared Rsq to 3D data
  //
  //    P is a structure that has been computed with the data earlier.
  //    P.npoints is the number of elements; the length of X,Y,Z are identical.
  //    P's members are logically named.
  //
  //    X[n] is the x component of point n
  //    Y[n] is the y component of point n
  //    Z[n] is the z component of point n
  //
  //    A is the x coordiante of the sphere
  //    B is the y coordiante of the sphere
  //    C is the z coordiante of the sphere
  //    Rsq is the radius squared of the sphere.
  //
  //This method should converge; maybe 5-100 iterations or more.
  //
  float x_sum = pLSQ->x_sumplain / pLSQ->size;        //sum( X[n] )
  float x_sum2 = pLSQ->x_sumsq / pLSQ->size;    //sum( X[n]^2 )
  float x_sum3 = pLSQ->x_sumcube / pLSQ->size;    //sum( X[n]^3 )
  float y_sum = pLSQ->y_sumplain / pLSQ->size;        //sum( Y[n] )
  float y_sum2 = pLSQ->y_sumsq / pLSQ->size;    //sum( Y[n]^2 )
  float y_sum3 = pLSQ->y_sumcube / pLSQ->size;    //sum( Y[n]^3 )
  float z_sum = pLSQ->z_sumplain / pLSQ->size;        //sum( Z[n] )
  float z_sum2 = pLSQ->z_sumsq / pLSQ->size;    //sum( Z[n]^2 )
  float z_sum3 = pLSQ->z_sumcube / pLSQ->size;    //sum( Z[n]^3 )
  
  float XY = pLSQ->xy_sum / pLSQ->size;        //sum( X[n] * Y[n] )
  float XZ = pLSQ->xz_sum / pLSQ->size;        //sum( X[n] * Z[n] )
  float YZ = pLSQ->yz_sum / pLSQ->size;        //sum( Y[n] * Z[n] )
  float X2Y = pLSQ->x2y_sum / pLSQ->size;    //sum( X[n]^2 * Y[n] )
  float X2Z = pLSQ->x2z_sum / pLSQ->size;    //sum( X[n]^2 * Z[n] )
  float Y2X = pLSQ->y2x_sum / pLSQ->size;    //sum( Y[n]^2 * X[n] )
  float Y2Z = pLSQ->y2z_sum / pLSQ->size;    //sum( Y[n]^2 * Z[n] )
  float Z2X = pLSQ->z2x_sum / pLSQ->size;    //sum( Z[n]^2 * X[n] )
  float Z2Y = pLSQ->z2y_sum / pLSQ->size;    //sum( Z[n]^2 * Y[n] )
  
  //Reduction of multiplications
  float F0 = x_sum2 + y_sum2 + z_sum2;
  float F1 =  0.5f * F0;
  float F2 = -8.0f * (x_sum3 + Y2X + Z2X);
  float F3 = -8.0f * (X2Y + y_sum3 + Z2Y);
  float F4 = -8.0f * (X2Z + Y2Z + z_sum3);
  
  //Set initial conditions:
  float A = x_sum;
  float B = y_sum;
  float C = z_sum;
  
  //First iteration computation:
  float A2 = A * A;
  float B2 = B * B;
  float C2 = C * C;
  float QS = A2 + B2 + C2;
  float QB = -2.0f * (A * x_sum + B * y_sum + C * z_sum);
  
  //Set initial conditions:
  float Rsq = F0 + QB + QS;
  
  //First iteration computation:
  float Q0 = 0.5f * (QS - Rsq);
  float Q1 = F1 + Q0;
  float Q2 = 8.0f * (QS - Rsq + QB + F0);
  float aA, aB, aC, nA, nB, nC, dA, dB, dC;
  
  //Iterate N times, ignore stop condition.
  unsigned int n = 0;
  
  while (n < max_iterations) {
    n++;
    
    //Compute denominator:
    aA = Q2 + 16.0f * (A2 - 2.0f * A * x_sum + x_sum2);
    aB = Q2 + 16.0f * (B2 - 2.0f * B * y_sum + y_sum2);
    aC = Q2 + 16.0f * (C2 - 2.0f * C * z_sum + z_sum2);
    aA = (aA == 0.0f) ? 1.0f : aA;
    aB = (aB == 0.0f) ? 1.0f : aB;
    aC = (aC == 0.0f) ? 1.0f : aC;
    
    //Compute next iteration
    nA = A - ((F2 + 16.0f * (B * XY + C * XZ + x_sum * (-A2 - Q0) + A * (x_sum2 + Q1 - C * z_sum - B * y_sum))) / aA);
    nB = B - ((F3 + 16.0f * (A * XY + C * YZ + y_sum * (-B2 - Q0) + B * (y_sum2 + Q1 - A * x_sum - C * z_sum))) / aB);
    nC = C - ((F4 + 16.0f * (A * XZ + B * YZ + z_sum * (-C2 - Q0) + C * (z_sum2 + Q1 - A * x_sum - B * y_sum))) / aC);
    
    //Check for stop condition
    dA = (nA - A);
    dB = (nB - B);
    dC = (nC - C);
    
    if ((dA * dA + dB * dB + dC * dC) <= delta) { break; }
    
    //Compute next iteration's values
    A = nA;
    B = nB;
    C = nC;
    A2 = A * A;
    B2 = B * B;
    C2 = C * C;
    QS = A2 + B2 + C2;
    QB = -2.0f * (A * x_sum + B * y_sum + C * z_sum);
    Rsq = F0 + QB + QS;
    Q0 = 0.5f * (QS - Rsq);
    Q1 = F1 + Q0;
    Q2 = 8.0f * (QS - Rsq + QB + F0);
  }
  
  *sphere_x = A;
  *sphere_y = B;
  *sphere_z = C;
  *sphere_radius = sqrt(Rsq);
}
