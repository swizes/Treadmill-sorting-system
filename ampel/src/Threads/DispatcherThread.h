/*
 * CommunnicationThread.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */


#ifndef DISPATCHERTHREAD_H_
#define DISPATCHERTHREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Dispatcher.h"


#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace thread;

class DispatcherThread: public HAWThread {
public:
	DispatcherThread(void);
	virtual ~DispatcherThread();

private:
	DispatcherThread(const DispatcherThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	DispatcherThread& operator=(DispatcherThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();


};

#endif /* DISPATCHERTHREAD_H_ */
