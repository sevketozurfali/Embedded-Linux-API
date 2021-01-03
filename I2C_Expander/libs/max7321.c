//
// Created by so on 1/3/21.
//

#include "max7321.h"

void pabort(const char *s){
    perror(s);
    abort();
}

void debug(const char *message){
    printf("%s \n", message);
}

exp_max7321* expMax7321_init(char filename[1024], unsigned long address){
    debug("Initialize IO Expander Module...");

    exp_max7321* expMax7321;

    if((expMax7321 = malloc(sizeof(expMax7321))) == NULL ){
        return NULL;
    }

    strcpy(expMax7321->filename, filename);
    expMax7321->address = address;

    expMax7321->file = open(expMax7321->filename, O_RDWR);

    if(expMax7321->file < 0){
        pabort("I2C Device Open Error : ");
    }

    printf("///*******************Module Info****************************///\n");
    printf("///Module Name : %s \n", expMax7321->filename);
    printf("///Module Address : %.2lX \n", expMax7321->address);
    printf("///**********************************************************///\n");

    if(ioctl(expMax7321->file, I2C_SLAVE, expMax7321->address) < 0){
        pabort("Module Bus IOCTL Error : ");
    }

    return expMax7321;

}

unsigned long expMax7321_readBus(exp_max7321* expMax7321){
    unsigned long buffer[] = {0};

    if(expMax7321->file < 0){
        pabort("I2C Device Open Error : ");
    }

    if(read(expMax7321->file,buffer, ARRAY_SIZE(buffer)) != ARRAY_SIZE(buffer)){
        pabort("I2C Read Error : ");
    }

    for(int i = 0; i <= ARRAY_SIZE(buffer); i++){
        printf("Read data : %.2lX \n", buffer[i]);
    }

}

unsigned long expMax7321_writeBus(exp_max7321* expMax7321, unsigned long *buffer){
    if(expMax7321->file < 0){
        pabort("I2C Device Open Error : ");
    }

    if(write(expMax7321->file, buffer, ARRAY_SIZE(buffer)) != ARRAY_SIZE(buffer)){
        pabort("I2C Bus Write Error : ");
    }

    return 0;
}