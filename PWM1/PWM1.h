/*
 * PWM1.h
 *
 * Created: 18/04/2024 06:20:50
 *  Author: asrol
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>

void setupPWM1(void);
void setPWMChannelA(uint8_t duty_cycle);
void setPWMChannelB(uint8_t duty_cycle);

#endif /* PWM1_H_ */