#ifndef BSP_GPS_H
#define BSP_GPS_H

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"

/* Defines */
typedef struct
{
	int32_t XPos, YPos, ZPos;
	uint32_t GPSTime;
} BSP_GPS_Position;

typedef struct
{
	int32_t XVel, YVel, ZVel;
	uint32_t GPSTime;
} BSP_GPS_Velocity;

typedef struct
{
	uint32_t Nanosecond, Second, WeekNumber;
} BSP_GPS_SolutionTime;

typedef struct
{
	uint8_t SV_ID[12], Version, OtherStatus;
	uint16_t Ephemeris, Constel, Almanac;
	uint32_t Status;
} BSP_GPS_ReceiverStatus;

typedef struct
{
	uint8_t SNR[12];
} BSP_GPS_SNR;

typedef struct
{
	uint16_t HDOP, PDOP;
	uint32_t GPSSecond;
} BSP_GPS_DOP;

typedef struct
{
	uint32_t GPSTimeOfWeek;
	int32_t Latitude, Longitude, Altitude;
} BSP_GPS_GPosition;

typedef struct
{
	uint8_t Hours, Minutes, Seconds, Date, Month;
	uint16_t Year;
} BSP_GPS_TimeDate;

typedef struct
{
	BSP_GPS_Position GPS_Position;
	BSP_GPS_Velocity GPS_Velocity;
	BSP_GPS_SolutionTime GPS_SolutionTime;
	BSP_GPS_ReceiverStatus GPS_ReceiverStatus;
	BSP_GPS_SNR GPS_SNR;
	BSP_GPS_DOP GPS_DOP;
	BSP_GPS_GPosition GPS_GPosition;
	BSP_GPS_TimeDate GPS_TimeDate;
	uint8_t DataReady;
} BSP_GPS_Data;

//extern BSP_GPS_Data GPS_Data_Buffer;
//extern uint8_t GPS_Ready[8];
//extern uint8_t GPS_test;
//extern uint16_t GPS_Data;
//extern int GPS_set;
//extern int GPS_Loop;
//extern uint16_t GPS_Buffer[100];

/* Function prototypes */
void BSP_GPS_Init(void);
void transferbuffer(BSP_GPS_Data *Data_Buffer,uint8_t Ready[8],uint8_t *test,uint16_t *Data,int *set,int *Loop,uint16_t Buffer[]);
uint8_t BSP_GPS_ParseData(uint8_t GPS_Buffer[],uint8_t length);
BSP_GPS_Data *BSP_GPS_GetData(uint8_t GPS_Buffer[]);

#endif /* BSP_GPS_H */
