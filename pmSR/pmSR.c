/*
 * pmSR.c
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#include <avr/io.h>
#include "../mac.h"

#include "pmSR.h"

uint8_t getIO(TPI *io);

void setIO(TPO *io){ if(io->PORTX) *io->PORTX |= io->MASK; }
void resIO(TPO *io){ if(io->PORTX) *io->PORTX &= ~io->MASK; }

uint8_t getIO(TPI *io){
	if( (*io->PINX & io->MASK) ) return 1; else return 0;
}

#ifdef SR_PWR
uint8_t srSetPwr(TSR *sr){
	if(sr->pwr.PORTX){
		static uint8_t status;
		if(!status) {
			#ifdef SR_PWR_ON_BIT
				if(sr->pwr_on) setIO(&sr->pwr); else resIO(&sr->pwr);
			#else
				setIO(&sr->pwr);
			#endif
			status++;
			return 0;
		}else{
			if(status<5) {
				status++;
				return 0;
			}else{
				return status;
			}
		}
	}else{
		return 1;
	}
}
void srResPwr(TSR *sr){
	if(sr->pwr.PORTX){
		static uint8_t status;
		if(status) {
			#ifdef SR_PWR_ON_BIT
				if(sr->pwr_on) resIO(&sr->pwr); else setIO(&sr->pwr);
			#else
				resIO(&sr->pwr);
			#endif
			#ifdef SR_LED
				#ifdef SR_LED_ON_BIT
					if(sr->led_on) resIO(&sr->led); else setIO(&sr->led);
				#else
					resIO(&sr->led);
				#endif
			#endif
			status=0;
		}
	}
}
#endif

#ifdef SR_LED
void srSetLed(TSR *sr){
	if(sr->led.PORTX){
		#ifdef SR_LED_ON_BIT
			if(sr->led_on) setIO(&sr->led); else resIO(&sr->led);
		#else
			setIO(&sr->led);
		#endif
	}
}
void srResLed(TSR *sr){
	if(sr->led.PORTX){
		#ifdef SR_LED_ON_BIT
			if(sr->led_on) resIO(&sr->led); else setIO(&sr->led);
		#else
			resIO(&sr->led);
		#endif
	}
}
#endif

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
		sr->new_dat=0;
	}
}

void srGet(TSR *sr){
	if(!sr->sr_typ && sr->seri.PINX && sr->sck.PORTX && sr->rck.PORTX){
		uint8_t *reg;
		uint8_t pin;
		int8_t x;
		resIO(&sr->rck);
		setIO(&sr->rck);


		reg=sr->pin_buf;
		for(uint8_t i=0;i<sr->num;i++){
			if(sr->dir) pin=0x80; else pin=0x01;
			while(pin){
				//x=getIO(&sr->seri);
				x=(PINC & (1<<PC3));
				//if(x==-1) return;
				if( sr->on_bit==x ) *reg |= pin; else *reg &= ~pin;
				//*reg &= ~(1<<pin);
				resIO(&sr->sck);
				setIO(&sr->sck);

				if(sr->dir) pin>>=1; else pin<<=1;
			}
			reg++;
		}
		//sr->new_dat=1;
	}
}

