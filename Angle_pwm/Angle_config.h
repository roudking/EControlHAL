#ifndef __ANGLE_CONFIG_H
#define __ANGLE_CONFIG_H

#include "tim_ic.h"

typedef struct{
    double frequency; // Frequency of the angle signal
    double duty;      // Duty cycle of the angle signal
    double angle;     // Calculated angle based on duty cycle
} DATA_BUFFER;

typedef struct ANGLE_CONFIG{
    TIM_HandleTypeDef *htim; // Timer handle for input capture
    int prescaler;           // Prescaler value for the timer
    int cnt_clk;             // Counter clock frequency
    int CCR1;
    int CCR2;

    volatile DATA_BUFFER data_buffer; // Buffer to store angle data

    void (*tim_ic_callback)(void); // Callback function for input capture events
    void (*angle_callbackfunc)(struct ANGLE_CONFIG *config); // Callback function for angle calculation

} ANGLE_CONFIG;

extern ANGLE_CONFIG angle1_config;

void Angle_config_set_anglecallback(ANGLE_CONFIG *config, void (*callback)(ANGLE_CONFIG *)); // Function to set the angle calculation callback

#endif // __ANGLE_CONFIG_H