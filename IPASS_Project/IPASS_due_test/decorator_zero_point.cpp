#include "decorator_zero_point.h"

zero_point::zero_point(accel_meter & minion):
        minion(minion)
    {
//            hwlib::cout << "HOLD HORIZONTAL" <<"\n"; hwlib::wait_ms(2000);
//            Z_MAX = minion.read().Z;
//            hwlib::cout << "HOLD VERTICAL" << "\n"; hwlib::wait_ms(2000);
//            X_MAX = minion.read().X;
//            hwlib::cout << "HOLD SIDEWAYS" << "\n"; hwlib::wait_ms(2000);
//            Y_MAX = minion.read().Y;
//            hwlib::cout << "DONE!" << Y_MAX << "\t" << X_MAX << "\t" << Z_MAX << hwlib::endl;
    }



xyz zero_point::get_accel(){    
//    xyz offsets(X_MAX, Y_MAX, Z_MAX);
    xyz offsets(8122, 8304, 8736);

    return offsets;
}