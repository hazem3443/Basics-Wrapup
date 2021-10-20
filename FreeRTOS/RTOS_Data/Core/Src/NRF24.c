/*
 * NRF24.c
 *
 *  Created on: Oct 3, 2021
 *      Author: root
 */

#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "SPI.h"
#include "NRF24.h"
#include <stdlib.h>

void NRF_Init(unsigned short spi){
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

	SPIx[spi-1]->CR1 |= (1<<2);//enable master mode
	SPIx[spi-1]->CR1 |= 0x10;// fclk /265

	SPIx[spi-1]->CR2 |= (1<<2);//SS output is enabled in master mode and when the cell is enabled. The cell cannot work	in a multimaster environment.

	SPIx[spi-1]->CR1 |= (1<<6);//enable spi
	W_GP(SPI_PORT[spi-1], SPI_Pins[spi-1][0], HIGH);
/*
	if(spi ==1 ){
		//activate SPI-1 peripheral / AFIO function
		RCC->APB2ENR |= (1<<12) | (1<<0);

		//setup pins
		init_GP(PA, 4, OUT50, O_GP_PP);
		init_GP(PA, 5, OUT50, O_AF_PP);
		init_GP(PA, 6, IN, I_PP);
		init_GP(PA, 7, OUT50, O_AF_PP);

		//setup the spi peripheral
		SPI1->CR1 |= (1<<2);//enable mastr mode
		SPI1->CR1 |= 0x10;// fclk /8

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

		// setup the spi peripheral
		SPI2->CR1 |= (1<<2);//enable mastr mode
		SPI2->CR1 |= 0x10;// fclk /8

		SPI2->CR2 |= (1<<2);

		SPI2->CR1 |= (1<<6);//enable spi
		W_GP(PB, 12, HIGH);
	}*/
}
//Read command from NRF
char NRF_Cmd_Rd(unsigned short spi, char register_addr){
	char nrf_spi_rd;
	SPI_CS(spi, LOW);
	SPI_Rx(spi, (register_addr & nrf_read));//send the register address to be read and receive the status register
	nrf_spi_rd = SPI_Rx(spi, 0x00);//then receive the data of that register in the next clocks on clock pin this happen by shifting and
	SPI_CS(spi, HIGH);
	return nrf_spi_rd;
}

char NRF_Cmd_wr(unsigned short spi, char register_addr,char new_val,char mask){
	char reg_val, new_reg_val, cmd;
	cmd = nrf_write | register_addr;

	reg_val = NRF_Cmd_Rd(spi, register_addr);//read register value
	new_reg_val = (reg_val & mask) | new_val;//modify the register with certain bit without modifying the other bits

	SPI_CS(spi, LOW);
	SPI_Rx(spi, cmd);//send the command within the address of the data to be updated
	SPI_Rx(spi, new_reg_val);//send the data to be writen into the register address in the cmd
	SPI_CS(spi, HIGH);

	reg_val = NRF_Cmd_Rd(1, register_addr);
	if(reg_val == new_reg_val) return 1;
	else return 0;
}

char NRF_Cmd(unsigned short spi, char cmd){
	char nrf_spi_rd;
	SPI_CS(spi, LOW);
	SPI_Rx(spi, cmd);//send the register address to be read and receive the status register
	nrf_spi_rd = SPI_Rx(spi, cmd);//then receive the data of that register in the next clocks on clock pin this happen by shifting and
	SPI_CS(spi, HIGH);
	return nrf_spi_rd;
}
