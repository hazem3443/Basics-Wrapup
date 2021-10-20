/*
 * UART.c
 *
 *  Created on: Sep 26, 2021
 *      Author: root
 */
#include <stdlib.h>

#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "UART.h"

void UART_Init(unsigned short uart,unsigned long BR ){
	// INIT UART
	//Enable the alternate function for PINs
	__disable_irq();
	RCC->APB2ENR |= 1;

	USART_TypeDef * USARTx[] = {USART1,USART2,USART3};
	unsigned long ENR []= {(1<<14), (1<<17), (1<<18)};

	//if we use uart1 clock is 72MHZ else 36MHZ
	//UART1 PA9 (Tx),PA10 (Rx)
	//UART2 PA2 (Tx),PA3 (Rx)
	//UART3 PB10 (Tx),PB11 (Rx)
	char Tx_Rx_pins [3][2] = {{9,10},{2,3},{10,11}};

	volatile uint32_t * APB[] = {&(RCC->APB2ENR),&(RCC->APB1ENR),&(RCC->APB1ENR)};

	//enable Clock for the related UART
	*(APB[uart-1]) |= ENR[uart-1];

	unsigned char P [] = {PA, PA, PB};

	init_GP((P[uart-1]), Tx_Rx_pins[uart-1][0], OUT50, O_AF_PP);
	init_GP((P[uart-1]), Tx_Rx_pins[uart-1][1], IN, I_PP);

	unsigned long UART_BR = UART_BRR_CALC(BR);

	USARTx[uart-1]->BRR = UART_BR;

	//Enable interrup section--|enable RXNE		| enable TXE
	USARTx[uart-1]->CR1 	|= 	(1<<5) 			;

	//Enable UART Transmit
	//------------------| Tx Enable | Rx Enable | Uart Enable
	USARTx[uart-1]->CR1 |= (1<<3) 	| (1<<2) 	| (1<<13);


	IRQn_Type nvics[] = {USART1_IRQn,USART2_IRQn,USART3_IRQn};

	NVIC_EnableIRQ(nvics[uart-1]);//enable Uart interrupt

	__enable_irq();
/*
	//	if(uart == 1){
	//
	//		RCC->APB2ENR |= (1<<14);
	//		//Enable the related pins
	//		init_GP(PA, 9, OUT50, O_AF_PP);
	//		init_GP(PA, 10, IN, I_PP);
	//		USARTx = USART1;
	//	}else if(uart == 2){
	//		//Enable UART
	//		RCC->APB1ENR |= (1<<17);
	//		//Enable the related pins
	//		init_GP(PA, 2, OUT50, O_AF_PP);
	//		init_GP(PA, 3, IN, I_PP);
	//		USARTx = USART2;
	//	}
	//	else if(uart == 3){
	//		RCC->APB1ENR |= (1<<18);
	//		//Enable the related pins
	//		init_GP(PB, 10, OUT50, O_AF_PP);
	//		init_GP(PB, 11, IN, I_PP);
	//		USARTx = USART3;
	//	}
	//
	//	//setup the baud rate BRR register
	//	//for 8MHZ
	//	//4800    bps = BRR 0x683
	//	//9600    bps = BBR 0x341
	//	//19200   bps = BBR 0x1A1
	//	//38400   bps = BBR 0x0D0
	//	//57600   bps = BBR 0x08A
	//	//74880   bps = BBR 0x06A
	//	//115200  bps = BBR 0x045
	//	//230400  bps = BBR 0x023
	//
	//	unsigned long UART_BR = UART_BRR_CALC(uart,BR);
	//
	//	USARTx->BRR = UART_BR;
	//
	//	//Enable UART Transmit
	//	USARTx->CR1 |= (1<<3);
	//	//Enable UART Receive
	//	USARTx->CR1 |= (1<<2);
	//
	//	//Enable UART
	//	USARTx->CR1 |= (1<<13);
 *
 */
}

unsigned long UART_BRR_CALC(unsigned long BR ){
	unsigned long div = 8000000;
	unsigned long dec;
	unsigned long final;

	double fraq = 8000000.00;
	double fraq2 = 1.00;

	div /= (BR * 16);
	fraq = 16*(fraq/(BR * 16) - div);
	dec = fraq;
	fraq2 = 100*(fraq-dec);
	if(fraq2 >50){
		dec++;
		if(dec == 16){
			dec=0;
			div++;
		}
	}
	final = (div<<4);
	final += dec;
	return final;
}

