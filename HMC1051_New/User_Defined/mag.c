/*
 * mag.c
 *
 * created on 17/01/2024
 * Author:Ritika Salimath
 *
 */

#include"mag.h"


/*  @brief         Reads magnetometer value from configuration register of ch1
 *  @parameter     Pointer to i2c structure, pointer to the variable storing the value from magnetometer
 *  @return value  Void

 */
void read_x(I2C_HandleTypeDef *hi2c1,uint8_t *mag)
{
	/*function to read value sent by magnetometer*/
    HAL_I2C_Mem_Read(hi2c1, devadd,memadd_x, 1u, mag, 1u, 1000);//not using & because it is an address
}

void read_y(I2C_HandleTypeDef *hi2c1,uint8_t *mag)
{
	/*function to read value sent by magnetometer*/
    HAL_I2C_Mem_Read(hi2c1, devadd,memadd_y, 1u, mag, 1u, 1000);//not using & because it is an address
}

void read_z(I2C_HandleTypeDef *hi2c1,uint8_t *mag)
{
	/*function to read value sent by magnetometer*/
    HAL_I2C_Mem_Read(hi2c1, devadd,memadd_z, 1u, mag, 1u, 1000);//not using & because it is an address
}
