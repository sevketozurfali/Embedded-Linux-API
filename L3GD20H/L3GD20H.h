/**
 * Linux API for 3-axes digital output gyroscope connected to I2C or SPI.
 *
 * This API is for the usage Embedded Linux and it support only SPI interface for now.
 * You can find the license detail in LICENSE file.
 * Created By Sevket Ozurfali on 22 December 2020
 *
 */

#ifndef L3GD20H_L3GD20H_H
#define L3GD20H_L3GD20H_H

#endif //L3GD20H_L3GD20H_H


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

//Hardware Base Setting...
// CS pin high -> SPI : disabled, I2C enabled.
// CS pin low -> SPI : enabled, I2C disabled. (current)

//L3GD20H chip id
#define L3GD20H_CHIP_ID                 0xd7    //L3GD20H_REG_WHO_AM_I<7:0>

//Error codes for SPI and I2C interfaces with L3GD20H API
#define L3GD20H_SPI_READ_FAILED         1
#define L3GD20H_SPI_WRITE_FAILED        2
#define L3GD20H_SPI_BUFFER_OVERFLOW     3

/*
//Register Map                                 Default
L3GD20H_WHO_AM_I        R           0x0F    //11010111
L3GD20H_CTRL1           RW          0x20    //00000111
L3GD20H_CTRL2           RW          0x21    //00000000
L3GD20H_CTRL3           RW          0x22    //00000000
L3GD20H_CTRL4           RW          0x23    //00000000
L3GD20H_CTRL5           RW          0x24    //00000000
L3GD20H_REFERENCE       RW          0x25    //00000000
L3GD20H_OUT_TEMP        R           0x26    //output
L3GD20H_STATUS          R           0x27    //output
L3GD20H_OUT_X_L         R           0x28    //output
L3GD20H_OUT_X_H         R           0x29    //output
L3GD20H_OUT_Y_L         R           0x2A    //output
L3GD20H_OUT_Y_H         R           0x2B    //output
L3GD20H_OUT_Z_L         R           0x2C    //output
L3GD20H_OUT_Z_H         R           0x2D    //output
L3GD20H_FIFO_CTRL       RW          0x2E    //00000000
L3GD20H_FIFO_SRC        R           0x2F    //output
L3GD20H_IG_CFG          RW          0x30    //00000000
L3GD20H_IG_SRC          R           0x31    //output
L3GD20H_IG_THIS_XH      RW          0x32    //00000000
L3GD20H_IG_THIS_XL      RW          0x33    //00000000
L3GD20H_IG_THIS_YH      RW          0x34    //00000000
L3GD20H_IG_THIS_YL      RW          0x35    //00000000
L3GD20H_IG_THIS_ZH      RW          0x36    //00000000
L3GD20H_IG_THIS_ZL      RW          0x37    //00000000
L3GD20H_IG_DURATION     RW          0x38    //00000000
L3GD20H_LOW_ODR         RW          0x39    //00000000
*/

//Register Address Map
#define L3GD20H_WHO_AM_I            0x0F
#define L3GD20H_CTRL1               0x20
#define L3GD20H_CTRL2               0x21
#define L3GD20H_CTRL3               0x22
#define L3GD20H_CTRL4               0x23
#define L3GD20H_CTRL5               0x24
#define L3GD20H_REFERENCE           0x25
#define L3GD20H_OUT_TEMP            0x26
#define L3GD20H_STATUS              0x27
#define L3GD20H_OUT_X_L             0x28
#define L3GD20H_OUT_X_H             0x29
#define L3GD20H_OUT_Y_L             0x2A
#define L3GD20H_OUT_Y_H             0x2B
#define L3GD20H_OUT_Z_L             0x2C
#define L3GD20H_OUT_Z_H             0x2D
#define L3GD20H_FIFO_CTRL           0x2E
#define L3GD20H_FIFO_SRC            0x2F
#define L3GD20H_IG_CFG              0x30
#define L3GD20H_IG_SRC              0x31
#define L3GD20H_IG_THIS_XH          0x32
#define L3GD20H_IG_THIS_XL          0x33
#define L3GD20H_IG_THIS_YH          0x34
#define L3GD20H_IG_THIS_YL          0x35
#define L3GD20H_IG_THIS_ZH          0x36
#define L3GD20H_IG_THIS_ZL          0x37
#define L3GD20H_IG_DURATION         0x38
#define L3GD20H_LOW_ODR             0x39

#define READ_REGISTER               0x80
#define WRITE_REGISTER              0x40


/**
 * @brief L3GD20H info struct
 *
 * @param filename          SPI device file which is connected L3GD20H sensor in linux(/dev/spidevX.X)
 * @param bitsPerWord       L3GD20H sensor supported bitsPerWord
 * @param spi_speed         L3GD20H sensor supported speed
 * @param spi_mode          L3GD20H sensor supported mode
 * @param file              L3GD20H sensor file open value
 */
