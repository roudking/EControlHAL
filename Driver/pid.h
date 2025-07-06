#ifndef _PID_H
#define _PID_H

#include "math.h"

typedef struct
{
   float kp;
	 float ki;
   float kd;
	 float last_bias;
	 float integral;
	 float outvalue;
}PID;

// 位置式 PID 计算函数（带输出限幅和积分抗饱和）
float positionPid_Cal(float targetvalue, float currentvalue, PID* pid, float xianfu_value);
float deltaPid_Cal(float targetvalue,float currentvalue,PID* pid,float xianfu_value);
void pidmemory_clear(PID* pid);

#endif
