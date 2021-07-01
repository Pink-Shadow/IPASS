# Automatic stabalizer
Made by Jasper van der Post as a student of Computer Science at the Hogeschool Utrecht (HU).

# Things you will need
* Aruduino Due
* MPU6050
* 2 servo's

Note: This code is based on a little-endian chip. If you use this code with big-endian chip, this code will most likely not work. Find more information about Endianness [here](https://en.wikipedia.org/wiki/Endianness#:~:text=In%20computing%2C%20endianness%20is%20the,little%2Dendian%20(LE)).
# How to install
* This application uses hwlib. To download hwlib, go to [this](https://github.com/wovo/hwlib) page. 
* When you've downloaded the repository, please insert it into the root directory of your own clone of this repository [here](https://github.com/Pink-Shadow/IPASS).
* The included makefiles in this repository will do the rest.

Note: You will need to change the [COM](IPASS_Project/Makefile.due) port to whatever your arduino DUE is connected to.

