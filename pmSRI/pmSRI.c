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
