#include "Driver_Encoder.h"

void DriverEncoder_init(void)
{
	 encoder_init(&LeftDriver_Encoder_Timer);
	 encoder_init(&RightDriver_Encoder_Timer);
}

int16_t DriverEncoder_getleftcounter(void)
{
	return encoder_getcounter(&LeftDriver_Encoder_Timer);
}

int16_t DriverEncoder_getrightcounter(void)
{
	return encoder_getcounter(&RightDriver_Encoder_Timer);
}

