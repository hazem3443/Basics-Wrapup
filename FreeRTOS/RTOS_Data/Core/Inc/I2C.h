/*
 * I2C.h
 *
 *  Created on: Oct 9, 2021
 *      Author: root
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#define I2C_SM 0x2D
#define I2C_FM 0xB4

void I2C_Init(char i2c,unsigned short speed_mode);

void I2C_Start(char i2c);
void I2C_Add(char i2c,char address, char RW);
void I2C_Data(char i2c,char data);
void I2C_Stop(char i2c);
void I2C_Write(char i2c,char address,char data[]);

#endif /* INC_I2C_H_ */
