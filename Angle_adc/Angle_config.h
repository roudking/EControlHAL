#ifndef _ANGLE_CONFIG_H
#define _ANGLE_CONFIG_H

#include "my_adc.h"

typedef struct {

   ADC_HandleTypeDef *adc_port;  // ADC handle for angle sensor

    uint32_t origin_data[1];                   // Variable to store the angle value
    int index;              // Index for the angle value
    int size;               // Size of the angle data buffer

} ANGLE_CONFIG;

extern ANGLE_CONFIG angle_config;  // Declare the angle configuration structure

#endif /* _ANGLE_CONFIG_H */