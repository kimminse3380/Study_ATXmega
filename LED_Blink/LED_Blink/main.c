/*
 * GccApplication1.c
 *
 * Created: 2023-01-26 오후 4:01:34
 * Author : mss33
 */ 
#define F_CPU 2000000UL

#include <avr/io.h>
#include "util/delay.h"

#define LED_ON PORTJ.OUTSET = PIN0_bm
#define LED_OFF PORTJ.OUTCLR = PIN0_bm

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(500);
		LED_ON;
		_delay_ms(500);
		LED_OFF;
    }
}

