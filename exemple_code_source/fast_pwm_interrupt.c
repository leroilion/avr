#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef ARDUINO
	#define PORT_SORTIE PORTB5
#endif
#ifdef ARDUINO_MEGA
	#define PORT_SORTIE PORTB7
#endif

int main( void )
{
	//Configuration de la pin en sortie
	DDRB |= ( 1 << PORT_SORTIE );
	//Configuration du TIMER0 en mode Fast PWM
	TCCR0A |= ( 1 << WGM00 );
	TCCR0A &= ~( 1 << WGM01 );
	TCCR0B |= ( 1 << WGM02 );
	//Reglage du diviseur de clock
	TCCR0B |= ( 1 << CS00 );
	TCCR0B &= ~( 1 << CS01 );
	TCCR0B |= ( 1 << CS02 );
	//Activation de l'interruption d'overflow du TIMER0
	TIMSK0 |= ( 1 << TOIE0 );
	//Reglage du mode de comparaison
	TCCR0A &= ~( 1 << COM0A1 );
	TCCR0A &= ~( 1 << COM0A0 );
	//Activation de l'interruption de comparaison
	TIMSK0 |= ( 1 << OCIE0A );
	//Activation global des interruptions
	sei();
	//Chargement de la valeur de comparaison dans la conf du timer
	OCR0A = 254;

	//Boucle principale
	while ( 1 )
	{}
}

ISR( TIMER0_OVF_vect )
{
	PORTB &= ~( 1 << PORT_SORTIE );
}

ISR( TIMER0_COMPA_vect )
{
	PORTB |= ( 1 << PORT_SORTIE );
}
