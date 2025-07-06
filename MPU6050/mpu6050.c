#include "mpu6050.h"

KALMAN KalmanX = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f
};

KALMAN KalmanY = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f,
};

void Creat_mpu(MPU *mpu,MPU_CONFIG config_struct,KALMAN kalmanx,KALMAN kalmany)
{
   mpu->config = config_struct;
	 mpu->KalmanX = kalmanx;
	 mpu->KalmanY = kalmany;
}

void Mpu_init(MPU *mpu)
{
	    delay_ms(1000);
		mpu_iicsend(mpu->config, PWR_MGMT_1,   &(mpu_config.clock_config), 1);
	  mpu_iicsend(mpu->config, MPU_CFG_REG,  &(mpu_config.DLFP_Config),  1); 
    mpu_iicsend(mpu->config, MPU_SAMPLE_RATE_REG,&(mpu_config.samping_rate),1) ;
	  mpu_iicsend(mpu->config, GYRO_CONFIG,  &(mpu_config.gyro_config),  1);
	  mpu_iicsend(mpu->config, ACCEL_CONFIG, &(mpu_config.accel_config), 1);
}

void Mpu_test_who_am_i(MPU *mpu)
{
    mpu_iicgetdata(mpu->config,MPU_DEVICE_ID_REG,&(mpu->config.Who_am_I_ID),1);
}
	

static void Mpu_getdata_original(MPU_RAW *mpu_raw,MPU_CONFIG config)
{
    uint8_t buf[14];
    // �� ACCEL_XOUT_H ��ʼ�������� 14 �ֽ�
    mpu_iicgetdata(config,ACCEL_XOUT_H, buf, 14);

    // �ߵ��ֽ���װ
    mpu_raw->accel_x = (int16_t)((buf[0] << 8) | buf[1]);
    mpu_raw->accel_y = (int16_t)((buf[2] << 8) | buf[3]);
    mpu_raw->accel_z = (int16_t)((buf[4] << 8) | buf[5]);
    mpu_raw->gyro_x  = (int16_t)((buf[8] << 8) | buf[9]);
    mpu_raw->gyro_y  = (int16_t)((buf[10]<< 8) | buf[11]);
    mpu_raw->gyro_z  = (int16_t)((buf[12]<< 8) | buf[13]);
}

// ���̶�Ӧ�ķ�ĸ�������� ��2 g �� ��250 ��/s��
const float accel_sens = 16384.0f;
const float gyro_sens  = 131.0f;

static void Mpu_convert_raw_to_data(MPU_DATA *mpu_data,MPU_RAW *mpu_raw)
{
    mpu_data->ax = (float)mpu_raw->accel_x / accel_sens;
    mpu_data->ay = (float)mpu_raw->accel_y / accel_sens;
    mpu_data->az = (float)mpu_raw->accel_z / accel_sens;

    mpu_data->gx = (float)mpu_raw->gyro_x / gyro_sens;
    mpu_data->gy = (float)mpu_raw->gyro_y / gyro_sens;
    mpu_data->gz = (float)mpu_raw->gyro_z / gyro_sens;
}

void Mpu_getdata(MPU *mpu) {
	  Mpu_getdata_original(&(mpu->mpu_raw),mpu->config);
    Mpu_convert_raw_to_data(&(mpu->mpu_data),&(mpu->mpu_raw));
}



static double Kalman_getAngle(KALMAN *Kalman, double newAngle, double newRate, double dt) {
    double rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    double S = Kalman->P[0][0] + Kalman->R_measure;
    double K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    double y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    double P00_temp = Kalman->P[0][0];
    double P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
};



/// ���ڿ������˲�ʱ����������
static uint32_t mpu_timer = 0;
#define RAD_TO_DEG 57.295779513082320876798154814105


void Mpu_getKalmandata(MPU *mpu){
    uint8_t Rec_Data[14];
    int16_t temp;

    // Read 14 BYTES of data starting from ACCEL_XOUT_H register
    Mpu_getdata_original(&(mpu->mpu_raw),mpu->config);
    Mpu_convert_raw_to_data(&(mpu->mpu_data),&(mpu->mpu_raw));

 //���� 4. �������ں� ����  
    // 4.1 ����ʱ������ dt���룩
    double dt = (HAL_GetTick() - mpu_timer) * 0.001;
    mpu_timer = HAL_GetTick();

    // 4.2 ���ٶȼ�˲ʱ Roll/Pitch ����
    double roll_sqrt = sqrt(
        mpu->mpu_raw.accel_x * mpu->mpu_raw.accel_x +
        mpu->mpu_raw.accel_z * mpu->mpu_raw.accel_z);
    double roll  = (roll_sqrt > 0.0)
                   ? atan((double)mpu->mpu_raw.accel_y / roll_sqrt) * RAD_TO_DEG
                   : 0.0;
    double pitch = atan2(
                       -(double)mpu->mpu_raw.accel_x,
                       (double)mpu->mpu_raw.accel_z
                   ) * RAD_TO_DEG;

    // 4.3 �����ǣ�Y ��ǣ��˲������� ��90�� ͻ��
    if ((pitch < -90.0 && mpu->KalmanAngleY > 90.0) ||
        (pitch >  90.0 && mpu->KalmanAngleY < -90.0))
    {
        mpu->KalmanY.angle       = pitch;
        mpu->KalmanAngleY   = pitch;
    }
    else
    {
        mpu->KalmanAngleY = Kalman_getAngle(
            &(mpu->KalmanY),
            pitch,
            mpu->mpu_data.gy,
            dt
        );
    }

    // 4.4 ���������ת�� 90�㣬���� X ���������
    if (fabs(mpu->KalmanAngleY) > 90.0)
        mpu->mpu_data.gx = -mpu->mpu_data.gx;

    // 4.5 ����ǣ�X ��ǣ�����������
    mpu->KalmanAngleX = Kalman_getAngle(
        &(mpu->KalmanX),
        roll,
        mpu->mpu_data.gy,
        dt
    );
}


