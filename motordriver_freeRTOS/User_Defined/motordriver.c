/*
 * motor.c
 * Author- Ritika Salimath
 * Created on 30/1/24
 */

#include "motordriver.h"
#include "main.h"


//static TIM_HandleTypeDef *tim2,*tim3,*tim1,*tim4;
static int frx,fry,frz; //desired fr value for direction of operation
static double duty_dx,duty_dy,duty_dz; //desired duty values
static double fbx_duty, fby_duty, fbz_duty; //feedback duty values

//Below set of variables used to calculate the feedback duty value
static uint32_t IC_Val1x=0,IC_Val1y=0,IC_Val1z=0;
static uint32_t IC_Val2x=0,IC_Val2y=0,IC_Val2z=0;
static int32_t Difference_x=0,Difference_y=0,Difference_z=0;
static int Is_First_Captured_x=0,Is_First_Captured_y=0,Is_First_Captured_z=0;

/*
 *void motor_initialize(GPIO_InitTypeDef *GPIO_InitStruct)
 *fn- used to initialize the gpio pins to default settings. the CMTMOD pin has been set to low for all 3 motor drivers
 *    the timers are also initialized
 *param- GPIO_InitTypeDef *GPIO_InitStruct -the GPIO_InitStruct is passed so that the GPIO pins can be initialized
 *return type- void
 *Additional info- RD1-109 PC10  rotor lock detection. GPIO input
                   RD2-110 PC11
                   RD3-111 PC12
                   CMT1-112 PD0  commutation mode. GPIO output
                   CMT2-113 PD1
                   CMT3-114 PD2
                   BRK1-4 PE5    braking mode. GPIO output
                   BRK2-5 PE6
                   BRK3-9 PC13
                   FR1-1 PE2     FR pin. GPIO output
                   FR2-2 PE3
                   FR3-3 PE4
                   FG1-125 PG12  FG pin. PWM input
                   FG2-126 PG13
                   FG3-127 PG14
 */
void motor_initialize(GPIO_InitTypeDef *GPIO_InitStruct)
{
	/*Configure GPIO pins : PC10 PC11 PC12 */
	  GPIO_InitStruct->Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
	  GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct->Pull = GPIO_NOPULL;
	  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, GPIO_InitStruct);

	  /*Configure GPIO pins : PD1 PD2 PD3 PD5
	                           PD6 PD7 */
	  GPIO_InitStruct->Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5
	                          |GPIO_PIN_6|GPIO_PIN_7;
	  GPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct->Pull = GPIO_NOPULL;
	  GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOD, GPIO_InitStruct);

	  /*Configure GPIO pins : PB4 PB5 PB6 */
	  GPIO_InitStruct->Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
	  GPIO_InitStruct->Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct->Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOB, GPIO_InitStruct);

    //Initializing CMTMOD to ground(sinusoidal mode)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET); //CMT1
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); //CMT2
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET); //CMT3

    //Initializing BRKMOD to high(dynamic braking mode)
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET); //BRK1
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET); //BRK2
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET); //BRK3

    //Initializing timers

   /* htim2.Instance = TIM2;
    htim2.Init.Prescaler = 64-1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 100-1;

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 64-1;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 100-1;

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 64-1;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 65535;

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 64-1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 100-1;

    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 64-1;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 100-1;
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.RepetitionCounter = 0;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    htim9.Instance = TIM9;
    htim9.Init.Prescaler = 64-1;
    htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim9.Init.Period = 100-1;
    htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    htim12.Instance = TIM12;
    htim12.Init.Prescaler = 64-1;
    htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim12.Init.Period = 100-1;
    htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
*/
    //note-the timer parameters will change so edit accordingly
}


/*
 *uint8_t check_rotorlock(int a)
 *fn- used to read the RD pins to check if the rotation lock is detected or not.
 *param- int a : if a=1 we check to rotor lock condition for reaction wheel in x
 *               direction, if a=2 then y direction and if a=3 then z direction
 *return type- uint8_t returns 1 if rotor is locked and 0 otherwise
 */

uint8_t check_rotorlock(int a)
{
	switch(a)
	{
	case 1:
	{
		//reaction wheel in x-direction
		if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
			return 1;
		return 0;
	}
	case 2:
		{
			//reaction wheel in y-direction
			if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
				return 1;
			return 0;
		}
	case 3:
		{
			//reaction wheel in z-direction
			if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))
				return 1;
			return 0;
		}
	}
}

