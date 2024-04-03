/*
 * hbridge.h
 * Author- Ritika Salimath
 * Created on 12/03/24
 */
#ifndef HBRIDGE_H
#define HBRIDGE_H

#include "stm32h7xx.h"
#include "main.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;

#define FORWARD 0
#define REVERSE 1

extern int flag;

void initialize(GPIO_InitTypeDef *GPIO_InitStruct);
void sleep_1();
void sleep_2();
void sleep_3();
void getValues_torque(double t1,double t2,double t3);
void give_torque1(double t,int dir);
void give_torque2(double t,int dir);
void give_torque3(double t,int dir);
void fastdecay_torque1();
void slowdecay_torque1();
void fastdecay_torque2();
void slowdecay_torque2();
void fastdecay_torque3();
void slowdecay_torque3();
void setreset_x();
void setreset_y();
void setreset_z();

#endif
