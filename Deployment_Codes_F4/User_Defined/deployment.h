/*
 * deployment.h
 * Author- Ritika Salimath
 * Created on 4/MAR/24
 */

#ifndef DEPLOYMENT_H
#define DEPLOYMENT_H

#include "stm32f4xx.h"

void deployment_init(GPIO_InitTypeDef *GPIO_InitStruct);
void deploy_antenna();
void long_deploy_antenna();
void deploy_door();
void long_deploy_door();
void deploy_tether();
void long_deploy_tether();



#endif
