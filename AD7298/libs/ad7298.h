//
// Created by so on 4.01.2021.
//

#ifndef AD7298_AD7298_H
#define AD7298_AD7298_H

#endif //AD7298_AD7298_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <zconf.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/**
 * From Datasheet Control Register Structure:
 *
 * D15          Write bit                       (1 -> write, 0 -> do nothing)
 * D14          Repeat bit                      (1 -> enabled, 0 -> disabled)
 * D13 - D6     Analog input bits CH0 - CH7     (1 -> enabled, 0 -> disabled) for each channel ex.(11001100) CH0,CH1,CH4,CH5 are enabled, CH2,CH3,CH6,CH7 are disabled
 * D5           Temperature conversion bit      (1 -> enabled, 0 -> disabled)
 * D4 - D3      DON'T CARE
 * D2           Ext_Ref bit                     (1 -> enabled, 0 -> disabled) 1V - 2.5V range
 * D1           Temperature Average bit         (1 -> enabled, 0 -> disabled) This bit also set to start a temperature sensor conversion
 * D0           Partial Down mode selection bit (1 -> enabled, 0 -> disabled)
 *
 * +------------+-----------+-----------+-----------+---------------------------+
 * |    ADD3    |   ADD2    |   ADD1    |   ADD0    |   Analog Input Channel    |
 * |------------+-----------+-----------+-----------+---------------------------+
 * |    0       |   0       |   0       |   0       |   VIN0                    |
 * |    0       |   0       |   0       |   1       |   VIN1                    |
 * |    0       |   0       |   1       |   0       |   VIN2                    |
 * |    0       |   0       |   1       |   1       |   VIN3                    |
 * |    0       |   1       |   0       |   0       |   VIN4                    |
 * |    0       |   1       |   0       |   1       |   VIN5                    |
 * |    0       |   1       |   1       |   0       |   VIN6                    |
 * |    0       |   1       |   1       |   1       |   VIN7                    |
 * |    1       |   0       |   0       |   0       |   TSense                  |
 * |    1       |   0       |   0       |   1       |   TSense With Averaging   |
 * +------------+-----------+-----------+-----------+---------------------------+
 *
 */


#define READ_REGISTER               0x80
#define WRITE_REGISTER              0x40


/**
 * @brief L3GD20H info struct
 *
 * @param filename          SPI device file which is connected AD7298 analog digital converter in linux(/dev/spidevX.X)
 * @param bitsPerWord       AD7298 analog digital converter supported bitsPerWord
 * @param spi_speed         AD7298 analog digital converter supported speed
 * @param spi_mode          AD7298 analog digital converter supported mode
 * @param file              AD7298 analog digital converter file open value
 */
typedef struct {
    char filename[1024];
    u_int8_t bitsPerWord;
    u_int32_t spi_speed;
    u_int8_t spi_mode;
    u_int16_t file;
} ad7298_adc;


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
