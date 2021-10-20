/*
 * PWM.c
 *
 *  Created on: Sep 11, 2021
 *      Author: root
 */

/*
 *PA0 -> T2C1 -> PWM_signal0
 *PA1 -> T2C2 -> PWM_signal1
 *PA2 -> T2C3 -> PWM_signal2
 *PA3 -> T2C4 -> PWM_signal3
 *PA6 -> T3C1 -> PWM_signal4
 *PA7 -> T3C2 -> PWM_signal5
 *PB0 -> T3C3 -> PWM_signal6
 *PB1 -> T3C4 -> PWM_signal7
 *PB6 -> T4C1 -> PWM_signal8
 *PB7 -> T4C2 -> PWM_signal9
 *PB8 -> T4C3 -> PWM_signal10
 *PB9 -> T4C4 -> PWM_signal11
 * */

/*
 * Frequency of PWM signal = 8000000/ARR*PSC
 * we will make ARR = 1000 as our resolution from 0 to 1000 we can modify that through configuration
 * */
#include "stm32f1xx_hal.h"
#include "PWM.h"
#include "gp_driver.h"

void PWM_init(char PWM_signal, int frequency, int resolution){

	RCC->CR |= bit(0); //enable HSION 8000000 HZ
	int pin;
	volatile unsigned long port;

	int signal_pins[12]={0,1,2,3,6,7,0,1,6,7,8,9};

	pin = signal_pins[(int)PWM_signal];

	port = PA;
	if(PWM_signal>=6){
		port = PB;
	}

	init_GP(port,pin,OUT50, O_AF_PP);//enable clock for this peripheral and configure the pin mode as ALT_FUNC_OUT_50_mhz,OUTPUT mode

	//enable clock for timer x peripheral
	volatile TIM_TypeDef * TIMx[] = {TIM2,TIM3,TIM4};
	char timerIndex;

	//map timer index
	if(PWM_signal<4) timerIndex=0;
	else if(PWM_signal<8) timerIndex=1;
	else timerIndex=2;


	RCC->APB1ENR |= bit(timerIndex);

	//map channel index
	char channel;
	if(PWM_signal<4) channel = PWM_signal;
	else if(PWM_signal<8) channel = PWM_signal - 4;
	else channel = PWM_signal - 8;

	TIMx[(int)timerIndex]->CCER |= bit(channel*4); //Enable CC4E bit which enable
	TIMx[(int)timerIndex]->CR1 |= bit(7);//set ARPE bit which make ARR register is buffered



	//set OC4PE bit : Output compare 4 preload enable
	//set bit 13,14 for OC4M :Output compare 4 mode
	if(channel < 2) {
		if(channel < 1) TIMx[(int)timerIndex]->CCMR1 |= ( bit(3) | bit(5) |bit(6) );
		else TIMx[(int)timerIndex]->CCMR1 |= ((bit(3) | bit(5) |bit(6)) << 8);
	}
	else {
		if(channel < 3) TIMx[(int)timerIndex]->CCMR2 |= ( bit(3) | bit(5) |bit(6) );
		else TIMx[(int)timerIndex]->CCMR2 |= ((bit(3) | bit(5) |bit(6))<< 8);
	}

	//PWM frequency = Fclk / PSC * ARR
	//PWM Duty = CCR4 / ARR

	TIMx[(int)timerIndex]->PSC = 8000000/(frequency * resolution);//configure the prescaler for this timer from the main clock prescaller means (clock divider )

	TIMx[(int)timerIndex]->ARR = resolution;

	//reset all channels while configuration of PWM signals
	TIMx[(int)timerIndex]->CCR1 = 0;
	TIMx[(int)timerIndex]->CCR2 = 0;
	TIMx[(int)timerIndex]->CCR3 = 0;
	TIMx[(int)timerIndex]->CCR4 = 0;

	//start counting
	TIMx[(int)timerIndex]->EGR |= bit(0);
	TIMx[(int)timerIndex]->CR1 |= bit(0);//enable counter
}

void PWM_channel_Set(char PWM_signal, int PWM_Val){
	volatile TIM_TypeDef * TIMx[] = {TIM2,TIM3,TIM4};
	char timerIndex;

	//map timer index
	if(PWM_signal<4) timerIndex=0;
	else if(PWM_signal<8) timerIndex=1;
	else timerIndex=2;

	char channel;
	if(PWM_signal<4) channel = PWM_signal;
	else if(PWM_signal<8) channel = PWM_signal - 4;
	else channel = PWM_signal - 8;

	volatile uint32_t * CCR_ch_reg[] ={&TIMx[(int)timerIndex]->CCR1,&TIMx[(int)timerIndex]->CCR2,&TIMx[(int)timerIndex]->CCR3,&TIMx[(int)timerIndex]->CCR4};

	*(CCR_ch_reg[(int)channel]) =  PWM_Val;
}
