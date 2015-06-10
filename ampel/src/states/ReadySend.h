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

#ifndef READYSEND_H_
#define READYSEND_H_

using namespace thread;

class ReadySend: public HAWThread{
public:
	ReadySend();
	virtual ~ReadySend();

	bool isBusy() const {
		return busy;
	}

	void setBusy(bool busy = 1) {
		this->busy = busy;
	}

private:
	ReadySend(const ReadySend& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	ReadySend& operator=(ReadySend& b);
	virtual void execute(void* con); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
	bool busy = 1;
};

#endif /* PUCKLIFCYCLEFSM_H_ */
