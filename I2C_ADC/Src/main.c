#include "cpal_i2c.h"
CPAL_TransferTypeDef RX,TX;
uint8_t pBuf_RX, pBuf_TX=0x90,y1=0x00,y2=0x00;
int main(void)
{
RX.pbBuffer=&pBuf_RX;
RX.wNumData=3u;
RX.wAddr1=0xD0;
RX.wAddr2=0x00;

TX.pbBuffer=&pBuf_TX;
TX.wNumData=3u;
TX.wAddr1=0xD0;
TX.wAddr2=0x00;


I2C_InitTypeDef I2C_InitStruct;


I2C_InitStruct.I2C_ClockSpeed=400000;
I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;
I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
I2C_InitStruct.I2C_DutyCycle=I2C_DutyCycle_2;
I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;
I2C_InitStruct.I2C_OwnAddress1=0;  //address of the master mcu

I2C_Init(I2C1, &I2C_InitStruct);

//CPAL_InitTypeDef I2C1_DevStructure; //this is not necessary coz its already declared in cpal_i2c_hal_stm32f4xx.c file
I2C1_DevStructure.CPAL_Dev=CPAL_I2C1;
I2C1_DevStructure.CPAL_Direction=CPAL_DIRECTION_TXRX;
I2C1_DevStructure.CPAL_Mode=CPAL_MODE_MASTER;
I2C1_DevStructure.CPAL_ProgModel=CPAL_PROGMODEL_INTERRUPT;
I2C1_DevStructure.CPAL_State=CPAL_STATE_READY;
I2C1_DevStructure.pCPAL_I2C_Struct= &I2C_InitStruct;
I2C1_DevStructure.pCPAL_TransferRx= &RX;
I2C1_DevStructure.pCPAL_TransferTx=&TX;

//I2C1_DevStructure.wCPAL_DevError=CPAL_I2C_ERR_NONE;
//I2C1_DevStructure.wCPAL_Options= ((uint32_t)0x00000000);
    //I2C1_DevStructure.wCPAL_Timeout=((uint32_t)CPAL_I2C_TIMEOUT_DEFAULT);


    CPAL_I2C_Init(&I2C1_DevStructure);

    //CPAL_I2C_Write(&I2C1_DevStructure);
    //for(int i=0;i<1000;i++);
    //CPAL_I2C_DeInit(&I2C1_DevStructure);
    y1=I2C1_DevStructure.CPAL_State;
    //I2C1_DevStructure.CPAL_State=CPAL_STATE_READY;
    //while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY_TX);
    //I2C1_DevStructure.CPAL_State=CPAL_STATE_READY;

    CPAL_I2C_Read(&I2C1_DevStructure);
    y2=I2C1_DevStructure.CPAL_State;
    //while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY);
    //CPAL_I2C_Read(&I2C1_DevStructure);
    while(1);

}


/*#include"stm32f4xx.h"
#include"cpal_i2c.h"

uint8_t data=0;

CPAL_TransferTypeDef Rx;
CPAL_TransferTypeDef Tx;

int main()
{

I2C_InitTypeDef I2C_InitStruct;

I2C_InitStruct.I2C_ClockSpeed = 400000;
I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
I2C_InitStruct.I2C_OwnAddress1 = 0;
I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

//CPAL_TransferTypeDef Rx;
Rx.pbBuffer=&data;
Rx.wAddr1=0xD0;
Rx.wAddr2=0x00;
Rx.wNumData=1u;

//CPAL_TransferTypeDef Tx;
Tx.pbBuffer=0x90;
Tx.wAddr1=0xD0;
Tx.wAddr2=0x00;
Tx.wNumData=1u;

CPAL_I2C_StructInit(&I2C1_DevStructure);

I2C1_DevStructure.CPAL_Direction=CPAL_DIRECTION_TXRX;
I2C1_DevStructure.CPAL_Mode=CPAL_MODE_MASTER;
I2C1_DevStructure.pCPAL_TransferRx=&Rx;
I2C1_DevStructure.pCPAL_TransferTx=&Tx;
I2C1_DevStructure.CPAL_ProgModel=CPAL_PROGMODEL_INTERRUPT;

CPAL_I2C_Init(&I2C1_DevStructure);


if(CPAL_I2C_Write(&I2C1_DevStructure)==CPAL_PASS)
while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY);
//CPAL_I2C_ER_IRQHandler(&I2C1_DevStructure);
if(CPAL_I2C_Read(&I2C1_DevStructure)==CPAL_PASS)
while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY);

//data= Rx.pbBuffer[0];
//for(int i=1;i>=7;i++)
//data=(data<<1)+Rx.pbBuffer[i];


while(1);
}
*/
