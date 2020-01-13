
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>

#include "avr_base.h"
#include "encoder.h"
#include "timer2.h"
#include "lcd.h"
#include "led.h"

void transceiver_initialize(void);

void clear_flag(void);

_Bool transceiver_get_flag(void);

_Bool transceiver_input_msg(void);

void transceiver_clear(void);

char* transceiver_get_msg(void);
