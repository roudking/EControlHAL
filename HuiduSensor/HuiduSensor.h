#ifndef _HUIDUSENSOR_H
#define _HUIDUSENSOR_H

#include "HuiduSensor_gpio.h"


typedef enum
{
	 incomplete,
   in_the_line,
	 in_the_turnright,
	 in_the_turnleft,
	 in_the_allwhite,
	 in_the_end
}HUIDU_STATE;

typedef struct
{
	HUIDU_STATE state;
  int huiduvalue[8];
	uint8_t huiduvalue_bin;
	float	huidu_bias;
}HUIDU;

void Huidu_getvalue(HUIDU *huidu_data);
void Huidu_getstate(HUIDU *huidu,int index1, int index2);



#endif
