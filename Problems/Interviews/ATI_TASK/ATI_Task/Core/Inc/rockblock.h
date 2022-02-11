/*
 * rockblock.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Hazem
 */

#ifndef INC_ROCKBLOCK_H_
#define INC_ROCKBLOCK_H_

#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "UART.h"
#include "help_func.h"

void Receive_from_Rock_Modem(unsigned short uart_mgr[], char Uart_1_msg[]);

void Send_To_Rock_Modem(unsigned short uart_mgr[], char Uart_1_msg[],char ROCK_BLOCK_MSG[]);
#endif /* INC_ROCKBLOCK_H_ */
