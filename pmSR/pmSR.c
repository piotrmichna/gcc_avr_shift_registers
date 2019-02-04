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

void srSend(TSR *sr){
	if(sr->sr_typ && sr->ser.PORTX && sr->sck.PORTX && sr->rck.PORTX){
		uint8_t *reg;
		uint8_t pin;

		reg=sr->pin_buf;
		reg+=sr->num-1;
		for(uint8_t i=0;i<sr->num;i++){
			if(sr->dir) pin=0x80; else pin=0x01;
			while(pin){
				if( (*reg & pin) ){
					if(sr->on_bit) setIO(&sr->ser); else resIO(&sr->ser);
				}else{
					if(sr->on_bit) resIO(&sr->ser); else setIO(&sr->ser);
				}
				setIO(&sr->sck);
				resIO(&sr->sck);
				if(sr->dir) pin>>=1; else pin<<=1;
			}
			reg--;
		}
		setIO(&sr->rck);
		resIO(&sr->rck);
	}
}
