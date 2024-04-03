/*
 * motor.h
 * Author- Ritika Salimath
 * Created on 30/1/24
 */

#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "stm32h7xx.h"

//reference clock parameters
#define TIMCLOCK 64000000
#define PRESCALAR 64

extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim23;

void motor_initialize(GPIO_InitTypeDef *GPIO_InitStruct);
void transfer(TIM_HandleTypeDef *tim2,TIM_HandleTypeDef *tim3,TIM_HandleTypeDef *tim14,TIM_HandleTypeDef *tm23,double *d_dutyx,double *d_dutyy,double *d_dutyz,double *f_dutyx,double *f_dutyy,double *f_dutyz);
uint8_t check_rotorlock(int a);

void set_rpm_motorx(double duty,int fr);
void set_rpm_motory(double duty,int fr);
void set_rpm_motorz(double duty,int fr);

void set_desired_motorx(double duty,int fr);
void set_desired_motory(double duty,int fr);
void set_desired_motorz(double duty,int fr);

void maintain_rpm_x(void);
void maintain_rpm_y(void);
void maintain_rpm_z(void);

void sleep_x(void);
void sleep_y(void);
void sleep_z(void);

#endif
