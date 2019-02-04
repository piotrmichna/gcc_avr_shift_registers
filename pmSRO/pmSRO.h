/*
 * pmSRO.h
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#ifndef PMSRO_PMSRO_H_
#define PMSRO_PMSRO_H_

#include "../pmSR/srDef.h"

#define OSR0_REG_NUM 1		// 1...7 ilosc obslugiwanych rejestrow przesownych
#define OSR0_ON_BIT_STATE 1
#define OSR0_DIR_0_7 0		// kierunek wsuwania bitow


// definicja pinow sterujacych rejestrem przesownym
#define OSR0_SER_PIN PB1
#define OSR0_SCK_PIN PD6
#define OSR0_RCK_PIN PD7

// definicje portow
#define OSR0_SER_PORT B
#define OSR0_SCK_PORT D
#define OSR0_RCK_PORT D

#ifdef SR_PWR
	// definicje pin steruj¹cym zasilaniem modu³u
	#define OSR0_PWR_PIN PD5 	// zakomentuj jesli niedostepne
	#define OSR0_PWR_PORT D

#endif
#ifdef SR_LED
	// definicja pinu kontrolki led dla modu³u
	#define OSR0_LED_PIN PB2	// zakomentuj jesli niedostepne
	#define OSR0_LED_PORT B
#endif
#ifdef SR_EN
	#define OSR0_EN_PIN PB0			// zakomentuj jesli pin EN na sta³e podciagniety do GND
	#define OSR0_EN_PORT B
#endif



uint8_t sroSetBit(uint8_t bit, uint8_t state);
uint8_t sroSetByte(uint8_t byte, uint8_t val);
void sroResBuf(void);
void sroEvent(void);

#endif /* PMSRO_PMSRO_H_ */
