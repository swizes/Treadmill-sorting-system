/*
 * ISR.h
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */

#include <iostream>
#include <cstdlib>
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include "lib/HWaccess.h"

#include "Dispatcher.h"
#include "HAL.h"

#ifndef ISR_H_
#define ISR_H_

extern int isrId;
extern int isrChannel;
extern int isrConnection;
extern struct sigevent isrEvent;


extern void registerISR(void);
extern void unregisterISR(void);


#endif /* ISR_H_ */
