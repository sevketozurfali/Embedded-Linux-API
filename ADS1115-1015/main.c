#include "libs/ADS1115-1015.h"


int main() {
    printf("Welcome to ADS1115-1015 ADC device test softwares.... \n\n");


    ads1115_adc* ads1115Adc;

    ads1115Adc = ads1115Adc_init("/dev/i2c-3", 0x48);

    //printf("ADS address %.2lX \n", ads1115Adc->address);
/*
    unsigned long test_reg[] = {0x01, 0x8583};
    ads1115Adc_writeBus(ads1115Adc, test_reg);
    ads1115Adc_readBus(ads1115Adc);


    unsigned long test_reg[] = {0x01, 0x0483};
    ads1115Adc_writeBus(ads1115Adc, test_reg);
    ads1115Adc_readBus(ads1115Adc);
/*
    unsigned long second_test_reg[] = {0x00};
    ads1115Adc_writeBus(ads1115Adc, second_test_reg);
    ads1115Adc_readBus(ads1115Adc);
*/
/*
    unsigned long test_reg[] = {0x90, 0x01, 0x04, 0x83};
    ads1115Adc_writeBus(ads1115Adc, test_reg);
    ads1115Adc_readBus(ads1115Adc);

    printf("---------------------------\n");

    unsigned long second_test_reg[] = {0x90, 0x00};
    ads1115Adc_writeBus(ads1115Adc, second_test_reg);
    ads1115Adc_readBus(ads1115Adc);

    printf("---------------------------\n");

    unsigned long third_test_reg[] = {0x91};
    ads1115Adc_writeBus(ads1115Adc, third_test_reg);
    ads1115Adc_readBus(ads1115Adc);

    printf("---------------------------\n");
*/
    unsigned long fourth_test_reg[] = {0xDBC3};
    ads1115Adc_writeBus(ads1115Adc, fourth_test_reg);
    ads1115Adc_readBus(ads1115Adc);

    printf("---------------------------\n");

    unsigned long fifth_test_reg[] = {0x00};
    ads1115Adc_writeBus(ads1115Adc, fifth_test_reg);
    ads1115Adc_readBus(ads1115Adc);



    return 0;
}
