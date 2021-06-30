#include "hwlib.hpp"
#include "MPU6050.h"
#include "decorator_average.h"
#include "decorator_zero_point.h"
#include "servo.h"

int main(){
    hwlib::wait_ms(2000);
    
    // initialize servo pins.
    auto servo_pin_Y = hwlib::target::pin_out (hwlib::target::pins::d3);
    auto servo_pin_X = hwlib::target::pin_out (hwlib::target::pins::d2);
    
    // setup CLOCK and DATA pin and combine them in a I2C BUS.
    auto scl = hwlib::target::pin_oc (hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc (hwlib::target::pins::sda);
    auto bus = hwlib::i2c_bus_bit_banged_scl_sda (scl, sda);
    //=====================================
    
    // default address: 0x68.
    auto mpu = MPU6050(bus); 
    
    // Setup decorators.
    auto mid = deco_average(mpu);
    auto zero = zero_point(mpu);
    
    // Initialize servo objects.
    auto serv_Y = servo(servo_pin_Y, 460);
    auto serv_X = servo(servo_pin_X, 460);
    
    // Read maximum force on all axis.
    xyz offsets = zero.get_accel();
    
    for(;;){
        
        // Read the moving average of the force on each axis, calculated from 30 readings.
        xyz accel = mid.get_accel();
        
        // Write readings to the servo's and calculate the HIGH pulse length.
        int delay_y = serv_Y.calculate_pulse(accel.Y, offsets.Y);
        int delay_x = serv_X.calculate_pulse(accel.X, offsets.X);
        
        serv_Y.write_pulse(delay_y);
        serv_X.write_pulse(delay_x);
    
        // Wait so the servo has enough time to adjust to new data.
        hwlib::wait_ms(15);
    }
}