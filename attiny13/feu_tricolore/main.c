#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/**
 * Programme permettant de gérer le feu tricolore.
 * @file main.c
 * @author Jérémy Cheynet
 * @brief Programme permettant de gérer le feu tricolore pour le faire clignoter
 * @version 1.0
 * @date 21/01/2011
 * Nous avons en entrer sur le port B0 (INT0 et pin 5) un signal changeans d'état à chaque fois que la sinusoide de EDF change de polarité
 * En sortie, nous avons sur portB3, portB2 et portB1 qui sont reliés à des triacs commandant les lampes du feu tricolore.
 */

/**
 * Define interne de la taille du ring buffer de la liaison série
 * @fn LAMP_ROUGE
 * @def LAMP_ROUGE
 */
#define LAMP_ROUGE PORTB3

/**
 * Define interne de la taille du ring buffer de la liaison série
 * @fn LAMP_ORANGE
 * @def LAMP_ORANGE
 */
#define LAMP_ORANGE PORTB2

/**
 * Define interne de la taille du ring buffer de la liaison série
 * @fn LAMP_VERT
 * @def LAMP_VERT
 */
#define LAMP_VERT PORTB1

/**
 * Define interne de la taille du ring buffer de la liaison série
 * @fn ENTREE
 * @def ENTREE
 */
#define ENTREE PORTB0

int main( void )
{
	/*
	 * Initialisation du TIMER
	 * diviser la clock par 1024 pour que les 256 points du TIMER correspond à tout la gamme de comptage du timer.
	 * Il y a en tout, 187 points du timer pour correspondre à une periode EDF
	 * F=9600000Hz, divisé par 1024, pour une période de 0.02s
	 */
	TCCR0B |= ( ( 1 << CS02) || ( 1 << CS00 ));
	
	/*
	 * Remise à zéro du timer
	 */
	TCNT0 = 0x00;
	
	/*
	 * Activation des interruptions externes sur changement d'état portB0
	 */
	MCUCR |= ( 1 << ISC00 );
	GIMSK |= ( 1 << INT0 );
	
	/*
	 * Configuration des ports en sortie et initialisation des ports
	 */
	DDRB &= ~( 1 << ENTREE );
	PORTB |= ( 1 << ENTREE );
	DDRB |= ( ( 1 << LAMP_ORANGE ) || ( 1 << LAMP_ROUGE ) || ( 1 << LAMP_VERT ) );
	PORTB &= ~( ( 1 << LAMP_ORANGE ) || ( 1 << LAMP_ROUGE ) || ( 1 << LAMP_VERT ) );
	
	/*
	 * Activation globale des interruptions
	 */
	sei();
	
	while( 42 )
	{
		if( TCNT0 > 93)
		{
			PORTB |= ( 1 << LAMP_ORANGE );
			_delay_us( 50 );
			PORTB &= ~( 1 << LAMP_ORANGE);
		}
		if( TCNT0 > 25)
		{
			PORTB |= ( 1 << LAMP_ROUGE );
			_delay_us( 50 );
			PORTB &= ~( 1 << LAMP_ROUGE);
		}
		if( TCNT0 > 150)
		{
			PORTB |= ( 1 << LAMP_VERT );
			_delay_us( 50 );
			PORTB &= ~( 1 << LAMP_VERT);
		}
	}
	
	return 0;
}

/**
 * @fn ISR( INT0_vect )
 * @brief Gestion de l'interruption du changement d'état de EDF
 * Dans cette section, on remet à zéro le timer
 */
ISR(INT0_vect)
{
	TCNT0 = 0x00;
}