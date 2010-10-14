/***	Petit programme pour faire un gradateur pwm sur une led pour la 
** faire joliment clignoter en utilisant le timer2.
**	Author::  Guillaume DEMAISON (mailto:guillaume.demaison@minet.net)
**	Copyright:: Copyright (c) 2010 INTech - TechTheFruit
**	License::   GPL
***/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

//valeur de controle pour savoir si, pour le gradateur, 
//on veut augmenter ou diminuer l'intensité lumineuse.
uint8_t cont=0;
//on peut certainement n'utiliser qu'un seul bit, mais
//on ne manque pas franchement d'espace mémoire avec
//ce programme donc bon...

int main() {
	//mode pwm partagé
	TCCR2A &= ~(1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
	TCCR2A &= ~(1<<COM2B0);
	TCCR2A &= ~(1<<COM2B1);
	TCCR2A &= ~(1<<WGM21);
	TCCR2A &= ~(1<<WGM20);
	TCCR2B &= ~(1<<WGM22);
	//diviseur d'horloge
	TCCR2B |= (1<<CS22);
	TCCR2B &= ~(1<<CS21);
	TCCR2B |= (1<<CS20);
	//interruptions sur overflow et sur comparaisonA
	TIMSK2 |= (1<<OCIE2A);
	TIMSK2 |= (1<<TOIE0);

	//activation des interruptions
	sei();

	//patte de sortie de la led
	DDRB |= (1<<PORTB5);

	//valeur de bascule du pwm (sur un total du 255 car Timer2=8bits)
	OCR2A = 127;

	//la boucle du programme
	while(42){
		//on augmente l'intensité lumineuse
		if (cont == 0) {
			if (OCR2A<255) {
				OCR2A++;
			}
			else {
				cont=1;//on arrive en haut
			}
		}
		//on diminue l'intensité lumineuse
		else {
			if (OCR2A>0) {
				OCR2A--;
			}
			else {
				cont=0;//on arrive en bas
			}
		}
		//pour qu'on puisse voir ce gradateur : 
		_delay_ms(1);
	}
}

//sur overflow, on eteint la led : 
ISR (TIMER2_OVF_vect) {
	PORTB &= ~(1<<PORTB5);

}

//sur comparaison valide, on allume la led
ISR (TIMER2_COMPA_vect) {
	PORTB |= (1<<PORTB5);
}

