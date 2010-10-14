all: a.hex

a.hex: a.out
	avr-objcopy -O ihex -R .eeprom a.out a.hex

a.out: timer.o blink_timer.o
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000 -DARDUINO timer.o blink_timer.o -o a.out

timer.o: timer.c
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000 -DARDUINO timer.c -c

blink_timer.o: blink_timer.c
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000 -DARDUINO blink_timer.c -c

clean:
	rm -rf *.o *.hex