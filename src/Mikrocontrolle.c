/*
 ============================================================================
 Name        : Mikrocontrolle.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//84:31:e4:d4:25:6d:a6:a0:e9:3c:5f:db:93:b2:86:8f knight.arturia@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>

#include "avr_base.h"
#include "led.h"
#include "lcd.h"
#include "timer2.h"
#include "timer0.h"
#include "encoder.h"
#include "spi.h"
#include "rfm69c.h"
#include "transceiver.h"

#define F_CPU 16000000UL

void Send(char *str){
	lcd_clear();
	printf("%s\n",str);
	lcd_locate(1 , 0);
	printf("%s\n","Sendung...");	// show the send information at display

	clear_flag();	// clear the trans_interrupt_flag
	RFM_StandbyMode();
	RFM_Send( 1, str);
	RFM_TxMode();

	while(1){
		timer2_wait(2000);
		if(transceiver_get_flag() == 1) break;
	}
	RFM_StandbyMode();
	RFM_RxMode();
}

int main(void) {
	led_init();
	timer0_init();
	timer2_init();
	encoder_INT0_init();
	encoder_INT1_init();
	lcd_init();
	SPI_Initialize();
	transceiver_initialize();
		while(1){
			transceiver_input_msg();	// input the message with encoder
			if(encoder_get_longpressflag() == 1)
				break;
		}
		if( RFM_Initialize( 10, 233) == 1){	// p_out is 10 and nodeAddress is 233
			Send( transceiver_get_msg() );
		} else{
			printf("Kann nicht Sendung");
		}
		transceiver_clear();	// clear the message after send the message


	return 0;
}
/*
int main(void){
	led_init();
	while(1){
		led_toggle(6);
	}
	return 1;
}*/
