#include "libs/max7321.h"

int main() {
    debug("Welcome to I2C Expander (MAX7321) Test Software");

    exp_max7321* expMax7321;

    expMax7321 = expMax7321_init("/dev/i2c-1", 0x21);

    int selection, custom_value;
    debug("Please select one of the section which is defined in the below (exit -> 0) : ");
    debug("1 : Send 0x01 command.");
    debug("2 : Send 0x03 command.");
    debug("3 : Send 0x07 command.");
    debug("4 : Send 0x0F command.");
    debug("5 : Send 0x1F command.");
    debug("6 : Send 0x3F command.");
    debug("7 : Send 0x7F command.");
    debug("8 : Send 0xFF command.");
    debug("9 : Send custom command.");
    debug("10 : Just read command.");


    scanf("%d", selection);
    printf("You selected : %d", selection);


    unsigned long one_io[] = {0x01};
    unsigned long two_io[] = {0x03};
    unsigned long three_io[] = {0x07};
    unsigned long four_io[] = {0x0F};
    unsigned long five_io[] = {0x1F};
    unsigned long six_io[] = {0x3F};
    unsigned long seven_io[] = {0x7F};
    unsigned long eight_io[] = {0xFF};
    unsigned long custom_io[] = {0x00};
    unsigned long read_io[] = {0};
    if(selection == 9){
        custom_io[0] = custom_value;
    }


    switch (selection) {
        case 0:
            break;
        case 1:
            expMax7321_writeBus(expMax7321, one_io);
            break;
        case 2:
            expMax7321_writeBus(expMax7321, two_io);
            break;
        case 3:
            expMax7321_writeBus(expMax7321, three_io);
            break;
        case 4:
            expMax7321_writeBus(expMax7321, four_io);
            break;
        case 5:
            expMax7321_writeBus(expMax7321, five_io);
            break;
        case 6:
            expMax7321_writeBus(expMax7321, six_io);
            break;
        case 7:
            expMax7321_writeBus(expMax7321, seven_io);
            break;
        case 8:
            expMax7321_writeBus(expMax7321, eight_io);
            break;
        case 9:
            expMax7321_writeBus(expMax7321, custom_io);
            break;
        case 10:
            expMax7321_readBus(expMax7321);

        default:
            break;

    }


    return 0;
}
