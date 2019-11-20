
// TIMER2 initial, get the Counter of TIMER2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>
#include "timer2.h"



void timer2_init(void){
	counter = 0;

	TIMSK &= ~( (1 << OCIE2) | (1 << TOIE2));		// disable interrupt OUTPUT_COMPARE of Counter2
	ASSR |= (1 << AS2);		// 	Timer2 is clocked from Oscillator with 32kHz frequency
	TCNT2 = 0;
	OCR2 = 32;
	TCCR2 |= (1 << WGM21) | (1 << CS20);
	while( (ASSR & 0b00000111) != 0 ){

	}	//wait for the TCN2UB, OCR2UB, TCR2UB become 0
	TIFR |= (1 << OCF2) | (1 << TOV2); // clear the Timer/Counter2 Interrupt Flags
	TIMSK |= (1 << OCIE2);
	sei();
}

uint32_t timer2_get(void){
	return counter;
}	// get the system time


void timer2_wait(uint32_t delay){

	uint32_t system_time;
	system_time = timer2_get();
	while( (counter - system_time) < delay ){

	}	// wait when counter < delay

}


ISR(TIMER2_COMP_vect){
	counter++;

}
