#ifndef _K210_H
#define _K210_H

#include "K210_usart.h"


typedef enum
{
   k210_wait_echo,
	 k210_complite_echo
}K210_STATE;

typedef struct
{
	volatile int angle;
	volatile K210_STATE state;
}K210_TEMP;

typedef struct
{
   int angle;
}K210;

void K210_init(void);
void K210_angledataIN(int indata);
void K210_stateIN(K210_STATE state);

void K210_getangle(K210 *k210);

#endif
