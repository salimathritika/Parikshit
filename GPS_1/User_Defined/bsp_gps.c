#include "bsp_gps.h"
#include<stdlib.h>

BSP_GPS_Data *GPS_Data_Buffer;
uint8_t *GPS_Ready;
uint8_t *GPS_test;
uint16_t *GPS_Data;
int *GPS_set;
int *GPS_Loop;
uint16_t *GPS_Buffer;
/* Private functions */
void BSP_GPS_StructInit(BSP_GPS_Data *GPS_Data);

/*this function is just used to transfer buffers from the main.c file*/
void transferbuffer(BSP_GPS_Data *Data_Buffer,uint8_t Ready[8],uint8_t *test,uint16_t *Data,int *set,int *Loop,uint16_t Buffer[])
{
	GPS_Ready=(uint8_t *)malloc(sizeof(uint8_t)*8);
	GPS_Buffer=(uint16_t *)malloc(sizeof(uint16_t)*100);

	GPS_Data_Buffer=Data_Buffer;
	GPS_Ready=Ready;
	GPS_test=test;
	GPS_Data=Data;
	GPS_set=set;
	GPS_Loop=Loop;
	GPS_Buffer=Buffer;
}

/* Function to initialize the GPS UART and interrupts */
void BSP_GPS_Init(void)
{

	BSP_GPS_StructInit(GPS_Data_Buffer);
         
      //  USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

        NVIC_EnableIRQ(USART6_IRQn);

//	USART_Cmd(USART6, ENABLE);
}

