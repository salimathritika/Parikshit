#include "Magnetometer.h"
#include "stm32h7xx_hal.h"
//#include "stm32h7xx_it.h"
#include "stm32h7xx_hal_conf.h"

uint16_t devadd;
uint16_t memadd;
uint8_t mag;

void read(I2C_HandleTypeDef hi2c1)
{
HAL_I2C_Mem_Read(&hi2c1,devadd,memadd,1u, &mag, 1u, 1000);
}
