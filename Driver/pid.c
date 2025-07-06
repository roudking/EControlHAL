#include "pid.h"


static float xianfu(float value, float min, float max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}


// 位置式 PID 计算函数（带输出限幅和积分抗饱和）
float positionPid_Cal(float targetvalue, float currentvalue, PID* pid, float xianfu_value) {
    // 1. 计算当前偏差
    float bias = targetvalue - currentvalue;

    // 2. 计算比例项
    float P = pid->kp * bias;

    // 3. 更新积分项（累积当前偏差）
    pid->integral += bias;

    // 4. 计算积分项和微分项
    float I = pid->ki * pid->integral;
    float D = pid->kd * (bias - pid->last_bias);

    // 5. 计算总输出
    float output = P + I + D;

    // 6. 对输出进行限幅
    float output_limited = xianfu(output, -xianfu_value, xianfu_value);

    // 7. 积分抗饱和处理：如果输出被限幅，回退积分项
    if (output != output_limited && pid->ki != 0.0f) {
        // 计算限幅后的有效积分项，使得 P + I_clamped + D = output_limited
        float I_clamped = output_limited - P - D;
        pid->integral = I_clamped / pid->ki;  // 反向计算积分累积值
    }

    // 8. 更新状态
    pid->last_bias = bias;      // 保存当前偏差，用于下一次微分计算
    pid->outvalue = output_limited; // 记录限幅后的输出值

    return output_limited;
}

float deltaPid_Cal(float targetvalue,float currentvalue,PID* pid,float xianfu_value)
{
	float bias,current_bias,outputvalue; 
	
	current_bias = targetvalue - currentvalue;

  bias = current_bias - pid->last_bias;
	
	pid -> outvalue += pid->kp * bias + pid->ki * current_bias;

	pid->last_bias = current_bias;
	
  pid -> outvalue = xianfu(pid -> outvalue,-xianfu_value,xianfu_value);
	
	return pid -> outvalue;
}

void pidmemory_clear(PID* pid)
{
	  pid->integral  = 0;
    pid -> last_bias = 0;
	  pid -> outvalue  = 0;
}