//parsing data is to convert data from one format to another
/* Function to parse data into the GPS data structure */
uint8_t BSP_GPS_ParseData(uint8_t GPS_Buffer[],uint8_t length)
{
uint8_t i, j, checksum, tempchecksum;

	/* Get the checksum */
	for(i = 0; i < length; i++);
        i--;
	if(i > 30)
		return ERROR;
	j = i - 1;
	checksum = GPS_Buffer[j];

	/* Compute and verify the checksum */
	tempchecksum = 0;
	for(i = 0; i < j; i++)
		tempchecksum ^= GPS_Buffer[i];
	if(tempchecksum != checksum)
		return ERROR;

	/* Parse the message */
	switch(GPS_Buffer[2])
	{
	case 0x04:
		GPS_Data_Buffer->GPS_Position.XPos = ((int32_t)GPS_Buffer[4]) |
											(((int32_t)GPS_Buffer[5]) << 8) |
											(((int32_t)GPS_Buffer[6]) << 16) |
											(((int32_t)GPS_Buffer[7]) << 24);
		GPS_Data_Buffer->GPS_Position.YPos = ((int32_t)GPS_Buffer[8]) |
											(((int32_t)GPS_Buffer[9]) << 8) |
											(((int32_t)GPS_Buffer[10]) << 16) |
											(((int32_t)GPS_Buffer[11]) << 24);
		GPS_Data_Buffer->GPS_Position.ZPos = ((int32_t)GPS_Buffer[12]) |
											(((int32_t)GPS_Buffer[13]) << 8) |
											(((int32_t)GPS_Buffer[14]) << 16) |
											(((int32_t)GPS_Buffer[15]) << 24);
		GPS_Data_Buffer->GPS_Position.GPSTime = ((uint32_t)GPS_Buffer[16]) |
											   (((uint32_t)GPS_Buffer[17]) << 8) |
											   (((uint32_t)GPS_Buffer[18]) << 16) |
											   (((uint32_t)GPS_Buffer[19]) << 24);
		GPS_Ready[0] = SUCCESS;
		break;
	case 0x05:
		GPS_Data_Buffer->GPS_Velocity.XVel = ((int32_t)GPS_Buffer[4]) |
											(((int32_t)GPS_Buffer[5]) << 8) |
											(((int32_t)GPS_Buffer[6]) << 16) |
											(((int32_t)GPS_Buffer[7]) << 24);
		GPS_Data_Buffer->GPS_Velocity.YVel = ((int32_t)GPS_Buffer[8]) |
											(((int32_t)GPS_Buffer[9]) << 8) |
											(((int32_t)GPS_Buffer[10]) << 16) |
											(((int32_t)GPS_Buffer[11]) << 24);
		GPS_Data_Buffer->GPS_Velocity.ZVel = ((int32_t)GPS_Buffer[12]) |
											(((int32_t)GPS_Buffer[13]) << 8) |
											(((int32_t)GPS_Buffer[14]) << 16) |
											(((int32_t)GPS_Buffer[15]) << 24);
		GPS_Data_Buffer->GPS_Velocity.GPSTime = ((uint32_t)GPS_Buffer[16]) |
											   (((uint32_t)GPS_Buffer[17]) << 8) |
											   (((uint32_t)GPS_Buffer[18]) << 16) |
											   (((uint32_t)GPS_Buffer[19]) << 24);
		GPS_Ready[1] = SUCCESS;
		break;
	case 0x06:
		GPS_Data_Buffer->GPS_SolutionTime.Nanosecond = ((uint32_t)GPS_Buffer[4]) |
													  (((uint32_t)GPS_Buffer[5]) << 8) |
													  (((uint32_t)GPS_Buffer[6]) << 16) |
													  (((uint32_t)GPS_Buffer[7]) << 24);
		GPS_Data_Buffer->GPS_SolutionTime.Second = ((uint32_t)GPS_Buffer[8]) |
												  (((uint32_t)GPS_Buffer[9]) << 8) |
												  (((uint32_t)GPS_Buffer[10]) << 16) |
												  (((uint32_t)GPS_Buffer[11]) << 24);
		GPS_Data_Buffer->GPS_SolutionTime.WeekNumber = ((uint32_t)GPS_Buffer[12]) |
													  (((uint32_t)GPS_Buffer[13]) << 8) |
													  (((uint32_t)GPS_Buffer[14]) << 16) |
													  (((uint32_t)GPS_Buffer[15]) << 24);
		GPS_Ready[2] = SUCCESS;
		break;
	case 0x08:
		for(i = 0, j = 4; i < 12; i++, j++)
			GPS_Data_Buffer->GPS_ReceiverStatus.SV_ID[i] = GPS_Buffer[j];
		GPS_Data_Buffer->GPS_ReceiverStatus.Ephemeris = ((uint16_t)GPS_Buffer[16]) |
													   (((uint16_t)GPS_Buffer[17]) << 8);
		GPS_Data_Buffer->GPS_ReceiverStatus.Constel = ((uint16_t)GPS_Buffer[18]) |
													 (((uint16_t)GPS_Buffer[19]) << 8);
		GPS_Data_Buffer->GPS_ReceiverStatus.Status = ((uint32_t)GPS_Buffer[20]) |
													(((uint32_t)GPS_Buffer[21]) << 8) |
													(((uint32_t)GPS_Buffer[22]) << 16) |
													(((uint32_t)GPS_Buffer[23]) << 24);
		GPS_Data_Buffer->GPS_ReceiverStatus.Almanac = ((uint16_t)GPS_Buffer[24]) |
													 (((uint16_t)GPS_Buffer[25]) << 8);
		GPS_Data_Buffer->GPS_ReceiverStatus.Version = GPS_Buffer[26];
                if((GPS_Data_Buffer->GPS_ReceiverStatus.OtherStatus & (0x01<<7)) != (GPS_Buffer[27]&(0x01<<7)))
                  GPS_test = 1;
                else
                  GPS_test=0;
                
		GPS_Data_Buffer->GPS_ReceiverStatus.OtherStatus = GPS_Buffer[27];
		GPS_Ready[3] = SUCCESS;
		break;
	case 0x0A:
		for(i = 0, j = 4; i < 12; i++, j++)
			GPS_Data_Buffer->GPS_SNR.SNR[i] = GPS_Buffer[j];
		GPS_Ready[4] = SUCCESS;
		break;
	case 0x0B:
		GPS_Data_Buffer->GPS_DOP.HDOP = ((uint16_t)GPS_Buffer[4]) |
									   (((uint16_t)GPS_Buffer[5]) << 8);
		GPS_Data_Buffer->GPS_DOP.PDOP = ((uint16_t)GPS_Buffer[6]) |
									   (((uint16_t)GPS_Buffer[7]) << 8);
		GPS_Data_Buffer->GPS_DOP.GPSSecond = ((uint32_t)GPS_Buffer[8]) |
											(((uint32_t)GPS_Buffer[9]) << 8) |
											(((uint32_t)GPS_Buffer[10]) << 16) |
											(((uint32_t)GPS_Buffer[11]) << 24);
		GPS_Ready[5] = SUCCESS;
		break;
	case 0x0E:
		GPS_Data_Buffer->GPS_GPosition.GPSTimeOfWeek = ((uint32_t)GPS_Buffer[4]) |
													  (((uint32_t)GPS_Buffer[5]) << 8) |
													  (((uint32_t)GPS_Buffer[6]) << 16) |
													  (((uint32_t)GPS_Buffer[7]) << 24);
		GPS_Data_Buffer->GPS_GPosition.Latitude = ((int32_t)GPS_Buffer[8]) |
												 (((int32_t)GPS_Buffer[9]) << 8) |
												 (((int32_t)GPS_Buffer[10]) << 16) |
												 (((int32_t)GPS_Buffer[11]) << 24);
		GPS_Data_Buffer->GPS_GPosition.Longitude = ((int32_t)GPS_Buffer[12]) |
												  (((int32_t)GPS_Buffer[13]) << 8) |
												  (((int32_t)GPS_Buffer[14]) << 16) |
												  (((int32_t)GPS_Buffer[15]) << 24);
		GPS_Data_Buffer->GPS_GPosition.Altitude = ((int32_t)GPS_Buffer[16]) |
												 (((int32_t)GPS_Buffer[17]) << 8) |
												 (((int32_t)GPS_Buffer[18]) << 16) |
												 (((int32_t)GPS_Buffer[19]) << 24);

		GPS_Ready[6] = SUCCESS;
		break;
	case 0x0F:
		GPS_Data_Buffer->GPS_TimeDate.Hours = GPS_Buffer[4];
		GPS_Data_Buffer->GPS_TimeDate.Minutes = GPS_Buffer[5];
		GPS_Data_Buffer->GPS_TimeDate.Seconds = GPS_Buffer[6];
		GPS_Data_Buffer->GPS_TimeDate.Date = GPS_Buffer[7];
		GPS_Data_Buffer->GPS_TimeDate.Month = GPS_Buffer[8];
		GPS_Data_Buffer->GPS_TimeDate.Year = ((uint16_t)GPS_Buffer[9]) |
											(((uint16_t)GPS_Buffer[10]) << 8);
		GPS_Ready[7] = SUCCESS;
		break;
	default:
		return ERROR;
	}
	GPS_Data_Buffer->DataReady = SUCCESS;
	for(i = 0; i < 8; i++)
		GPS_Data_Buffer->DataReady &= GPS_Ready[i];
	return SUCCESS;
}

