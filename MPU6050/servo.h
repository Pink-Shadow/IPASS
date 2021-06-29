#ifndef SERVO_HPP
#define SERVO_HPP
/// @file
#include "hwlib.hpp"

/// This class creates a servo object to which you can write a pulse
class servo{
private:
    hwlib::target::pin_out & PIN_OUT;
    int offset;

public:
    /// constructs an interface for the servo.
    /// You need to give the offset of the servo, the offset of the servo is the minimal treshold by which the servo can measure the pulse.
    /// For example:
    ///         The SG-90 can measure a pulse between 0.5 and 2.5 milliseconds. This can vary depending on the servo. My servo can measure a pulse somewhere
    ///         around 0.46 and 2.5. You need to pass on the offset of your servo. By default it is set to 0.5 = 500 micro seconds.
    servo(hwlib::target::pin_out & pin, const int & offset_us = 500);
    
    /// \brief
    /// Calculate pulse for servo.
    /// \details
    /// This function calculates a pulse from the newest reading and the maximum of the given axis.
    /// This is only to be used with accel_meter values, preferably the deco_average ones for more stable movement.
    float calculate_pulse(int16_t axis_reading, int16_t MAX_AXIS);
    
    /// \brief
    /// Write pulse to servo
    /// \details
    /// This function writes a give pulse to the servo.
    void write_pulse(float delay);
    
};

#endif // SERVO_HPP