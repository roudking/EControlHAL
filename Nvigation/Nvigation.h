#ifndef _NVIGATION_H
#define _NVIGATION_H


#include "Nvigation_Encoder.h"
#include "math.h"

#define left_d 58.0f
#define right_d 58.0f


typedef struct{
int32_t left_counter;
int32_t right_counter;
double left_distance;
double right_distance;
double yaw_angle;
double x_position;
double y_position;
double dx;
double dy;
}NVIGATION;

void Nvigation_init(void);
void Nvigation_getposition(NVIGATION* nvigation);


#endif
