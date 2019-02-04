/*
 * pmSR.c
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#include <avr/io.h>
#include "mac.h"

#include "pmSR.h"

void setIO(TIO *io){ if(io->PORTX) *io->PORTX |= io->MASK; }
void resIO(TIO *io){ if(io->PORTX) *io->PORTX &= ~io->MASK; }

void srInit(TSR *sr){

}
