/*
 * mag.c
 *
 * created on 10/08/2023
 * Author:Ritika Salimath
 *
 */

#include"mag_int.h"
#include"stm32l4xx_hal.h"
#include"stm32l4xx_hal_i2c.h"

/*  @brief         Reads magnetometer value from configuration register
 *  @parameter     Pointer to i2c structure, pointer to the variable storing the value from magnetometer
 *  @return value  Void
 *
 */
void read(I2C_HandleTypeDef *hi2c1,uint8_t *mag)
{
	/*function to read value sent by magnetometer*/
    HAL_I2C_Mem_Read(hi2c1, 0xD0, 0x00, 1u, mag, 1u, 1000);//not using & because it is an address
}
