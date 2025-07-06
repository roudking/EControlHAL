#ifndef _DRIVER_ENCODER_H
#define _DRIVER_ENCODER_H


#include "encoder.h"
#include "stdint.h"

//编码器分配 
#define LeftDriver_Encoder_Timer  htim5 
#define RightDriver_Encoder_Timer htim4

void DriverEncoder_init(void);

int16_t DriverEncoder_getleftcounter(void);

int16_t DriverEncoder_getrightcounter(void);

#endif
