#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "I2C.h"
/*
 * I2C1
 * 		SCK -> PB6
 * 		SDA -> PB7
 *
 * I2C2
 * 		SCK -> PB10
 * 		SDA -> PB11
 *
 * */

void I2C_Init(char i2c,unsigned short speed_mode){
	RCC->APB2ENR |= 1; //enable alternate function

	if(i2c==1){
		RCC->APB1ENR |=(1<<21);//enable i2c

		//pin configuration
		init_GP(PB, 6, OUT50, O_AF_OD);
		init_GP(PB, 7, OUT50, O_AF_OD);

		//reset the I2C peripheral
		I2C1->CR1 |= (1<<15);
		//remove ethe reset
		I2C1->CR1 &= ~(1<<15);

		I2C1->CR2 |= 0x8;//select frequency of 8 Mb

		I2C1->CCR = 40;//seelct speed of sck pin

		I2C1->TRISE = 9;// Maximum rise time
		/*
		 *  These bits should provide the maximum duration of the SCL feedback loop in master mode.
			The purpose is to keep a stable SCL frequency whatever the SCL rising edge duration.
			These bits must be programmed with the maximum SCL rise time given in the I2C bus
			specification, incremented by 1.
			For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			therefore the TRISE[5:0] bits must be programmed with 09h.
			(1000 ns / 125 ns = 8 + 1)
			The filter value can also be added to TRISE[5:0].
			If the result is not an integer, TRISE[5:0] must be programmed with the integer part, in order
			to respect the tHIGH parameter.
			Note: TRISE[5:0] must be configured only when the I2C is disabled (PE = 0).*/
		//enable I2C1
		I2C1->CR1 |= 1;
	}else if(i2c==2){
		RCC->APB1ENR |=(1<<22);//enable i2c

		init_GP(PB, 10, OUT50, O_AF_OD);
		init_GP(PB, 11, OUT50, O_AF_OD);//reset the I2C peripheral

		I2C2->CR1 |= (1<<15);
		I2C2->CR1 &= ~(1<<15);

		I2C1->CR1 = 0x00;
		I2C1->CR2 = 0x00;

		I2C1->CR2 = 0x08;

		I2C2->CCR = 40;//select speed of sck pin

		I2C2->TRISE = 0x09;// Maximum rise time

		I2C1->CR1 |= (1<<10);

//		I2C2->CR2 |= 0x8;//select frequency of 8 Mb

//		I2C2->CCR = speed_mode;//select speed of sck pin
//
//		I2C2->TRISE = 0x9;// Maximum rise time

		I2C2->CR1 |= 1;
	}
}


//start step

void I2C_Start(char i2c){
	if(i2c==1){
		I2C1->CR1 |= (1<<10);  // Enable the ACK
		I2C1->CR1 |= (1<<8);
		while(!(I2C1->SR1 & 1));
	}
	else if(i2c==2){
		I2C2->CR1 |= (1<<10);  // Enable the ACK
		I2C2->CR1 |= (1<<8);
		while(!(I2C2->SR1 & 1));
	}
}
//Sending the address + R/W
void I2C_Add(char i2c,char address, char RW){
	volatile int tmp;
	if(i2c==1){
		I2C1->DR = ((address)|RW);
		while((I2C1->SR1 & 0x2));
		while(!(I2C1->SR1 & 0x2)){
			tmp = I2C1->SR1;
			tmp = I2C1->SR2;
			if((I2C1->SR1 & 2) == 0)break;
		}
	}else if(i2c ==2){

		I2C2->DR |= ((address<<1)|RW);
		while(!(I2C2->SR1 & 0x2));
		char temp = I2C1->SR1 | I2C1->SR2;
	}
}
//Sending data Step
void I2C_Data(char i2c,char data){
	if(i2c==1){
//		while((I2C1->SR1 & 0x80) == 0);
		DelayMs(10);
		I2C1->DR = data;

		while((I2C1->SR1 & 0x80) == 0);
	}else if(i2c==2){
		I2C2->DR = data;
		while(!(I2C2->SR1 & (1<<7)));
	while((I2C2->SR1 & (1<<2)) == 0);
	}
}
//Stop Step
void I2C_Stop(char i2c){
	volatile int tmp;
	if(i2c==1){
		tmp = I2C1->SR1|I2C1->SR2;
		I2C1->CR1 |= (1<<9);
	}
	else if(i2c==2){
		tmp = I2C2->SR1|I2C2->SR2;
		I2C2->CR1 |= (1<<9);
	}
}
//I2C_Write()
void I2C_Write(char i2c,char address,char data[]){

	I2C_Start(i2c);

	I2C_Add(i2c, address, 0);//write

	int i=0;
	while(data[i]){
		I2C_Data(i2c, data[i++]);
	}

	I2C_Stop(i2c);
}

