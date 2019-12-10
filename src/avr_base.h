

/**

 * General definitions and macros for the whole project.

 */


#ifndef AVR_BASE_H

#define AVR_BASE_H



// CPU clock frequency

//#define F_CPU 16000000UL	/* 16MHz */



// basic include files

#include <stdlib.h>

#include <stdint.h>

#include <stdio.h>

#include <avr/io.h>

#include <avr/interrupt.h>

/*
#ifndef F_CPU

#error "F_CPU not defined!"

#endif
*/

//#include <util/delay.h>



// type definitions

#define bool uint8_t

#define TRUE	1

#define true	1

#define FALSE	0

#define false	0



// available ports on microcontroller

#define A 1

#define B 2

#define C 3

#define D 4



/**

 * Port name macros

 * 

 * These macros allow access to port registers through port name definitions or

 * the definitions above.

 * E.g. if you define something like

 * 

 *   #define SPI_PORT	B

 * 

 * you can change its port registers through

 * 

 *   PORT(SPI_PORT) = ...

 *   DDR(SPI_PORT) = ...

 *   PIN(SPI_PORT) = ...

 */

#define PORT(X) PORT_CONCAT(X)

#define PORT_CONCAT(X) MY_PORT ## X

#define MY_PORT1 PORTA

#define MY_PORT2 PORTB

#define MY_PORT3 PORTC

#define MY_PORT4 PORTD


#define DDR(X) DDR_CONCAT(X)

#define DDR_CONCAT(X) MY_DDR ## X

#define MY_DDR1 DDRA

#define MY_DDR2 DDRB

#define MY_DDR3 DDRC

#define MY_DDR4 DDRD


#define PIN(X) PIN_CONCAT(X)

#define PIN_CONCAT(X) MY_PIN ## X

#define MY_PIN1 PINA

#define MY_PIN2 PINB

#define MY_PIN3 PINC

#define MY_PIN4 PIND



/**

 * GPIO macros

 * 

 * The following macros make GPIO handling easier and provide better

 * readable code.

 * 

 * Example: switch on PB0, LED on PB1

 * 

 * 		setInput(B, 0);

 * 		setPullupOn(B, 0);

 * 		setOutput(B, 1);

 * 

 * 		if (pinRead(B, 0))

 * 			pinWriteHigh(B, 1);

 * 		else

 * 			pinWriteLow(B, 1);

 */

// Pin configuration

#define setOutput(port, pin)		DDR(port) |= (1 << pin)

#define setInput(port, pin)			DDR(port) &= ~(1 << pin)

#define setPullupOn(port, pin)		PORT(port) |= (1 << pin)

#define setPullupOff(port, pin)		PORT(port) &= ~(1 << pin)


// Read from given input pin.

// Note that this macro can yield any non-zero value if the pin is HIGH!

// Pin state should therefore be checked through "if (pinRead(...))" or "if (!pinRead(...))"

#define pinRead(port, pin)			(PIN(port) & (1 << pin))


// Set state of given output pin

#define pinWriteHigh(port, pin)		PORT(port) |= (1 << pin)

#define pinWriteLow(port, pin)		PORT(port) &= ~(1 << pin)

#define pinToggle(port, pin)		PORT(port) ^= (1 << pin)



#endif /* AVR_BASE_H */

