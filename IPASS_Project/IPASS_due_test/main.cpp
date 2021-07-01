#include "MPU6050.h"
#include "decorator_average.h"
#include "decorator_zero_point.h"
#include "servo.h"

int main()
{
    hwlib::wait_ms(2000);
    auto servo_pin_Y = hwlib::target::pin_out (hwlib::target::pins::d5);
    
    auto scl = hwlib::target::pin_oc (hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc (hwlib::target::pins::sda);
    auto bus = hwlib::i2c_bus_bit_banged_scl_sda (scl, sda);
    
    auto serv = servo(servo_pin_Y, 500);
    
    auto mpu = MPU6050(bus);
    auto mid = deco_average(mpu);
    auto zero = zero_point(mid);
    
    char c;
    
    //*********************************************************
    hwlib::cout << "Test case 1:\n\n" << "We beginnen met de accelerometer. U krijgt straks en paar instructies in beeld van hoe u\nde chip moet orienteren voor de accelerometer test.\n\n";
    hwlib::cout << "--------------Press any key to continue--------------\n\n";
    hwlib::cin >> c;
        
    hwlib::cout << "Instructie 1 'X-as': " << "houd de sensor met de chip naar u toe, verticaal en met de kabels naar de grond gericht.\nDe waarde zou tussen 8100 en 8800 moeten zijn." << "\n";
    hwlib::cout << "Druk op een toets als u de chip op die manier georienteerd hebt...\n\n";
    hwlib::cin >> c;
    
    xyz accel = mpu.get_accel();
    int16_t X = accel.X;
    
    hwlib::cout << "Instructie 2 'Y-as':\n\n" << "houd de sensor vanuit de pin-kant gezien, op zijn rechter zij gekantelt, met de chip naar u toe.\nDe waarde zou tussen de 7700 en 8800 moeten zijn.\n";
    hwlib::cout << "Druk op een toets als u de chip op die manier georienteerd hebt...\n\n";
    hwlib::cin >> c;
    
    accel = mpu.get_accel();
    int16_t Y = accel.Y;
    
      
    hwlib::cout << "Instructie 3 'Z-as':\n\n" << "Houd de sensor met de chip naar boven parallel met de grond houd.\nDe waarde zou tussen 8600 en 9300 moeten zijn." << "\n";
    hwlib::cout << "Druk op een toets als u de chip op die manier georienteerd hebt...\n\n";
    hwlib::cin >> c;
    
    accel = mpu.get_accel();
    int16_t Z = accel.Z;
    
    hwlib::cout << "De waardes zijn:\n" << "X: " << X << "\t" << "Y: " << Y << "\t" << "Z: " << Z << "\n\n";

    if(8200 < X && X < 8800){
        hwlib::cout << "De X as meting is correct!" << "\n";
    }
    else{
        hwlib::cout << "De X as meting is niet correct..." << "\n";
    }
    if(7700 < Y && Y < 8800){
        hwlib::cout << "De Y as meting is correct!" << "\n";
    }
    else{
        hwlib::cout << "De Y as meting is niet correct..." << "\n";
    }
    if(8600 < Z && Z < 9300){
        hwlib::cout << "De Z as meting is correct!" << "\n\n";
    }
    else{
        hwlib::cout << "De Z as meting is niet correct..." << "\n\n";
    }
    
    hwlib::cout << "Nu volgt de gemiddelde decorator...\n";
    hwlib::cout << "--------------Press any key to continue--------------\n";
    hwlib::cin >> c;
    
    //**********************************************************  
  
    hwlib::cout << "Test case 2:\n\n" << "Nu gaan we de gemiddelde decorator testen. Deze zou bij elke as\neen verschil van tussen de 0 en 700 moeten hebben in zijn maximale meting en minimale meting van 30 metingen." << "\n";
    hwlib::cout << "LET OP: HOUD DE SENSOR STIL.\n";
    hwlib::cout << "Druk op een toets als u de chip stabiel gepositioneerd heeft...\n\n";
    
    hwlib::cin >> c;
    
    int16_t x[30], y[30], z[30];
    for(int i = 0; i < 30; i++){
        xyz tmp = mpu.get_accel();
        x[i] = tmp.X;
        y[i] = tmp.Y;
        z[i] = tmp.Z;
    }
    int16_t max_x = x[0];
    int16_t max_y = y[0];
    int16_t max_z = z[0];
    
    int16_t min_x = x[0];
    int16_t min_y = y[0];
    int16_t min_z = z[0];
    
    for(int i = 0; i < 30; i++){
        if(x[i] > max_x){
            max_x = x[i];
        }
        if(x[i] < min_x){
            min_x = x[i];
        }
        if(y[i] > max_y){
            max_y = y[i];
        }
        if(y[i] < min_y){
            min_y = y[i];
        }
        if(z[i] > max_z){
            max_z = z[i];
        }
        if(z[i] < min_z){
            min_z = z[i];
        }
        
//        hwlib::cout << max_x << "\t" << max_y << "\t" << max_z << "\t\t" << min_x << "\t" << min_y << "\t" << min_z << "\n";
    }
    
    int16_t verschilX = max_x - min_x;
    int16_t verschilY = max_y - min_y;
    int16_t verschilZ = max_z - min_z;
    
    hwlib::cout << "De verschillen zijn:\n" << "X: " << verschilX << "\t" << "Y: " << verschilY << "\t" << "Z: " << verschilZ << "\n\n";
    
    if( (0 <= verschilX && verschilX < 700) ){
        hwlib::cout << "De decorator werkt goed op de X as\n";
    }
    else{
        hwlib::cout << "De decorator werkt niet goed op de X as\n";
    }
    if( (0 <= verschilY && verschilY < 500) ){
        hwlib::cout << "De decorator werkt goed op de Y as\n";
    }
    else{
        hwlib::cout << "De decorator werkt niet goed op de Y as\n";
    }
    if( (0 <= verschilZ && verschilZ < 500) ) {
        hwlib::cout << "De decorator werkt goed op de Z as\n\n";
    }
    else{
        hwlib::cout << "De decorator werkt niet goed op de Z as\n\n";
    }
    
    hwlib::cout << "Nu volgt de servo pulse test...\n";
    hwlib::cout << "--------------Press any key to continue--------------\n";
    hwlib::cin >> c;  
    

    
    //**********************************************************
    
    hwlib::cout << "Test case 3:\n\n" << "Nu gaan we de servo pulse berekening testen. Ik geef 2 test waardes. 2000 als maximum,\nen 0 als current reading. Het resultaat ervan is dat dat jou servo op 90 graden zou moeten staan.\nDe delay zou dan 1500 moeten zijn." << "\n";
    hwlib::cout << "Druk op een toets als u verder wilt gaan\n\n";
    hwlib::cin >> c;  
    
    int result = serv.calculate_pulse(0, 2000);
    hwlib::cout << "Het resultaat is een delay van: " << result << "\n";
    
        
    if( (result == 1500) ){
        hwlib::cout << "De calculate_pulse funtie werkt goed!\n\n";
    }
    else{
        hwlib::cout << "De calculate_pulse funtie werkt niet goed...\n\n";
    }
    
    hwlib::cout << "Nu volgt de temperatuur test..." << "\n";
    hwlib::cout << "--------------Press any key to continue--------------\n";
    hwlib::cin >> c;  
    
    
    
    //**********************************************************
    
    hwlib::cout << "Test case 4:\n\n" << "Nu gaan we de temperatuur sensor testen. Deze zou ongeveer tussen\nde 24 en 33 graden Celcius moeten aangeven (op kamer temperatuur)" << "\n";
    hwlib::cout << "Druk op een toets als u de chip klaar hebt om te testen...\n\n";
    
    hwlib::cin >> c;
    
    int temperature = mpu.get_temperature();
    
    hwlib::cout << "De temperatuur is:\t" << temperature << "\n";
    
    if(24 < temperature && temperature < 33){
        hwlib::cout << "De temperatuur meting is correct!" << "\n\n";
    }
    else{
        hwlib::cout << "De temperatuur meting is niet correct..." << "\n\n";
    }
    
    hwlib::cout << "We zijn klaar met de chip testen!\n";
    hwlib::cout << "--------------Press any key to continue--------------\n";
    hwlib::cin >> c;
    
        
    //**********************************************************
    
    hwlib::cout << "Test case 5:\n\n" << "Als laatst gaan we de gyroscoop testen. Dit gaat iets anders dan de rest.\nOmdat we deze niet makkelijk kunnen testen met dingen berekenen enzovoort, doen we het als volgt:\n";
    hwlib::cout << "Je krijgt zometeen oneindig veel readings te zien van de gyroscoop, in het format: X Y Z.\nHier kun je zelf naar kijken en bepalen of het is wat je verwacht.\nJe zou positieve waardes moeten meten als je naar de ene kant kantelt, en negatieve waardes naar de andere kant.\n\n";
    hwlib::cout << "de X is wanneer je met de chip naar boven en kabels naar je toe, de chip naar links en rechts kantelt.\nDe Y is als je op die manier naar voren kantelt en naar achter.\nEn de Z is wanneer je hem naar rechts en links laat wijzen.";
    hwlib::cout << "Als je klaar bent kun je deze window sluiten.\n";
    hwlib::cout << "--------------Press any key to continue--------------\n";
    hwlib::cin >> c;
    
    uint8_t GYRO_CONFIG = 0x1B;
    mpu.write(GYRO_CONFIG, 0x01);
    for(;;){
        xyz gyro = mpu.get_gyro();
        hwlib::cout << "X: " << gyro.X << "  " << "Y: " << gyro.Y << "  " << "Z: " << gyro.Z << "\n";
        hwlib::wait_ms(20);
    }
    
    
}
