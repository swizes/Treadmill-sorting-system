/*
 * SerialReceiveThread.h
 *
 *  Created on: 30.06.2015
 *      Author: abl441
 */

#ifndef SERIALRECEIVETHREAD_H_
#define SERIALRECEIVETHREAD_H_

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

class SerialReceiveThread: public HAWThread {
public:
	SerialReceiveThread();
	virtual ~SerialReceiveThread();

	int recvPacket(puckStruct* puck);
private:
	SerialReceiveThread(const SerialReceiveThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	SerialReceiveThread& operator=(SerialReceiveThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
};



#endif /* SERIALRECEIVETHREAD_H_ */
