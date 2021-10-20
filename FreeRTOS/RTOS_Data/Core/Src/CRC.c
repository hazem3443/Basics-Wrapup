/*
 * CRC.c
 *
 *  Created on: Sep 20, 2021
 *      Author: root
 */
#include "stm32f1xx_hal.h"
#include <stdlib.h>

void CRC_init(void) {

 RCC->AHBENR |= RCC_AHBENR_CRCEN;  // enable clock for CRC
 CRC->CR |= CRC_CR_RESET;   // Reset calculation

}

//this function takes int or char and returns the CRC value of it
uint32_t CRC_Send_32(uint32_t data){
	CRC->CR = CRC_CR_RESET;
	CRC->DR = data;
	return CRC->DR;
}

//this function takes Data Stream as pointer to it, it's size and returns it's CRC Value
uint32_t CRC_Send_Stream_32(uint32_t *data, size_t len){
	CRC->CR = CRC_CR_RESET;
	for (int i = 0; i < len; i++) {
		CRC->DR = data[i];
	}
	return CRC->DR;
}
