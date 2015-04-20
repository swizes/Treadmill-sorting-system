/*
 * CommunnicationThread.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Serial.h"

#ifndef COMMUNNICATIONTHREAD_H_
#define COMMUNNICATIONTHREAD_H_

class Communnication_Thread: public HAWThread {
public:
	Communnication_Thread(Serial& ser);
	virtual ~Communnication_Thread();

private:
	Communnication_Thread(const Communnication_Thread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	Communnication_Thread& operator=(Communnication_Thread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();

	Serial& ser;

};

#endif /* COMMUNNICATIONTHREAD_H_ */
