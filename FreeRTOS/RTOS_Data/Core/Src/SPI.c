/*
 * SPI.c
 *
 *  Created on: Oct 2, 2021
 *      Author: Hazem
 */

#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "SPI.h"
#include <stdlib.h>

void SPI_init(unsigned short spi){
	RCC->APB2ENR |= (1<<0);//enable AFIO function

	volatile uint32_t *RCCENR[] = {&(RCC->APB2ENR), &(RCC->APB1ENR)};
	uint16_t RCCENR_val[] = {(1<<12), (1<<14)};

	*RCCENR[spi-1] |= RCCENR_val[spi-1];//enable clock for SPIx

	uint8_t SPI_PORT[]={PA,PB};
	uint8_t SPI_Pins[2][4]={{4,5,6,7},{12,13,14,15}};

	init_GP(SPI_PORT[spi-1], SPI_Pins[spi-1][0], OUT50, O_GP_PP);//Configure CS pin
	init_GP(SPI_PORT[spi-1], SPI_Pins[spi-1][1], OUT50, O_AF_PP);//Configure Clock pin
	init_GP(SPI_PORT[spi-1], SPI_Pins[spi-1][2], IN, I_PP);//Configure MISO pin
	init_GP(SPI_PORT[spi-1], SPI_Pins[spi-1][3], OUT50, O_AF_PP);//Configure MOSI pin

	SPI_TypeDef *SPIx[]={SPI1,SPI2};

	SPIx[spi-1]->CR1 |= (1<<2);//enable mastr mode
	SPIx[spi-1]->CR1 |= 0x31;// fclk /265

	SPIx[spi-1]->CR2 |= (1<<2);//SS output is enabled in master mode and when the cell is enabled. The cell cannot work	in a multimaster environment.

	SPIx[spi-1]->CR1 |= (1<<6);//enable spi
	W_GP(SPI_PORT[spi-1], SPI_Pins[spi-1][0], HIGH);//enable slave for first byte sent
	/*
	if(spi ==1 ){
		//activate SPI-1 peripheral / AFIO function
			RCC->APB2ENR |= (1<<12) | (1<<0);

			//setup pins
			init_GP(PA, 4, OUT50, O_GP_PP);
			init_GP(PA, 5, OUT50, O_AF_PP);
			init_GP(PA, 6, IN, I_PP);
			init_GP(PA, 7, OUT50, O_AF_PP);

			// setup the spi peripheral
			SPI1->CR1 |= (0<<2);//enable mastr mode
			SPI1->CR1 |= 0x31;// fclk /265

			SPI1->CR2 |= (1<<2);

			SPI1->CR1 |= (1<<6);//enable spi
			W_GP(PA, 4, HIGH);

	}else if(spi==2){
		//activate SPI-2 peripheral / AFIO function
			RCC->APB2ENR |= (1<<0);
			RCC->APB1ENR |= (1<<14);

			//setup pins
			init_GP(PB, 12, OUT50, O_GP_PP);
			init_GP(PB, 13, OUT50, O_AF_PP);
			init_GP(PB, 14, IN, I_PP);
			init_GP(PB, 15, OUT50, O_AF_PP);

			//setup the spi peripheral
			SPI2->CR1 |= (0<<2);//enable mastr mode
			SPI2->CR1 |= 0x31;// fclk /265

			SPI2->CR2 |= (1<<2);

			SPI2->CR1 |= (1<<6);//enable spi
			W_GP(PB, 12, HIGH);
	}*/
}

void SPI_Tx(unsigned short spi,char Data){
	uint8_t SPI_PORT[] = {PA,PB};
	uint8_t SPI_PIN[] = {4,12};

	W_GP(SPI_PORT[spi-1], SPI_PIN[spi-1], HIGH);

	SPI_TypeDef *SPIx[]={SPI1,SPI2};
	SPIx[spi-1]->DR = Data;
	while(SPIx[spi-1]->SR & 0x80);
	W_GP(SPI_PORT[spi-1], SPI_PIN[spi-1], LOW);
	/*
	if(spi==1){
		W_GP(PA, 4, HIGH);
		SPI1->DR = Data;
		while(SPI1->SR & 0x80);
		W_GP(PA, 4, LOW);
	}else if(spi==2){
		W_GP(PB, 12, HIGH);
		SPI2->DR = Data;
		while(SPI2->SR & 0x80);
		W_GP(PB, 12, LOW);
	}*/
}

void SPI_Msg(unsigned short spi, char str[]){
	int i =0;

	uint8_t SPI_PORT[] = {PA,PB};
	uint8_t SPI_PIN[] = {4,12};

	SPI_TypeDef *SPIx[]={SPI1,SPI2};

	W_GP(SPI_PORT[spi-1], SPI_PIN[spi-1], HIGH);
	while(str[i]){
		SPIx[spi-1]->DR = str[i++];
		while(SPIx[spi-1]->SR & 0x80);
	}
	W_GP(SPI_PORT[spi-1], SPI_PIN[spi-1], LOW);
	/*
	if(spi==1){
		W_GP(PA, 4, HIGH);
		while(str[i]){
			SPI1->DR = str[i++];
			while(SPI1->SR & 0x80);
		}
		W_GP(PA, 4, LOW);

	}else if(spi==2){
		W_GP(PB, 12, HIGH);
		while(str[i]){
			SPI2->DR = str[i++];
			while(SPI2->SR & 0x80);
		}
		W_GP(PB, 12, LOW);
	}*/
}

//To be used with NRF Library
char SPI_Rx(unsigned short spi, char value){
	char Rx_val;
	SPI_TypeDef *SPIx[]={SPI1,SPI2};

	SPIx[spi-1]->DR = value;//send a value of a register to be read from a slave module
	while(SPIx[spi-1]->SR & 0x80);//wait till not being busy
	while(SPIx[spi-1]->SR & (1<<0)){Rx_val = SPIx[spi-1]->DR;} //read the data sent back from the slave
	return Rx_val;
/*
	if(spi==1){
		SPI1->DR = value;
		while(SPI1->SR & 0x80);
		while(SPI1->SR & (1<<0)){Rx_val = SPI1->DR;}
	}else if(spi==2){
		SPI2->DR = value;while(SPI2->SR & 0x80);
		while(SPI2->SR & 0x01){Rx_val = SPI2->DR;}
	}
	return Rx_val;
*/
}

void SPI_CS(unsigned short spi,unsigned short LOW_HIGH){
/*spi CS (chip select)*/
	uint8_t SPI_PORT[] = {PA,PB};
	uint8_t SPI_PIN[] = {4,12};
	W_GP(SPI_PORT[spi-1], SPI_PIN[spi-1], LOW_HIGH);
	/*
	if(spi ==1 ){
		W_GP(PA, 4, LOW_HIGH);
	}else if(spi == 2){
		W_GP(PB, 12, LOW_HIGH);
	}*/
}
