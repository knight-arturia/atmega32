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

const uint8_t receiver_id = 0xcd;
const uint8_t own_id = 0xcc;
const int8_t out_power = 10;

int main(void) {
	led_init();
	timer0_init();
	timer2_init();
	encoder_INT0_init();
	encoder_INT1_init();
	lcd_init();
	SPI_Initialize();
	RFM_Initialize(out_power, own_id);
	transceiver_init();

	while(1){

		transceiver_run(receiver_id);
	}

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
