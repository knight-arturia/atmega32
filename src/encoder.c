// impulsgeber initiation and interrupt generate


#include "encoder.h"


int32_t turn_count = 0;
uint32_t press_time = 0;
uint32_t press_duration = 0;
_Bool clockwise = 0;
_Bool anti_clockwise = 0;
_Bool press_flag = 0;
_Bool long_press_flag = 0;
_Bool short_press_flag = 0;

void encoder_INT0_init(void){
	DDRD &= ~(1 << PD2 | 1 << PD4);	// PIN INT0 as input set
	PORTD |= 1 << PD2 | 1 << PD4;	// set pull-up resistance

	GICR |= 1 << INT0;	// set interrupt at INT0
	MCUCR |= 1 << ISC01;
	MCUCR &= ~(1 << ISC00);	// interrupt at falling edge of INT0
	sei();

}

void encoder_INT1_init(void){
	DDRD &= ~(1 << PD3);	// PIN INT1 as input set
	PORTD |= 1 << PD3;	// set pull-up resistance

	GICR |= 1 << INT1;	// set interrupt at INT1
	MCUCR &= ~(1 << ISC11);
	MCUCR |= (1 << ISC10);	// any Logical Change
	sei();
}

void encoder_press_time(void){
	if(press_duration > 1000){
		long_press_flag = 1;
	}else{
		long_press_flag = 0;
		short_press_flag = 1;
	}
}

void encoder_clear(void){	// clear all the flag and parameter
	turn_count = 0;
	press_flag = 0;
	short_press_flag = 0;
	long_press_flag = 0;
	press_duration = 0;
	clockwise = 0;
	anti_clockwise = 0;
}

int32_t encoder_get_turn(void){
	return turn_count;
}

_Bool encoder_get_clockwise(void){
	return clockwise;
}

_Bool encoder_get_anticlockwise(void){
	return anti_clockwise;
}

_Bool encoder_get_pressflag(void){
	return short_press_flag;
}

_Bool encoder_get_longpressflag(void){
	return long_press_flag;
}


// confirm turn direction and impulse number
ISR(INT0_vect){

	led_toggle(0);

	if(PIND & (1 << PD4)){
		turn_count++;
		clockwise = 1;	// turn at clockwise
	}else {
		turn_count--;
		anti_clockwise = 1;	// turn at anti-clockwise
	}
}

// confirm press time
ISR(INT1_vect){

	led_toggle(1);

	if(press_flag == 0){
		press_time = timer2_get();
		press_flag = 1;
	}else {
		press_duration = timer2_get() - press_time;
		press_flag = 0;
		encoder_press_time();
	}
}
