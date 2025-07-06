#include "Resberry_Pi.h"

static RESBERRY_TEMP resberry_temp;

void Resberry_init(void)
{
   Resberry_uartinit();
}

void Resberry_speeddataIN(int indata)
{
   resberry_temp.speed = indata;
}

void Resberry_getspeed(RESBERRY *resberry)
{
	resberry->speed = resberry_temp.speed;
}

void Resberry_angledataIN(double angle)
{
   resberry_temp.angle = angle;
}

void Resberry_getangle(RESBERRY *resberry)
{
	resberry->angle = resberry_temp.angle;
}

void Resberry_stateIN(Resberry_STATE state)
{
   resberry_temp.state = state;
}   

void Resberry_getstate(RESBERRY *resberry)
{
	resberry->state = resberry_temp.state;
}