/*
 *void set_rpm_motor?(int duty,int a)
 *fn- used to set the duty cycle for the selected motor driver
 *param- int fr : if fr=0 then phase driving sequence is U->V->W
 *                   fr=1 then phase driving sequence is U->W->V
 *                   U phase is leading V phase by 120
 *       int duty : the value of the duty cycle in percentage(%)
 *return type- void
 */

//duty received is as a percentage and our max ARR is 100 so can apply directly

void set_rpm_motorx(double duty,int fr)
{
	//reaction wheel in x-direction
	TIM1->CCR1=duty;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, fr);
}

void set_rpm_motory(double duty,int fr)
{
	//reaction wheel in y-direction
	TIM2->CCR1=duty;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, fr);
}

void set_rpm_motorz(double duty,int fr)
{
	//reaction wheel in z-direction
	TIM3->CCR1=duty;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, fr);
}

/*
 * void set_desired_motor?(int duty,int fr)
 * fn- used to update the values in the static variable of the desired duty cycle and fr given by adcs
 *     Also calls the set_rpm fn to set with the desired values in the beginning
 * param- int duty: desired duty % given by ADCS
 *        int fr: fr or the desired direction given by ADCS
 * return type- void
 */

void set_desired_motorx(double duty,int fr)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	duty_dx=duty;
	frx=fr;
	set_rpm_motorx(duty_dx,frx);
	//test_pwmip_x(duty_dx);
}

void set_desired_motory(double duty,int fr)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	duty_dy=duty;
	fry=fr;
	set_rpm_motory(duty_dy,fry);
	test_pwmip_y(duty_dy);
}

void set_desired_motorz(double duty,int fr)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	duty_dz=duty;
	frz=fr;
	set_rpm_motorz(duty_dz,frz);
	test_pwmip_z(duty_dz);
}

/*
 * void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * fn-used to calculate the feedback duty value(only one motor at a time)
 *    it is actually an inbuilt function which we can overrie for our use. this function is called
 *    every time there is a rising or falling edge detected by the pin
 * param- TIM_HandleTypeDef *htim : timer variable
 * return type- void
 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if (Is_First_Captured_x==0) // if the first value is not captured
		{
			IC_Val1x = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured_x = 1;  // set the first captured as true

		}

		else   // if the first is already captured
		{
			IC_Val2x = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value

			if (IC_Val2x > IC_Val1x)
			{
				Difference_x = IC_Val2x-IC_Val1x;
			}

			else if (IC_Val1x > IC_Val2x)
			{
				Difference_x = (100 - IC_Val1x) + IC_Val2x;
			}

			double refClock = TIMCLOCK/(PRESCALAR);
			double mFactor = 1000000/refClock;
			fbx_duty = (Difference_x*mFactor)*100/htim8.Init.Period;

			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
			Is_First_Captured_x = 0; // set it back to false

		}
	}
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel1
		{
			if (Is_First_Captured_y==0) // if the first value is not captured
			{
				IC_Val1y = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read the first value
				Is_First_Captured_y = 1;  // set the first captured as true

			}

			else   // if the first is already captured
			{
				IC_Val2y = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);  // read second value

				if (IC_Val2y > IC_Val1y)
				{
					Difference_y = IC_Val2y-IC_Val1y;
				}

				else if (IC_Val1y > IC_Val2y)
				{
					Difference_y = (100 - IC_Val1y) + IC_Val2y;
				}

				double refClock = TIMCLOCK/(PRESCALAR);
				double mFactor = 1000000/refClock;
				fby_duty = (Difference_y*mFactor)*100/htim9.Init.Period;

				__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
				Is_First_Captured_y = 0; // set it back to false

			}
		}
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)  // if the interrupt source is channel1
		{
			if (Is_First_Captured_z==0) // if the first value is not captured
			{
				IC_Val1z = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read the first value
				Is_First_Captured_z = 1;  // set the first captured as true

			}

			else   // if the first is already captured
			{
				IC_Val2z = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);  // read second value

				if (IC_Val2z > IC_Val1z)
				{
					Difference_z = IC_Val2z-IC_Val1z;
				}

				else if (IC_Val1z > IC_Val2z)
				{
					Difference_z = (100 - IC_Val1z) + IC_Val2z;
				}

				double refClock = TIMCLOCK/(PRESCALAR);
				double mFactor = 1000000/refClock;
				fbz_duty = (Difference_z*mFactor)*100/htim12.Init.Period;

				__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
				Is_First_Captured_z = 0; // set it back to false

			}
		}

}

/*
 * void maintain_rpm_?(void)
 * fn- this function is used to implement the closed loop speed control.
 *     the feedback duty value and the desired duty value is constantly compared so to
 *     make sure that our motor runs at the desired speed (pseudo code available in documentation)
 *     the approved range for the duty value is taken to be desired_duty_value+-0.5(can be changed if needed)
 * param- void
 * return type- void
 */

