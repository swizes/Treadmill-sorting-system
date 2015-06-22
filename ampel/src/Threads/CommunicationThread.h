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

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECKSUM 10

using namespace thread;

class CommunicationThread: public HAWThread {
public:
	CommunicationThread(void);
	virtual ~CommunicationThread();

private:
	CommunicationThread(const CommunicationThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	CommunicationThread& operator=(CommunicationThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();

	Serial ser;
};

#endif /* COMMUNNICATIONTHREAD_H_ */
