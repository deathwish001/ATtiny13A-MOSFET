/*
MIT License

Copyright (c) 2018 deathwish001

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Atmel ATtiny 13/13A
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+


// CPU main clock frequency, needed for delay library
#define F_CPU 1200000 // 9.6Mhz/8 = 1.2Mhz

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <util/delay.h>

#define mosfet_pin PB4

volatile int wake_count = 0;

ISR(WDT_vect) {
	if (++wake_count >= 2) {
		PORTB |= (1<<mosfet_pin); // set pin on
		_delay_ms(3000);
		
		PORTB &= ~(1<<mosfet_pin); // set pin off
		wake_count = 0;
	}
}

int main(void) {
	power_adc_disable(); // disable the Analog to Digital Converter module
	power_all_disable (); // disable all modules

	// set up PortB pin mode to output
	DDRB = (1<<mosfet_pin);
	
	// slow clock to divide by 8
	clock_prescale_set (clock_div_8);

	// temporarily prescale timer to 8s
	WDTCR |= (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);

	// enable watchdog timer interrupts
	WDTCR |= (1<<WDTIE);

	sei(); // enable global interrupts

	// use the Power Down sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	for (;;) {
		sleep_mode();   // go to sleep and wait for interrupt...
	}
}
