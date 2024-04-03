/*
 * hbridge.c
 * Author- Ritika Salimath
 * Created on 12/03/24
 */

#include"hbridge.h"


/*
 *void initialize(GPIO_InitTypeDef *GPIO_InitStruct)
 *fn- used to initialize the gpio pins to default settings.
 *    the nSLEEP pin has been set to high for all 3 h-bridges
 *    the timers have also been initialized.
 *note- this function is to be called in the MX_GPIO_Init function of main file
 *      because GPIO_InitStruct is local to that function only
 *param- GPIO_InitTypeDef *GPIO_InitStruct
 *return type- void
 */

void initialize(GPIO_InitTypeDef *GPIO_InitStruct)
{
	GPIO_InitStruct->Pin = nSleep_1_Pin|nSleep_2_Pin|nSleep_3_Pin;
	GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, GPIO_InitStruct);

	/*Configure GPIO pins : nFault_1_Pin nFault_2_Pin nFault_3_Pin */
	GPIO_InitStruct->Pin = nFault_1_Pin|nFault_2_Pin|nFault_3_Pin;
	GPIO_InitStruct->Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, GPIO_InitStruct);

	/*Configure GPIO pin : BIN2_3_Pin */
	GPIO_InitStruct->Pin = BIN2_3_Pin;
	GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(BIN2_3_GPIO_Port, GPIO_InitStruct);

	/*Configure GPIO pins : BIN1_2_Pin BIN2_2_Pin */
	GPIO_InitStruct->Pin = BIN1_2_Pin|BIN2_2_Pin;
	GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, GPIO_InitStruct);

	/*Configure GPIO pins : AIN2_3_Pin BIN1_3_Pin */
	GPIO_InitStruct->Pin = AIN2_3_Pin|BIN1_3_Pin;
	GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, GPIO_InitStruct);

	/*Configure GPIO pin : AIN1_3_Pin */
	GPIO_InitStruct->Pin = AIN1_3_Pin;
	GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct->Pull = GPIO_NOPULL;
	GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AIN1_3_GPIO_Port, GPIO_InitStruct);

	//keeping nSLEEP of all h-bridges high
	HAL_GPIO_WritePin(GPIOE, nSleep_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,nSleep_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, nSleep_3_Pin, GPIO_PIN_SET);


	//PWM initialization
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 200-1;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 100-1;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	htim5.Instance = TIM5;
	htim5.Init.Prescaler = 4000-1; //clk frequency is 200MHz hence this brings it down to 50khz
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.Period = 1-1; //have to get time period of 20us
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	htim12.Instance = TIM12;
	htim12.Init.Prescaler = 200-1;
	htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim12.Init.Period = 100-1;
	htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

}

/*
 * void sleep_1()
 * fn- to put the 1st hbridge to sleep mode(low power mode)
 * param- void
 * return type-void
 */


void sleep_1()
{
	HAL_GPIO_WritePin(GPIOE, nSleep_1_Pin, GPIO_PIN_RESET);
}

/*
 * void sleep_2()
 * fn- to put the 2nd hbridge to sleep mode(low power mode)
 * param- void
 * return type-void
 */

void sleep_2()
{
	HAL_GPIO_WritePin(GPIOE, nSleep_2_Pin, GPIO_PIN_RESET);
}

/*
 * void sleep_3()
 * fn- to put the 3rd hbridge to sleep mode(low power mode)
 * param- void
 * return type-void
 */

void sleep_3()
{
	HAL_GPIO_WritePin(GPIOE, nSleep_3_Pin, GPIO_PIN_RESET);
}

/*
 * void give_torque1(double t,int dir)
 * fn- this function is used to get the value and direction for torque_1 from the adcs
 *      module which is put into a formula to get corresponding duty cycle.
 *      i'm considering torqe_1 to be connected to the 'A' channel of hbridge1
 *      this fn then sets the pwm depending on the direction and the mode of decay
 * param- double t- torque for 1st torquer[connected to 'A' channel of 1st hbridge]
 *        int dir- direction in which torque is to be given. FORWARD(0) and REVERSE(1) are
 *                 the accepted values to be passed
 * return type- void
 */
