#include "Stepper.h"

void Stepper_setzero(STEPPER *stepper)
{
  Emm_V5_Origin_Set_O(stepper->stepper_id, true); // 设置当圈回零的零点位置
}

void Stepper_gotozero(STEPPER *stepper)
{
Emm_V5_Origin_Trigger_Return(stepper->stepper_id, 0, false);
}

void Stepper_creatstepper(STEPPER *stepper,int id)
{
    stepper->stepper_id = id;
	 Stepper_gotozero(stepper);
}

void Stepper_setstep(STEPPER *stepper,int step)
{
   Emm_V5_Pos_Control(stepper->stepper_id, stepper->dir, 100, 5, step, true, false);	
}

const double Cycle_Count = 3200.0;
const double angle_per_count = 360.0/Cycle_Count;

static int get_rotation_dir(double current_angle, double target_angle) {
    // 计算逆时针的转动角度（0 ≤ d_ccw < 360）
    double d_ccw = fmod(target_angle - current_angle + 360.0, 360.0);
    // 顺时针的转动角度
    double d_cw  = 360.0 - d_ccw;

    // 选择较小的旋转角度对应的方向
    if (d_cw < d_ccw) {
        return 0;  // 顺时针
    } else {
        return 1;  // 逆时针（包括 d_cw == d_ccw 时）
    }
}

void Stepper_setangle(STEPPER *stepper,float target_angle)
{
	stepper->last_targetangle = stepper->current_targetangle;
	
	stepper->current_targetangle = target_angle;
	
		int step ;
	
	if(stepper->last_targetangle <= 180 &&stepper->last_targetangle>=0)
	{
	   if(stepper->current_targetangle<360&&(stepper->current_targetangle > (stepper->last_targetangle+180.0)))
		 {
			 stepper->dir = 1;
			 	step = (int)((360.0 - stepper->current_targetangle) / angle_per_count);
		 }
		 else
		 {
		  stepper->dir = 0;
			step = (int)((stepper->current_targetangle) / angle_per_count);
		 }
	}
	else
	{
	   if(stepper->current_targetangle > 0&&(stepper->current_targetangle < (stepper->last_targetangle - 180.0)))
		 {
		  stepper->dir = 0;
			 step = (int)((stepper->current_targetangle) / angle_per_count);
		 }
		 else
		 {
		  stepper->dir = 0;
			 step = (int)((stepper->current_targetangle) / angle_per_count);
		 }
	}

	

	Stepper_setstep(stepper,step);
}
