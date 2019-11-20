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

#define F_CPU 16000000UL

int main(void) {
	timer0_init();
	timer2_init();
	lcd_init();
	printf("LIKEäöü");

	while(1){

	}
	return 0;
}
