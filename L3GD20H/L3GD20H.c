#include "L3GD20H.h"

void pabort(const char *s){
    perror(s);
    abort();
}

void debug(const char *message){
    printf("%s \n", message);
}


l3gd20h_gyro* l3gd20h_init(char filename[1024], u_int8_t bitsPerWord, u_int32_t spi_speed, u_int8_t spi_mode) {
    debug("Initialize L3GD20H sensor...");

    l3gd20h_gyro* l3Gd20HGyro;

    if((l3Gd20HGyro = malloc(sizeof(l3gd20h_gyro))) == NULL){
        return NULL;
    }

    strcpy(l3Gd20HGyro->filename, filename);
    l3Gd20HGyro->bitsPerWord = bitsPerWord;
    l3Gd20HGyro->spi_speed = spi_speed;
    l3Gd20HGyro->spi_mode = spi_mode;

    l3Gd20HGyro->file = open(l3Gd20HGyro->filename, O_RDWR);
    if (l3Gd20HGyro->file < 0) {
        pabort("Device can't open : ");
    }

    printf("///**************   Device Info  ****************///\n");
    printf("///Device name : %s\n", l3Gd20HGyro->filename);
    printf("///Bits Per Word : %d \n", l3Gd20HGyro->bitsPerWord);
    printf("///SPI Mode : %d \n", l3Gd20HGyro->spi_mode);
    printf("///SPI Speed : %d \n", l3Gd20HGyro->spi_speed);
    printf("///************************************************///\n");
    printf("\n");

    int spiModeCheck, spiSpeedCheck, bitsPerWorldCheck;

    spiModeCheck = ioctl(l3Gd20HGyro->file, SPI_IOC_WR_MODE, &l3Gd20HGyro->spi_mode);
    if(spiModeCheck < 0) {
        pabort("Couldn't set spi mode (WR) : ");
    }

    spiModeCheck = ioctl(l3Gd20HGyro->file, SPI_IOC_RD_MODE, &l3Gd20HGyro->spi_mode);
    if(spiModeCheck < 0) {
        pabort("Couldn't get spi mode (RD) : ");
    }

    bitsPerWorldCheck = ioctl(l3Gd20HGyro->file, SPI_IOC_WR_BITS_PER_WORD, &l3Gd20HGyro->bitsPerWord);
    if(bitsPerWorldCheck < 0) {
        pabort("Couldn't set bits per word (WR) : ");
    }

    bitsPerWorldCheck = ioctl(l3Gd20HGyro->file, SPI_IOC_RD_BITS_PER_WORD, &l3Gd20HGyro->bitsPerWord);
    if(bitsPerWorldCheck < 0) {
        pabort("Couldn't get bits per word (RD) : ");
    }

    spiSpeedCheck = ioctl(l3Gd20HGyro->file, SPI_IOC_WR_MAX_SPEED_HZ, &l3Gd20HGyro->spi_speed);
    if(spiSpeedCheck < 0) {
        pabort("Couldn't set spi speed (WR) : ");
    }

    spiSpeedCheck = ioctl(l3Gd20HGyro->file, SPI_IOC_RD_MAX_SPEED_HZ, &l3Gd20HGyro->spi_speed);
    if(spiSpeedCheck < 0) {
        pabort("Couldn't get spi speed (RD) : ");
    }

    return l3Gd20HGyro;
}

unsigned long l3gd20h_readRegister(l3gd20h_gyro* l3Gd20HGyro, unsigned char *TxData, unsigned char *RxData, int length){

    struct spi_ioc_transfer l3gd20h_spi;
    int result_value;

    memset(&l3gd20h_spi, 0, sizeof(l3gd20h_spi));

    l3gd20h_spi.tx_buf = (unsigned long)TxData;
    l3gd20h_spi.rx_buf = (unsigned long)RxData;
    l3gd20h_spi.len = length;
    l3gd20h_spi.delay_usecs = 0;
    l3gd20h_spi.speed_hz = l3Gd20HGyro->spi_speed;
    l3gd20h_spi.bits_per_word = l3Gd20HGyro->bitsPerWord;

    result_value = ioctl(l3Gd20HGyro->file, SPI_IOC_MESSAGE(1), &l3gd20h_spi);

    if(result_value < 0){
        perror("Error in ioctl while reading register... : ");
        exit(1);
    }
    if(result_value == 1){
        pabort("Can't send spi message... : ");
    }

    return RxData[1];
}

