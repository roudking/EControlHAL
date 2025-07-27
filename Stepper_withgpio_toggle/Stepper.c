#include "Stepper.h"

#define STEPPER_BUFFER_NUM 2 // Define the size of the stepper buffer
static STEPPER stepper_buffer[STEPPER_BUFFER_NUM];

static void Stepper_timecallbackfunc(void);

void Stepper_create(STEPPER *stepper, STEPPER_CONFIG config, int index) {
    stepper->index = index; // Set the index for the stepper
    stepper_buffer[index - 1].config = config; // Store the stepper in the buffer
    stepper->config = config; // Initialize the stepper configuration

}

void Stepper_init(STEPPER *stepper) {
    tim_callbackregister(stepper->config.tim_port, Stepper_timecallbackfunc);
    tim_it_start(stepper->config.tim_port);
}

void Stepper_set_steps_relative(STEPPER *stepper, int steps) {
    // Store the last step count for comparison
    stepper_buffer[stepper->index - 1].status.arrived = 0; 

    // Set direction based on steps
    Stepper_gpio_set_direction(stepper_buffer[stepper->index - 1].config, steps > 0 ? 1 : -1);

    // Update the step count in the buffer
    stepper_buffer[stepper->index - 1].step_count = steps > 0 ? steps : -steps;
}

void Stepper_get_arrived(STEPPER *stepper) {
    // Check if the stepper has arrived at the target position
    stepper->status.arrived = stepper_buffer[stepper->index - 1].status.arrived;
}

static void Stepper_timecallbackfunc(void) {
    for(int i = 0; i < STEPPER_BUFFER_NUM; i++) {
        if(stepper_buffer[i].step_count > 0 && stepper_buffer[i].status.arrived == 0) {

            // If there are steps to take, toggle the step pin 
            Stepper_gpio_togglepin(stepper_buffer[i].config);

            // Toggle the status
            stepper_buffer[i].status.toggle = stepper_buffer[i].status.toggle == 0 ? 1 : 0; 

            if (stepper_buffer[i].status.toggle == 0) {
                // If toggled, decrement the step count
                stepper_buffer[i].step_count--;
            }
            
        } else {
            // If no steps left, set arrived status
            stepper_buffer[i].status.arrived = 1;

            // Reset step count
            stepper_buffer[i].step_count = 0;
        }
    }
}

void Stepper_set_steps_absolute(STEPPER *stepper, int steps) {
    stepper->last_step_count = stepper->step_count; // Store the last step count for comparison
    stepper->step_count = steps; // Set the new step count
    int relative_steps = stepper->step_count - stepper->last_step_count;

    Stepper_set_steps_relative(stepper, relative_steps);
}
