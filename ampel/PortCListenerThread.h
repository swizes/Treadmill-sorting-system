/*
 * PortCListenerThread.h
 *
 *  Created on: 25.06.2015
 *      Author: tobi
 */

#ifndef PORTCLISTENERTHREAD_H_
#define PORTCLISTENERTHREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "ISRPortC.h"
#include "HAL.h"


using namespace thread;

class PortC_ListenerThread: public HAWThread {
public:
	PortC_ListenerThread(void);
	virtual ~PortC_ListenerThread();

private:
	PortC_ListenerThread(const PortC_ListenerThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	PortC_ListenerThread& operator=(PortC_ListenerThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();

};

#endif /* PORTCLISTENERTHREAD_H_ */
