/*
 * GATECONTROLLERTHREAD.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */


#ifndef GATECONTROLLERTHREAD_H_
#define GATECONTROLLERTHREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Serial.h"
#include "Hal.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Timer/Timer.h"



using namespace thread;

class GateControllerThread: public HAWThread {
public:

	virtual ~GateControllerThread();
	static 	GateControllerThread* getInstance();
	void setTimer(void);

private:
	volatile bool run = 0;
	volatile bool wait = 0;
	Timer *timer;
	static GateControllerThread*  instance_;
	GateControllerThread(void);
	GateControllerThread(const GateControllerThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	GateControllerThread& operator=(GateControllerThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();

	Serial ser;
};

#endif /* GATECONTROLLERTHREAD_H_ */
