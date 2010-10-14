#include <avr/io.h>

#ifdef ARDUINO
	#define PORT_SORTIE PORTB5
#endif
#ifdef ARDUINO_MEGA
	#define PORT_SORTIE PORTB7
#endif

int main( void )
{
	DDRB |= ( 1 << PORT_SORTIE );			//Configuration de la PIN 5 du PORT B en sortie
	DDRB &= ~( 1 << PORTB0 );			//Configuration du port B 0 en entrée
	PORTB |= ( 1 << PORTB0 );			//Mise en route du pull-up
	while(42)					//Boucle infinie
	{
		if( (PINB & ( 1 << PORTB0 )) )		//Si le portb0 est à l'état haut
		{
			PORTB |= ( 1 << PORT_SORTIE );	//Mise à 1 du portb5
		}
		else					//Si le portb0 est à l'état bas
		{
			PORTB &= ~( 1 << PORT_SORTIE );	//Mise à 0 du portb5
		}
	}
	return 0;
}
