DEVICE=attiny2313

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(DEVICE)

PROGRAMMER=avrdude
BOARD=stk500v2
PORT=/dev/ttyS1

PFLAGS=-p $(DEVICE) -c $(BOARD) -P $(PORT)

rom.hex: simon.out
	$(OBJCOPY) -j .text -O ihex simon.out rom.hex

simon.out: simon.o
	$(CC) $(CFLAGS) -o simon.out -Wl,-Map,simon.map simon.o

simon.o: simon.c
	$(CC) $(CFLAGS) -Os -c simon.c

program:
	$(PROGRAMMER) $(PFLAGS) -U flash:w:rom.hex

clean:
	rm -rf *.o *.out *.map *.hex
