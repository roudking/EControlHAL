#ifndef _DHT11_H
#define _DHT11_H

#include "DHT11_gpio.h"
#include "my_delay.h"

typedef struct
{

  unsigned int rec_data[4];	
  
}DHT11;

void DHT11_REC_Data(DHT11 *dht11);



#endif
