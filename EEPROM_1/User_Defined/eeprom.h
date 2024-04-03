#ifndef BSP_EEPROM_H
#define BSP_EEPROM_H

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_gpio.h"


/*
command variables to be used in the program
*/

#define wren 0x06       //Write enable
#define wrdi 0x04       //Write disable
#define rdsr 0x05       //Read status reg
#define wrsr 0x01       //Write status reg
#define read 0x03       //Read
#define writ 0x02       //Write

extern  uint8_t eeprom_flag_flag ;
extern char read_data[90];
extern char write_data[90];
extern int q;
extern int bytes,no,re_no;
extern unsigned char br;
extern int add_r;
extern int testing_flag;
extern int testing_flag_read;
extern int add_eep;
extern char packet1[21],packet2[9],packet3[26],packet4[3];
extern char* bit_eeprom;

void buffer(uint8_t *rb,uint8_t *tb);

void BSP_EEPROM_Init();
void BSP_EEPROM_CS_Low();
void BSP_EEPROM_Power();
void BSP_EEPROM_CS_High();
void BSP_EEPROM_SPI_Init();
//void BSP_EEPROM_WriteCmd(unsigned char opcode,unsigned char cmd);
void BSP_EEPROM_WriteCmd(unsigned char opcode,unsigned char cmd);
unsigned char BSP_EEPROM_ReadStatusRegister(unsigned char opcode);
void BSP_EEPROM_InitAddress(unsigned char read_op,unsigned int addr);
void BSP_EEPROM_ReadData(unsigned char read_op,unsigned int addr,int r);
void BSP_EEPROM_WriteData(unsigned char write_op,unsigned int addr,int no,int byt);
void BSP_EEPROM_Write();
void BSP_EEPROM_Read();
char BSP_EEPROM_ReadFlags();
void BSP_EEPROM_WriteFlags(char data);
void BSP_EEPROM_WriteResetCount(char data);
char BSP_EEPROM_ReadResetCount();
void BSP_EEPROM_WriteLocationZero(char data);
char BSP_EEPROM_ReadLocationZero();
void BSP_EEPROM_Erase();
#endif
