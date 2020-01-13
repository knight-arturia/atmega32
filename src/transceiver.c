// Transceiver set

#include "transceiver.h"

_Bool trans_interrupt_flag = 0;	// interrupt flag fur transceiver
char message[16];			// array for the whole message
char current_letter;			// the letter which was managed rightnow
int letter_number = 0;		// the number of letters in the message
uint8_t row_location = 0;
uint8_t col_location = 0;


void transceiver_initialize(void){
	DDRB &= ~(1 << PB2);	// set pin PB2  as input
	PORTB |= 1 << PB2;// set pull-up resistance , OC2 and INT2 = 1

	MCUCSR |= 1 << ISC2; // interrupt at rising edge of INT2
	GICR |= 1 << INT2;	// set interrupt at INT2
	GIFR |= 1 << INT2;

	lcd_clear();
	current_letter = 'A';		// set A as begin letter
	letter_number = 0;

}

void clear_flag(void){
	trans_interrupt_flag = 0;	// set interrupt flag to 0
}

_Bool transceiver_input_msg(void){
	if( encoder_get_clockwise() == 1 ){		//choose letter when encoder turn at clockwise
		current_letter ++;
		row_location = 0;
		lcd_locate(row_location, col_location);
		printf("%c", current_letter);
		encoder_clear();
		led_toggle(0);
	}else if( encoder_get_anticlockwise() == 1 ){		//choose letter when encoder turn at anti-clockwise
		current_letter --;
		row_location = 0;
		lcd_locate(row_location, col_location);
		printf( "%c", current_letter);
		encoder_clear();
		led_toggle(1);
	}
	if( encoder_get_pressflag() == 1){
		if( current_letter == 0x40){		// choose 0x40 as delete current letter
			if( letter_number == 0){
				lcd_clear();	// when no letter to delete
				printf("Nothing to delete");
				timer2_wait(1000);

				lcd_clear();
				printf("%c", current_letter);	//show the current letter at diaplay
				encoder_clear();
				return false;
			}
			else{							//delete letter in normal situation
				row_location = 0;
				letter_number--;
				col_location--;
				lcd_locate(row_location, col_location);	// locate at new location
				current_letter = message[letter_number];
				message[letter_number] = '\0';
				encoder_clear();
				lcd_clear();
				printf("%s%c", message,current_letter);
				return true;

			}
		}
		else{							// normal situation
			message[letter_number] = current_letter;
			letter_number++;
			col_location++;
			message[letter_number] = '\0';
			lcd_clear();
			encoder_clear();
			printf("%s%c",message,current_letter);
			return true;
		}
	}
	if( encoder_get_longpressflag() == 1){
		if(letter_number ==0){		// nothing to send
			lcd_clear();
			printf("Nothing to Send");
			timer2_wait(1000);
			lcd_clear();
			printf("%c",current_letter);
			encoder_clear();
			return false;
		}
		encoder_clear();		// something to send
		return true;

	}
	if(letter_number > 15){
		letter_number = 0;
		message[letter_number] = '\0';
		return true;
	}

	return false;
}

void transceiver_clear(void){		// clear the message
	int i;
	for(i = 0; i < letter_number; i++){
		message[i] = 0;
	}
	current_letter = 'A';
	letter_number = 0;
	lcd_clear();
}


char* transceiver_get_msg(void){
	return message;
}

_Bool transceiver_get_flag(void){
	return trans_interrupt_flag;
}



ISR(INT2_vect){
	trans_interrupt_flag = 1;	// set interrupt flag to 1
}

