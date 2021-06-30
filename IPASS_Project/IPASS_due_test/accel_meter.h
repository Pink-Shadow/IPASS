#ifndef ACCELERATION_METER
#define ACCELERATION_METER
/// @file

#include "hwlib.hpp"

/// This class is used to store X, Y and Z values.
class xyz{
public:
    int16_t X;
    int16_t Y;
    int16_t Z; 
    
    /// Constructs the object from the given x, y and z values.
    xyz(int16_t x, int16_t y, int16_t z):
        X(x),
        Y(y),
        Z(z)
    {}
    
    xyz():
        X(0), Y(0), Z(0)
    {}
    
    /// \brief
    /// This operator adds two xyz objects.
    /// \details
    /// This operator+ adds two xyz's and returns the result.
    xyz operator+(const xyz & rhs) const{
        return xyz(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
    }
    
    /// \brief
    /// add an xyz to another xyz
    /// \details
    /// This operator+= adds an xyz to another xyz.
    xyz & operator+=(const xyz & rhs) {
        X = X + rhs.X;
        Y = Y + rhs.Y;
        Z = Z + rhs.Z;
        
        return *this;
    }
    
    /// \brief
    /// This operator- subtracts two xyz objects.
    /// \details
    /// This operator- subtracts two xyz's and returns the result.
    xyz operator-(const xyz & rhs) const{
        return xyz(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
    }
    
    /// \brief
    /// subtract an xyz off another xyz
    /// \details
    /// This operator-= subtracts an xyz off of another xyz.
    xyz & operator-=(const xyz & rhs) {
        X = X - rhs.X;
        Y = Y - rhs.Y;
        Z = Z - rhs.Z;
        
        return *this;
    }
    
    /// \brief
    /// Multiply xyz by an integer.
    /// \details
    /// This operator* muliplies an xyz by an integer and returns the result.
    xyz operator*(const int & rhs) const{
        return xyz(X * rhs, Y * rhs, Z * rhs);
    }
    
    /// \brief
    /// Multiply xyz by an integer.
    /// \details
    /// This operator*= multiplies an xyz by an integer.
    xyz & operator*=(const int & rhs) {
        X = X * rhs;
        Y = Y * rhs;
        Z = Z * rhs;
        
        return *this;
    }
    
    /// \brief
    /// This operator== checks for equality.
    /// \details
    /// This operator== returns true, only if every axis value is equal to the axis value of the other xyz.
    bool operator==(const xyz & rhs) const {
        return (X == rhs.X) && (Y == rhs.Y) && (Z == rhs.Z);
    }
    
};

/// This is an abstract class used for accelerometer readings. 
class accel_meter {
public:

    /// an interface to read 3 axis, used in MPU6050.
    virtual xyz get_accel() = 0;
};

#endif // ACCELERATION_METER