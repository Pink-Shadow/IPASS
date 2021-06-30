#ifndef DECORATOR_ZERO_POINT
#define DECORATOR_ZERO_POINT

/// @file

#include "accel_meter.h"

/// This class is used to store the maximum force on the X, Y and Z axis, as measured by the accelerometer.
class zero_point : public accel_meter{
private:
    accel_meter & minion;
    int16_t X_MAX, Y_MAX, Z_MAX;

public:
    /// \brief
    /// This constructor constructs the interface of the zero_point class.
    /// \details
    /// This constructor can measure the maximum forces on the accelerometer axis
    /// You can hardcode these valus if you'd like in the zero_point::read() funtion, and comment out the body of the constructor.
    zero_point(accel_meter & minion);
    
    
    /// \brief 
    /// returns maximum measurements
    /// \details
    /// This funtion returns the maximum measurements as an xyz object.
    /// If you choose to hardcode the maximum readings, you can uncomment the line " xyz offsets(X_MAX, Y_MAX, Z_MAX); " and
    /// return your hardcoded values as an object of the xyz class with the xyz(int16_t x, int16_t y, int16_t z) function.  
    xyz get_accel() override;
    
};

#endif // DECORATOR_ZERO_POINT