/* Function to return pointer to the GPS data structure */
BSP_GPS_Data *BSP_GPS_GetData(uint8_t GPS_Buffer[])
{
   int u=0;
  uint8_t length = 0;
  uint8_t GPS_Data[30];
    for(int i=0;i<8;i++)
    {
     switch(i)
         {
       case 0:length =22;
         break;
       case 1:length = 22;
       break;
       case 2:length = 18;
       break;
       case 3:length = 30;
       break;
       case 4:length = 18;
       break;
       case 5:length = 14;
       break;
       case 6:length = 22;
       break;
       case 7:length = 13;
       break;
        }

        for(int j=0;j<length;j++)
        {
            GPS_Data[j]=GPS_Buffer[u];
            u++;
        }
    
     //printf("%x",BSP_GPS_ParseData(GPS_Data,length));
     BSP_GPS_ParseData(GPS_Data,length);
    }
	return GPS_Data_Buffer;
}

/* Function to initialize the members of the BSP_GPS_Data structure */
void BSP_GPS_StructInit(BSP_GPS_Data *GPS_Data)
{
	uint8_t i;

	/* Initialize all members to zero */
	GPS_Data->GPS_Position.XPos = 0;
	GPS_Data->GPS_Position.YPos = 0;
	GPS_Data->GPS_Position.ZPos = 0;
	GPS_Data->GPS_Position.GPSTime = 0;

	GPS_Data->GPS_Velocity.XVel = 0;
	GPS_Data->GPS_Velocity.YVel = 0;
	GPS_Data->GPS_Velocity.ZVel = 0;
	GPS_Data->GPS_Velocity.GPSTime = 0;

	GPS_Data->GPS_SolutionTime.Nanosecond = 0;
	GPS_Data->GPS_SolutionTime.Second = 0;
	GPS_Data->GPS_SolutionTime.WeekNumber = 0;

	for(i = 0; i < 12; i++)
		GPS_Data->GPS_ReceiverStatus.SV_ID[i] = 0;
	GPS_Data->GPS_ReceiverStatus.Version = 0;
	GPS_Data->GPS_ReceiverStatus.OtherStatus = 0;
	GPS_Data->GPS_ReceiverStatus.Ephemeris = 0;
	GPS_Data->GPS_ReceiverStatus.Constel = 0;
	GPS_Data->GPS_ReceiverStatus.Almanac = 0;
	GPS_Data->GPS_ReceiverStatus.Status = 0;

	for(i = 0; i < 12; i++)
		GPS_Data->GPS_SNR.SNR[i] = 0;

	GPS_Data->GPS_DOP.HDOP = 0;
	GPS_Data->GPS_DOP.PDOP = 0;
	GPS_Data->GPS_DOP.GPSSecond = 0;

	GPS_Data->GPS_GPosition.Latitude = 0;
	GPS_Data->GPS_GPosition.Longitude = 0;
	GPS_Data->GPS_GPosition.Altitude = 0;
	GPS_Data->GPS_GPosition.GPSTimeOfWeek = 0;

	GPS_Data->GPS_TimeDate.Hours = 0;
	GPS_Data->GPS_TimeDate.Minutes = 0;
	GPS_Data->GPS_TimeDate.Seconds = 0;
	GPS_Data->GPS_TimeDate.Date = 0;
	GPS_Data->GPS_TimeDate.Month = 0;
	GPS_Data->GPS_TimeDate.Year = 0;

	/* Set the ready flags */
	GPS_Data->DataReady = ERROR;
	for(i = 0; i < 8; i++)
		GPS_Ready[i] = ERROR;
}

