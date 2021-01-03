//
// Created by so on 1/3/21.
//

#ifndef I2C_EXPANDER_MAX7321_H
#define I2C_EXPANDER_MAX7321_H

#endif //I2C_EXPANDER_MAX7321_H


#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <zconf.h>


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

typedef struct {
    char filename[1024];
    unsigned long address;
    u_int8_t file;
}exp_max7321;

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


exp_max7321* expMax7321_init(char filename[1024], unsigned long address);

unsigned long expMax7321_readBus(exp_max7321* expMax7321);

unsigned long expMax7321_writeBus(exp_max7321* expMax7321, unsigned long *buffer);