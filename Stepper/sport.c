#include "Emm_V5.h"
#include "math.h"
#include "stdio.h"
#include "tim.h"
#include "usart.h"
int  cnt; 
int flag = -1;

int while_flag;

void Stepper_Setz(int step)
{
	
	 while_flag = 0;
	if(step > 0)
	{
	   HAL_GPIO_WritePin(Dir_GPIO_Port,Dir_Pin,GPIO_PIN_SET);
	}
	else 
	{
	   HAL_GPIO_WritePin(Dir_GPIO_Port,Dir_Pin,GPIO_PIN_RESET);
	}

	    cnt = 2 * step;
	  HAL_TIM_Base_Start_IT(&htim7);
	
//		
	  while(while_flag == 0)
	  {
	    HAL_Delay(1);
	  }
   
//		char message[2];
//		
//		sprintf(message,"%d\n",while_flag);
//			
//			
//	HAL_UART_Transmit(&huart3,(unsigned char *)message,2,HAL_MAX_DELAY);

}

void Stepper_Zset0(void)
{
	
	HAL_GPIO_WritePin(Dir_GPIO_Port,Dir_Pin,GPIO_PIN_SET);
    flag = 0;
	HAL_TIM_Base_Start_IT(&htim7);
while(HAL_GPIO_ReadPin(Z_Set0_GPIO_Port,Z_Set0_Pin) != 0);
	 flag = 1;
}

void Stepper_Set0(void)
{
	
  Emm_V5_Origin_Set_O(0, true); // 设置挡圈回零的零点位置
	
}

void Stepper_Setstep(int x_step,int y_step)
{

   int x_dir,y_dir;
	
   if(x_step >= 0) x_dir = 1;
   else if(x_step < 0)
   {
	   x_dir = 0;
	   x_step = -x_step;
   }
	

  if(y_step >= 0) y_dir = 1;
   else if(y_step < 0) 
   {
	   y_dir = 0;	
	   y_step = -y_step;
   }
	
     Emm_V5_Pos_Control(1, x_dir, 10, 100, x_step, 1, 1);	
   
	   HAL_Delay(100);
	
	 Emm_V5_Pos_Control(2, y_dir, 10, 100, y_step, 1, 1);	
	
	    HAL_Delay(100);
   
	 Emm_V5_Synchronous_motion(0);
	
	   HAL_Delay(500);
   
}


double Stepper_Getangle(uint8_t addr)
{
			Emm_V5_Read_Sys_Params(addr, S_CPOS);
		while(rxFrameFlag == false){}rxFrameFlag = false;
			
		 double angle = 0.0,pos = 0.0;
				
	  if(rxCmd[0] == addr && rxCmd[1] == 0x36 && rxCount == 8)
	  {
					// 拼接成uint32_t类型
				  
					 pos = (uint32_t)(
					((uint32_t)rxCmd[3] << 24)    |
					((uint32_t)rxCmd[4] << 16)    |
					((uint32_t)rxCmd[5] << 8)     |
					((uint32_t)rxCmd[6] << 0)
								   );

			// 转换成角度
			angle =  (double)pos * 360.0 / 65536.0;

			// 符号
			if(!rxCmd[2]) { angle = -angle; }
			
	 }
			  return angle;           				
}
 


void Stepper_Setangle(double x_angle,double y_angle)
{
     int x_step = x_angle / 0.00703125;
	 int y_step = y_angle / 0.00703125;
	
	Stepper_Setstep(x_step,y_step);
}

void Stepper_Setposition(double x_position,double y_position,double l1, double l2)
{
	 double alpha,beta;
	
	 // 计算角 phi
    double cos_phi = (x_position * x_position + y_position * y_position - l1 * l1 - l2 * l2) / (2 * l1 * l2);
	

    double phi = acos(cos_phi);

    // 计算 Beta 角度
    beta = phi * 180.0 / 3.1415926535897932384;

    // 计算 Alpha
    double k1 = l1 + l2 * cos_phi;
    double k2 = l2 * sin(phi);
    alpha = atan2(y_position, x_position) - atan2(k2, k1);
    alpha = alpha * 180.0 / 3.1416;
	 
// 1.34   -5.0
//1.46    -7.29
//
	Stepper_Setangle(alpha,beta);
	
}

void Stepper_Getposition(double alpha, double beta, double l1, double l2, double *x, double *y) {
    double alpha_rad = alpha * 3.1415926535897932384 / 180.0; // 将角度转换为弧度
    double beta_rad  = beta  * 3.1415926535897932384 / 180.0;

    // 计算第一个关节臂的末端位置
    double x1 = l1 * cos(alpha_rad);
    double y1 = l1 * sin(alpha_rad);

    // 计算整个末端执行器的位置
    *x = x1 + l2 * cos(alpha_rad + beta_rad);
    *y = y1 + l2 * sin(alpha_rad + beta_rad);
}

