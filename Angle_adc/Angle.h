#ifndef _ANGLE_H
#define _ANGLE_H

#include "Angle_adc.h"

typedef struct {
    ANGLE_CONFIG config;  // Configuration for the angle sensor
    double angle;          // Current angle value in degrees
    double last_angle;    // Last angle value for comparison
    double filter_angle;  // Filtered angle value
} ANGLE;

void Angle_create(ANGLE *angle, ANGLE_CONFIG config);
void Angle_init(ANGLE *angle);
void Angle_read(ANGLE *angle);

#endif /* _ANGLE_H */