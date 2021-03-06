/*
 * pmSR.h
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#ifndef PMSR_PMSR_H_
#define PMSR_PMSR_H_

#include "srDef.h"


typedef struct{
	volatile uint8_t *PORTX;
	uint8_t MASK;
}TPO;

typedef struct{
	volatile uint8_t *PINX;
	uint8_t MASK;
}TPI;

typedef struct{
	TPO ser;
	TPI seri;
	TPO sck;
	TPO rck;
#ifdef SR_EN
	TPO en;
#endif
#ifdef SR_PWR
	TPO pwr;
#endif
#ifdef SR_LED
	TPO led;
#endif
#ifdef SR_PWR_ON_BIT
	uint8_t pwr_on	:1;	// stan wlaczanie diody led
#endif
#ifdef SR_LED_ON_BIT
	uint8_t led_on	:1;	// stan wlaczania zasilania rejestru
#endif
#ifdef SR_PWR_ON_BIT
	uint8_t 		:0;	// dopełnienie bitow do pelnego bajtu
#else
#ifdef SR_LED_ON_BIT
	uint8_t 		:0;	// dopełnienie bitow do pelnego bajtu
#endif
#endif
	uint8_t *pin_buf;
	uint8_t num		:3;	// ilosc rejestrow
	uint8_t new_dat	:1;	// nowe dane do wyslania lub nowe dane pobrane
	uint8_t sr_typ	:1;	// 1=rejestr wyjsciowy 0=rejestr wejsciowy
	uint8_t dir		:1;	// kierunek wsuwania bitow
	uint8_t on_bit	:1;	// bit wlaczany 0 lub 1
	uint8_t enable 	:1;	// 0=wylaczony 1= aktywny
}TSR;

void setIO(TPO *io);
void resIO(TPO *io);


#ifdef SR_PWR
uint8_t srSetPwr(TSR *sr);
void srResPwr(TSR *sr);
#endif
#ifdef SR_LED
void srSetLed(TSR *sr);
void srResLed(TSR *sr);
#endif

void srSend(TSR *sr);
void srGet(TSR *sr);


#endif /* PMSR_PMSR_H_ */
