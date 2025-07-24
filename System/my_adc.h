#ifndef _MY_ADC_H
#define _MY_ADC_H

#include "adc.h"

void adc_calibration_start(ADC_HandleTypeDef *adc);
void adc_start(ADC_HandleTypeDef *adc);
void adc_getdata(ADC_HandleTypeDef *adc, uint32_t *data, int data_head_index, int data_size);

#endif /* _MY_ADC_H */