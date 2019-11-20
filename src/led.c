#include <avr/io.h>
#include <avr/iom32.h>

void led_init(){
	DDRD |= (1<<PD0)|(1<<PD1)|(1<<PD6);
	PORTD &= ~((1<<PD0)|(1<<PD1)|(1<<PD6));
}

void led_red(uint8_t val1){
	if((val1==0)|(val1==1)|(val1==6)){
		DDRD |= (1<<val1);
		PORTD &= ~(1<<val1);
	}

}

void led_green(uint8_t val2){
	if((val2==0)|(val2==1)|(val2==6)){
			DDRD |= (1<<val2);
			PORTD |= (1<<val2);
		}
}
void led_off(uint8_t val3){
	if((val3==0)|(val3==1)|(val3==6)){
			DDRD &= ~(1<<val3);
			PORTD |= (1<<val3);
		}
}
void led_toggle(uint8_t val4){
	if((val4==0)|(val4==1)|(val4==6)){
				PORTD^= (1<<val4);
			}
}
