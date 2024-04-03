#include"stm32f4xx.h"
#include"cpal_i2c.h"

uint8_t address=0;
uint8_t data=0;
CPAL_TransferTypeDef Rx;

int main()
{

I2C_InitTypeDef I2C_InitStruct;
I2C_InitStruct.I2C_ClockSpeed = 100000;
I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
I2C_InitStruct.I2C_OwnAddress1 = 0;
I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;



Rx.pbBuffer=&address;
Rx.wAddr1=0xD0;
Rx.wAddr2=0x75;
Rx.wNumData=1u;

CPAL_I2C_StructInit(&I2C1_DevStructure);

I2C1_DevStructure.CPAL_Direction=CPAL_DIRECTION_TXRX;
I2C1_DevStructure.CPAL_Mode=CPAL_MODE_MASTER;
I2C1_DevStructure.pCPAL_TransferRx=&Rx;
I2C1_DevStructure.CPAL_ProgModel=CPAL_PROGMODEL_INTERRUPT;
CPAL_I2C_Init(&I2C1_DevStructure);


if(CPAL_I2C_Read(&I2C1_DevStructure)==CPAL_PASS)
while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY_RX);


/*data=Rx.pbBuffer[0];
for(int i=1;i>=7;i++)
data=(data<<1)+Rx.pbBuffer[i];*/

while(1);

}