typedef struct {
    char filename[1024];
    u_int8_t bitsPerWord;
    u_int32_t spi_speed;
    u_int8_t spi_mode;
    u_int16_t file;
} l3gd20h_gyro;

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
 * @brief Initialize the sensor.
 *
 * Initialize the sensor file with the bitsperword, speed and spimode values. All registers are reset default values.
 *
 * @param filename          SPI device file which is connected L3GD20H sensor in linux(/dev/spidevX.X)
 * @param bitsPerWord       L3GD20H sensor supported bitsPerWord
 * @param spi_speed         L3GD20H sensor supported speed
 * @param spi_mode          L3GD20H sensor supported mode
 * @return                  l3gd20h_gyro sensor pointer struct
 */
l3gd20h_gyro* l3gd20h_init(char filename[1024], u_int8_t bitsPerWord, u_int32_t spi_speed, u_int8_t spi_mode);

/**
 * @brief Read register from sensor
 *
 * Read register value from L3GD20H sensor device which is defined address.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param TxData        Dataset which includes register address and default value to read
 * @param RxData        Dataset which includes register sent value
 * @param length        TxData and RxData length
 * @return              The returned value from the register
 */
unsigned long l3gd20h_readRegister(l3gd20h_gyro* l3Gd20HGyro , unsigned char *TxData, unsigned char *RxData, int length);

/**
 * @brief Write register from sensor
 *
 * Write the value to the defined L3GD20H sensor register
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param TxData        Dataset which includes register address and default value to read
 * @param RxData        Dataset which includes register sent value
 * @param length        TxData and RxData length
 * @return              The returned value from the register
 */
bool l3gd20H_writeRegister(l3gd20h_gyro* l3Gd20HGyro, unsigned char *TxData, unsigned char *RxData, int length);

/**
 * @brief Read WHO_AM_I register
 *
 * Read who am i register from the L3GD20H sensor
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The returned value from the register
 */
