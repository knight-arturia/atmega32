// Transceiver set

#include "transceiver.h"

_Bool trans_interrupt_flag = 0;	// interrupt flag fur transceiver

void transceiver_initialize(void){
	DDRB &= ~(1 << PB2);	// set pin PB2  as input
	PORTB |= 1 << PB2;// set pull-up resistance , OC2 and INT2 = 1

	MCUCSR |= 1 << ISC2; // interrupt at rising edge of INT2
	GICR |= 1 << INT2;	// set interrupt at INT2
	GIFR |= 1 << INT2;

}

void clear_flag(void){
	trans_interrupt_flag = 0;	// set interrupt flag to 0
}

_Bool trans_get_flag(void){
	return trans_interrupt_flag;
}

ISR(INT2_vect){
	trans_interrupt_flag = 1;	// set interrupt flag to 1
}
