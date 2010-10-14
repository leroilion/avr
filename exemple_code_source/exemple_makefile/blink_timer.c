#include "timer.h"
#include <avr/io.h>

int main( void )
{
	//Configuration en sortie du port B 5 pour un arduino, et 
#ifdef ARDUINO
	DDRB |= ( 1 << PORTB5 );
#endif
#ifdef ARDUINO_MEGA
	DDRB |= ( 1 << PORTB7 );
#endif
	
	configurationTimer();
	//Boucle principale
	while( 1 )
	{}

	return 0;
}