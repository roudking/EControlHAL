#include "Car.h"

#define motor_D 67.0f //直径67.0mm
#define encoder_singlecount 1456.0f
#define require_realspeed 5.0f  // 5mm/10ms

const double mmpercnt = 3.1415926 * motor_D/encoder_singlecount;
const double require_speed = require_realspeed / mmpercnt ;
//const float  my_speed = 25.0;
const float  my_speed = require_speed;

void Car_creatimu(IMU *imu,PID tracePid,PID turnPid)
{
	  imu->trace_pid.kp = tracePid.kp;
	  imu->trace_pid.ki = tracePid.ki;
		imu->trace_pid.kd = tracePid.kd;
	  pidmemory_clear(&(imu->trace_pid));
	
	  imu->turn_pid.kp = turnPid.kp;
	  imu->turn_pid.ki = turnPid.ki;
		imu->turn_pid.kd = turnPid.kd;
	  pidmemory_clear(&(imu->turn_pid));
	
	  imu->targetyaw = 0.0;
	  imu->turn_state = not_started;
	  imu->last_targetyaw = 0.0;
}

void Car_creatmotor(MOTOR *motor,PID pid,POSITION position)
{
	  Driver_creatmotor(motor, pid, position);
}

void Car_creatstepper(STEPPER *stepper,int id)
{
   Stepper_creatstepper(stepper,id);
}

void Car_settargetyaw(CAR *car,float target_yaw)
{
		car->imu.last_targetyaw = car->imu.targetyaw;
    car->imu.targetyaw = target_yaw;
}

void Car_creatservo(SERVO *servo,float zero_angle)
{
    Servo_settargetangle(servo,zero_angle);
	  Servo_gotoangle(servo);
}

void Car_setservotargetangle(SERVO *servo,float angle)
{
		Servo_settargetangle(servo,angle);
}

void Car_servogotoangle(SERVO *servo)
{
	  Servo_gotoangle(servo);
}

void Car_laseron(LASER *laser)
{
   Laser_on(laser);
}

void Car_laseroff(LASER *laser)
{
	 Laser_off(laser);
}

void Car_getdistance(CAR *car)
{
    car->distance += (car->motor1.currentspeed + car->motor2.currentspeed)/2;
}

void Car_cleardistance(CAR *car)
{
    car->distance = 0;
}

void Car_clearhuidustate(CAR *car)
{
	  car -> huidu.state = incomplete;
}

void Car_setstepperangle(CAR *car,float target_angle)
{
    Stepper_setangle(&(car->stepper),target_angle);
}

void Car_startk210uart(CAR *car)
{
   K210_startit();
}

void Car_stopk210uart(CAR *car)
{
   K210_stopit();
}

void Car_getvoiceangele(CAR *car)
{
    K210_getangle(&(car->k210));
}

void Car_clearturnstate(CAR *car)
{
    car->imu.turn_state = not_started;
}

void Car_getrecognizegreen_area(CAR *car)
{
     Resberry_getgreen_area(&(car->resberry));
}

void Car_resberrysendgetnumercmd(CAR *car)
{
	  Resberry_sendgetnumercmd(&(car->resberry));
}

void Car_resberrygetstate(CAR *car)
{
   Resberry_getstate(&(car->resberry));
}

void Car_resberrygetnumber(CAR *car)
{
	 Resberry_getnumber(&(car->resberry));
}

void Car_beepon(void)
{
   Beep_on();
}

void Car_beepoff(void)
{
	 Beep_off();
}

void Car_setangleforward(CAR *car)
{
   Car_setservotargetangle(&(car->servo),90.0);
	 Car_servogotoangle(&(car->servo));
}

void Car_setanglelateral(CAR *car)
{
	 Car_setservotargetangle(&(car->servo),40);
	 Car_servogotoangle(&(car->servo));
}

void Car_getkeyvalue(CAR *car)
{
    Key_getvalue(&(car->key));
}


