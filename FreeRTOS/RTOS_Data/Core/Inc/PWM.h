/*
 * PWM.h
 *
 *  Created on: Sep 11, 2021
 *      Author: root
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

/*
 *PA0 -> T2C1 -> PWM_signal0
 *PA1 -> T2C2 -> PWM_signal1
 *PA2 -> T2C3 -> PWM_signal2
 *PA3 -> T2C4 -> PWM_signal3
 *PA6 -> T3C1 -> PWM_signal4
 *PA7 -> T3C2 -> PWM_signal5
 *PB0 -> T3C3 -> PWM_signal6
 *PB1 -> T3C4 -> PWM_signal7
 *PB6 -> T4C1 -> PWM_signal8
 *PB7 -> T4C2 -> PWM_signal9
 *PB8 -> T4C3 -> PWM_signal10
 *PB9 -> T4C4 -> PWM_signal11
 * */

enum PWM_Signals{
	   PWM_signal0
	 , PWM_signal1
	 , PWM_signal2
	 , PWM_signal3
	 , PWM_signal4
	 , PWM_signal5
	 , PWM_signal6
	 , PWM_signal7
	 , PWM_signal8
	 , PWM_signal9
	 , PWM_signal10
	 , PWM_signal11
};

void PWM_init(char PWM_signal, int frequency, int resolution);
void PWM_channel_Set(char PWM_signal, int PWM_Val);

#define bit(x) (1<<x)

#endif /* INC_PWM_H_ */
