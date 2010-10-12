#include <avr/io.h>

int main( void )
{
	DDRB |= ( 1 << PORTB5 );			//Configuration de la PIN 5 du PORT B en sortie
	DDRB &= ~( 1 << PORTB0 );			//Configuration du port B 0 en entrée
	PORTB |= ( 1 << PORTB0 );			//Mise en route du pull-up
	while(42)					//Boucle infinie
	{
		if( (PINB & ( 1 << PORTB0 )) )		//Si le portb0 est à l'état haut
		{
			PORTB |= ( 1 << PORTB5 );	//Mise à 1 du portb5
		}
		else					//Si le portb0 est à l'état bas
		{
			PORTB &= ~( 1 << PORTB5 );	//Mise à 0 du portb5
		}
	}
	return 0;
}
