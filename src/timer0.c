// TIMER0 initial, get the Counter of TIMER0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>
#include "timer0.h"

void timer0_init(void){
	TCNT0 = 0;
	OCR0 = 4;		                           //dutyfactor set to 0.
	DDRB |= (1 << PB3);
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (1<<CS00);   //prescaler is 1

}

