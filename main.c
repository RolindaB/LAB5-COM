/*
 * lab5xx5.c
 *
 * Created: 17/04/2024 21:54:08
 * Author : asrol
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC/ADC.h"    // Incluye la biblioteca para el ADC
#include "PWM1/PWM1.h"    // Incluye la biblioteca para el PWM

uint8_t adc_value_A = 0;
uint8_t adc_value_B = 0;

int main(void)
{
	initADC();     // Inicializa el módulo ADC
	setupPWM1();    // Inicializa el módulo PWM
	
	sei();  // Habilita las interrupciones globales

	while (1)
	{
		// Inicia una conversión ADC para el canal A (A6)
		ADMUX = (ADMUX & 0xF8) | 0x06; // Selecciona el canal A6
		ADCSRA |= (1 << ADSC);  // Inicia una conversión ADC
		_delay_ms(10);           // Pequeña espera entre actualizaciones del ADC
		
		// Inicia una conversión ADC para el canal B (A4)
		ADMUX = (ADMUX & 0xF8) | 0x04; // Selecciona el canal A4
		ADCSRA |= (1 << ADSC);  // Inicia una conversión ADC
		_delay_ms(10);           // Pequeña espera entre actualizaciones del ADC
	}

	return 0;
}

ISR(ADC_vect)
{
	if ((ADMUX & 0x07) == 0x04) // Si el canal B (A4)
	{
		adc_value_B = ADCH; // Actualiza el valor del ADC para el canal B

		// Ajusta el ciclo de trabajo del PWM en el canal B
		setPWMChannelB((adc_value_B * 180) / 255); // Ajusta el ciclo de trabajo del canal B
	}
	else // Si es el canal A (A6)
	{
		adc_value_A = ADCH; // Actualiza el valor del ADC para el canal A

		// Ajusta el ciclo de trabajo del PWM en el canal A
		setPWMChannelA((adc_value_A * 180) / 255 + 10); // Ajusta el ciclo de trabajo del canal A
	}

	ADCSRA |= (1 << ADIF); // Apaga la bandera de interrupción del ADC
}
