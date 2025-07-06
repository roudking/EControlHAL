#include "K210.h"

static K210_TEMP k210_temp;

void K210_init(void)
{
    K210_uartinit();
}

void K210_angledataIN(int indata)
{
   k210_temp.angle = indata;
}

void K210_stateIN(K210_STATE state)
{
   k210_temp.state = state;
}   

void K210_getangle(K210 *k210)
{
	while(k210_temp.state == k210_wait_echo){};
  k210->angle = k210_temp.angle;
	k210_temp.state = k210_wait_echo;
}