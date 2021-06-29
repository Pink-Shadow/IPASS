#include "servo.h"

servo::servo(hwlib::target::pin_out & pin, const int & offset_us):
        PIN_OUT(pin),
        offset(offset_us)
    {}
    

float servo::calculate_pulse(int16_t axis_reading, int16_t MAX_AXIS) {
    float interval = 2.0 / (MAX_AXIS *2);
    float delay_us = (((MAX_AXIS-axis_reading) * interval) * 1000) + offset;
    
    return delay_us;
}
    
void servo::write_pulse(float delay){
    
    PIN_OUT.write(1);
    PIN_OUT.flush();
    
    hwlib::wait_us(delay);
    
    PIN_OUT.write(0);
    PIN_OUT.flush();
    
    
}