#include <avr/io.h>
#include <util/delay.h>

#define TRUE 1

int main( void )
{
	DDRB |= ( 1 << PORTB5 );
	while( TRUE )
	{
		PORTB |= ( 1 << PORTB5 );
		_delay_ms( 1000 );
		PORTB &= ~( 1 << PORTB5 );
		_delay_ms( 2000 );
	}
	return 0;
}
