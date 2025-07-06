
#ifndef _MPU6050_H
#define _MPU6050_H

#include "mpu6050_iic.h"
#include "math.h"
#include "my_delay.h"

typedef struct
{
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x,  gyro_y,  gyro_z;
}MPU_RAW;

typedef struct
{
    float ax, ay, az;     // 单位：g
    float gx, gy, gz;     // 单位：°/s
}MPU_DATA;

typedef struct {
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} KALMAN;

typedef struct
{
		 MPU_CONFIG config;
     MPU_DATA mpu_data;
	   MPU_RAW  mpu_raw;
	   double KalmanAngleX;
     double KalmanAngleY;
	   KALMAN KalmanX;
	   KALMAN KalmanY;
}MPU;

void Mpu_test_who_am_i(MPU *mpu);

void Creat_mpu(MPU *mpu,MPU_CONFIG config_struct,KALMAN kalmanx,KALMAN kalmany);
void Mpu_init(MPU *mpu);
void Mpu_getdata(MPU *mpu);
void Mpu_getKalmandata(MPU *mpu);

extern KALMAN KalmanX;
extern KALMAN KalmanY;

#endif
