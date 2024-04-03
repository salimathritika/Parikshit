/*
 * mag.h
 *
 * created on 17/01/2024
 * Author:Ritika Salimath
 *
 */
#ifndef MAG_H
#define MAG_H

#include"stm32f4xx.h"


#define devadd 0xDC  //slave address=>address of ADC after bit shift, before bit shift it is 0x6E. we are taking both high
#define memadd_x 0x90 //address of configuration register for ch1
#define memadd_y 0xB0  //address of configuration register for ch2
#define memadd_z 0xD0  //address of configuration register for ch1


/*function to read value sent by magnetometer*/
void read_x(I2C_HandleTypeDef *hi2c1,uint8_t *mag);
void read_y(I2C_HandleTypeDef *hi2c1,uint8_t *mag);
void read_z(I2C_HandleTypeDef *hi2c1,uint8_t *mag);

#endif
