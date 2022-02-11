/*
 * UART.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Hazem
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdlib.h>

#include "stm32f1xx_hal.h"
#include "gp_driver.h"

#define Uart1 1 //UART1 PA9 (Tx),PA10 (Rx)
#define Uart2 2 //UART2 PA2 (Tx),PA3 (Rx)
#define Uart3 3 //UART3 PB10 (Tx),PB11 (Rx)

void UART_Init(unsigned short uart,unsigned long BR );
unsigned long UART_BRR_CALC(unsigned long BR );

char UART_Rx(unsigned short uart);
void UART_Tx(unsigned short uart,char c);

void UART_Tx_Stream(unsigned short uart, char str[]);
void UART_ISR(unsigned short uart, unsigned short uart_mgr[],char * str);

void systick_interrupt_start();
void systick_int(unsigned short uart_1_mgr[],unsigned short uart_2_mgr[],unsigned short uart_3_mgr[]);

void UART_msg(unsigned short uart,char str[],unsigned short str_mgr[]);

#endif /* INC_UART_H_ */
