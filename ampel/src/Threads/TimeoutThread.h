/*
 * ESTOPTHREAD.h
 *
 *  Created on: 30.06.2015
 *      Author: abl441
 */

#ifndef TIMEOUTTHREAD_H_
#define TIMEOUTTHREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Dispatcher.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BandController.h"

using namespace thread;

class TimeoutThread: public HAWThread {
public:
	TimeoutThread();
	virtual ~TimeoutThread();
private:
	TimeoutThread(const TimeoutThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	TimeoutThread& operator=(TimeoutThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
};



#endif /* TIMEOUTTHREAD_H_ */