void maintain_rpm_x()
{
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	double prevd;
	int i=0;
	while(i!=10000)
	{
		i++;
		prevd=duty_dx;
		while(prevd==duty_dx)
		{
			if((fbx_duty>(duty_dx+5)))
			{
				set_rpm_motorx((duty_dx),frx); //decreasing duty by 1% to get closer to desired rpm
			}
			else if((fbx_duty<(duty_dx-5)))
			{
				if(check_rotorlock(1)==1)
					{
					  continue;
					  //if needed more code to indicate that x direction motor is in locked state to be added here
					}
				set_rpm_motorx((duty_dx),frx); //increasing duty by 1% to get closer to desired rpm
			}
			if(i==10000)
				break;
		}
	}
}

void maintain_rpm_y()
{
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);
	double prevd;
	while(1)
	{
		prevd=duty_dy;
		while(prevd==duty_dy)
		{
			if((fby_duty>(duty_dy+5)))
			{
				set_rpm_motory((duty_dy),fry); //decreasing duty by 1% to get closer to desired rpm
			}
			else if((fby_duty<(duty_dy-5)))
			{
				if(check_rotorlock(2)==1)
					{
					  continue;
					  //if needed more code to indicate that y direction motor is in locked state to be added here
					}
				set_rpm_motory((duty_dy),fry); //increasing duty by 1% to get closer to desired rpm
			}
		}
	}
}

void maintain_rpm_z()
{
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
	double prevd;
	while(1)
	{
		prevd=duty_dz;
		while(prevd==duty_dz)
		{
			if((fbz_duty>(duty_dz+5)))
			{
				set_rpm_motorz((duty_dz),frz); //decreasing duty by 1% to get closer to desired rpm
			}
			else if((fbz_duty<(duty_dz-5)))
			{
				if(check_rotorlock(3)==1)
					{
					  continue;
					  //if needed more code to indicate that z direction motor is in locked state to be added here
					}
				set_rpm_motorz((duty_dz),frz); //increasing duty by 1% to get closer to desired rpm
			}
		}
	}
}

/*
 * void sleep_?(void)
 * fn- used to put the motor in sleep mode.
 *     driving the pwm low for a minimum of 1.2ms puts the motor in sleep mode
 * param- void
 * return type- void
 */

void sleep_x()
{
	set_rpm_motorx(0,frx);
	HAL_Delay(3); //minimum time to put motor to sleep is 1.2ms
}

void sleep_y()
{
	set_rpm_motory(0,fry);
	HAL_Delay(3); //minimum time to put motor to sleep is 1.2ms
}

void sleep_z()
{
	set_rpm_motorz(0,frz);
	HAL_Delay(3); //minimum time to put motor to sleep is 1.2ms
}

/*
 * void test_pwmip_x(double duty)
 * fn- to provide input pwm to test the speed control loop
 * param- double duty: duty value
 * return type- void
 */

void test_pwmip_x(double duty)
{
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
	TIM8->CCR1=duty;
}

void test_pwmip_y(double duty)
{
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
	TIM9->CCR1=duty;
}

void test_pwmip_z(double duty)
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	TIM12->CCR1=duty;
}

//uint32_t read_x()
//{
//	return fbx_duty;// read second va
//}


/*
 * void stop_motor_?()
 * fn- used to gradually stop the motor after testing is done
 * param- void
 * return type-void
 */
void stop_motor_x()
{
	for(double i=duty_dx;i>=0;i=i-5)
	{
		set_rpm_motorx(i,frx);
		HAL_Delay(5000);//delay of 5s between every 5% decrease in duty value
	}
	set_rpm_motorx(0,frx);
}
void stop_motor_y()
{
	for(double i=duty_dy;i>=0;i=i-5)
	{
		set_rpm_motory(i,fry);
		HAL_Delay(5000);//delay of 5s between every 5% decrease in duty value
	}
	set_rpm_motory(0,fry);
}
void stop_motor_z()
{
	for(double i=duty_dz;i>=0;i=i-5)
	{
		set_rpm_motorz(i,frz);
		HAL_Delay(5000);//delay of 5s between every 5% decrease in duty value
	}
	set_rpm_motorz(0,frz);
}
