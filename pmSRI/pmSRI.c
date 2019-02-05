/*
 * pmSRI.c
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */
#include <avr/io.h>
#include "../mac.h"
#include "pmSRI.h"

#include "../pmSR/pmSR.h"
#include "../pmUART/pmuart.h"

TSR sri;
uint8_t sri0_pin_buf[ISR0_REG_NUM];

void (*sriNew)(uint8_t id, uint8_t val);

void sriInit(void);


void sriRegisterUpdate(void (*cal)(uint8_t id, uint8_t val)){
	sriNew=cal;
}


void sriInit(void){
	uart_puts("sriInit\r\n");
		sri.sr_typ=0;
		sri.num=ISR0_REG_NUM;
		sri.pin_buf=sri0_pin_buf;
		sri.on_bit = ISR0_ON_BIT_STATE;
		sri.dir=ISR0_DIR_0_7;
		sri.enable=0;

		sri.seri.PINX= &PIN(ISR0_SER_PORT);
		sri.seri.MASK= (1<<ISR0_SER_PIN);

		sri.sck.PORTX= &PORT(ISR0_SCK_PORT);
		sri.sck.MASK= (1<<ISR0_SCK_PIN);

		sri.rck.PORTX= &PORT(ISR0_RCK_PORT);
		sri.rck.MASK= (1<<ISR0_RCK_PIN);

		#ifdef ISR0_EN_PIN
			sri.en.PORTX= &PORT(ISR0_EN_PORT);
			sri.en.MASK= (1<<ISR0_EN_PIN);
			DDR(ISR0_EN_PORT) |= (1<<ISR0_EN_PIN);
			PORT(ISR0_EN_PORT) |= (1<<ISR0_EN_PIN);
		#endif
		#ifdef ISR0_PWR_PIN
			sri.pwr.PORTX= &PORT(ISR0_PWR_PORT);
			sri.pwr.MASK= (1<<ISR0_PWR_PIN);
			DDR(ISR0_PWR_PORT) |= (1<<ISR0_PWR_PIN);

			#ifdef SR_PWR_ON_BIT
				sri.pwr_on=SR_PWR_ON_BIT;
				if(SR_PWR_ON_BIT) PORT(ISR0_PWR_PORT) &= ~(1<<ISR0_PWR_PIN); else PORT(ISR0_PWR_PORT) |= (1<<ISR0_PWR_PIN);
			#endif
		#endif
		#ifdef ISR0_LED_PIN
			sri.led.PORTX= &PORT(ISR0_LED_PORT);
			sri.led.MASK= (1<<ISR0_LED_PIN);
			DDR(ISR0_LED_PORT) |= (1<<ISR0_LED_PIN);
			#ifdef SR_LED_ON_BIT
				sri.led_on=SR_LED_ON_BIT;
				if(SR_PWR_ON_BIT) PORT(ISR0_LED_PORT) &= ~(1<<ISR0_LED_PIN); else PORT(ISR0_LED_PORT) |= (1<<ISR0_LED_PIN);
			#endif
		#endif

		if(sri.sr_typ) DDR(ISR0_SER_PORT) |= (1<<ISR0_SER_PIN); else DDR(ISR0_SER_PORT) &= ~(1<<ISR0_SER_PIN);
		DDR(ISR0_SCK_PORT) |= (1<<ISR0_SCK_PIN);
		DDR(ISR0_RCK_PORT) |= (1<<ISR0_RCK_PIN);

		if(sri.on_bit) PORT(ISR0_SER_PORT) &= ~(1<<ISR0_SER_PIN); else PORT(ISR0_SER_PORT) |= (1<<ISR0_SER_PIN);
		PORT(ISR0_SCK_PORT) &= ~(1<<ISR0_SCK_PIN);
		PORT(ISR0_RCK_PORT) &= ~(1<<ISR0_RCK_PIN);
//		for(uint8_t i=0;i<sri.num;i++){
//			if(ISR0_ON_BIT_STATE)sri.pin_buf[i]=0; else sri.pin_buf[i]=255;
//		}
}
uint8_t sriGetByte(uint8_t id){
	if (id<sri.num){
		return sri.pin_buf[id];
	}else return 0;
}
uint8_t sirGetNum(void){
	return sri.num;
}

void sriEvent(void){

	static uint8_t pin_buf[ISR0_REG_NUM];
	if(!sri.pin_buf){
		sriInit();

		return;
	}
	if(!sri.enable){
		#ifdef ISR0_PWR_PIN
			if(!srSetPwr(&sri)) return;
		#endif
		#ifdef ISR0_EN_PIN
			resIO(&sri.en);
		#endif
//		for(uint8_t i=0;i<sri.num;i++){
//			if(ISR0_ON_BIT_STATE)pin_buf[i]=0; else pin_buf[i]=255;
//		}
		sri.enable=1;
		srSetLed(&sri);
	}

	srGet(&sri);



	uint8_t id=0, pin;
	uint8_t *reg;
	reg=sri.pin_buf;
	for(uint8_t i=0;i<sri.num;i++){
		pin=0x01;
		while(pin){
			if( (*reg & pin) != (pin_buf[i] & pin) ){
				if( (*reg & pin) ) pin_buf[i] |= pin; else  pin_buf[i] &= ~pin;
				// wywolanie zarejstrowanej funkcji zrwacajacej id bitu zmienionego

				if(sriNew) sriNew(id, (*reg & pin) );
				uart_puts("id=");
													uart_putint(i,10);
													uart_puts(", ");
													uart_putint(sri.pin_buf[0], 2);
													uart_puts("\r\n");
			}

			id++;
			pin<<=1;
		}

		reg++;
	}
}
