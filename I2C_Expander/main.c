#include "libs/max7321.h"

int main() {
    debug("Welcome to I2C Expander (MAX7321) Test Software");

    exp_max7321* expMax7321;

    expMax7321 = expMax7321_init("/dev/i2c-1", 0x21);

    unsigned long first_io[] = {0x01};
    expMax7321_writeBus(expMax7321, first_io);
    
    return 0;
}