#define time_sleep 500 //ms
int Car_stop(CAR *car)
{
  	Driver_setmotor_targetspeed(&(car->motor1),0);
	  Driver_setmotor_targetspeed(&(car->motor2),0);
		 
		Car_clearhuidustate(car);
		Car_cleardistance(car);
		Car_clearturnstate(car);
	
		static int i = 1;
		if(i < time_sleep/10)
		{
			i++;
		  return 0;
		}
		else 
		{
			i = 1;
			return 1;
		}
}

void Car_cal_and_settracelinespeed(CAR *car,float speed)
{
		float imubias = positionPid_Cal(car->imu.targetyaw,car->imu.angle.fAngle[yaw_id],&(car->imu.trace_pid),5.0);
	  float huidubias = car->huidu.huidu_bias;
	  float final_bias = imubias + huidubias;
	
    Driver_setmotor_targetspeed(&(car->motor1),(int)(speed - final_bias));
	  Driver_setmotor_targetspeed(&(car->motor2),(int)(speed + final_bias));
}
void Car_cal_and_settracelinespeed_withoutHuidusensor(CAR *car,float speed)
{
		float imubias = positionPid_Cal(car->imu.targetyaw,car->imu.angle.fAngle[yaw_id],&(car->imu.trace_pid),5.0);
	  float final_bias = imubias;
    Driver_setmotor_targetspeed(&(car->motor1),(int)(speed - final_bias));
	  Driver_setmotor_targetspeed(&(car->motor2),(int)(speed + final_bias));
}	

void Car_cal_and_setturnspeed(CAR *car)
{
  int turn_speed = positionPid_Cal(car->imu.targetyaw, car->imu.angle.fAngle[yaw_id], &(car->imu.turn_pid), 7.0);
	  Driver_setmotor_targetspeed(&(car->motor1),-turn_speed);
	  Driver_setmotor_targetspeed(&(car->motor2),turn_speed);
}

void Car_calrealspeed(float *real_speed,CAR *car)
{
   *real_speed = (car->motor1.currentspeed + car->motor2.currentspeed) / 2.0 * mmpercnt * 100.0;
}

void Car_returnnum(CAR *car,int* num1,int *num2)
{
   *num1 = car->resberry.num[0];
	 *num2 = car->resberry.num[1];
}



#define overflow 250
#define overflow_speed 15
int Car_gostrightoverflowfuc(CAR *car)
{
   if(car->distance <= overflow)
	 {
	  Driver_setmotor_targetspeed(&(car->motor1),(int)overflow_speed);
	  Driver_setmotor_targetspeed(&(car->motor2),(int)overflow_speed);
		 return 0;
	 }
	 else 
	 {
	   return 1;
	 }
}



int Car_gotolinefuc(CAR *car)
{
		Car_cal_and_settracelinespeed(car,my_speed);
    Huidu_getstate(&(car->huidu),3,6);
	
	 if(car->huidu.state == in_the_line)
	 {
		 Car_cleardistance(car);
		 return 1;
	 }
		else return 0;
}



int Car_gototurnrightfuc(CAR *car)
{
		Car_cal_and_settracelinespeed(car,my_speed);
		Huidu_getstate(&(car->huidu),5,8);
	
   if(car->huidu.state == in_the_turnright)
	 {
	    Car_cleardistance(car);
  		return 1;
	 }
	 else return 0;
}

int Car_gototurnleftfuc(CAR *car)
{
 		Car_cal_and_settracelinespeed(car,my_speed);
		Huidu_getstate(&(car->huidu),1,4);
	 if(car->huidu.state == in_the_turnleft)
	 {
		 Car_cleardistance(car);
  		return 1;
	 }
	 else return 0;
}

#define yaw_threshold 1.0f
int Car_turnrightfuc(CAR *car)
{
	if(car->imu.turn_state == not_started)
	{
		Car_settargetyaw(car,car->imu.targetyaw - 85);
		car->imu.turn_state = turning;
		return 0;
	}
  else if(car->imu.turn_state == turning)
	{
			Car_cal_and_setturnspeed(car);
		  if(fabs(car->imu.angle.fAngle[yaw_id] - car->imu.targetyaw) < yaw_threshold)
			{
		Driver_setmotor_targetspeed(&(car->motor1),0);
	  Driver_setmotor_targetspeed(&(car->motor2),0);
			  car->imu.turn_state = complite_turn;
			}
			return 0;
	}
	else if(car->imu.turn_state == complite_turn)
	{
		Car_clearturnstate(car);
		Car_clearhuidustate(car);
	   return 1;
	}
	else return 0;
}

