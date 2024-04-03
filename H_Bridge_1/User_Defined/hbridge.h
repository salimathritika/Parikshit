/*
 * hbridge.h
 * Author- Ritika Salimath
 * Created on 18/11/23
 */
#ifndef HBRIDGE_H
#define HBRIDGE_H

#include "stm32f4xx.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void initialize(GPIO_InitTypeDef *GPIO_InitStruct);
void getValues(double t1,double t2,double t3);
void send_pwm_1(double pwm);
void send_pwm_2(double pwm);
void send_pwm_3(double pwm);
void sleep_1();
void sleep_2();
void sleep_3();




#endif
