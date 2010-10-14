#ifndef TIMER_H
#define TIMER_H
/**
 * Librairie de gestion des interruptions timers
 */

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Permet de configurer le timer pour qu'il fonctionne selon le mode choisi
 * Mode normal
 */
void configurationTimer( void );

#endif