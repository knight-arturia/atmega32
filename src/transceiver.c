// Transceiver set

#include "transceiver.h"

_Bool trans_interrupt_flag = 0;	// interrupt flag fur transceiver
_Bool entry_mode;				// entry message now
_Bool msg_inputted;				// input finish
_Bool msg_received;				// receive finish
_Bool msg_sent;					// send finish

char message[16];			// array for the whole message
char current_letter;			// the letter which was managed rightnow
int letter_number = 0;		// the number of letters in the message
uint8_t row_location = 0;
uint8_t col_location = 0;


void transceiver_init(void){

	DDRB &= ~(1 << PB2);	// set pin PB2  as input
	PORTB &= ~(1 << PB2); 	// set pull-up resistance , OC2 and INT2 = 1

	MCUCSR |= 1 << ISC2; // interrupt at rising edge of INT2
	GICR |= 1 << INT2;	// set interrupt at INT2
	GIFR |= 1 << INT2;

	lcd_clear();
	message[0] = '\0';
	current_letter = 'A';		// set A as begin letter
	letter_number = 0;

}

void transceiver_entryMode(void){	// begin with entry mode
	if(encoder_get_pressflag( ) == 1){

		entry_mode = true;
		encoder_clear();
		lcd_clear();

		lcd_locate(0,0);
		printf("Entry Mode");
		timer2_wait(500);

		transceiver_clear();
	}
	else{
		switch_to_receiveMode();	// switch to receive mode after press the bottom
	}
}

void transceiver_run(uint8_t receiver_id){	// decide the transceiver in send or receive mode

	transceiver_entryMode();

	while(entry_mode){
		msg_inputted = transceiver_input_msg();

		if(msg_inputted){
			entry_mode = false;				// set entry_mode 0 when input finish

			transceiver_sendMsg(receiver_id);	// send message to this id

			msg_inputted = false;
		}
	}
	if(msg_received){
		transceiver_receiveMsg();			// change to receiver mode after send
	}
}

void transceiver_receiveMsg(void){

	if(msg_received){

		timer2_wait(500);
		lcd_clear();
		lcd_locate(1 , 0);
		printf("MSG Received");

		Packet received_packet = RFM_GetRxPacket();	// function at rfm69c.c line 287

		while(encoder_get_pressflag() == 0){	// wait for press the encoder and finisch

			timer2_wait(500);
			lcd_locate(0,0);
			printf("....");
		}
		encoder_clear();
		lcd_clear();
		printf("%s",received_packet.messageText);	// show the message after press the encoder

		timer2_wait(2000);

		msg_received = false;	//change the flag when finish the receive
	}
}

void transceiver_sendMsg(uint8_t receiver_id){

	RFM_StandbyMode();

	timer2_wait(500);
	lcd_clear();
	lcd_locate(1,0);
	printf("MSG Sending");
	//message [0] = 'A';

	timer2_wait(500);
	lcd_clear();
	lcd_locate(1,0);
	printf("MSG:%s",message);

	RFM_Send(receiver_id, &message[0]);
	RFM_TxMode();

	while(!msg_sent);	// wait until the message sending finish

	transceiver_sendFinish();
}

void transceiver_sendFinish(void){

	timer2_wait(500);
	lcd_clear();
	lcd_locate(1,0);
	printf("MSG Sent");

	switch_to_receiveMode();	// when finish sending process switch to receive mode
	msg_sent = false;

	transceiver_init();		// initialize the transceiver after send msg
}

void switch_to_receiveMode(void){

	RFM_StandbyMode();
	RFM_RxMode();
	timer2_wait(500);
}


_Bool transceiver_input_msg(void){

	if( encoder_get_clockwise() == 1 ){		//choose letter when encoder turn at clockwise
		current_letter ++;
		row_location = 0;
		lcd_locate(row_location, col_location);
		printf("%c", current_letter);
		encoder_clear();

	}else if( encoder_get_anticlockwise() == 1 ){		//choose letter when encoder turn at anti-clockwise
		current_letter --;
		row_location = 0;
		lcd_locate(row_location, col_location);
		printf( "%c", current_letter);
		encoder_clear();

	}
	if( encoder_get_pressflag() == 1){
		if( current_letter == 0x40){		// choose 0x40 as delete current letter
			if( letter_number == 0){
				lcd_clear();	// when no letter to delete
				printf("Nothing to delete");
				timer2_wait(1000);

				lcd_clear();
				printf("%c", current_letter);	//show the current letter at diaplay
				col_location--;
				encoder_clear();
				return false;
			}
			else{							//delete letter in normal situation
				row_location = 0;
				letter_number--;
				col_location--;				// change the col_location at new location
				current_letter = message[letter_number];
				message[letter_number] = '\0';
				encoder_clear();
				lcd_clear();
				printf("%s%c", message,current_letter);

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

void clear_flag(void){
	trans_interrupt_flag = 0;	// set interrupt flag to 0
}

void transceiver_clear(void){		// clear the message

	message[0] = '\0';
	current_letter = 'A';
	letter_number = 0;
	lcd_clear();
	printf("%c",current_letter);
}


char* transceiver_get_msg(void){
	return message;
}

_Bool transceiver_get_flag(void){
	return trans_interrupt_flag;
}



ISR(INT2_vect){

	trans_interrupt_flag = 1;	// set interrupt flag to 1
	led_toggle(6);
	if(RFM_GetMode() == RX){

		msg_received = true;
	}
	if(RFM_GetMode() == TX){

		msg_sent= true;
	}
}

