#ifndef _RESBERRY_PI_H
#define _RESBERRY_PI_H

#include "Resberry_uart.h"

typedef enum
{
     resberry_wait_echo,
	 resberry_complite_echo
}Resberry_STATE;

typedef struct
{
    volatile int speed;
	volatile double angle;
	volatile Resberry_STATE state;
}RESBERRY_TEMP;

typedef struct
{
    volatile int speed;
	volatile double angle;
	volatile Resberry_STATE state;
}RESBERRY;

void Resberry_init(void);

void Resberry_speeddataIN(int indata);
void Resberry_getspeed(RESBERRY *resberry);
void Resberry_angledataIN(double angle);
void Resberry_getangle(RESBERRY *resberry);
void Resberry_stateIN(Resberry_STATE state);
void Resberry_getstate(RESBERRY *resberry);



#endif
