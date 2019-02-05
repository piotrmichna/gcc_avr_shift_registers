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
#include "pmSRI/pmSRI.h"

//uint8_t sri_buf[ISR0_REG_NUM];
uint8_t flag=0;

void setPk(uint8_t id, uint8_t val);

int main(void){

	_delay_ms(3000);
	sriRegisterUpdate(setPk);

	while(1){
		sroEvent();
		sriEvent();

		if(flag) sroSend();
		flag=0;
		_delay_ms(10);
	}
}


void setPk(uint8_t id, uint8_t val){
	flag=1;
	sroSetBit(id, val);
}
