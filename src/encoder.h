// impulsgeber initiation and interrupt generate

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>
#include "led.h"
#include "timer2.h"



void encoder_INT0_init(void);

void encoder_INT1_init(void);

void encoder_press_time(void);

void encoder_clear(void);

int32_t encoder_get_turn(void);

_Bool encoder_get_clockwise(void);

_Bool encoder_get_anticlockwise(void);

_Bool encoder_get_pressflag(void);

_Bool encoder_get_longpressflag(void);