unsigned long l3gd20h_getwhoami(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Close the senor data file
 *
 * Stop the reading or writing to L3GD20H sensor file
 *
 * @param l3Gd20HGyro   Sensor info struct
 */
void l3gd20h_close(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set CTRL1 register
 *
 * This register is sets the L3GD20H sensor for work properly. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        Register value to write the CTRL1 register
 * @return              The status of setting is ok or not
 */
bool l3gd20h_setCTRL1(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get CTRL1 register
 *
 * Read this register from L3GD20H sensor for work properly or not. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is ok or not
 */
unsigned long l3gd20h_getCTRL1(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set CTRL2 register
 *
 * This register is sets the L3GD20H sensor for work properly. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        Register value to write the CTRL2 register
 * @return              The status of setting is ok or not
 */
bool l3gd20h_setCTRL2(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get CTRL2 register
 *
 * Read this register from L3GD20H sensor for work properly or not. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is ok or not
 */
unsigned long l3gd20h_getCTRL2(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set CTRL3 register
 *
 * This register is sets the L3GD20H sensor for work properly. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        Register value to write the CTRL3 register
 * @return              The status of setting is ok or not
 */
bool l3gd20h_setCTRL3(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get CTRL3 register
 *
 * Read this register from L3GD20H sensor for work properly or not. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is ok or not
 */
unsigned long l3gd20h_getCTRL3(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set CTRL4 register
 *
 * This register is sets the L3GD20H sensor for work properly. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        Register value to write the CTRL4 register
 * @return              The status of setting is ok or not
 */
bool l3gd20h_setCTRL4(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get CTRL4 register
 *
 * Read this register from L3GD20H sensor for work properly or not. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is ok or not
 */
unsigned long l3gd20h_getCTRL4(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set CTRL5 register
 *
 * This register is sets the L3GD20H sensor for work properly. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        Register value to write the CTRL5 register
 * @return              The status of setting is ok or not
 */
bool l3gd20h_setCTRL5(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get CTRL5 register
 *
 * Read this register from L3GD20H sensor for work properly or not. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is ok or not
 */
unsigned long l3gd20h_getCTRL5(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set REFERENCE register
 *
 * This register sets the REFERENCE register of L3GD20H sensor. You can find detail info in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        Register value to write the REFERENCE register default is 0x00
 * @return              The status of setting is ok or not
 */
bool l3gd20h_setREFERENCE(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get REFERENCE register
 *
 * Read this register from L3GD20H sensor for work properly or not. You can find more detail in the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is ok or not
 */
unsigned long l3gd20h_getReference(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get Temperature value
 *
 * Get Temperature value (Celsius) from the L3GD20H sensor device
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              Celsius Degree
 */
int l3gd20h_getTemperature(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get STATUS of register
 *
 * Get Status value from the L3GD20H sensor device
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The status of setting is Ok or Not
 */
unsigned long l3gd20h_getStatus(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get X-axis L angular rate value
 *
 * Get X-axis angular rate value from L3GD20H sensor device. For more information please check the datasheet.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of OUT_X_L register
 */
unsigned long l3gd20h_getOUT_X_L(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get X-axis H angular rate value
 *
 * Get X-axis angular rate value from L3GD20H sensor device. For more information please check the datasheet.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of OUT_X_L register
 */
unsigned long l3gd20h_getOUT_X_H(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get Y-axis L angular rate value
 *
 * Get Y-axis angular rate value from L3GD20H sensor device. For more information please check the datasheet.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of OUT_Y_L register
 */
unsigned long l3gd20h_getOUT_Y_L(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get Y-axis H angular rate value
 *
 * Get Y-axis angular rate value from L3GD20H sensor device. For more information please check the datasheet.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of OUT_Y_L register
 */
unsigned long l3gd20h_getOUT_Y_H(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get Z-axis L angular rate value
 *
 * Get Z-axis angular rate value from L3GD20H sensor device. For more information please check the datasheet.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of OUT_Z_L register
 */
unsigned long l3gd20h_getOUT_Z_L(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get Z-axis H angular rate value
 *
 * Get Z-axis angular rate value from L3GD20H sensor device. For more information please check the datasheet.
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of OUT_Z_L register
 */
unsigned long l3gd20h_getOUT_Z_H(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set FifoCTRL register
 *
 * Sets the fifo control register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setFifoCTRL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get FifoCTRL register value
 *
 * Get fifo control register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of FIFOCTRL register
 */
unsigned long l3gd20h_getFifoCTRL(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get FifoSRC register value
 *
 * Get fifosrc register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of FIFOSRC register
 */
unsigned long l3gd20h_getFifoSRC(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_CFG register
 *
 * Sets the Interrupt config register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_CFG(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_CFG register value
 *
 * Get Interrupt config register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_CFG register
 */
unsigned long l3gd20h_getIG_CFG(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Get IG_SRC register value
 *
 * Get Interrupt source register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_CFG register
 */
unsigned long l3gd20h_getIG_SRC(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_THS_XH register
 *
 * Sets the Interrupt threshold on X-axis register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_THS_XH(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_THS_XH register value
 *
 * Get Interrupt threshold on X-axis register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_THS_XH register
 */
unsigned long l3gd20h_getIG_THS_XH(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_THS_XL register
 *
 * Sets the Interrupt threshold on X-axis register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_THS_XL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_THS_XL register value
 *
 * Get Interrupt threshold on X-axis register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_THS_XL register
 */
unsigned long l3gd20h_getIG_THS_XL(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_THS_YH register
 *
 * Sets the Interrupt threshold on Y-axis register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_THS_YH(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_THS_YH register value
 *
 * Get Interrupt threshold on Y-axis register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_THS_YH register
 */
unsigned long l3gd20h_getIG_THS_YH(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_THS_YL register
 *
 * Sets the Interrupt threshold on Y-axis register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_THS_YL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_THS_YL register value
 *
 * Get Interrupt threshold on Y-axis register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_THS_YL register
 */
unsigned long l3gd20h_getIG_THS_YL(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_THS_ZH register
 *
 * Sets the Interrupt threshold on Z-axis register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_THS_ZH(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_THS_ZH register value
 *
 * Get Interrupt threshold on Z-axis register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_THS_ZH register
 */
unsigned long l3gd20h_getIG_THS_ZH(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_THS_ZL register
 *
 * Sets the Interrupt threshold on Z-axis register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_THS_ZL(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_THS_ZL register value
 *
 * Get Interrupt threshold on Z-axis register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_THS_ZL register
 */
unsigned long l3gd20h_getIG_THS_ZL(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set IG_DURATION register
 *
 * Sets the Interrupt duration register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setIG_DURATION(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get IG_DURATION register value
 *
 * Get Interrupt duration register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of IG_DURATION register
 */
unsigned long l3gd20h_getIG_DURATION(l3gd20h_gyro* l3Gd20HGyro);

/**
 * @brief Set LOW_ODR register
 *
 * Sets the low output data rate register of L3GD20H sensor device. For the variations please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @param regVal        The value which will be written to the register
 * @return              The status of setting is Ok or Not
 */
bool l3gd20h_setLOW_ODR(l3gd20h_gyro* l3Gd20HGyro, unsigned long regVal);

/**
 * @brief Get LOW_ODR register value
 *
 * Get low output data rate register value of L3GD20H sensor device. For the meaning of value please check the datasheet
 *
 * @param l3Gd20HGyro   Sensor info struct
 * @return              The value of LOW_ODR register
 */
unsigned long l3gd20h_getLOW_ODR(l3gd20h_gyro* l3Gd20HGyro);

