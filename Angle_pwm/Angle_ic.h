#ifndef __ANGLE_IC_H
#define __ANGLE_IC_H

#include "Angle_config.h"

void Angle_ic_init(ANGLE_CONFIG config);
uint32_t Angle_ic_getvalue(ANGLE_CONFIG config, uint32_t channel);

#endif // __ANGLE_IC_H