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
  volatile int num;
	volatile int green_area;
	volatile Resberry_STATE state;
}RESBERRY_TEMP;

typedef struct
{
  volatile int num[2];
	volatile int green_area;
	volatile Resberry_STATE state;	
}RESBERRY;

void Resberry_init(void);
void Resberry_greenareadataIN(int indata);
void Resberry_numerdataIN(int num);
void Resberry_stateIN(Resberry_STATE state);
void Resberry_getgreen_area(RESBERRY *resberry);
//void Resberry_getnumer(RESBERRY *resberry);
void Resberry_sendgetnumercmd(RESBERRY *resberry);
void Resberry_getstate(RESBERRY *resberry);
void Resberry_getnumber(RESBERRY *resberry);


#endif
