#include "Nvigation_Encoder.h"

void Encoder_init(void)
{
	 encoder_init(&left_Encoder_Timer);
	 encoder_init(&right_Encoder_Timer);
}

int16_t Encoder_Getleftcounter(void)
{
   return encoder_getcounter(&left_Encoder_Timer);
}

int16_t Encoder_Getrightcounter(void)
{
	return encoder_getcounter(&right_Encoder_Timer);
}
