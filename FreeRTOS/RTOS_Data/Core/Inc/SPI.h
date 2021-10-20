/*
 * SPI.h
 *
 *  Created on: Oct 2, 2021
 *      Author: root
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

void SPI_init(unsigned short spi);
void SPI_Tx(unsigned short spi,char Data);


void SPI_Msg(unsigned short spi, char str[]);

//for NRF library
void SPI_CS(unsigned short spi,unsigned short LOW_HIGH);
char SPI_Rx(unsigned short spi, char value);

#endif /* INC_SPI_H_ */
