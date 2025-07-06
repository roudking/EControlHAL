#include "mpu6050_config.h"

MPU_CONFIG mpu_config = {
	    
      .IIC_Port =  &hi2c2,  //硬件IIC端口选择
			.ADDR = MPU_ADDR,       //MPU地址
      .DLFP_Config = 0x00,    //配置DLFP为0延迟，同时给定输出速率为8Khz
	    .samping_rate = 0x00,   //采样率分频器，采样率为8Khz
	    .gyro_config = 0x00,		//陀螺仪满量程配置 为 250°/s
	    .accel_config = 0x00,	  //加速度计满量程配置 为 2g/s
			.clock_config = 0x01    //设置内部时钟源为X轴的MEMS时钟
};