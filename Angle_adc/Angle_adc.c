#include "Angle_adc.h"

void Angle_adc_start(ANGLE_CONFIG *config) {
    // Start ADC calibration for angle sensor
    adc_calibration_start(config->adc_port);

    // Start ADC conversion in DMA mode
    adc_start(config->adc_port);
}

void Angle_adc_read(ANGLE_CONFIG *config) {
    // Get ADC data for angle sensor
    adc_getdata(config->adc_port, config->origin_data, config->index, config->size);
}