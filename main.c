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
#include <avr/interrupt.h>
#include "pmUART/pmuart.h"

//uint8_t sri_buf[ISR0_REG_NUM];
uint8_t flag=0;

void setPk(uint8_t id, uint8_t val);

int main(void){

	_delay_ms(3000);
	USART_Init( __UBRR);

	sei();
	uart_puts("start\r\n");
	sriRegisterUpdate(setPk);

	while(1){
		sroEvent();
		sriEvent();

		if(flag) sroSend();
		flag=0;
		_delay_ms(500);
	}
}


void setPk(uint8_t id, uint8_t val){
	flag=1;
	uart_puts("detekcja__ ");
	uart_putint(id,10);
	uart_puts(", ");
	uart_putint(val, 2);
	uart_puts("\r\n");

	sroSetBit(id, val);
}
