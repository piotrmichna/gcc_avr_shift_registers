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

TSR sri;
uint8_t sri0_pin_buf[ISR0_REG_NUM];

void sriInit(void);

void sriInit(void){
		sri.sr_typ=0;
		sri.num=ISR0_REG_NUM;
		sri.pin_buf=sri0_pin_buf;
		sri.on_bit = ISR0_ON_BIT_STATE;
		sri.dir=ISR0_DIR_0_7;
		sri.enable=0;

		sri.seri.PINX= &PIN(ISR0_SER_PORT);
		sri.ser.MASK= (1<<ISR0_SER_PIN);

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
}
uint8_t sriGetByte(uint8_t id){
	if (id<sri.num){
		return sri.pin_buf[id];
	}else return 0;

}
