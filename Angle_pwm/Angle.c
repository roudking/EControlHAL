#include "Angle.h"

/**
 * @brief Create and initialize the angle buffer with the given configuration.
 * This function initializes the input capture for angle measurement and registers the callback function.
 * 
 * @param config Configuration for angle measurement, including timer handle and capture channels.
 */
void Angle_Create(ANGLE *angle, ANGLE_CONFIG *config) {
	// Register the callback function for input capture events
	Angle_config_set_anglecallback(config, Angle_ic_callbackfunc); 
	angle->config = config;
}

/**
 * @brief Initialize the angle structure.
 * This function sets up the input capture for angle measurement and initializes the angle buffer.
 * 
 * @param angle Pointer to the ANGLE structure to initialize.
 */
void Angle_init(ANGLE *angle) {

    tim_ic_callbackregister(angle->config->htim, angle->config->tim_ic_callback);
	Angle_ic_init(*angle->config); // Initialize the input capture for angle measurement

}

/**
 * @brief Get the current duty cycle and frequency from the angle buffer.
 * This function updates the angle structure with the latest duty cycle and frequency.
 * 
 * @param angle Pointer to the ANGLE structure to update.
 */
void Angle_getduty_and_frequency(ANGLE *angle) {
	angle->duty = angle->config->data_buffer.duty; // Return the current duty cycle
	angle->frequency = angle->config->data_buffer.frequency; // Return the current frequency
}


/**
 * @brief Calculate the angle based on the duty cycle.
 * The duty cycle is expected to be in the range of 0-100%.
 * 
 * @param duty The duty cycle percentage (0-100).
 * @return The calculated angle in degrees (0-360).
 */
static double Angle_CalculateAngle(double duty) {
	// Calculate the angle based on the duty cycle 0-100% mapped to 0-360 degrees
	return (duty / 100.0) * 360.0; // Return the angle in degrees
}

 /**
 * @brief Get the current angle based on the duty cycle.
 * This function updates the angle field in the ANGLE structure.
 * 
 * @param angle Pointer to the ANGLE structure to update.
 */
void Angle_getangle(ANGLE *angle) {
	angle->last_angle = angle->angle; // Store the last angle
	Angle_getduty_and_frequency(angle); // Get the current duty cycle and frequency
	angle->angle = Angle_CalculateAngle(angle->duty); // Calculate the angle based on the duty cycle

	 static int cnt = 0;
	if(angle->angle >= 300 && angle->last_angle < 60) {
		cnt--; // Increment the counter if crossing zero
	} else if(angle->angle < 60 && angle->last_angle > 300) {
		cnt++; // Decrement the counter if crossing zero in the opposite direction
	}

	 angle->real_angle = angle->angle + cnt * 360; // Adjust the angle based on the counter
}