int Car_turnleftfuc(CAR *car)
{
	if(car->imu.turn_state == not_started)
	{
		Car_settargetyaw(car,car->imu.targetyaw + 85);
		car->imu.turn_state = turning;
		return 0;
	}
  else if(car->imu.turn_state == turning)
	{
			Car_cal_and_setturnspeed(car);
		  if(fabs(car->imu.angle.fAngle[yaw_id] - car->imu.targetyaw) < yaw_threshold)
			{
		Driver_setmotor_targetspeed(&(car->motor1),0);
	  Driver_setmotor_targetspeed(&(car->motor2),0);
			  car->imu.turn_state = complite_turn;
			}
			return 0;
	}
	else if(car->imu.turn_state == complite_turn)
	{
		Car_clearturnstate(car);
		Car_clearhuidustate(car);
	   return 1;
	}
	else return 0;
}

int Car_stopfuc(CAR* car)
{
	return Car_stop(car);
}

#define beep_time 200//ms
int Car_beepfuc(CAR *car)
{
	static int cnt = 1;
	if(cnt <= 3)
	{
		static int i = 1;
		if(i <= beep_time/10)
			{
				i++;
				Car_beepon();
			}
		else if(i < 2 * beep_time/10)
			{
				i++;
				Car_beepoff();
			}
		else if(i == 2 * beep_time/10){
				Car_beepoff();
				i=1;
				cnt++;
		 }
		return 0;
	}
	
   else 
	 {
		 cnt = 1;
	   return 1;
	 }
}

const float avoid_speed = 10.0;
const int green_area_threshold = 36000;
const int avoid_overflow = 600;
int Car_goavoidance(CAR *car)
{
	  Car_cal_and_settracelinespeed(car,avoid_speed);  
//	  Car_getrecognizegreen_area(car);
//	  printf("%d\n",car->resberry.green_area);
 
	  if(car->distance >= avoid_overflow	|| car->resberry.green_area >= green_area_threshold)
		{
		  return 1;
		}
		else return 0;
}


const float back_speed = 5.0;
int Car_gobacktolinefuc(CAR *car)
{
   Car_cal_and_settracelinespeed(car,-back_speed); 
    Huidu_getstate(&(car->huidu),3,6);
	
	if(car->huidu.state == in_the_line)
	 {
		 Car_cleardistance(car);
		 return 1;
	 }
		else return 0;
	
}

int Car_gotoallwhitefuc(CAR *car)
{
   Car_cal_and_settracelinespeed(car,my_speed); 
	
	 Huidu_getstate(&(car->huidu),1,8);
	
		if(car->huidu.state == in_the_allwhite)
	 {
		 Car_cleardistance(car);
		 return 1;
	 }
	 else return 0;
}

int Car_waitstartfuc(CAR *car)
{
		Car_getkeyvalue(car);
	 if(car->key.pin_value == 0)
	 {
		 car->key.pin_value = 1;
	   return 1;
	 }
	 else return 0;
}


