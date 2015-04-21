/*
 * CommunnicationThread.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */


#ifndef COMMUNNICATIONTHREAD_H_
#define COMMUNNICATIONTHREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Serial.h"

#define CHECKSUM 10

using namespace thread;

class Communnication_Thread: public HAWThread {
public:
	Communnication_Thread(void);
	virtual ~Communnication_Thread();

private:
	Communnication_Thread(const Communnication_Thread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	Communnication_Thread& operator=(Communnication_Thread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();

	Serial ser;
};

#endif /* COMMUNNICATIONTHREAD_H_ */
