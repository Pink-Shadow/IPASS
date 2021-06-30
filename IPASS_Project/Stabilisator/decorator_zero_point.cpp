#include "decorator_zero_point.h"

zero_point::zero_point(accel_meter & minion):
        minion(minion)
    {
//            char c;
//            
//            hwlib::cout << "HOLD HORIZONTAL" <<"\n"; hwlib::cout << "--------------Press any key to continue--------------\n\n";
//            hwlib::cin >> c;
//            Z_MAX = minion.get_accel().Z;
//            hwlib::cout << "HOLD VERTICAL" << "\n"; hwlib::cout << "--------------Press any key to continue--------------\n\n";
//            hwlib::cin >> c;
//            X_MAX = minion.get_accel().X;
//            hwlib::cout << "HOLD SIDEWAYS" << "\n"; hwlib::cout << "--------------Press any key to continue--------------\n\n";
//            hwlib::cin >> c;
//            Y_MAX = minion.get_accel().Y;
//            hwlib::cout << "DONE!" << Y_MAX << "\t" << X_MAX << "\t" << Z_MAX << "--------------Press any key to continue--------------\n\n";
//            hwlib::cin >> c;
    }



xyz zero_point::get_accel(){    
//    xyz offsets(X_MAX, Y_MAX, Z_MAX);
    xyz offsets(8620, 8122, 8736);

    return offsets;
}