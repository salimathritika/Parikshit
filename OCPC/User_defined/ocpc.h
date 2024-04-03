#include "main.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_hal_conf.h"

typedef enum
{
	BSP_OCPC_MAG,    //MAGNETOMETER
	BSP_OCPC_GYRO,   //GYROSCOPE
	BSP_OCPC_SUN,   //SUNSENSOR
	BSP_OCPC_HB,   //H-BRIDGE
	BSP_OCPC_CVS ,    //CURRENT AND VOLTAGE SENSOR
	BSP_OCPC_MD,     //MOTOR DRIVER
	BSP_OCPC_WDT,  //WATCHDOG TIMER
	BSP_OCPC_TS,    //TEMPERATURE SENSOR
} BSP_OCPC_Device;


void BSP_OCPC_Init(void);
void BSP_OCPC_DeInit(void);
uint8_t BSP_OCPC_GetFaultStatus(BSP_OCPC_Device OCPC_Device);
uint8_t BSP_OCPC_GetOutputStatus(BSP_OCPC_Device OCPC_Device);
uint8_t BSP_OCPC_SetOutputStatus(BSP_OCPC_Device OCPC_Device, FunctionalState NewState);

#define MAG_OCPC_SET (0x0001)
#define GYRO_OCPC_SET   (0x0001<<1)
#define SUN_OCPC_SET  (0x0001<<2)
#define HB_OCPC_SET    (0x0001<<3)
#define CVS_OCPC_SET   (0x0001<<4)
#define MD_OCPC_SET      (0x0001<<5)
#define WDT_OCPC_SET      (0x0001<<6)
#define TS_OCPC_SET   (0x0001<<7)

#define MAG_OCPC_FAULT (0x0001)
#define GYRO_OCPC_FAULT   (0x0001<<1)
#define SUN_OCPC_FAULT  (0x0001<<2)
#define HB_OCPC_FAULT    (0x0001<<3)
#define CVS_OCPC_FAULT   (0x0001<<4)
#define MD_OCPC_FAULT      (0x0001<<5)
#define WDT_OCPC_FAULT      (0x0001<<6)
#define TS_OCPC_FAULT   (0x0001<<7)



