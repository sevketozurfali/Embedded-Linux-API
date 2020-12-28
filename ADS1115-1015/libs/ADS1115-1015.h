//
// Created by so on 12/27/20.
//

#ifndef ADS1115_1015_ADS1115_1015_H
#define ADS1115_1015_ADS1115_1015_H

#endif //ADS1115_1015_ADS1115_1015_H


#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <zconf.h>


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

// Hardware Base Settings...
//





typedef struct {
    char filename[1024];
    unsigned long address;
    u_int8_t file;
}ads1115_adc;


/**
 * @brief   Abort after error occurred.
 *
 * Abort the mission and print the error which is caused this mission.
 *
 * @param s Error title. Print this param before the error message.
 * @return  Null.
 */
void pabort(const char *s);

/**
 * @brief   Debug printer.
 *
 * Print the debug message during the mission continue or not.
 *
 * @param message
 * @return Null.
 */
void debug(const char *message);

/**
 * @brief ADS1115 ADC Module Initialisation
 *
 * File name and address are setting for ADS1115 ADC Module.
 *
 * @param filename      Defined string for ADS1115 ADC Module in Linux device table
 * @param address       Defined long for ADS1115 ADC Module bus address to communicate
 * @return              Struct of ads1115_adc
 */
ads1115_adc* ads1115Adc_init(char filename[1024], unsigned long address);

/**
 * @brief ADS1115 ADC Module Read Bus
 *
 * Read the register value from ADS1115 ADC Module with i2c interface
 *
 * @param ads1115Adc    Defined structure for communication info
 * @return              Register value which is read from defined register or null
 */
unsigned long ads1115Adc_readBus(ads1115_adc* ads1115Adc);

/**
 * @brief ADS1115 ADC Module Write Bus
 *
 * Write the defined register value to ADS1115 ADC Module with 12c interface
 *
 * @param ads1115Adc    Defined structure for communication info
 * @param buffer        Defined char array to write ADC Module register
 * @return              Register value which is write or NULL
 */
unsigned long ads1115Adc_writeBus(ads1115_adc* ads1115Adc, unsigned long *buffer);



























