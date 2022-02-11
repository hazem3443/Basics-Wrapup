/*
 * rockblock.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Hazem
 */

#include "rockblock.h"

void Receive_from_Rock_Modem(unsigned short uart_mgr[], char Uart_1_msg[]){
	//	char OK[]="OK\r";
	unsigned long int timeoutVal=0;
	//clear received buffer
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;

	/* Receive response */
	UART_Tx_Stream(Uart1,"AT\r");
	while( !find_str("OK\r",Uart_1_msg) || timeoutVal==1000000 )timeoutVal++;//wait for a certain period of time then move on
	//clear received buffer
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;

	/* Turn off Flow Control */
	timeoutVal=0;
	UART_Tx_Stream(Uart1,"AT&K0\r");
	while( !find_str("OK\r",Uart_1_msg) || timeoutVal==1000000)timeoutVal++;//wait for a certain period of time then move on
	//clear received buffer
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;

	/* Initiate an Extended SBD Session */
	UART_Tx_Stream(Uart1,"AT+SBDIX\r");

	//we can check message success before abort in this section :D
}

void Send_To_Rock_Modem(unsigned short uart_mgr[], char Uart_1_msg[],char ROCK_BLOCK_MSG[]){
	/* Issue AT command */
	unsigned long int timeoutVal=0;
	//clear received buffer
	uart_mgr[0] = 0;

	/* Receive response */
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;
	UART_Tx_Stream(Uart1,"AT\r");
	find_str("OK\r",Uart_1_msg);
	while( !find_str("OK\r",Uart_1_msg) || timeoutVal==1000000 )timeoutVal++;//wait for a certain period of time then move on

	/* Turn off Flow Control */
	timeoutVal=0;
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;
	UART_Tx_Stream(Uart1,"AT&K0\r");
	while( !find_str("OK\r",Uart_1_msg) || timeoutVal==1000000)timeoutVal++;//wait for a certain period of time then move on

	/* Insert ASCII message into MO buffer */
	//AT+SBDWT=Hello World\r
	timeoutVal=0;
	char TR_msg[50];

	concatenate(TR_msg, "AT+SBDWT=");
	concatenate(TR_msg, ROCK_BLOCK_MSG);
	concatenate(TR_msg, "\r");

	//clear received buffer
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;
	UART_Tx_Stream(Uart1,TR_msg);
	while( !find_str("OK\r",Uart_1_msg) || timeoutVal==1000000)timeoutVal++;//wait for a certain period of time then move on

	//clear received buffer
	str_empty(Uart_1_msg);
	uart_mgr[0] = 0;
	/* Initiate an Extended SBD Session */
	UART_Tx_Stream(Uart1,"AT+SBDIX\r");
}
