#ifndef TEMP_METER
#define TEMP_METER
/// @file

/// This is an abstract class used for temperature meters. 
#include "hwlib.hpp"

class temp_meter{
public:

    /// an interface to read the temperature, used in MPU6050, deco_average and zero_point.
    virtual int get_temperature() = 0;
    
};


#endif // TEMP_METER