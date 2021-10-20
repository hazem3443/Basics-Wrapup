/*
 * ADC.c
 *
 *  Created on: Sep 5, 2021
 *      Author: Hazem
 */
#include "stm32f1xx_hal.h"
#include "ADC.h"
/*
PA0 -> ADC12_IN0
PA1 -> ADC12_IN1
PA2 -> ADC12_IN2
PA3 -> ADC12_IN3
PA4 -> ADC12_IN4
PA5 -> ADC12_IN5
PA6 -> ADC12_IN6
PA7 -> ADC12_IN7
PB0 -> ADC12_IN8
PB1 -> ADC12_IN9

PC0 -> ADC12_IN10
PC1 -> ADC12_IN11
PC2 -> ADC12_IN12
PC3 -> ADC12_IN13
PC4 -> ADC12_IN14
PC5 -> ADC12_IN15

ADC12_IN16 input channel which is used to convert the sensor output voltage into a digital value (connected internally to the temperature sensor).

*/


// Initializing the ADC for the STM32F1
char adc_init(char adc, short port, short pin)
{
	//enable clock for gpio peripheral for i/o mode selection
	//configure pin as input
	//configure the pin as input analog function
	init_GP(port,pin,IN,I_AN);

	volatile int portsChannels[] = {pin,8+pin,10+pin};
	volatile int ADC_RCC_APB2ENR[] = {0x201,0x401};

	ADC_TypeDef * ADCs[] = {ADC1,ADC2};

	//enable clock for ADC module
	RCC->APB2ENR |= ADC_RCC_APB2ENR[adc-1];
	//reset control register for adc12 module
	ADCs[adc-1]->CR2 = 0;
	//select the channel to be used
	//we can use 6 channels at the same time but read on
	ADCs[adc-1]->SQR3 = portsChannels[port-1];
	//make ADC on then wait Tstab time to which is two clocks of clock adc connected to
	ADCs[adc-1]->CR2 |= 1;

	__asm__("nop	\n"
	        "nop	\n");
	ADCs[adc-1]->CR2 |= 1;//must be on two separate write commands

	ADCs[adc-1]->CR2 |= 2;//set bit 1 to configure ADC for continuous conversion

	return 1;//return 1 indicating successfull initialization
}

// Reading the flag that says the data is ready
char adc_check(char adc, short port, short pin)
{
	volatile int ADC_SRs[]={(ADC1->SR & 2), (ADC2->SR & 2)};

	return ADC_SRs[adc-1];//read EOC bit which is set to 0 when Conversion is not complete  and set to 1 when Conversion completed
}

// Reading the ADC value
int adc_rx(char adc, short port, short pin)
{
	volatile int ADC_Data_Register[]={(ADC1->DR), (ADC2->DR)};

	return ADC_Data_Register[adc-1];//read data register of 0xfff maximum value from 0 to 2^12=4096
}


