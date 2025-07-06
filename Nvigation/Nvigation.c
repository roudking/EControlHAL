#include "Nvigation.h"
#include "my_HWT101.h"

void Nvigation_init(void)
{
    Encoder_init();
}

//获得angle角度
static void Nvigation_getangle(NVIGATION* nvigation)
{
    HWT101_DATA hwt_data;
		Myhwt101_getdata(&hwt_data);
		nvigation->yaw_angle = hwt_data.fAngle[yaw_id] * 3.14159265 / 180.0;
}

//获得轮子转动步数
static void Nvigation_getcounter(NVIGATION* nvigation)
{
     nvigation->left_counter = Encoder_Getleftcounter();
	   nvigation->right_counter = Encoder_Getrightcounter();
}


//轮子转动实际距离解算
static void distance_cal(double leftcounter,double rightcounter,double left_D,double right_D,double *left_distance,double *right_distance)
{
     *left_distance  = leftcounter * left_D * 3.14 / 2048.0;
	   *right_distance = rightcounter * right_D *3.14 / 2048.0;
}

//位置坐标增量解算
static void deltaposition_cal(double left_distance, double right_distance,double theta, double* x, double* y) {
    // 1. 投影到车体坐标系（forward/lateral）
    double forward = (left_distance + right_distance) / sqrt(2.0);
    double lateral = (left_distance - right_distance) / sqrt(2.0);

//    // 2. 旋转到世界坐标系
	  double dx = forward * sin(theta) + lateral * cos(theta);
    double dy = forward * cos(theta) - lateral * sin(theta);

    *x = dx;
    *y = dy;
}


//获得轮子移动的实际距离(通过解算)
static void Nvigation_getdistance(NVIGATION* nvigation)
{
	   Nvigation_getcounter(nvigation);
     distance_cal((double)nvigation->left_counter,(double)nvigation->right_counter,left_d,right_d,&(nvigation->left_distance),&(nvigation->right_distance));
}

//获得轮子实际的坐标
void Nvigation_getposition(NVIGATION* nvigation)
{
	 Nvigation_getangle(nvigation);
   Nvigation_getcounter(nvigation);
	 distance_cal((double)nvigation->left_counter,(double)nvigation->right_counter,left_d,right_d,&(nvigation->left_distance),&(nvigation->right_distance));
	 deltaposition_cal(nvigation->left_distance,nvigation->right_distance,-nvigation->yaw_angle,&(nvigation->dx),&(nvigation->dy));
   
	 nvigation->x_position+=nvigation->dx;
	 nvigation->y_position+=nvigation->dy;
}

