/*
 * PuckLifcycleFSM.h
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "states/PuckStates.h"

#ifndef ERRORRECEIVE_H_
#define ERRORRECEIVE_H_

using namespace thread;

class ErrorReceive: public HAWThread{
public:
	ErrorReceive();
	virtual ~ErrorReceive();



private:
	ErrorReceive(const ErrorReceive& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	ErrorReceive& operator=(ErrorReceive& b);
	virtual void execute(void* con); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
};

#endif /* PUCKLIFCYCLEFSM_H_ */
