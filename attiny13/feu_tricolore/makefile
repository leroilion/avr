all: a.hex

a.hex: a.out
	avr-objcopy -O ihex -R .eeprom a.out a.hex

a.out: main.c
	avr-gcc -Wall -O2 -mmcu=attiny13 -DF_CPU=9600000 main.c -o a.out

clean:
	rm -rf *.o *.hex

upload:
	sudo avrdude -c usbtiny -p t13 -U flash:w:a.hex

fuse:
	sudo avrdude -c usbtiny -p t13 -U lfuse:w:0x7a:m -U hfuse:w:0xff:m