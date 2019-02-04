/*
 * pmSR.h
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#ifndef PMSR_PMSR_H_
#define PMSR_PMSR_H_

#define SR_EN 1		// dostepne sterowanie linia CE rejestru
#define SR_PWR 1	// dostepne sterowanie linia zasilania rejestru
#define SR_LED 1	// dostepna kotrolka pracy rejestru
typedef struct{
	volatile uint8_t *PORTX;
	uint8_t MASK;
}TIO;

typedef struct{
	TIO ser;
	TIO sck;
	TIO rck;
#ifdef SR_EN
	TIO en;
#endif
#ifdef SR_PWR
	TIO pwr;
#endif
#ifdef SR_LED
	TIO led;
#endif
	uint8_t *pin_buf;
	uint8_t num;	// ilosc rejestrow
	uint8_t sr_typ;	// 1=rejestr wyjsciowy 0=rejestr wejsciowy
	uint8_t dir;	// kierunek wsuwania bitow
	uint8_t on_bit;	// bit wlaczany 0 lub 1
	uint8_t enable;	// 0=wylaczony 1= aktywny
}TSR;

#endif /* PMSR_PMSR_H_ */
