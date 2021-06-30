#ifndef GYRO_METER
#define GYRO_METER
/// @file

#include "hwlib.hpp"

/// This is an abstract class used for gyroscope meters. 
class gyro_meter{
public:

    /// an interface to read the gyroscope readings, used in MPU6050.
    virtual xyz get_gyro() = 0;
    
};


#endif // GYRO_METER