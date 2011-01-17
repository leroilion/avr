#include "millis.h"

uint32_t temps = 0;

void millis_init(void )
{
  TCCR0A &= ~( 1 << COM0A1);
  TCCR0A &= ~( 1 << COM0A0);
  TCCR0A &= ~( 1 << COM0B1);
  TCCR0A &= ~( 1 << COM0B0);
  TCCR0A &= ~( 1 << WGM00 );
  TCCR0A &= ~( 1 << WGM01 );
  TCCR0B &= ~( 1 << WGM02 );
}

uint32_t millis( void )
{
  return temps;
}