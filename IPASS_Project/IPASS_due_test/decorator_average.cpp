#include "decorator_average.h"

deco_average::deco_average(accel_meter & minion):
        minion(minion)
    {
            // Set all array indexes to the first 30 readings.
            for(int i = 0; i < 30; i++){
                xyz tmp = minion.get_accel();
                X[i] = tmp.X;
                Y[i] = tmp.Y;
                Z[i] = tmp.Z;
            }
            
            // Calculate total on the X-axis
            total_x = 0;
            for(const auto & x : X){
                total_x += x;
            }
            
            // Calculate total on the Y-axis
            total_y = 0;
            for(const auto & y : Y){
                total_y += y;
            }
            
            // Calculate total on the Z-axis
            total_z = 0;
            for(const auto & z : Z){
                total_z += z;
            }
            
            
    }


xyz deco_average::get_accel(){
    // Get latest readings
    xyz tmp = minion.get_accel();
    
    // If index is above array size, reset it.
    if(old_i > 29){
        old_i = 0;
    }

    // Subtract oldest reading and add newest to the total of each axis.
    total_x = ((total_x - X[old_i]) + tmp.X);
    total_y = ((total_y - Y[old_i]) + tmp.Y);
    total_z = ((total_z - Z[old_i]) + tmp.Z);
    
    // Set newest reading at the oldes index.
    X[old_i] = tmp.X;
    Y[old_i] = tmp.Y;
    Z[old_i] = tmp.Z;
    
    // Add one to index.
    old_i++;
    
    // return an xyz object with the average measurements.
    return xyz(total_x / 30, total_y / 30, total_z / 30);
}