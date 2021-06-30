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
    servo(hwlib::target::pin_out & pin, const int & offset);
    
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