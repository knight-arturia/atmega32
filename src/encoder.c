// impulsgeber initiation and interrupt generate


#include "encoder.h"


int32_t turn_count = 0;
uint32_t press_time = 0;
uint32_t press_duration = 0;
_Bool direction;
_Bool press_flag = 0;
_Bool long_press_flag = 0;

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

int32_t encoder_turn_get(void){
	return turn_count;
}

_Bool encoder_press_time(void){
	if(press_duration > 1000){
		long_press_flag = 1;
		return long_press_flag;
	}else{
		long_press_flag = 0;
		return long_press_flag;
	}
}


// confirm turn direction and impulse number
ISR(INT0_vect){

	if(PIND & (1 << PD4)){
		turn_count++;
		led_toggle(0);
		direction = 1;	// turn at clockwise
	}else {
		turn_count--;
		led_toggle(1);
		direction = 0;	// turn at anti-clockwise
	}
}

// confirm press time
ISR(INT1_vect){
	led_toggle(6);
	if(press_flag == 0){
		press_time = timer2_get();
		press_flag = 1;
	}else {
		press_duration = timer2_get() - press_time;
		press_flag = 0;
	}
}