void give_torque1(double t,int dir)
{
	int pwm;
	/*
	 * Right now according to EPS:
	 * For 0 millinewton metres(Min torque) it is 0 duty cycle
	 * For 0.3 milli newton metre(Max torque) it is 0.15 or 15% duty cycle
	 * following is the conversion factor given by EPS. It is subject to change.
	 * here the torque values are recieved in uNm (micro newton metre)
	 */
	pwm=(int)t/2;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);

	switch(dir)
	{
	  case 0:
	 {
		//have to choose one of the following
		//FOR FAST DECAY
		TIM12->CCR1=pwm;
		TIM12->CCR2=0;
		//FOR SLOW DECAY
		TIM12->CCR1=1;
		TIM12->CCR2=pwm;
	 }
	  case 1:
	  {
		  //have to choose one of the following
		  //FOR FAST DECAY
		  TIM12->CCR1=0;
		  TIM12->CCR2=pwm;
		  //FOR SLOW DECAY
		  TIM12->CCR1=pwm;
		  TIM12->CCR2=1;
	  }

	}

}


/*
 * void give_torque2(double t,int dir)
 * fn- this function is used to get the value and direction for torque_2 from the adcs
 *      module which is put into a formula to get corresponding duty cycle.
 *      i'm considering torque_2 to be connected to the 'B' channel of hbridge1
 *      this fn then sets the pwm depending on the direction and the mode of decay
 * param- double t- torque for 2nd torquer[connected to 'B' channel of 1st hbridge]
 *        int dir- direction in which torque is to be given. FORWARD(0) and REVERSE(1) are
 *                 the accepted values to be passed
 * return type- void
 */
void give_torque2(double t,int dir)
{
	int pwm;
	/*
	 * Right now according to EPS:
	 * For 0 millinewton metres(Min torque) it is 0 duty cycle
	 * For 0.3 milli newton metre(Max torque) it is 0.15 or 15% duty cycle
	 * following is the conversion factor given by EPS. It is subject to change.
	 * here the torque values are recieved in uNm (micro newton metre)
	 */
	pwm=(int)t/2;
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);

	switch(dir)
	{
	  case 0:
	 {
		//have to choose one of the following
		//FOR FAST DECAY
		TIM4->CCR1=pwm;
		TIM4->CCR2=0;
		//FOR SLOW DECAY
		TIM4->CCR1=1;
		TIM4->CCR2=pwm;
	 }
	  case 1:
	  {
		  //have to choose one of the following
		  //FOR FAST DECAY
		  TIM4->CCR1=0;
		  TIM4->CCR2=pwm;
		  //FOR SLOW DECAY
		  TIM4->CCR1=pwm;
		  TIM4->CCR2=1;
	  }

	}

}

/*
 * void give_torque3(double t,int dir)
 * fn- this function is used to get the value and direction for torque_3 from the adcs
 *      module which is put into a formula to get corresponding duty cycle.
 *      i'm considering torque_3 to be connected to the 'A' channel of hbridge2
 *      this fn then sets the pwm depending on the direction and the mode of decay
 * param- double t- torque for 3rd torquer[connected to 'A' channel of 2nd hbridge]
 *        int dir- direction in which torque is to be given. FORWARD(0) and REVERSE(1) are
 *                 the accepted values to be passed
 * return type- void
 */
