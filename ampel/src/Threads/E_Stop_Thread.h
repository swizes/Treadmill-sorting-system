/*
 * ESTOPTHREAD.h
 *
 *  Created on: 30.06.2015
 *      Author: abl441
 */

#ifndef ESTOPTHREAD_H_
#define ESTOPTHREAD_H_

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

class E_Stop_Thread: public HAWThread {
public:
	E_Stop_Thread();
	virtual ~E_Stop_Thread();
private:
	E_Stop_Thread(const E_Stop_Thread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	E_Stop_Thread& operator=(E_Stop_Thread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
};



#endif /* ESTOPTHREAD_H_ */
