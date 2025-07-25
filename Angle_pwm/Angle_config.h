#ifndef __ANGLE_CONFIG_H
#define __ANGLE_CONFIG_H

#include "tim_ic.h"

typedef struct {
    TIM_HandleTypeDef *htim; // Timer handle for input capture
    int CCR1;
    int CCR2;
} ANGLE_CONFIG;

extern ANGLE_CONFIG angle_config;

#endif // __ANGLE_CONFIG_H