char UART_Rx(unsigned short uart){
	USART_TypeDef * USARTx[] = {USART1,USART2,USART3};

	while( !(USARTx[uart-1]->SR & (1<<5)));

	return USARTx[uart-1]->DR ;

	/*
	if(uart == 1){
		while( (USART1->SR & (1<<5)) == 0x00);

		c = USART1->DR;
	}else if(uart == 2){
		while( (USART2->SR & (1<<5)) == 0x00);

		c = USART2->DR;
	}
	else if(uart == 3){
		while( (USART3->SR & (1<<5)) == 0x00);

		c = USART3->DR;
	}
	return c;
	*/
}

void UART_Tx(unsigned short uart,char c){

	USART_TypeDef * USARTx[] = {USART1,USART2,USART3};

	USARTx[uart-1]->DR = c;

	while( !(USARTx[uart-1]->SR & (1<<6))){
//		USARTx[uart-1]->DR = 0x00;
	}
	/*
	if(uart == 1){
		USART1->DR = c;
		while( (USART1->SR & (1<<7)) ){
			USART1->DR = 0x00;
		};
	}else if(uart == 2){
		USART2->DR = c;
		while( (USART2->SR & (1<<7)) ){
			USART2->DR = 0x00;
		};
	}
	else if(uart == 3){
		USART3->DR = c;
		while( (USART3->SR & (1<<7)) ){
			USART3->DR = 0x00;
		};
	}
	*/
}

void UART_Tx_Stream(unsigned short uart, char str[]){

	int i=0;
 	while(str[i] != '\0'){
		UART_Tx(uart, str[i++]);
//		DelayMs(2);
	}

}

void UART_ISR(unsigned short uart, unsigned short uart_mgr[],char * str){
	//if bridge = 0 receive and save to the buffer
	//else then bridge send to the brige, the received from uart
	if(uart_mgr[2]==0){
		str[uart_mgr[0]] = UART_Rx(uart);
		if(uart_mgr[3] ){
			//terminator strategy (receive untill the terminator found then send)
			if(str[uart_mgr[0]] == uart_mgr[4]){
				uart_mgr[0]=0;
				uart_mgr[1]=1;
			}else
			{
				uart_mgr[0]++;
			}
		}else{
			//timer strategy (receive and after a certain period send)
			uart_mgr[0]++;
			uart_mgr[6] = uart_mgr[5];
			systick_interrupt_start();
		}
	}else{
		UART_Tx(uart_mgr[2], UART_Rx(uart));
	}
}
void systick_interrupt_start(){
	//will generate an interrupt
	__disable_irq();
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;//fires the interrupt
	//and inside the SysTick_Handler we call the systick_int function
	__enable_irq();
}

void systick_int(unsigned short uart_1_mgr[],unsigned short uart_2_mgr[],unsigned short uart_3_mgr[]){

	if(uart_1_mgr[0]!=0){
		if(uart_1_mgr[6] == 0){
			uart_1_mgr[0] = 0;
			uart_1_mgr[1] = 1;
			Systic_init();
		}else{
			uart_1_mgr[6]--;
		}
	}else if(uart_2_mgr[0]!=0){
		if(uart_2_mgr[6] == 0){
			uart_2_mgr[0] = 0;
			uart_2_mgr[1] = 1;
			Systic_init();
		}else{
			uart_2_mgr[6]--;
		}
	}else if(uart_3_mgr[0]!=0){
		if(uart_3_mgr[6] == 0){
			uart_3_mgr[0] = 0;
			uart_3_mgr[1] = 1;
			Systic_init();
		}else{
			uart_3_mgr[6]--;
		}
	}
}

void UART_msg(unsigned short uart,char str[],unsigned short str_mgr[]){
	unsigned long timeout = 1000000;
	UART_Tx_Stream(uart, str);
	while((str_mgr[1] == 0) & (timeout !=0)){
		timeout--;
	}
	str_mgr[1] = 0;
}
