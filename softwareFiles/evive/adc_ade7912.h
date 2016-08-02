/*
 * evive_oscilloscope.h
 *
 *  Created on: May 26, 2016
 *      Author: dhrups
 *  Screen Implementation for oscilloscope feature is done in
 *  SCREEN_IMPLEMENTATION_H
 */

#ifndef ADC_ADE7912_H_
#define ADC_ADE7912_H_

#include "evive.h"

//void evive_oscilloscope();
void ade791x_init(void);
long ade791x_read_v1(void);
long ade791x_read_vim(void);
long ade791x_read_im(void);

#endif /* ADC_ADE7912_H_ */
