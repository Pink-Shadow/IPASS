#ifndef MPU6050_HPP
#define MPU6050_HPP
/// @file

/// MPU6050 acceleration, gyroscope and temperature sensor.
///
/// This is a class for the MPU6050.
/// The MPU6050 is a chip that can measure the gravity acceleration on the X, Y and Z axis, the
/// temperature of the sensor, aswell as a gyroscope. 
/// The operating voltage is around 2.4V - 3.5V (for the exact operating voltage, please refer to the datasheet: <A>https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf</A>
/// 
/// The connections to the chip are as followed:
///     - VCC: 3.3V
///     - GND: ground
///     - SCL: GPIO pin / scl pin (on the arduino)
///     - SDA: GPIO pin / sda pin (on the arduino)
///     - XDA: used to add third party sensors like a magnetor meter
///     - XCL: used to add third party sensors like a magnetor meter
///     - AD0: is used to determine the chips I2C address. 
///            AD0 to ground:   0x68.
///            AD0 to VCC:      0x69.
///     - INT: is used to trigger interrupts.
///
///
/// This code declares the funtions used by the MPU6050 class.


#include "accel_meter.h"
#include "temp_meter.h"
#include "gyro_meter.h"

/// This class allows you to read and write to the MPU6050 chip
class MPU6050 : public accel_meter, public temp_meter, public gyro_meter{
private:
    hwlib::i2c_bus & bus;
    uint_fast8_t address;
    
public:
    /// This union is used to convert unsigned 8-bit integers to signed 16-bit integers.
    union{
        int16_t result;
        uint8_t OUT[2]; 
    } conv;
    
    /// \brief
    /// Construct the interface for the MPU6050
    /// \details
    /// This constructor creates the interface of the MPU6050 with the default I2C address set to 0x68.
    MPU6050(hwlib::i2c_bus & bus, uint_fast8_t address = 0x68);
    
    /// \brief
    /// return a single 8 bit data read
    /// \details
    /// This funtion returns a single byte of data out of the given register.
    uint8_t single_reg_read(uint_fast8_t register_add);
    
    /// \brief
    /// return 16 bit data from 2 registers combined
    /// \details
    /// This funtion returns a 16 bit integer value of the given High and Low data registers.
    /// It uses the conv union to convert the two 8-bit registers to a 16-bit value.
    int16_t bit16_read(uint8_t MSB, uint8_t LSB);
    
    /// \brief
    /// returns axis readings
    /// \details
    /// This funtion returns the 3 axis accelerometer readings as an xyz object.
    xyz get_accel() override;
    
    /// \brief
    /// returns temperature
    /// \details
    /// this funtion returns an integer value of degrees in Celcius, measured by the sensor.
    int get_temperature() override;
    
    /// \brief
    /// return gyroscope values
    /// \details
    /// This funtion returns the 3 axis gyroscope readings as an xyz object.
    xyz get_gyro() override;
    
    /// \brief
    /// write to register
    /// \details
    /// This funtion allows you to write data into a given register.
    void write(uint_fast16_t input, uint_fast8_t register_add);
    
       
};

#endif // MPU6050_HPP