void I2C_Read (char i2c,char Address, char *buffer, char size)
{
/**** STEPS FOLLOWED  ************
1. If only 1 BYTE needs to be Read
	a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
	b) the Acknowledge disable is made during EV6 (before ADDR flag is cleared) and the STOP condition generation is made after EV6
	c) Wait for the RXNE (Receive Buffer not Empty) bit to set
	d) Read the data from the DR

2. If Multiple BYTES needs to be read
  a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
	b) Clear the ADDR bit by reading the SR1 and SR2 Registers
	c) Wait for the RXNE (Receive buffer not empty) bit to set
	d) Read the data from the DR
	e) Generate the Acknowlegment by settint the ACK (bit 10 in SR1)
	f) To generate the nonacknowledge pulse after the last received data byte, the ACK bit must be cleared just after reading the
		 second last data byte (after second last RxNE event)
	g) In order to generate the Stop/Restart condition, software must set the STOP/START bit
	   after reading the second last data byte (after the second last RxNE event)
*/

	int remaining = size;

/**** STEP 1 ****/
	volatile I2C_TypeDef* I2Cx[] = {I2C1,I2C2};
	if (size == 1)
	{
		/**** STEP 1-a ****/
		I2Cx[i2c-1]->DR = Address;  //  send the address
		while(!(I2C1->SR1 & (1<<6)));  // wait for ADDR bit to set

		/**** STEP 1-b ****/
		I2Cx[i2c-1]->CR1 &= ~(1<<10);  // clear the ACK bit
		uint8_t temp = I2Cx[i2c-1]->SR1 | I2Cx[i2c-1]->SR2;  // read SR1 and SR2 to clear the ADDR bit.... EV6 condition
		I2Cx[i2c-1]->CR1 |= (1<<9);  // Stop I2C

		/**** STEP 1-c ****/
		while (!(I2Cx[i2c-1]->SR1 & (1<<6)));  // wait for RxNE to set

		/**** STEP 1-d ****/
		buffer[size-remaining] = I2Cx[i2c-1]->DR;  // Read the data from the DATA REGISTER

	}

/**** STEP 2 ****/
	else
	{
		/**** STEP 2-a ****/
		I2Cx[i2c-1]->DR = Address;  //  send the address
		while (!(I2Cx[i2c-1]->SR1 & (1<<1)));  // wait for ADDR bit to set

		/**** STEP 2-b ****/
		uint8_t temp = I2Cx[i2c-1]->SR1 | I2Cx[i2c-1]->SR2;  // read SR1 and SR2 to clear the ADDR bit

		while (remaining>2)
		{
			/**** STEP 2-c ****/
			while (!(I2Cx[i2c-1]->SR1 & (1<<6)));  // wait for RxNE to set

			/**** STEP 2-d ****/
			buffer[size-remaining] = I2Cx[i2c-1]->DR;  // copy the data into the buffer

			/**** STEP 2-e ****/
			I2Cx[i2c-1]->CR1 |= 1<<10;  // Set the ACK bit to Acknowledge the data received

			remaining--;
		}

		// Read the SECOND LAST BYTE
		while (!(I2Cx[i2c-1]->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = I2Cx[i2c-1]->DR;

		/**** STEP 2-f ****/
		I2Cx[i2c-1]->CR1 &= ~(1<<10);  // clear the ACK bit

		/**** STEP 2-g ****/
		I2Cx[i2c-1]->CR1 |= (1<<9);  // Stop I2C

		remaining--;

		// Read the Last BYTE
		while (!(I2Cx[i2c-1]->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = I2Cx[i2c-1]->DR;  // copy the data into the buffer
	}

}
