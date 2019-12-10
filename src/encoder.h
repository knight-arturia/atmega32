// impulsgeber initiation and interrupt generate

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>
#include "led.h"
#include "timer2.h"



void encoder_INT0_init(void);

void encoder_INT1_init(void);

int32_t encoder_turn_get(void);

_Bool encoder_press_time(void);
