//
// Created by so on 12/23/20.
//

#include "L3GD20H.h"

l3gd20h_gyro* l3Gd20HGyro;

int main(){
    printf("Welcome to L3GD20H device test software...\n");

    /**
     * initialize the sensor...
     */
    l3Gd20HGyro = l3gd20h_init("/dev/spidev3.0", 8, 10000000, 0);

    /**
     * get who am i value from device to check the device working or not...
     */
    unsigned long who_am_i_value;
    who_am_i_value = l3gd20h_getwhoami(l3Gd20HGyro);

    if(who_am_i_value == L3GD20H_CHIP_ID){
        printf("Devie is ready to use... \n");
    }

    /**
     *  0x0F -> 0000 1111 : about datasheet
     *  Output data rate selection : 00
     *  Bandwidth selection : 00
     *  Power Down mode : 1 : Normal Mode
     *  Z axis data status ? 1: enable 0: disable
     *  Y axis data status ? 1: enable 0: disable
     *  X axis data status ? 1: enable 0: disable
     */
    //if(l3gd20h_setCTRL1(l3Gd20HGyro, 0x0F)){
    //    printf("Setting CTRL1 is ok... \n");
    //}

    unsigned long result = l3gd20h_getCTRL1(l3Gd20HGyro);
    printf("GET CTRL1 reg result : %.2lX\n", result);

    /**
     * Get Temperature
     */
    l3gd20h_getTemperature(l3Gd20HGyro);

    /**
     * close the device file to use later...
     */
    l3gd20h_close(l3Gd20HGyro);
}