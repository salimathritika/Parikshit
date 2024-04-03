/*
 * hbridge.c
 * Author- Ritika Salimath
 * Created on 18/11/23
 */

#include"hbridge.h"


/*
 *void initialize()
 *fn- used to initialize the gpio pins to default settings. the nSLEEP pin has been set to high for all 3 h-bridges
 *no param
 *return type- void
 */

void initialize(GPIO_InitTypeDef *GPIO_InitStruct)
{
	//keeping nSLEEP of all h-bridges high
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	GPIO_InitStruct->Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
	                          |GPIO_PIN_11|GPIO_PIN_12;
	  GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct->Pull = GPIO_NOPULL;
	  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;

	  //PWM initialization
	  htim3.Init.Prescaler = 0;
	  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim3.Init.Period = 100-1;
	  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	  htim4.Init.Prescaler = 0;
	  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim4.Init.Period = 100-1;
	  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	  htim2.Init.Prescaler = 0;
	  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim2.Init.Period = 100-1;
	  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
}

/*
 * void sleep_1()
 * fn- to put the 1st hbridge to sleep mode(low power mode)
 * no param
 * return type-void
 */


void sleep_1()
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
}

/*
 * void sleep_2()
 * fn- to put the 2nd hbridge to sleep mode(low power mode)
 * no param
 * return type-void
 */

void sleep_2()
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
}

/*
 * void sleep_3()
 * fn- to put the 3rd hbridge to sleep mode(low power mode)
 * no param
 * return type-void
 */

void sleep_3()
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
}

/*
 * void getValues(int pwm1,int pwm2,int pwm3)
 * fn- this function is used to get the values for torque from the adcs module which is put into a formula to get corresponding duty cycle of each of the hbridges. this is then passed to set and start duty cycle of each hbridge
 * param- double t1- torque for 1st hbridge
 *        double t2- torque for 2nd hbridge
 *        double t3- torque for 3rd hbridge
 * return type- void
 */

void getValues(double t1,double t2,double t3)
{
	double pwm1,pwm2,pwm3;

	/*
	 * Right now according to EPS:
	 * For 0 millinewton metres(Min torque) it is 0 duty cycle
	 * For 0.3 milli newton metre(Max torque) it is 0.15 or 15% duty cycle
	 * following is the conversion factor given by EPS. It is subject to change.
	 * here the torque values are recieved in uNm (micro newton metre)
	 */
	pwm1=t1/2;
	pwm2=t2/2;
	pwm3=t3/2;

	//do typecast into int

	send_pwm_1(pwm1);
	send_pwm_2(pwm2);
	send_pwm_3(pwm3);
}

/*
 * void send_pwm_1(int pwm)
 * fn- used to set the duty cycle of 1st hbridge and to start the pwm
 * param- double pwm- duty cycle value
 * return type- void
 */

void send_pwm_1(double pwm)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	TIM2->CCR1=pwm;
	TIM2->CCR2=pwm;
	TIM2->CCR3=pwm;
	TIM2->CCR4=pwm;

}

/*
 * void send_pwm_2(int pwm)
 * fn- used to set the duty cycle of 2nd hbridge and to start the pwm
 * param- double pwm- duty cycle value
 * return type- void
 */

void send_pwm_2(double pwm)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	TIM3->CCR1=pwm;
	TIM3->CCR2=pwm;
	TIM3->CCR3=pwm;
	TIM3->CCR4=pwm;

}

/*
 * void send_pwm_3(int pwm)
 * fn- used to set the duty cycle of 3rd hbridge and to start the pwm
 * param- double pwm- duty cycle value
 * return type- void
 */

void send_pwm_3(double pwm)
{
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	TIM4->CCR1=pwm;
	TIM4->CCR2=pwm;
	TIM4->CCR3=pwm;
	TIM4->CCR4=pwm;

}
