#ifndef _NVIGATION_ENCODER_H
#define _NVIGATION_ENCODER_H


#include "encoder.h"
#include "stdint.h"

//编码器分配 
#define left_Encoder_Timer  htim2 
#define right_Encoder_Timer htim3

void Encoder_init(void);

int16_t Encoder_Getleftcounter(void);

int16_t Encoder_Getrightcounter(void);

#endif
