#ifndef _K210_H
#define _K210_H

#include "stdio.h"
#include "string.h"

typedef struct K210
{
	/* 状态变量 */
}K210_STATUS;

typedef struct
{
    volatile K210_STATUS status;
}K210;


#endif
