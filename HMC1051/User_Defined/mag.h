/*
 * mag.h
 *
 * created on 10/08/2023
 * Author:Ritika Salimath
 *
 */

#include "main.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_hal_conf.h"


#define devadd 0xD0;  //slave address=>address of ADC after bit shift, before bit shift it is 0x68
#define memadd 0x00;  //address of configuration register, need to test not sure


/*function to read value sent by magnetometer*/
void read(I2C_HandleTypeDef *hi2c1,uint8_t *mag);
