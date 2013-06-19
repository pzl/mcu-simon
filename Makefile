DEVICE=attiny2313

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(DEVICE)

PROGRAMMER=avrdude
BOARD=stk500v2
PORT=/dev/ttyS1

PFLAGS=-p $(DEVICE) -c $(BOARD) -P $(PORT)

rom.hex: demo.out
	$(OBJCOPY) -j .text -O ihex demo.out rom.hex

demo.out: demo.o
	$(CC) $(CFLAGS) -o demo.out -Wl,-Map,demo.map demo.o

demo.o: demo.c
	$(CC) $(CFLAGS) -Os -c demo.c

program:
	$(PROGRAMMER) $(PFLAGS) -U flash:w:rom.hex

clean:
	rm -rf *.o *.out *.map *.hex
