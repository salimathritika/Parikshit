/*
 * i2c_slave.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Srishti Singh
 */

#ifndef INC_I2C_SLAVE_H_
#define INC_I2C_SLAVE_H_



extern void HAL_I2C_ListenCpltCallback (I2C_HandleTypeDef *hi2c);
extern void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);

#endif /* INC_I2C_SLAVE_H_ */
