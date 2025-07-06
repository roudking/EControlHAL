#include "Mask.h"

static void Mask_timcallback(void);

float real_speed;
int num1,num2;

//定义对象
CAR car;
//已整定pid
PID pidL = {40.0,11.5,0.0};
PID pidR = {40.0,11.5,0.0};
PID imu_tracepid = {0.32,0.0,-1.5};
PID imu_turnpid = {3.0,0.0,0.0};


//MASK_ASSIGNMENT assignments[] = {wait_start,stop,stop,beep,go_strightoverflow,goto_turnright,go_strightoverflow,stop,turnright,stop,goto_line,stop,beep,goto_turnleft,go_strightoverflow,stop,turnleft,stop,goto_turnleft,go_strightoverflow,stop,turnleft,goto_turnright,go_strightoverflow,stop,turnright,stop,goto_line,stop,go_avoidance,stop,gobackto_line,stop,stop,go_strightoverflow,stop,turnright,goto_allwhite,stop}; //test_assignments
MASK_ASSIGNMENT assignments[] = {wait_start,resethwt101,stop,stop,stop,beep,go_strightoverflow,goto_turnright,turnright,goto_line,stop,beep,stop,goto_turnleft,turnleft,goto_turnleft,turnleft,goto_turnright,turnright,goto_line,stop,go_avoidance,stop,gobackto_line,stop,stop,go_strightoverflow,stop,turnright,goto_allwhite,stop,beep,voice_trace,stop,getnum,stop,turnleftto_line,gountil_end,turnto_end,stop}; //test_assignments

#define assignments_num sizeof(assignments)/sizeof(assignments[0])
void Mask_start(void)
{
	 Mask_setassignments(&car,assignments, assignments_num);
	 Car_creatmotor(&(car.motor1),pidL,LEFT);
	 Car_creatmotor(&(car.motor2),pidR,RIGHT);
	 Car_creatimu(&(car.imu),imu_tracepid,imu_turnpid);
	 Car_creatstepper(&(car.stepper),1);
   Car_creatservo(&(car.servo),90.0);

   tim_callbackregister(&Mask_TIM_IT_Timer,Mask_timcallback);
   tim_it_start(&Mask_TIM_IT_Timer);
	
}

static void Mask_timcallback(void)
{ 
	  Driver_getmotor_currentspeed(&(car.motor1));
	  Driver_getmotor_currentspeed(&(car.motor2));
	  Myhwt101_getdata(&(car.imu.angle));
	  Huidu_getvalue(&(car.huidu));
	  Car_getdistance(&car);
	  Car_calrealspeed(&real_speed,&car);
	  Car_returnnum(&car,&num1,&num2);

//TEST代码
//	int time = 1000;
//	static int i = 0;
//  if(i<time/10)
//	{
//    Servo_settargetangle(&(car.servo),60.0);
//	  Servo_gotoangle(&(car.servo));
//		i++;
//	}
//	else if(i < 2*time/10)
//	{
//   Servo_settargetangle(&(car.servo),120.0);
//	  Servo_gotoangle(&(car.servo));
//		i++;
//		i++;	
//	}


		Mask_performassignments(&car,assignments_num);

		Driver_setspeed(&(car.motor1),&(car.motor2));

}






