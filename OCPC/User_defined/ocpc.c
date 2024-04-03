#include"ocpc.h"
#include"stm32h7xx_hal_gpio.h"


/*
 * Function to initialise the OCPC module
 *
 * Parameters: None
 *
 * Returns: Nothing
 */

void BSP_OCPC_Init(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
	//HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    //have to replicate for more pins

}

/*
 * Function to deinitialise the OCPC module
 *
 * Parameters: None
 *
 * Returns: Nothing
 */
void BSP_OCPC_DeInit(void)
{
	HAL_NVIC_DisableIRQ(EXTI2_IRQn);
	//have to replicate
}



/*
 * Function to get OCPC fault status
 *
 * Parameters: The BSP_OCPC device to query
 *
 * Returns: 1. The BSP_OCPC fault status on a successful query
 *          2. RESET if uninitialised or invalid device
 */


uint8_t BSP_OCPC_GetFaultStatus(BSP_OCPC_Device OCPC_Device)
  {
      int PinState;
	  switch(OCPC_Device)
	  	{
	  	case BSP_OCPC_MAG:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_GYRO:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_SUN:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_HB:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_CVS:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_MD:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_WDT:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	case BSP_OCPC_TS:
	  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
	  		break;
	  	default:
	  		return GPIO_PIN_RESET;
	  	}
	  	return PinState ? GPIO_PIN_RESET : GPIO_PIN_SET;
	  }

/*
 * Function to get OCPC output status
 *
 * Parameters: The BSP_OCPC device to query
 *
 * Returns: 1. The BSP_OCPC device status on a successful query
 *          2. DISABLE if uninitialised or invalid device
 */

uint8_t BSP_OCPC_GetOutputStatus(BSP_OCPC_Device OCPC_Device)
{
    int PinState;
	switch(OCPC_Device)
		  	{
		  	case BSP_OCPC_MAG:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_GYRO:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_SUN:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_HB:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_CVS:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_MD:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_WDT:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	case BSP_OCPC_TS:
		  		PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
		  		break;
		  	default:
		  		return DISABLE;
		  	}
		  	return PinState ? DISABLE : ENABLE;
}

/*
 * Function to switch a specific OCPC on or off
 *
 * Parameters: 1. The BSP_OCPC_Device device to command
 *             2. The new state of the device
 *
 * Returns: 1. SUCCESS on successful setting
 *          2. ERROR if uninitialised or invalid device
 */
uint8_t BSP_OCPC_SetOutputStatus(BSP_OCPC_Device OCPC_Device, FunctionalState NewState)
{
	int PinState = ((uint8_t)NewState) ? GPIO_PIN_RESET : GPIO_PIN_SET;
	switch(OCPC_Device)
			  	{
			  	case BSP_OCPC_MAG:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_GYRO:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_SUN:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_HB:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_CVS:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_MD:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_WDT:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	case BSP_OCPC_TS:
			  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, PinState);
			  		break;
			  	default:
			  		return ERROR;
			  	}
			  	return SUCCESS;
 }


