/*
 * motor.h
 * Author- Ritika Salimath
 * Created on 30/1/24
 */

#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "stm32f4xx.h"


//reference clock parameters
#define TIMCLOCK 64000000
#define PRESCALAR 64

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim12;

void motor_initialize(GPIO_InitTypeDef *GPIO_InitStruct);
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

void test_pwmip_x(double duty);
void test_pwmip_y(double duty);
void test_pwmip_z(double duty);

void stop_motor_x();
void stop_motor_y();
void stop_motor_z();


#endif
