/*
 * ADC.h
 *
 *  Created on: Sep 5, 2021
 *      Author: Hazem
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "gp_driver.h"


#define adc1          1
#define adc2          2

char adc_init(char adc, short port, short pin);
char adc_check(char adc, short port, short pin);
int adc_rx(char adc, short port, short pin);

#endif /* INC_ADC_H_ */
