#include "eeprom.h"

/*if write function doesnt work then transmit an address to the eeprom to which data has to be written*/

SPI_HandleTypeDef *spi1;
uint8_t *read_buf,*write_buf;
uint16_t size;

void buffers(SPI_HandleTypeDef *spi, uint8_t *rd, uint8_t *wd)
{
	spi1=spi;
	read_buf=rd;
	write_buf=wd;
}

/***********************************************************************************
Command write to EEPROM- This function is called to enable or disable write to the EEPROM.
    void enable_write(uint8_t opcode)
Parameters: opcode - send opcode wren to enable, wrdi to disable EEPROM write

Return Type: NULL

***********************************************************************************/
void enable_write(uint8_t opcode)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;  //CS low
	HAL_SPI_Transmit(spi1, &opcode, 1, 1000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;  //CS high
}

/***********************************************************************************
Writing status register- This function writes the status register of the EEPROM.
    void write_SR(uint8_t opcode,uint8_t cmd)
Parameters: opcode- The only command to this function is wrsr.
            cmd-This is the data to be written into the status register
Return Type: NULL
***********************************************************************************/

void write_SR(uint8_t opcode,uint8_t cmd)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_Transmit(spi1, &opcode, 1, 1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(spi1, &cmd, 1, 1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
}

/***********************************************************************************
Reading status register- This function reads the status register of the EEPROM at any read/write cycle.
    int read_SR(uint8_t opcode)
Parameters: opcode- The only command to this function is rdsr.
Return Type: integer. 1 if the module is busy, and 0 if the module is ready.We are checking if the WIP bit of SR is 1 or 0
***********************************************************************************/

int read_SR(uint8_t opcode)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_TransmitReceive(spi1, &opcode, read_buf, 1,1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
//	if(((*read_buf)&0x01)==(*read_buf))
//		return 1;
	if(((*read_buf)<<7)==128) //128 is 10000000 in binary
		return 1;
	return 0;
}

/***********************************************************************************
Reading from EEPROM- This function is used to read data from memory.
    void read_data(uint8_t opcode,uint8_t *rdata)
Parameter: opcode- The only op code to this function is read
           *rdata is the buffer in which data will be read
Return Type:NULL

***********************************************************************************/

void read_data(uint8_t opcode,uint8_t *rdata)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_TransmitReceive(spi1, &opcode, rdata, 1,1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
}

/***********************************************************************************
Writing to EEPROM- This function is used to write data to memory.
    void write_data(uint8_t opcode,uint8_t *wdata)
Parameter: opcode- The only op code to this function is pgwr
           *wdata- buffer containing data to be written
Return Type:NULL

***********************************************************************************/

void write_data(uint8_t opcode,uint8_t *wdata)
{
	enable_write(wren);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_Transmit(spi1, &opcode, 1, 1000);  //To indicate that we are writing data into page
	while(spi1->State==HAL_SPI_STATE_READY);
	size=sizeof(wdata);
	HAL_SPI_Transmit(spi1, wdata, size, 1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
}

/***********************************************************************************
Erasing a page in the EEPROM
    void page_erase(uint8_t opcode)
Parameter: opcode- The only op code to this function is pger

Return Type:NULL

***********************************************************************************/

void page_erase(uint8_t opcode)
{
	enable_write(wren);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_Transmit(spi1, &opcode, 1, 1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
}

/***********************************************************************************
Reading from ID page of EEPROM- This function is used to read identity page.
    void read_IDpage(uint8_t opcode,uint8_t *rdata)
Parameter: opcode- The only op code to this function is rdid
           *rdata- the buffer in which data will be read
Return Type:NULL

***********************************************************************************/

void read_IDpage(uint8_t opcode,uint8_t *rdata)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_TransmitReceive(spi1, &opcode, rdata, 1,1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
}


/***********************************************************************************
Writing to EEPROM- This function is used to write data to memory.
    void write_IDpage(uint8_t opcode,uint8_t *wdata)
Parameter: opcode- The only op code to this function is wdid
           *wdata- buffer containing data to be written
Return Type:NULL

***********************************************************************************/

void write_IDpage(uint8_t opcode,uint8_t *wdata)
{
	enable_write(wren);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET ) ;
	HAL_SPI_Transmit(spi1, &opcode, 1, 1000);  //To indicate that we are writing data into page
	while(spi1->State==HAL_SPI_STATE_READY);
	size=sizeof(wdata);
	HAL_SPI_Transmit(spi1, wdata, size, 1000);
	while(spi1->State==HAL_SPI_STATE_READY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET ) ;
}


