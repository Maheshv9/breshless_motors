/*
 * 001calibration.c
 *
 *  Created on: 26-Aug-2021
 *      Author: MAHESH
 */
#include<stm32f4xxx.h>
void PWM_Setup(void);
float squre(float x);
int main()
{
	USART_Init();
	PWM_Setup();
	float k;

	TIM2->CCR1 = 200;
	Delay_ms(5000);
	TIM2->CCR1 = 100;
	Delay_ms(2000);
	while(1)
	{
		for(float i = -14.17; i<=14.17;i=i+0.23)
		{
			if(k<110) k=110;
			else if(k >150) k=150;

			printdatafloat(k);
			TIM2->CCR1 = (int)k;
			print("\n");

			k=squre(i)+1;

			Delay_ms(500);
		}

	}
	return 0;
}
void PWM_Setup(void)
{
	RCC->AHB1ENR |= 1;
	    GPIOA->AFRL[0] |= 0x00100000;
	    GPIOA->MODER |=  0x00000800;
	    RCC->APB1ENR |= 1;
	    TIM2->PSC = 160-1;//1250=50hz at system clk = 180MHz and APB2 BUS = 90MHz
	    TIM2->ARR = 2000-1;
	    TIM2->CNT = 0;
	    TIM2->CCMR1 = 0x0060;
	    TIM2->CCER = 1;
	    TIM2->CR1 = 1;
}
float squre(float x)
{
	return x*x;
}
