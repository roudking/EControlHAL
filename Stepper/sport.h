#ifndef _SPORT_H
#define _SPORT_H

extern int cnt;
extern int flag;
extern int while_flag;

void Stepper_Set0(void);        //设置系统的0位置

void Stepper_Setz(int step);    //设置z轴步进步数

void Stepper_Zset0(void);       //设置z轴的0位置

double Stepper_Getangle(uint8_t addr);  //获得步进电机当前的旋转角度（相较于0位置）

void Stepper_Setstep(int x_step,int y_step);   //设置两个步进电机分别向前步进多少步

void Stepper_Setangle(double x_angle,double y_angle);  //设置两个步进电机相较于0位置旋转的度数

void Stepper_Setposition(double x_position,double y_position,double l1, double l2);   //设置两个步进电机末尾在坐标面上的坐标位置

void Stepper_Getposition(double alpha, double beta, double l1, double l2, double *x, double *y); //得到此时步进电机在坐标轴上坐标位置

#endif
