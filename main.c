/*
 * main.c
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */


#include <avr/io.h>
#include <util/delay.h>

#include "pmSRO/pmSRO.h"



int main(void){
	uint8_t cnt=0,n=0;
	_delay_ms(1000);

	while(1){
		sroEvent();
		if(cnt==99){
			sroResBuf();
			sroSetBit(n,1);
			sroSend();
			n++;
			if(n>8) n=0;
			cnt=0;

		}else{
			cnt++;
		}

		_delay_ms(10);
	}
}
