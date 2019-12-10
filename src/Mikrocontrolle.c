/*
 ============================================================================
 Name        : Mikrocontrolle.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>

#include "led.h"
#include "lcd.h"
#include "timer2.h"
#include "timer0.h"
#include "encoder.h"
#include "spi.h"
#include "rfm69c.h"

#define F_CPU 16000000UL

int main(void) {
	timer0_init();
	timer2_init();
	lcd_init();
	led_init();
	SPI_Initialize();
	uint8_t i = testSPI();
	if( i == 1) printf("true");
	else printf("false");
	while(1){

	}
	return 0;
}

//84:31:e4:d4:25:6d:a6:a0:e9:3c:5f:db:93:b2:86:8f knight.arturia@gmail.com
