/*
 * mac.h
 *
 *  Created on: 28 sty 2019
 *      Author: Piotr Michna
 *		e-mail: poczta@piotrmichna.pl
 */

#ifndef MAC_H_
#define MAC_H_

#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

#endif /* MAC_H_ */
