/*
simon.c
let's make a memory game!
*/


#include <avr/io.h>
#include <stdlib.h>

#define QUICK 60
#define MED 330
#define SLOW 400

void delay_ms(uint16_t ms) {
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
		delay_ms(QUICK);
	}
	for (i=8; i>0; i--){
		PORTB = ~(1<<(i-1));
		delay_ms(QUICK);
	}
}

void blink(void) {
	PORTB = 0;
	delay_ms(QUICK);
	PORTB = 0xFF;
	delay_ms(QUICK);
}

void intro(void) {
	PORTB = 0xFF; // begin off
	dance();
	blink();
	blink();
	PORTB = 0xFF; //end off
}



int stage(int level) {
	uint8_t i;
	uint8_t field[level];

	for (i = 0; i<level; i++) {
		field[i] = rand() % 7;
		PORTB = ~(1<<field[i]);
		delay_ms(MED);
		PORTB = 0xFF;
		delay_ms(QUICK);
	}
	i=0;
	while (i<level){
		if (bit_is_clear(PIND,field[i])) {
			PORTB = ~(1<<field[i]);
			delay_ms(SLOW);
			i++;
			PORTB = 0xFF;
			delay_ms(QUICK);
		}
	}
	return 1;
}

int main(void) {
	uint8_t lvl;
	lvl = 1;

	DDRB = 0xFF; // ALL the outputs
	PORTB = 0xFF; //start off

	DDRD = 0; //all the.. inputs!
	PORTD = 0xFF; //pull ups everywhere. DYEL?
	srand(5);

	intro();
	delay_ms(SLOW);
	while (stage(lvl)){
		lvl++;
		blink();
		blink();
		delay_ms(SLOW);
	}
}