void give_torque3(double t,int dir)
{
	int pwm;
	/*
	 * Right now according to EPS:
	 * For 0 millinewton metres(Min torque) it is 0 duty cycle
	 * For 0.3 milli newton metre(Max torque) it is 0.15 or 15% duty cycle
	 * following is the conversion factor given by EPS. It is subject to change.
	 * here the torque values are recieved in uNm (micro newton metre)
	 */
	pwm=(int)t/2;
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);

	switch(dir)
	{
	  case 0:
	 {
		//have to choose one of the following
		//FOR FAST DECAY
		TIM4->CCR3=pwm;
		TIM4->CCR4=0;
		//FOR SLOW DECAY
		TIM4->CCR3=1;
		TIM4->CCR4=pwm;
	 }
	  case 1:
	  {
		  //have to choose one of the following
		  //FOR FAST DECAY
		  TIM4->CCR3=0;
		  TIM4->CCR4=pwm;
		  //FOR SLOW DECAY
		  TIM4->CCR3=pwm;
		  TIM4->CCR4=1;
	  }

	}

}

/*
 * void fastdecay_torque1()
 * fn- this function is used to set the torque_1 to fast decay/coast decay
 *     can be called only once torque values are sent
 * param- void
 * return type- void
 */

void fastdecay_torque1()
{
	TIM12->CCR1=0;
	TIM12->CCR2=0;
}

/*
 * void fastdecay_torque2()
 * fn- this function is used to set the torque_2 to fast decay/coast decay
 *     can be called only once torque values are sent
 * param- void
 * return type- void
 */

void fastdecay_torque2()
{
	TIM4->CCR1=0;
	TIM4->CCR2=0;
}

/*
 * void fastdecay_torque3()
 * fn- this function is used to set the torque_3 to fast decay/coast decay
 *     can be called only once torque values are sent
 * param- void
 * return type- void
 */

void fastdecay_torque3()
{
	TIM4->CCR3=0;
	TIM4->CCR4=0;
}

/*
 * void slowdecay_torque1()
 * fn- this function is used to set the torque_1 to slow decay/brake decay
 *     can be called only once torque values are sent
 * param- void
 * return type- void
 */

void slowdecay_torque1()
{
	TIM12->CCR1=1;
	TIM12->CCR2=1;
}

/*
 * void slowdecay_torque2()
 * fn- this function is used to set the torque_2 to slow decay/brake decay
 *     can be called only once torque values are sent
 * param- void
 * return type- void
 */

void slowdecay_torque2()
{
	TIM4->CCR1=1;
	TIM4->CCR2=1;
}

/*
 * void slowdecay_torque3()
 * fn- this function is used to set the torque_3 to slow decay/brake decay
 *     can be called only once torque values are sent
 * param- void
 * return type- void
 */

void slowdecay_torque3()
{
	TIM4->CCR3=1;
	TIM4->CCR4=1;
}

/*
 * void setreset_?()
 * fn- used to control the MMSR strap of the magnetometer.This resets the accuracy of
 *     the magnetometer
 *     it keeps the xIN2 low throughout and keeps xIn1 high for only 20us after
 *     which it is pulled low again (as told by EPS)
 * param- void
 * return type- void
 */

void setreset_x()
{
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_GPIO_WritePin(GPIOA, BIN2_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, BIN1_2_Pin, GPIO_PIN_SET);
	while(flag!=1);
	if(flag==1)
	{
		HAL_GPIO_WritePin(GPIOA, BIN1_2_Pin, GPIO_PIN_RESET);
	}
	flag=0;
}

void setreset_y()
{
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_GPIO_WritePin(GPIOB, AIN2_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN1_3_GPIO_Port, AIN1_3_Pin, GPIO_PIN_SET);
	while(flag!=1);
	if(flag==1)
	{
		HAL_GPIO_WritePin(AIN1_3_GPIO_Port, AIN1_3_Pin, GPIO_PIN_RESET);
	}
	flag=0;
}

void setreset_z()
{
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_GPIO_WritePin(BIN2_3_GPIO_Port, BIN2_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BIN1_3_Pin, GPIO_PIN_SET);
	while(flag!=1);
	if(flag==1)
	{
		HAL_GPIO_WritePin(GPIOB, BIN1_3_Pin, GPIO_PIN_RESET);
	}
	flag=0;
}
