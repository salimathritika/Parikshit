
#include "stm32h7xx.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_hal_conf.h"
//#include "stm32h7xx_hal_i2c.h"

uint16_t devadd=0xD0;//slave address=>address of ADC after bit shift, before bit shift it is 0x68
uint16_t memadd=0x00;//address of configuration register, need to test not sure
uint8_t mag;

void read(I2C_HandleTypeDef hi2c1);
