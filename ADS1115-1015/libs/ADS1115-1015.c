//
// Created by so on 12/27/20.
//


#include "ADS1115-1015.h"

void pabort(const char *s){
    perror(s);
    abort();
}

void debug(const char *message){
    printf("%s \n", message);
}

ads1115_adc* ads1115Adc_init(char filename[1024], unsigned long address){
    debug("Initialize ADS1115 ADC Module...");

    ads1115_adc* ads1115Adc;

    if((ads1115Adc = malloc(sizeof(ads1115Adc))) == NULL){
        return NULL;
    }

    strcpy(ads1115Adc->filename, filename);
    ads1115Adc->address = address;

    ads1115Adc->file = open(ads1115Adc->filename, O_RDWR);

    if(ads1115Adc->file < 0){
        pabort("Module can not initialized : ");
    }

    printf("///*******************Module Info****************************///\n");
    printf("///Module Name : %s \n", ads1115Adc->filename);
    printf("///Module Address : %.2lX \n", ads1115Adc->address);
    printf("///**********************************************************///\n");

    if(ioctl(ads1115Adc->file, I2C_SLAVE, ads1115Adc->address) < 0){
        pabort("Module Bus IOCTL Error : ");
    }

    return ads1115Adc;

}

unsigned long ads1115Adc_readBus(ads1115_adc* ads1115Adc){
    unsigned long buffer[] = {0};

    if(read(ads1115Adc->file, buffer, ARRAY_SIZE(buffer)) != ARRAY_SIZE(buffer)){
        pabort("I2C Bus Read Error... : ");
    }
    printf("REad data 1: %.1lX \n",buffer[1]);
    printf("REad data 2: %.1lX \n",buffer[2]);
    printf("REad data 3: %.1lX \n",buffer[3]);
    printf("REad data 4: %.4lX \n",buffer[4]);
    printf("REad data 5: %.4lX \n",buffer[5]);
    printf("REad data 6: %.4lX \n",buffer[6]);
    printf("REad data 7: %.4lX \n",buffer[7]);

    /*
    for(int i = 0; i <= ARRAY_SIZE(buffer); i++){
        printf("Read data : %.4lX \n", buffer[i]);
    }
*/
/*
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 1]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 2]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 3]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 4]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 5]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 6]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 7]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 9]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 10]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 11]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 12]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 13]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 14]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 15]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 16]);
    printf("Read data : %.2lX \n", buffer[ARRAY_SIZE(buffer) + 17]);
*/

    return 0;
}

unsigned long ads1115Adc_writeBus(ads1115_adc* ads1115Adc, unsigned long *buffer){

    if(ads1115Adc->file < 0){
        pabort("Open error ... ");
    }

    if(write(ads1115Adc->file, buffer, ARRAY_SIZE(buffer)) != ARRAY_SIZE(buffer)){
        pabort("I2C Bus Write Error... ");
    }


    return 0;
}




















