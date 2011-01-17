#include <avr/io.h>
#include <util/delay.h>

#define PORT_SORTIE PORTB3

#define TRUE 1

int main( void )
{

	DDRB |= ( 1 << PORT_SORTIE );
	while( TRUE )
	{
		PORTB |= ( 1 << PORT_SORTIE );
		_delay_ms( 5 );
		PORTB &= ~( 1 << PORT_SORTIE );
		_delay_ms( 5 );
	}
	return 0;
}
