/*
 * gp_driver.c
 *
 *  Created on: Sep 1, 2021
 *      Author: Hazem
 */

#include "gp_driver.h"
#include "stm32f1xx_hal.h"

void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt)
{
	// volatile unsigned long * CR;
	unsigned short tPIN = pin;
	unsigned short offset = 0x00;

	if(pin > 7)
	{
		tPIN -= 8;
		offset = 0x01;
	}

	volatile unsigned long *CRL_or_CRH[] = {&GPIO_A+offset,&GPIO_B+offset,&GPIO_C+offset};
	char RCCValues[] = {4,8,0x10};

	RCC_APB2ENR |= RCCValues[port-1];

	*CRL_or_CRH[port-1] &= ~(0xf<<(tPIN)*4); ///Reset the below pins
	*CRL_or_CRH[port-1] |= ((dir <<(tPIN*4)) | (opt<<(tPIN*4+2))); //// Set up the direction and the option of the PIN
/*
//	if(port == PA)
//		{
//			RCC_APB2ENR |= 4; //// Enabling PORT A
//			CR = (volatile unsigned long *) (&GPIO_A + offset);
//		}
//	else if(port == PB)
//		{
//			RCC_APB2ENR |= 8; //// Enabling PORT B
//			CR = (volatile unsigned long *) (&GPIO_B + offset);
//		}
//	else if(port == PC)
//		{
//			RCC_APB2ENR |= 0x10; //// Enabling PORT C
//			CR = (volatile unsigned long *) (&GPIO_C + offset);
//		}
*/
}

int R_GP(unsigned short port, unsigned short pin)
{
	volatile unsigned long *portsarr[] = {&GPIO_A+0x02,&GPIO_B+0x02,&GPIO_C+0x02};

	return ((*portsarr[port-1] & (1<<pin))>>pin);//convert pin state to true or false

/*
//	if(port == 1)
//	{
//		IDR = (volatile unsigned long *) (&GPIO_A + offset);
//	}
//	else if(port == 2)
//	{
//		IDR = (volatile unsigned long *) (&GPIO_B + offset);
//	}
//	else if(port == 3)
//	{
//		IDR = (volatile unsigned long *) (&GPIO_C + offset);
//	}
//	state = ((*IDR & (1<<pin))>>pin);
//	return state;
 */
}

void W_GP(unsigned short port, unsigned short pin, volatile unsigned short state)
{
	volatile unsigned long *portsarr[] = {&GPIO_A+0x03,&GPIO_B+0x03,&GPIO_C+0x03};
	__disable_irq();
	state ? (*portsarr[port-1] |= (state<<pin)) : (*portsarr[port-1] &= ~(1<<pin));
	__enable_irq();

/*	if(port == 1)
		{
			ODR = (volatile unsigned long *) (&GPIO_A + offset);
		}
	else if(port == 2)
		{
			ODR = (volatile unsigned long *) (&GPIO_B + offset);
		}
	else if(port == 3)
	{
		ODR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	state ? (*ODR |= (state<<pin)) : (*ODR &= ~(1<<pin));*/
}

void toggle_GP(unsigned short port, unsigned short pin)
{
	W_GP(port,pin,1^R_GP(port,pin));
/*	if (R_GP(port,pin))
		{
			W_GP(port,pin,~R_GP(port,pin));
		}
	else
		{
			W_GP(port,pin,1);
		}*/
}

void Delays(int time) /// Random delay function
{
	for(;time>0;time--)
	 for(int t=0;t<100000;t++);
}

void Systic_init(void){

	SysTick->CTRL = 5;
}

void DelayMillis(void){
	SysTick->LOAD = 8000-1;//wait one milli second if clock  == 72Mhz = 72*10^6 =1s 72*10^3 =1ms
	SysTick->VAL = 0;//register that is going to decrement till reaching zero which triggers a flag
	while((SysTick->CTRL & 0x00010000) == 0);//reach zero value in Val register
	//== 1 when counted to 0 since last time this was read.
	//== 0 not reached to zero
}

void DelayMs(unsigned long t){
	for(;t>0;t--)
	{
		DelayMillis();
	}
}
