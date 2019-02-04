/*
 * pmSRO.c
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */


#include <avr/io.h>
#include "../mac.h"
#include "pmSRO.h"

#include "../pmSR/pmSR.h"

TSR sro;
uint8_t sro0_pin_buf[OSR0_REG_NUM];

void sroInit(void);

uint8_t sroSetBit(uint8_t bit, uint8_t state){
	uint8_t byte;
	byte=bit/8;
	if(byte>=sro.num || !sro.pin_buf) return 0;

	bit-=(byte*8);
	if (state) sro.pin_buf[byte] |=(1<<bit); else sro.pin_buf[byte] &=~(1<<bit);
	sro.new_dat=1;
	return 1;
}

uint8_t sroSetByte(uint8_t byte, uint8_t val){
	if(byte>=sro.num || !sro.pin_buf) return 0;
	sro.pin_buf[byte]=val;
	sro.new_dat=1;
	return 1;
}

void sroResBuf(void){
	if(sro.pin_buf){
		for (uint8_t i=0;i<sro.num;i++){
			sro.pin_buf[i]=0;
		}
		sro.new_dat=1;
	}
}

void sroSend(void){
	sro.new_dat=1;
}

void sroEvent(void){
	if(!sro.pin_buf){
		sroInit();
		return;
	}
	if(sro.new_dat){
		if(!sro.enable){
			#ifdef SR_PWR
				if( !srSetPwr(&sro) ) return;
			#endif
			#ifdef SR_EN
				resIO(&sro.en);
			#endif
			sro.enable=1;
		}
		srSend(&sro);
	}
}

void sroInit(void){
	sro.sr_typ=1;
	sro.num=OSR0_REG_NUM;
	sro.pin_buf=sro0_pin_buf;
	sro.on_bit = OSR0_ON_BIT_STATE;
	sro.dir=OSR0_DIR_0_7;
	sro.enable=0;

	sro.ser.PORTX= &PORT(OSR0_SER_PORT);
	sro.ser.MASK= (1<<OSR0_SER_PIN);

	sro.sck.PORTX= &PORT(OSR0_SCK_PORT);
	sro.sck.MASK= (1<<OSR0_SCK_PIN);

	sro.rck.PORTX= &PORT(OSR0_RCK_PORT);
	sro.rck.MASK= (1<<OSR0_RCK_PIN);

	#ifdef OSR0_EN_PIN
		sro.en.PORTX= &PORT(OSR0_EN_PORT);
		sro.en.MASK= (1<<OSR0_EN_PIN);
		DDR(OSR0_EN_PORT) |= (1<<OSR0_EN_PIN);
		PORT(OSR0_EN_PORT) |= (1<<OSR0_EN_PIN);
	#endif
	#ifdef OSR0_PWR_PIN
		sro.pwr.PORTX= &PORT(OSR0_PWR_PORT);
		sro.pwr.MASK= (1<<OSR0_PWR_PIN);
		DDR(OSR0_PWR_PORT) |= (1<<OSR0_PWR_PIN);

		#ifdef SR_PWR_ON_BIT
			sro.pwr_on=SR_PWR_ON_BIT;
			if(SR_PWR_ON_BIT) PORT(OSR0_PWR_PORT) &= ~(1<<OSR0_PWR_PIN); else PORT(OSR0_PWR_PORT) |= (1<<OSR0_PWR_PIN);
		#endif
	#endif
	#ifdef OSR0_LED_PIN
		sro.led.PORTX= &PORT(OSR0_LED_PORT);
		sro.led.MASK= (1<<OSR0_LED_PIN);
		DDR(OSR0_LED_PORT) |= (1<<OSR0_LED_PIN);
		#ifdef SR_LED_ON_BIT
			sro.led_on=SR_LED_ON_BIT;
			if(SR_PWR_ON_BIT) PORT(OSR0_LED_PORT) &= ~(1<<OSR0_LED_PIN); else PORT(OSR0_LED_PORT) |= (1<<OSR0_LED_PIN);
		#endif
	#endif

	if(sro.sr_typ) DDR(OSR0_SER_PORT) |= (1<<OSR0_SER_PIN); else DDR(OSR0_SER_PORT) &= ~(1<<OSR0_SER_PIN);
	DDR(OSR0_SCK_PORT) |= (1<<OSR0_SCK_PIN);
	DDR(OSR0_RCK_PORT) |= (1<<OSR0_RCK_PIN);

	if(sro.on_bit) PORT(OSR0_SER_PORT) &= ~(1<<OSR0_SER_PIN); else PORT(OSR0_SER_PORT) |= (1<<OSR0_SER_PIN);
	PORT(OSR0_SCK_PORT) &= ~(1<<OSR0_SCK_PIN);
	PORT(OSR0_RCK_PORT) &= ~(1<<OSR0_RCK_PIN);
	sroResBuf();
}
