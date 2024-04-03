/*
 * gyroscope.h
 *
 *  Created on: July 12, 2023
 *      Author: SRISHTI SINGH
 */

#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "math.h"

#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10
#define TIMER_TIMEOUT_I2C 0x000FFFFF
#define dev_addr 0xD0     //device address for MPU6050







/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from the
 * driver(s).
 * The following matrices refer to the configuration on internal test
 * boards at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
typedef struct
{
	double BSP_Acc_x;
	double BSP_Acc_y;
	double BSP_Acc_z;
	double BSP_Temp;
	double BSP_Gyr_x;
	double BSP_Gyr_y;
	double BSP_Gyr_z;
}BSP_GyrFetchTypeDef;


ErrorStatus BSP_Gyroscope_Init(I2C_HandleTypeDef *,uint8_t *);
ErrorStatus BSP_Gyroscope_SelfTest(I2C_HandleTypeDef *, uint8_t *);
ErrorStatus BSP_Gyroscope_ReadRegister(I2C_HandleTypeDef *,uint16_t , uint8_t *,uint8_t *);
ErrorStatus BSP_Gyroscope_GetValues(I2C_HandleTypeDef *, BSP_GyrFetchTypeDef *,uint8_t *);


#endif /* GYROSCOPE_H_*/
