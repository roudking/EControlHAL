#include "Driver_Encoder.h"

void DriverEncoder_start(DRIVER_CONFIG driver)
{
     encoder_init(driver.encoder_port);
}

int16_t DriverEncoder_getcounter(DRIVER_CONFIG driver)
{
    if (driver.encoder_polarity == 1) {
        return encoder_getcounter(driver.encoder_port);
    }
    else {
        return -encoder_getcounter(driver.encoder_port);
    }

}
