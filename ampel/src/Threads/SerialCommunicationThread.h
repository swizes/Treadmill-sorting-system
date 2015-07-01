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

#ifndef SERIALCOMMUNICATIONTHREAD_H_
#define SERIALCOMMUNICATIONTHREAD_H_

using namespace thread;

class SerialCommunicationThread: public HAWThread{
public:
	void receivePuck(puckStruct *puck);
	void sendPuck(puckStruct *puck);
	void copyPuck(puckStruct *puck);
	void sendError();
	void busy();
	void rdy();
	void waitForPuck();
	static SerialCommunicationThread* getInstance();
	virtual ~SerialCommunicationThread();
	int getType() const {
		return type;
	}

	void setType(int type) {
		this->type = type;
	}

private:
	SerialCommunicationThread();
	SerialCommunicationThread(const SerialCommunicationThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	SerialCommunicationThread& operator=(SerialCommunicationThread& b);
	virtual void execute(void* con); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
	int type;
	puckStruct ps;
	bool received = 0;
	static pthread_mutex_t mtx_; ///< Synchronisationsmutex.
	static SerialCommunicationThread* instance_;
	pthread_mutex_t mutexSend;
	pthread_cond_t condSend;
	pthread_mutex_t mutexRec;
	pthread_cond_t condRec;
};

#endif /* SERIALCOMMUNICATIONTHREAD_H_ */
