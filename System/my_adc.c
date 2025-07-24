#include "my_adc.h"
 
void adc_calibration_start(ADC_HandleTypeDef *adc){
    // Start ADC calibration process
    HAL_ADCEx_Calibration_Start(adc);
}

static uint32_t adc1_databuffer[100];
// static uint32_t adc2_databuffer[100];

#define adc1_databuffersize 1
// #define adc2_databuffersize 1


void adc_start(ADC_HandleTypeDef *adc) {
    // Start ADC conversion in DMA mode
   if(adc->Instance == ADC1)
    {
      HAL_ADC_Start_DMA(&hadc1, adc1_databuffer, adc1_databuffersize);
    } 
//    else if(adc->Instance == ADC2)
//     {
//       HAL_ADC_Start_DMA(&hadc2, adc2_databuffer, adc2_databuffersize);
//     }
}

void adc_getdata(ADC_HandleTypeDef *adc, uint32_t *data, int data_head_index, int data_size) {
    // Get ADC data from the buffer
    if(adc->Instance == ADC1) {
        for (int i = 0; i < data_size; i++) {
            data[i] = adc1_databuffer[data_head_index + i];
        }
    }
    // else if(adc->Instance == ADC2) {
    //     for (uint32_t i = 0; i < data_size; i++) {
    //         data[i] = adc2_databuffer[data_head_index + i];
    //     }
    // }
}
