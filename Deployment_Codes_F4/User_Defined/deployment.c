/*
 * deployment.c
 * Author- Ritika Salimath
 * Created on 4/MAR/24
 */

#include "deployment.h"

/*
 * void deployment_init(GPIO_InitTypeDef *GPIO_InitStruct)
 * func- to initialize the GPIO pins which help in the deployment mechanisms
 * [this fn is called in the MX_GPIO_Init in the main file because GPIO_InitStruct is local to that function only]
 * param- GPIO_InitTypeDef *GPIO_InitStruct : pointer to the GPIO_InitStruct to help in initialization
 * return type- void
 */

void deployment_init(GPIO_InitTypeDef *GPIO_InitStruct)
{
	GPIO_InitStruct->Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;  //pin 11-antenna; pin 12-door; pin 13- tether
	GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);
}

/*
 * void deploy_antenna()
 * fn- deploy the antenna. turn on the respective GPIO pin for 10s and then switch it off
 * param- void
 * return type- void
 */

void deploy_antenna()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_Delay(10000); //delay of 10s
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
}

/*
 * void long_deploy_antenna()
 * fn- deploy the antenna. turn on the respective GPIO pin for 1min and then switch it off
 * param- void
 * return type- void
 */

void long_deploy_antenna()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_Delay(60000); //delay of 60s or 1 min
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
}

/*
 * void deploy_door()
 * fn- deploy the door. turn on the respective GPIO pin for 10s and then switch it off
 * param- void
 * return type- void
 */

void deploy_door()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(10000); //delay of 10s
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
}

/*
 * void long_deploy_door()
 * fn- deploy the door. turn on the respective GPIO pin for 1min and then switch it off
 * param- void
 * return type- void
 */

void long_deploy_door()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(60000); //delay of 60s or 1 min
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
}

/*
 * void deploy_door()
 * fn- deploy the tether. turn on the respective GPIO pin for 10s and then switch it off
 * param- void
 * return type- void
 */

void deploy_tether()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(10000); //delay of 10s
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
}

/*
 * void long_deploy_tether()
 * fn- deploy the tether. turn on the respective GPIO pin for 1min and then switch it off
 * param- void
 * return type- void
 */

void long_deploy_tether()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(60000); //delay of 60s or 1 min
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
}
