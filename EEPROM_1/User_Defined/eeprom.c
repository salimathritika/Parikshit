//https://controllerstech.com/eeprom-and-stm32/ refer jic

#include "eeprom.h"

int bytes=0,no=0,re_no=0,q=0,testing_flag=0,add_eep=0x00,add_r=0x00,testing_flag_read=0;
unsigned char status[3]={'\0'},br=0;
char packet1[21]={0},packet2[9]={0},packet3[26]={0},packet4[3]={0},read_data[90]={'\0'},write_data[90]={'\0'},eeprom_read_flag=0;
uint8_t *rbuf;
uint8_t *tbuf;
void buffer(uint8_t *rb,uint8_t *tb)
{
	rbuf=rb;
	tbuf=tb;
}

/*
 * we do not have following functions:
 * 1)EEPROM clear to set all of those bytes to 0,initializing eeprom to hold new information
 * 2)EEPROM CRC to check if the stored data has been changed or corrupted
 * 3)EEPROM iteration to go through the entire EEPROM memory space(this func doesnt run on its own)
 * 4)EEPROM update to write data only if it is different from previous content
 */

void BSP_EEPROM_Init()
{
    BSP_EEPROM_CS_Low();
//    BSP_EEPROM_Power(); need to ask its function
   // BSP_EEPROM_SPI_Init();//it has already been initialized
    BSP_EEPROM_CS_High();
}

/***********************************************************************************
  Chip select low- This command pulls the Chip select line low to select the device.
    void eeprom_CS_low(void)
Parameters: NULL
Return Type: NULL

***********************************************************************************/
void BSP_EEPROM_CS_Low()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);//pulling CS line low
	HAL_Delay(100);
}

//void BSP_EEPROM_Power()
//{
//	//need to ask its function
////    P9DIR|= 0xFF; //Vcc for slave device
////    P9OUT|= 0xd1;
//}

/***********************************************************************************
Chip select high- This command pulls the Chip select line high to de-select the device.
    void eeprom_CS_high(void)
Parameters: NULL
Return Type: NULL

***********************************************************************************/
void BSP_EEPROM_CS_High()
{
	HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);//pulling CS high
    HAL_Delay(100);

}
/***********************************************************************************
SPI initialization- This function configures the SPI module of the MSP for EEPROM interface
    void eeprom_SPI_init(void)
Parameters: NULL
Return Type: NULL
***********************************************************************************/

//void BSP_EEPROM_SPI_Init()
//{
//    P9DIR|=0x91;        // direction for port 3
//    P9OUT|=0x91;        // ouutput for rest of the pins,CS,RESET
//    P9SEL|=0x31;        // P9.5,4,0 option select
//    UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
//    UCA2CTL0 |= UCMST+UCSYNC+UCMSB+UCCKPL; // 3-pin, 8-bit SPI master, MSB
//    UCA2CTL1 |= UCSSEL_3;// SMCLK
//    UCA2BR0 =4;
//    UCA2BR1 =0;
//    UCA2MCTL = 0; // No modulation
//    UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
//    UCA2IE |= UCRXIE+UCTXIE; // Enable USCI_A2 RX,TX interrupt
//}already initialized with the above values
/***********************************************************************************
Command write to EEPROM- This function is called to enable or disable write to the EEPROM.Also used to write to the status register
    void eeprom_write_cmd(opcode)
Parameters: opcode - send opcode �wren� to enable, �wrdi� to disable EEPROM write,'wrsr' to write to status register
            cmd- This is the data to be written into the status register. This field should be set to 0xff in case we want to enable or disable write to eeprom.
Return Type: NULL

***********************************************************************************/
void BSP_EEPROM_WriteCmd(unsigned char opcode,unsigned char cmd)
{
    BSP_EEPROM_CS_Low();
    while(!(testing_flag));
    //UCA2tbuf = opcode;
    *tbuf=opcode;
//    br=UCA2rbuf ;
    br=*(rbuf);
    testing_flag=1;
    if(cmd!=0xff)
    {
      while(!(testing_flag));
      //UCA2tbuf = cmd;
      *tbuf=cmd;
//      br=UCA2rbuf ;
      br=*(rbuf);
      testing_flag=1;
    }
    BSP_EEPROM_CS_High();
}
/***********************************************************************************
Reading status register- This function reads the status register of the EEPROM at any read/write cycle.
    int  read_status_register(opcode)
Parameters: opcode- The only command to this function is rdsr.
Return Type: integer. 1 if the module is busy, and 0 is the module is ready.
***********************************************************************************/
unsigned char BSP_EEPROM_ReadStatusRegister(unsigned char opcode)
{
    BSP_EEPROM_CS_Low();
    while(!(testing_flag));
//    br = UCA2rbuf ;
    br=*(rbuf);
//   UCA2tbuf = opcode;
    *tbuf=opcode;
//    br = UCA2rbuf ;
    br=*rbuf;
    testing_flag=1;
    int i=0;
    while(i<3)
    {
      while(!(testing_flag));
//      br=UCA2rbuf ;
      br=*rbuf;
//      UCA2tbuf = 0;
      *tbuf=0;
      testing_flag=1;
      while (!(testing_flag_read));
//      status[i++]= UCA2rbuf;
      status[i++]= *rbuf;
      testing_flag_read=0;
    }
    BSP_EEPROM_CS_High();
    return status[1];
}

/***********************************************************************************
This function is used to initialize the address location at which we are going to read or write. This function is called by the
program itself the using read and write functions.
***********************************************************************************/

