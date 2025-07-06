#include "Driver.h"

//PID pidL = {25.0,5.0,0.0};
//PID pidR = {25.0,5.0,0.0};


void Driver_creatmotor(MOTOR *mymotor,PID pid,POSITION Position)
{
	  mymotor->pid.kp = pid.kp;
	  mymotor->pid.ki = pid.ki;
		mymotor->pid.kd = pid.kd;
	  pidmemory_clear(&(mymotor->pid));
		
	  mymotor->lastspeed = 0;
	  mymotor->targetspeed = 0;
	
		mymotor->position = Position;
}

void Driver_init(void)
{
  DriverEncoder_init();
	Driver_pwminit();
}

void Driver_setmotor_targetspeed(MOTOR *motor,int target_speed)
{
    motor -> targetspeed = target_speed;
}

void Driver_getmotor_currentspeed(MOTOR *motor)
{
    if(motor->position == LEFT)
		{
			motor->currentspeed = DriverEncoder_getleftcounter();
		}
		else if(motor->position == RIGHT)
		{
			motor->currentspeed = DriverEncoder_getrightcounter();
		}
}

void Driver_setspeed(MOTOR *motor1,MOTOR *motor2)
{	
    int pwm1 = (int)deltaPid_Cal((float)(motor1->targetspeed),(float)(motor1->currentspeed),&(motor1->pid),7200);
	  int pwm2 = (int)deltaPid_Cal((float)(motor2->targetspeed),(float)(motor2->currentspeed),&(motor2->pid),7200);
	
   if(motor1->targetspeed == 0)
   {
    pwm1 = 0;
	  pidmemory_clear(&(motor1->pid));
   }
   if(motor2->targetspeed == 0)
	 {
	  pwm2 = 0;
	  pidmemory_clear(&(motor2->pid));
	 }
   
    Driver_setpwm(pwm1,pwm2);
}

float a = 0.1; //线性滤波系数
void Driver_setspeedwithfliter(MOTOR *motor1,MOTOR *motor2)
{	
	  motor1->flitspeed = (float)motor1->flitspeed * a + (float)motor1->currentspeed * (1.0-a);
	  motor2->flitspeed = (float)motor2->flitspeed * a + (float)motor2->currentspeed * (1.0-a);
	
    int pwm1 = (int)deltaPid_Cal((float)(motor1->targetspeed),(float)(motor1->flitspeed),&(motor1->pid),7200);
	  int pwm2 = (int)deltaPid_Cal((float)(motor2->targetspeed),(float)(motor2->flitspeed),&(motor2->pid),7200);
	
   if(motor1->targetspeed == 0 && motor2->targetspeed == 0)
   {
    pwm1 = 0;
		pwm2 = 0;   
	  pidmemory_clear(&(motor1->pid));
	  pidmemory_clear(&(motor2->pid));
   }
   
    Driver_setpwm(pwm1,pwm2);
}
