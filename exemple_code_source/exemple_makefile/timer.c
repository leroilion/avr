#include "timer.h"

void configurationTimer(void )
{
	//Mise de 101 dans CS1x pour diviser la clock par 1024
	TCCR1B |= ( 1 << CS12 );
	TCCR1B &= ~( 1 << CS11 );
	TCCR1B |= ( 1 << CS10 );
	//Mise en mode normal du timer 1
	TCCR1B &= ~( 1 << WGM13 );
	TCCR1B &= ~( 1 << WGM12 );
	TCCR1A &= ~( 1 << WGM11 );
	TCCR1A &= ~( 1 << WGM10 );
	//Activation global des interruptions
	sei();
	//Mise à zéro de la valeur du TIMER1 pour en pas avoir de problème lors de l'activation de celui-ci
	TCNT1H = 0;
	TCNT1L = 0;
	//Activation de l'interruption d'overflow du TIMER1
	TIMSK1 |= ( 1 << TOIE1 );
}

ISR( TIMER1_OVF_vect )
{
	//Lecture de l'état du PORBT5 pour arduino
#ifdef ARDUINO
	if( PINB & ( 1 << PORTB5 ))
		PORTB &= ~( 1 << PORTB5 );
	else
		PORTB |= ( 1 << PORTB5 );
#endif
	//Lecture de l'état du PORBT5 pour arduino mega
#ifdef ARDUINO_MEGA
	if( PINB & ( 1 << PORTB7 ))
		PORTB &= ~( 1 << PORTB7 );
	else
		PORTB |= ( 1 << PORTB7 );
#endif

	//Rechargement du TIMER1
	//Toujours commencer par la valeur Haute 
	TCNT1H = 0xc2;
	TCNT1L = 0xf6;
}