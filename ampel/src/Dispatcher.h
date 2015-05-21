/*
 * Dispatcher.h
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Transition.h"
#include <cstdio>
#include <cmath>
#include <stdint.h>
#include "ISR.h"


#define MAXLISTENERS 5

// Events in the System. Each EVENT needs a corresponding Method in class Transactions
enum EVENTS{RUNNING_IN, IN_HEIGHT, HEIGHT_STATUS, PUCK_IN_GATE, METAL_DETECTION, GATE_OPEN, SLIDE_FULL, RUNNING_OUT, NEVENTS};


// typedef: Method from Class "Transactions"
typedef void (Transitions::*method_t)(void);

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	virtual void addListeners(Transitions* listener, EVENTS event);
	virtual void remListeners(Transitions* listener, EVENTS event);
	virtual void callListeners(EVENTS event);
	virtual void listenForEvents();

private:
	method_t methods[NEVENTS];
	Transitions* listeners_[NEVENTS][MAXLISTENERS];

	Dispatcher(const Dispatcher& other);
	Dispatcher& operator=(const Dispatcher& other);
};

#endif /* DISPATCHER_H_ */