const int delay_time = 600; //ms
int Car_getnumberfuc(CAR *car)
{
   static int i = 0;
	 static int j = 0;
	 if(i == 0)
	 {
	   Car_resberrysendgetnumercmd(car);
		 i++;
		 return 0;
	 }
	 else
	 {
			Car_resberrygetstate(car);
			
		  if(car->resberry.state == resberry_complite_echo)
			{
			 Car_resberrygetnumber(car);
			 if(car->resberry.num[0] != 0&& car->resberry.num[1] != 0)
				 {
					  i = 0;
					  j = 0;
					 	Car_setservotargetangle(&(car->servo),90.0);
						Car_servogotoangle(&(car->servo));
					 	printf("%d,%d\n",car->resberry.num[0],car->resberry.num[1]);
						return 1;
				 }
			 else if(car->resberry.num[0] == 0||car->resberry.num[1] == 0)
				 {
						 i = 0;
					 if(j == 0)
					 {
					 	Car_setservotargetangle(&(car->servo),70.0);
						Car_servogotoangle(&(car->servo));
						 delay_ms(1000);
						 j++;
						 return 0;
					 }
					 else if(j == 1)
					 {
					 	Car_setservotargetangle(&(car->servo),50.0);
						Car_servogotoangle(&(car->servo));
						 	delay_ms(1000);
						 j++;
						 return 0;
					 }
					 else if(j == 2)
					 {
					 Car_setservotargetangle(&(car->servo),110.0);
					 Car_servogotoangle(&(car->servo));
						 	delay_ms(1000);
						 j++;
						 return 0;
					 }
					 	else if(j == 3)
					 {
					 Car_setservotargetangle(&(car->servo),130.0);
					 Car_servogotoangle(&(car->servo));
						 	delay_ms(1000);
						 j++;
						 return 0;
					 }
					 else
					 {
						 printf("%d,%d\n",car->resberry.num[0],car->resberry.num[1]);
						Car_setservotargetangle(&(car->servo),90.0);
						Car_servogotoangle(&(car->servo));
					   j = 0;
						 i = 0;
						 return 1;
					 }

			 }
				 
			}
			else return 0;		
	 }
}

const float the_last_angle = -65.5;
int Car_turnlefttolinefuc(CAR *car)
{
	if(car->imu.turn_state == not_started)
	{
		Car_settargetyaw(car, the_last_angle);
		car->imu.turn_state = turning;
		return 0;
	}
  else if(car->imu.turn_state == turning)
	{
			Car_cal_and_setturnspeed(car);
		  if(fabs(car->imu.angle.fAngle[yaw_id] - car->imu.targetyaw) < yaw_threshold)
			{
		Driver_setmotor_targetspeed(&(car->motor1),0);
	  Driver_setmotor_targetspeed(&(car->motor2),0);
			  car->imu.turn_state = complite_turn;
			}
			return 0;
	}
	else if(car->imu.turn_state == complite_turn)
	{
		Car_clearturnstate(car);
		Car_clearhuidustate(car);
	   return 1;
	}
	else return 0;
}

const float withoutline_speed = 25.0;
int Car_gountilend(CAR *car)
{
   Car_cal_and_settracelinespeed_withoutHuidusensor(car,withoutline_speed); 
	
	 Huidu_getstate(&(car->huidu),1,8);
	
		if(car->huidu.state == in_the_end)
	 {
		 Car_cleardistance(car);
		 Car_clearhuidustate(car);
		 
		 return 1;
	 }
	 else return 0;
}

int Car_turntoend(CAR *car)
{
	if(car->imu.turn_state == not_started)
	{
		Car_settargetyaw(car, 0.0);
		car->imu.turn_state = turning;
		return 0;
	}
  else if(car->imu.turn_state == turning)
	{
			Car_cal_and_setturnspeed(car);
		  if(fabs(car->imu.angle.fAngle[yaw_id] - car->imu.targetyaw) < yaw_threshold)
			{
		Driver_setmotor_targetspeed(&(car->motor1),0);
	  Driver_setmotor_targetspeed(&(car->motor2),0);
			  car->imu.turn_state = complite_turn;
			}
			return 0;
	}
	else if(car->imu.turn_state == complite_turn)
	{
		Car_clearturnstate(car);
		Car_clearhuidustate(car);
		
	   return 1;
	}
	else return 0;
}

int Car_resethwt101fuc(CAR *car)
{
   WitWriteReg(0x76, 0x00);
	 return 1;
}

int Car_voicetrance(CAR *car)
{  
 
	Car_getkeyvalue(car);
	if(car->key.pin_value == 0)
	{
		 Car_laseroff(&(car->laser));
		 car->key.pin_value = 1;
	   return 1;
	}
	else
	{
	   Car_laseron(&(car->laser));
		 return 0;
	}
	
}




