/*
 * pmSRI.h
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#ifndef PMSRI_PMSRI_H_
#define PMSRI_PMSRI_H_

#include "../pmSR/srDef.h"

#define ISR0_REG_NUM 1		// 1...7 ilosc obslugiwanych rejestrow przesownych
#define ISR0_ON_BIT_STATE 1
#define ISR0_DIR_0_7 0		// kierunek wsuwania bitow


// definicja pinow sterujacych rejestrem przesownym
#define ISR0_SER_PIN PC3
#define ISR0_SCK_PIN PC2
#define ISR0_RCK_PIN PC1

// definicje portow
#define ISR0_SER_PORT C
#define ISR0_SCK_PORT C
#define ISR0_RCK_PORT C

#ifdef SR_PWR
	// definicje pin steruj¹cym zasilaniem modu³u
	//#define ISR0_PWR_PIN PD5 	// zakomentuj jesli niedostepne
	#define ISR0_PWR_PORT D

#endif
#ifdef SR_LED
	// definicja pinu kontrolki led dla modu³u
	#define ISR0_LED_PIN PC0	// zakomentuj jesli niedostepne
	#define ISR0_LED_PORT C
#endif
#ifdef SR_EN
	#define ISR0_EN_PIN PC4			// zakomentuj jesli pin EN na sta³e podciagniety do GND
	#define ISR0_EN_PORT C
#endif

uint8_t sriGetByte(uint8_t id);
uint8_t sirGetNum(void);
void sriEvent(void);

#endif /* PMSRI_PMSRI_H_ */
