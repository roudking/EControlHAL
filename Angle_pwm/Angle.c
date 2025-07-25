#include "Angle.h"

static void Angle_ICCallbackfunc(void);
static ANGLE angle_buffer;

/**
 * @brief Create and initialize the angle buffer with the given configuration.
 * This function initializes the input capture for angle measurement and registers the callback function.
 * 
 * @param config Configuration for angle measurement, including timer handle and capture channels.
 */
void Angle_Create_and_Initbuffer(ANGLE_CONFIG config) {
    angle_buffer.config = config;

    // Initialize the input capture for angle measurement
    Angle_ic_init(angle_buffer.config);

    // Register the callback function for input capture events
    tim_ic_callbackregister(angle_buffer.config.htim, Angle_ICCallbackfunc);
}


/**
 * @brief Callback function for input capture events.
 * This function is called when an input capture event occurs.
 * It retrieves the captured values and calculates the frequency and duty cycle.
 */
static void Angle_ICCallbackfunc(void) { 
			angle_buffer.config.CCR1 = Angle_ic_getvalue(angle_buffer.config, TIM_CHANNEL_1);
			if(angle_buffer.config.CCR1 != 0)
				{
					angle_buffer.config.CCR2 = Angle_ic_getvalue(angle_buffer.config, TIM_CHANNEL_2);
					angle_buffer.frequency = (double)angle_buffer.config.cnt_clk/(angle_buffer.config.CCR1+1);
					angle_buffer.duty = (double)(angle_buffer.config.CCR2+1)*100/(angle_buffer.config.CCR1+1);
				}
			else
				{
					angle_buffer.frequency = 0;
					angle_buffer.duty = 0;
				}
}


 /**
 * @brief Get the current duty cycle and frequency from the angle buffer.
 * This function updates the angle structure with the latest duty cycle and frequency.
 * 
 * @param angle Pointer to the ANGLE structure to update.
 */
void Angle_getduty_and_frequency(ANGLE *angle) {
	angle->duty = angle_buffer.duty; // Return the current duty cycle
	angle->frequency = angle_buffer.frequency; // Return the current frequency
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
	if(angle->angle > 330 && angle->last_angle < 30) {
		cnt--; // Increment the counter if crossing zero
	} else if(angle->angle < 30 && angle->last_angle > 330) {
		cnt++; // Decrement the counter if crossing zero in the opposite direction
	}

	 angle->real_angle = angle->angle + cnt * 360; // Adjust the angle based on the counter
}
