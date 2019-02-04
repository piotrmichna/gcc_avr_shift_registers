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
#ifdef SR_PWR
#define SR_PWR_ON_BIT	0	// zakomentuj jesli sterwanie pinem zgodny z ustawianiem stanu pinu rejestru
#endif

#define SR_LED 1	// dostepna kotrolka pracy rejestru
#ifdef SR_LED
#define SR_LED_ON_BIT	0	// zakomentuj jesli sterwanie pinem zgodny z ustawianiem stanu pinu rejestru
#endif


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
#ifdef SR_PWR_ON_BIT
	uint8_t pwr_on	:1;	// stan wlaczanie diody led
#endif
#ifdef SR_LED_ON_BIT
	uint8_t led_on	:1;	// stan wlaczania zasilania rejestru
#endif
#ifdef SR_PWR_ON_BIT
	uint8_t 		:0;	// dope³nienie bitow do pelnego bajtu
#else
#ifdef SR_LED_ON_BIT
	uint8_t 		:0;	// dope³nienie bitow do pelnego bajtu
#endif
#endif
	uint8_t *pin_buf;
	uint8_t num		:4;	// ilosc rejestrow
	uint8_t sr_typ	:1;	// 1=rejestr wyjsciowy 0=rejestr wejsciowy
	uint8_t dir		:1;	// kierunek wsuwania bitow
	uint8_t on_bit	:1;	// bit wlaczany 0 lub 1
	uint8_t enable 	:1;	// 0=wylaczony 1= aktywny
}TSR;

void setIO(TIO *io);
void resIO(TIO *io);

void srInit(TSR *sr);
#ifdef SR_PWR
uint8_t srSetPwr(TSR *sr);
#endif

void srSend(TSR *sr);

#endif /* PMSR_PMSR_H_ */