bool l3gd20h_writeRegister(l3gd20h_gyro* l3Gd20HGyro, unsigned char *TxData, unsigned char *RxData, int length){
    struct spi_ioc_transfer l3gd20h_spi;
    int result_value;

    memset(&l3gd20h_spi, 0, sizeof(l3gd20h_spi));

    l3gd20h_spi.tx_buf = (unsigned long)TxData;
    l3gd20h_spi.rx_buf = (unsigned long)RxData;
    l3gd20h_spi.len = length;
    l3gd20h_spi.delay_usecs = 0;
    l3gd20h_spi.speed_hz = l3Gd20HGyro->spi_speed;
    l3gd20h_spi.bits_per_word = l3Gd20HGyro->bitsPerWord;

    result_value = ioctl(l3Gd20HGyro->file, SPI_IOC_MESSAGE(1), &l3gd20h_spi);

    if(result_value < 0){
        pabort("Error in ioctl while writing register... : ");
    }
    if(result_value == 1){
        pabort("Can't send spi message... : ");
    }

    return true;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getwhoami(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_who[] = {READ_REGISTER | L3GD20H_WHO_AM_I, 0X00};
    unsigned char rx_who[ARRAY_SIZE(tx_who)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_who, rx_who, ARRAY_SIZE(tx_who));
}

void l3gd20h_close(l3gd20h_gyro* l3Gd20HGyro){

    if(close(l3Gd20HGyro->file) < 0){
        pabort("Close error :");
    }
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setCTRL1(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ctrl1[] = {WRITE_REGISTER | L3GD20H_CTRL1, regVal};
    unsigned char rx_ctrl1[ARRAY_SIZE(tx_ctrl1)] = {0,};

    if(!l3gd20h_writeRegister(l3Gd20HGyro, tx_ctrl1, rx_ctrl1, ARRAY_SIZE(tx_ctrl1))){
        return false;
    }
    return true;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getCTRL1(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ctrl1[] = {READ_REGISTER | L3GD20H_CTRL1, 0x00};
    unsigned char rx_ctrl1[ARRAY_SIZE(tx_ctrl1)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ctrl1, rx_ctrl1, ARRAY_SIZE(tx_ctrl1));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setCTRL2(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ctrl2[] = {WRITE_REGISTER | L3GD20H_CTRL2, regVal};
    unsigned char rx_ctrl2[ARRAY_SIZE(tx_ctrl2)] = {0,};

    if(!l3gd20h_writeRegister(l3Gd20HGyro, tx_ctrl2, rx_ctrl2, ARRAY_SIZE(tx_ctrl2))){
        return false;
    }
    return true;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getCTRL2(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ctrl2[] = {READ_REGISTER | L3GD20H_CTRL2, 0x00};
    unsigned char rx_ctrl2[ARRAY_SIZE(tx_ctrl2)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ctrl2, rx_ctrl2, ARRAY_SIZE(tx_ctrl2));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setCTRL3(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ctrl3[] = {WRITE_REGISTER | L3GD20H_CTRL3, regVal};
    unsigned char rx_ctrl3[ARRAY_SIZE(tx_ctrl3)] = {0,};

    if(!l3gd20h_writeRegister(l3Gd20HGyro, tx_ctrl3, rx_ctrl3, ARRAY_SIZE(tx_ctrl3))){
        return false;
    }
    return true;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getCTRL3(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ctrl3[] = {READ_REGISTER | L3GD20H_CTRL3, 0x00};
    unsigned char rx_ctrl3[ARRAY_SIZE(tx_ctrl3)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ctrl3, rx_ctrl3, ARRAY_SIZE(tx_ctrl3));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setCTRL4(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ctrl4[] = {WRITE_REGISTER | L3GD20H_CTRL4, regVal};
    unsigned char rx_ctrl4[ARRAY_SIZE(tx_ctrl4)] = {0,};

    if(!l3gd20h_writeRegister(l3Gd20HGyro, tx_ctrl4, rx_ctrl4, ARRAY_SIZE(tx_ctrl4))){
        return false;
    }
    return true;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getCTRL4(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ctrl4[] = {READ_REGISTER | L3GD20H_CTRL4, 0x00};
    unsigned char rx_ctrl4[ARRAY_SIZE(tx_ctrl4)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ctrl4, rx_ctrl4, ARRAY_SIZE(tx_ctrl4));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setCTRL5(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ctrl5[] = {WRITE_REGISTER | L3GD20H_CTRL5, regVal};
    unsigned char rx_ctrl5[ARRAY_SIZE(tx_ctrl5)] = {0,};

    if(!l3gd20h_writeRegister(l3Gd20HGyro, tx_ctrl5, rx_ctrl5, ARRAY_SIZE(tx_ctrl5))){
        return false;
    }
    return true;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getCTRL5(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ctrl5[] = {READ_REGISTER | L3GD20H_CTRL5, 0x00};
    unsigned char rx_ctrl5[ARRAY_SIZE(tx_ctrl5)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ctrl5, rx_ctrl5, ARRAY_SIZE(tx_ctrl5));
}

bool l3gd20h_setREFERENCE(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_reference[] = {WRITE_REGISTER | L3GD20H_REFERENCE, regVal};
    unsigned char rx_reference[ARRAY_SIZE(tx_reference)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_reference, rx_reference, ARRAY_SIZE(tx_reference));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getReference(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_reference[] = {READ_REGISTER | L3GD20H_REFERENCE, 0x00};
    unsigned char rx_reference[ARRAY_SIZE(tx_reference)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_reference, rx_reference, ARRAY_SIZE(tx_reference));
}

//TODO  Write the register value from datasheet...
int l3gd20h_getTemperature(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_temp[] = {READ_REGISTER | L3GD20H_OUT_TEMP, 0x00};
    unsigned char rx_temp[ARRAY_SIZE(tx_temp)] = {0,};

    int celsius_temp = 0;
    unsigned long out_temp;

    out_temp = l3gd20h_readRegister(l3Gd20HGyro, tx_temp, rx_temp, ARRAY_SIZE(tx_temp));
    printf("out temp : %.2lX", out_temp);

    return celsius_temp;
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getStatus(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_status[] = {READ_REGISTER | L3GD20H_STATUS, 0x00};
    unsigned char rx_status[ARRAY_SIZE(tx_status)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_status, rx_status, ARRAY_SIZE(tx_status));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getOUT_X_L(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_x_l[] = {READ_REGISTER | L3GD20H_OUT_X_L, 0x00};
    unsigned char rx_x_l[ARRAY_SIZE(tx_x_l)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_x_l, rx_x_l, ARRAY_SIZE(tx_x_l));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getOUT_X_H(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_x_h[] = {READ_REGISTER | L3GD20H_OUT_X_H, 0x00};
    unsigned char rx_x_h[ARRAY_SIZE(tx_x_h)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_x_h, rx_x_h, ARRAY_SIZE(tx_x_h));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getOUT_Y_L(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_y_l[] = {READ_REGISTER | L3GD20H_OUT_Y_L, 0x00};
    unsigned char rx_y_l[ARRAY_SIZE(tx_y_l)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_y_l, rx_y_l, ARRAY_SIZE(tx_y_l));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getOUT_Y_H(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_y_h[] = {READ_REGISTER | L3GD20H_OUT_Y_H, 0x00};
    unsigned char rx_y_h[ARRAY_SIZE(tx_y_h)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_y_h, rx_y_h, ARRAY_SIZE(tx_y_h));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getOUT_Z_L(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_z_l[] = {READ_REGISTER | L3GD20H_OUT_Z_L, 0x00};
    unsigned char rx_z_l[ARRAY_SIZE(tx_z_l)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_z_l, rx_z_l, ARRAY_SIZE(tx_z_l));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getOUT_Z_H(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_z_h[] = {READ_REGISTER | L3GD20H_OUT_Z_H, 0x00};
    unsigned char rx_z_h[ARRAY_SIZE(tx_z_h)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_z_h, rx_z_h, ARRAY_SIZE(tx_z_h));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setFifoCTRL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_fifoctrl[] = {WRITE_REGISTER | L3GD20H_FIFO_CTRL, regVal};
    unsigned char rx_fifoctrl[ARRAY_SIZE(tx_fifoctrl)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_fifoctrl, rx_fifoctrl, ARRAY_SIZE(tx_fifoctrl));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getFifoCTRL(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_fifoctrl[] = {READ_REGISTER | L3GD20H_FIFO_CTRL, 0x00};
    unsigned char rx_fifoctrl[ARRAY_SIZE(tx_fifoctrl)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_fifoctrl, rx_fifoctrl, ARRAY_SIZE(tx_fifoctrl));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getFifoSRC(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_fifosrc[] = {READ_REGISTER | L3GD20H_FIFO_SRC, 0x00};
    unsigned char rx_fifosrc[ARRAY_SIZE(tx_fifosrc)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_fifosrc, rx_fifosrc, ARRAY_SIZE(tx_fifosrc));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_CFG(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_cfg[] = {WRITE_REGISTER | L3GD20H_IG_CFG, regVal};
    unsigned char rx_ig_cfg[ARRAY_SIZE(tx_ig_cfg)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_cfg, rx_ig_cfg, ARRAY_SIZE(tx_ig_cfg));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_CFG(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_cfg[] = {READ_REGISTER | L3GD20H_IG_CFG, 0x00};
    unsigned char rx_ig_cfg[ARRAY_SIZE(tx_ig_cfg)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_cfg, rx_ig_cfg, ARRAY_SIZE(tx_ig_cfg));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_SRC(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_src[] = {READ_REGISTER | L3GD20H_IG_SRC, 0x00};
    unsigned char rx_ig_src[ARRAY_SIZE(tx_ig_src)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_src, rx_ig_src, ARRAY_SIZE(tx_ig_src));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_THS_XH(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_ths_xh[] = {WRITE_REGISTER | L3GD20H_IG_THIS_XH, regVal};
    unsigned char rx_ig_ths_xh[ARRAY_SIZE(tx_ig_ths_xh)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_ths_xh, rx_ig_ths_xh, ARRAY_SIZE(tx_ig_ths_xh));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_THS_XH(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_ths_xh[] = {READ_REGISTER | L3GD20H_IG_THIS_XH, 0x00};
    unsigned char rx_ig_ths_xh[ARRAY_SIZE(tx_ig_ths_xh)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_ths_xh, rx_ig_ths_xh, ARRAY_SIZE(tx_ig_ths_xh));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_THS_XL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_ths_xl[] = {WRITE_REGISTER | L3GD20H_IG_THIS_XL, regVal};
    unsigned char rx_ig_ths_xl[ARRAY_SIZE(tx_ig_ths_xl)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_ths_xl, rx_ig_ths_xl, ARRAY_SIZE(tx_ig_ths_xl));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_THS_XL(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_ths_xl[] = {READ_REGISTER | L3GD20H_IG_THIS_XL, 0x00};
    unsigned char rx_ig_ths_xl[ARRAY_SIZE(tx_ig_ths_xl)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_ths_xl, rx_ig_ths_xl, ARRAY_SIZE(tx_ig_ths_xl));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_THS_YH(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_ths_yh[] = {WRITE_REGISTER | L3GD20H_IG_THIS_YH, regVal};
    unsigned char rx_ig_ths_yh[ARRAY_SIZE(tx_ig_ths_yh)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_ths_yh, rx_ig_ths_yh, ARRAY_SIZE(tx_ig_ths_yh));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_THS_YH(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_ths_yh[] = {READ_REGISTER | L3GD20H_IG_THIS_YH, 0x00};
    unsigned char rx_ig_ths_yh[ARRAY_SIZE(tx_ig_ths_yh)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_ths_yh, rx_ig_ths_yh, ARRAY_SIZE(tx_ig_ths_yh));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_THS_YL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_ths_yl[] = {WRITE_REGISTER | L3GD20H_IG_THIS_YL, regVal};
    unsigned char rx_ig_ths_yl[ARRAY_SIZE(tx_ig_ths_yl)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_ths_yl, rx_ig_ths_yl, ARRAY_SIZE(tx_ig_ths_yl));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_THS_YL(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_ths_yl[] = {READ_REGISTER | L3GD20H_IG_THIS_YL, 0x00};
    unsigned char rx_ig_ths_yl[ARRAY_SIZE(tx_ig_ths_yl)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_ths_yl, rx_ig_ths_yl, ARRAY_SIZE(tx_ig_ths_yl));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_THS_ZH(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_ths_zh[] = {WRITE_REGISTER | L3GD20H_IG_THIS_ZH, regVal};
    unsigned char rx_ig_ths_zh[ARRAY_SIZE(tx_ig_ths_zh)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_ths_zh, rx_ig_ths_zh, ARRAY_SIZE(tx_ig_ths_zh));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_THS_ZH(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_ths_zh[] = {READ_REGISTER | L3GD20H_IG_THIS_ZH, 0x00};
    unsigned char rx_ig_ths_zh[ARRAY_SIZE(tx_ig_ths_zh)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_ths_zh, rx_ig_ths_zh, ARRAY_SIZE(tx_ig_ths_zh));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_THS_ZL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_ths_zl[] = {WRITE_REGISTER | L3GD20H_IG_THIS_ZL, regVal};
    unsigned char rx_ig_ths_zl[ARRAY_SIZE(tx_ig_ths_zl)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_ths_zl, rx_ig_ths_zl, ARRAY_SIZE(tx_ig_ths_zl));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_THS_ZL(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_ths_zl[] = {READ_REGISTER | L3GD20H_IG_THIS_ZL, 0x00};
    unsigned char rx_ig_ths_zl[ARRAY_SIZE(tx_ig_ths_zl)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_ths_zl, rx_ig_ths_zl, ARRAY_SIZE(tx_ig_ths_zl));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setIG_DURATION(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_ig_duration[] = {WRITE_REGISTER | L3GD20H_IG_DURATION, regVal};
    unsigned char rx_ig_duration[ARRAY_SIZE(tx_ig_duration)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_ig_duration, rx_ig_duration, ARRAY_SIZE(tx_ig_duration));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getIG_DURATION(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_ig_duration[] = {READ_REGISTER | L3GD20H_IG_DURATION, 0x00};
    unsigned char rx_ig_duration[ARRAY_SIZE(tx_ig_duration)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_ig_duration, rx_ig_duration, ARRAY_SIZE(tx_ig_duration));
}

//TODO  Write the register value from datasheet...
bool l3gd20h_setLOW_ODR(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal){
    unsigned char tx_low_odr[] = {WRITE_REGISTER | L3GD20H_LOW_ODR, regVal};
    unsigned char rx_low_odr[ARRAY_SIZE(tx_low_odr)] = {0,};

    return l3gd20h_writeRegister(l3Gd20HGyro, tx_low_odr, rx_low_odr, ARRAY_SIZE(tx_low_odr));
}

//TODO  Write the register value from datasheet...
unsigned long l3gd20h_getLOW_ODR(l3gd20h_gyro* l3Gd20HGyro){
    unsigned char tx_low_odr[] = {READ_REGISTER | L3GD20H_LOW_ODR, 0x00};
    unsigned char rx_low_odr[ARRAY_SIZE(tx_low_odr)] = {0,};

    return l3gd20h_readRegister(l3Gd20HGyro, tx_low_odr, rx_low_odr, ARRAY_SIZE(tx_low_odr));
}
