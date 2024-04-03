#ifndef BSP_EEPROM_H
#define BSP_EEPROM_H

#include<stdlib.h>
#include "stm32f4xx.h"


#define wren 0x06 //Write enable
#define wrdi 0x04 //Write disable
#define rdsr 0x05 //Read status register
#define wrsr 0x01 //Write status register
#define read 0x03 //Read data single output
#define rdid 0x83 //Read identification page
#define wrid 0x82 //Write identification page
#define pgwr 0x02 //Page write(erase and program)
#define pger 0xDB //Page erase

void buffers(SPI_HandleTypeDef *spi, uint8_t *rd, uint8_t *wd);
void enable_write(uint8_t opcode);
void write_SR(uint8_t opcode,uint8_t cmd);
int read_SR(uint8_t opcode); //maybe return type should be integer
void read_data(uint8_t opcode,uint8_t *rdata);
void write_data(uint8_t opcode,uint8_t *wdata);
void page_erase(uint8_t opcode);
void read_IDpage(uint8_t opcode,uint8_t *rdata);
void write_IDpage(uint8_t opcode,uint8_t *wdata);


#endif
