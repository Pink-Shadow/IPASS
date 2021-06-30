#include "hwlib.hpp"
#include "MPU6050.h"

/// Constructor for the MPU6050
MPU6050::MPU6050(hwlib::i2c_bus & bus, uint_fast8_t address):
    bus(bus),
    address(address)
{
    /// Set the register "power_management_1" to 0x00 to 'wake up' the chip.
    ///
    /// Also set the accelerometer sensetivity to 1.
    /// level 1 means a sensetivity of 8192 LSB/g on a full scale range of +- 4g.
    /// You can change this if you'd like.
    write(0x00, 0x6B);  
    hwlib::wait_ms(1);
    write(0x08, 0x1C);  
                       
}

uint8_t MPU6050::single_reg_read(uint_fast8_t register_add){
    {
        uint8_t result = 0;
        bus.write(address).write(register_add);
        bus.read(address).read(result);
        return result;
    }
}

int16_t MPU6050::bit16_read(uint8_t MSB, uint8_t LSB){
    // store readings in the union and read the 16bit result.
    conv.OUT[0] = single_reg_read(LSB);
    conv.OUT[1] = single_reg_read(MSB);
    return conv.result;
}

xyz MPU6050::get_accel(){
    int16_t X = bit16_read(0x3B, 0x3C);
    int16_t Y = bit16_read(0x3D, 0x3E);
    int16_t Z = bit16_read(0x3F, 0x40);
    return xyz(X, Y, Z);
}

int MPU6050::get_temperature(){
    // calculate temperature as described in the datasheet.
    int16_t temp_raw = bit16_read(0x41, 0x42);
    return temp_raw/340 + 36.53;
}

xyz MPU6050::get_gyro(){
    int16_t X = bit16_read(0x43, 0x44);
    int16_t Y = bit16_read(0x45, 0x46);
    int16_t Z = bit16_read(0x47, 0x48);
    return xyz(X, Y, Z);
}

void MPU6050::write(uint_fast16_t input, uint_fast8_t register_add){
    {
        auto trans = bus.write(address);
        trans.write(register_add);
        trans.write(input);
    }
}