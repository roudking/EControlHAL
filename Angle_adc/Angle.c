#include "Angle.h"

void Angle_create(ANGLE *angle, ANGLE_CONFIG config) {
    angle->config = config;
}

void Angle_init(ANGLE *angle) {
    // Initialize angle sensor by starting ADC
    Angle_adc_start(&angle->config);
}

static double angle_Cal(uint16_t origin_data) {
    // Convert raw ADC data to angle in degrees
    // Assuming a linear mapping from ADC value to angle
    // Adjust the conversion factor based on your specific sensor characteristics
    double angle = (double)origin_data * 360.0 / 4096.0; // Example for a 12-bit ADC
    return angle;
}

void Angle_read(ANGLE *angle) {
    // Read angle data from ADC
    Angle_adc_read(&angle->config);
    
    // Store the last angle value
    angle->last_angle = angle->angle; 

    // Process the raw ADC data to get the angle value
    angle->angle = angle_Cal(angle->config.origin_data[0]);

     // Apply a simple low-pass filter to the angle
     double filter = 0.3; // Filter coefficient, adjust as needed
    angle->filter_angle = filter * angle->filter_angle + (1 - filter) * angle->angle;

}