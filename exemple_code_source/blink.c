#include <avr/io.h>
#include <util/delay.h>

#define TRUE 1

#ifdef ARDUINO
	#define PORT_SORTIE PORTB5
#endif
#ifdef ARDUINO_MEGA
	#define PORT_SORTIE PORTB7
#endif

int main( void )
{

	DDRB |= ( 1 << PORT_SORTIE );
	while( TRUE )
	{
		PORTB |= ( 1 << PORT_SORTIE );
		_delay_ms( 1000 );
		PORTB &= ~( 1 << PORT_SORTIE );
		_delay_ms( 2000 );
	}
	return 0;
}
