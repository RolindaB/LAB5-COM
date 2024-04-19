/*
 * PWM1.c
 *
 * Created: 18/04/2024 06:20:33
 *  Author: asrol
 */ 
#include "PWM1.h"


void setupPWM1(void) {
	// Configurar los pines como salidas PWM
	DDRB |= (1 << DDB1); // Canal A (OC1A)
	DDRB |= (1 << DDB2); // Canal B (OC1B)

	// Configurar el modo de PWM en el Timer1
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); // Modo Fast PWM, No invertido
	TCCR1B = (1 << WGM12); // Modo Fast PWM

	// Configurar el preescaler para el Timer1
	TCCR1B |= (1 << CS12); // Preescaler de 1024
}

void setPWMChannelA(uint8_t duty_cycle) {
	OCR1A = (duty_cycle * 180) /255+10; // Establecer el ciclo de trabajo del canal A
}

void setPWMChannelB(uint8_t duty_cycle) {
	OCR1B = (duty_cycle * 180) / 255; // Establecer el ciclo de trabajo del canal B
}