void BSP_EEPROM_InitAddress(unsigned char read_op,unsigned int addr)
{
    int x;
    while(!(testing_flag));
//    br=UCA2rbuf;
    br=*(rbuf);
//    UCA2tbuf = read_op;
    *tbuf=read_op;
//    br=UCA2rbuf;
    br=*rbuf;
    testing_flag=1;
    x=(addr>>8)&0xff;
    while(!(testing_flag));
//    br=UCA2rbuf ;
    br=*(rbuf);
    for(int delay=0;delay<750;delay++);
//    UCA2tbuf = x;
    *tbuf=x;
//    br=UCA2rbuf ;
    br=*(rbuf);
    testing_flag=1;
    x=(addr)&0xff;
    while(!(testing_flag));
//    br=UCA2rbuf ;
    br=*(rbuf);
    *tbuf = x;
//    br=UCA2rbuf ;
    br=*(rbuf);
    testing_flag=1;
}

/***********************************************************************************
Reading from EEPROM- This function is used to read data from memory.
    void eeprom_read_data(opcode,add,num)
Parameter: opcode- The only op code to this function is read
                     add- The 16 bit memory address to which address has to be written
                     num- The number of address locations which are to be read.
Return Type:NULL

***********************************************************************************/
void BSP_EEPROM_ReadData(unsigned char read_op,unsigned int addr,int r)
{
    BSP_EEPROM_CS_Low();
    BSP_EEPROM_InitAddress(read_op,addr);
//    br= UCA2rbuf;
    br=*(rbuf);
    *tbuf = 0;
//    br= UCA2rbuf;
    br=*(rbuf);
    while(re_no<r)
    {
      while(!(testing_flag));
      *tbuf = 0;
//      read_data[re_no++] = UCA2rbuf;
      read_data[re_no++] =*rbuf;
      testing_flag=1;
    }
    BSP_EEPROM_CS_High();
    while(BSP_EEPROM_ReadStatusRegister(rdsr)&0x01);
}


/***********************************************************************************
Writing to EEPROM- This function is used to write data to memory.
    void eeprom_write(opcode,add)
Parameter: opcode- The only op code to this function is writ
                     add- The 16 bit memory address to which address has to be written.
Return Type:NULL

***********************************************************************************/


void BSP_EEPROM_WriteData(unsigned char write_op,unsigned int addr,int no,int byt)
{
    //int j=0;
    BSP_EEPROM_CS_Low();
    BSP_EEPROM_InitAddress(write_op,addr);
    int i=0;
    if(byt==1)
    {
//      br=UCA2rbuf ;
    	br=*(rbuf);
      *tbuf = write_data[i];
//      br=UCA2rbuf ;
      br=*(rbuf);
      add_eep++;
     }
    else
    {
      if((bytes+59)>=128)
      {
       no=128-bytes;
       bytes=0;
      }
      for(i=0;i<no;i++)
      {
//       br=UCA2rbuf ;
    	  br=*(rbuf);
       *tbuf = write_data[i];
//       br=UCA2rbuf ;
       br=*(rbuf);
      }
      BSP_EEPROM_CS_High();
      if(no!=59)
      {
        add_eep+=128;
        BSP_EEPROM_CS_Low();
        BSP_EEPROM_WriteCmd(wren,0xff);
        BSP_EEPROM_CS_High();
        BSP_EEPROM_CS_Low();
        BSP_EEPROM_InitAddress(write_op,addr);
        for(int l=no;l<59;l++)
        {
//          br=UCA2rbuf ;
        	br=*(rbuf);
          *tbuf = write_data[l];
//          br=UCA2rbuf ;
          br=*(rbuf);
        }
        BSP_EEPROM_CS_High();
      }
    }
    bytes+=no;
    while(BSP_EEPROM_ReadStatusRegister(rdsr)&0x01);
}

void BSP_EEPROM_Write()
{
    BSP_EEPROM_WriteCmd(wren,0xff);
    BSP_EEPROM_CS_High();
    BSP_EEPROM_WriteData(writ,add_eep,59,0);
    q++;
    if(q%128==0)
    {
      add_eep+=128;
    }
    if(q==1108)
      add_eep=0x0000;
}

void BSP_EEPROM_Read()
{
    for(int i=0;i<200;i++)
      bit_eeprom[i]='\0';
    re_no=0;
    if(bytes>=59)//rtc needs to be added
    {
       BSP_EEPROM_ReadData(read,add_r,59);
    }
    else
    {
       BSP_EEPROM_ReadData(read,add_r,no);
       add_r=add_eep;
       BSP_EEPROM_ReadData(read,add_r,59-no);
    }
    int l=0;
    for(int i=0;i<21;i++)
      packet1[i]=read_data[l++];
    for(int i=0;i<9;i++)
      packet2[i]=read_data[l++];
    for(int i=0;i<26;i++)
      packet3[i]=read_data[l++];
    for(int i=0;i<3;i++)
      packet4[i]=read_data[l++];
}

char BSP_EEPROM_ReadFlags()
{
    char eeprom_flag_flag = 0;
    re_no=0;
    BSP_EEPROM_ReadData(read,0x01,1);
    eeprom_flag_flag=read_data[0];
    return eeprom_flag_flag;
}

void BSP_EEPROM_WriteFlags(char data)
{
    BSP_EEPROM_WriteCmd(wren,0xff);
    BSP_EEPROM_CS_High();
    write_data[0]=data;
    BSP_EEPROM_WriteData(writ,0x01,1,1);
}

void BSP_EEPROM_WriteLocationZero(char data)
{
    BSP_EEPROM_WriteCmd(wren,0xff);
    BSP_EEPROM_CS_High();
    write_data[0]=data;
    BSP_EEPROM_WriteData(writ,0x00,1,1);
}

