/*
 * srDef.h
 *
 *  Created on: 4 lut 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#ifndef PMSR_SRDEF_H_
#define PMSR_SRDEF_H_

#define SR_EN 1		// dostepne sterowanie linia CE rejestru
#define SR_PWR 1	// dostepne sterowanie linia zasilania rejestru
#define SR_LED 1	// dostepna kotrolka pracy rejestru

#ifdef SR_PWR
#define SR_PWR_ON_BIT	1	// zakomentuj jesli sterwanie pinem zgodny z ustawianiem stanu pinu rejestru
#endif
#ifdef SR_LED
#define SR_LED_ON_BIT	0	// zakomentuj jesli sterwanie pinem zgodny z ustawianiem stanu pinu rejestru
#endif

#endif /* PMSR_SRDEF_H_ */
