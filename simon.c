/*
simon.c
test program for attiny2313a on stk500v2 dev board
let's make the lights dance
*/


#include <avr/io.h>

#define wait 60

void delay_ms(uint8_t ms) {
	uint16_t delay_count = 1000000 / 17500;
	volatile uint16_t i;

	while (ms != 0) {
		for (i=0; i != delay_count; i++);
			ms--;
	}
}

void dance(void){
	volatile uint8_t i;

	for (i=0; i<8; i++){
		PORTB = ~(1<<i);
		delay_ms(wait);
	}
	for (i=8; i>0; i--){
		PORTB = ~(1<<(i-1));
		delay_ms(wait);
	}
}

void blink(void) {
	PORTB = 0;
	delay_ms(wait);
	PORTB = 0xFF;
	delay_ms(wait);
}

int main(void) {
	DDRB = 0xFF; // ALL the outputs
	PORTB = 0xFF; //start off

	dance();
	blink();
	blink();
	PORTB = 0xFF; //end off
	while (1){
	}
}