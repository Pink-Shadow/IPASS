#ifndef DECORATOR_AVERAGE_HPP
#define DECORATOR_AVERAGE_HPP
/// @file

#include "accel_meter.h"


/// This decorator allows you to read out a more stable output of the accelmeter values.
class deco_average : public accel_meter{

private:
    accel_meter & minion;
    
    int16_t X[30], Y[30], Z[30];
    int total_x, total_y, total_z;
    
    xyz average;
    int old_i = 0;

public:
    /// \brief
    /// This constructor constructs the interface of the deco_average class.
    /// \details
    /// When constructing, it fills 3 arrays of 30 elemts with readings from the chip and calculates the total value.
    deco_average(accel_meter & minion);
    
    /// \brief
    /// returns average accel_meter readings.
    /// \details
    /// This funtion returns the 3 axis accel_meter measurements, as a moving average, stored in an xyz object. 
    xyz get_accel() override;
    
};

#endif // DECORATOR_AVERAGE_HPP