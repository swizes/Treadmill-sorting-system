/*
 * ISRPortC.h
 *
 *  Created on: 25.06.2015
 *      Author: tobi
 */

#ifndef ISRPORTC_H_
#define ISRPORTC_H_

#include "HAL.h"

#ifndef ISR_H_
#define ISR_H_

extern int isrId;
extern int isrChannel;
extern int isrConnection;
extern struct sigevent isrEvent;


extern void registerISR_PortC(void);
extern void unregisterISR_PortC(void);


#endif /* ISRPORTC_H_ */
