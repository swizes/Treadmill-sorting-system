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
#define EVENT_OFFSET 8

// Events in the System. Each EVENT needs a corresponding Method in class Transactions
enum EVENTS{RUNNING_IN_TRUE, IN_HEIGHT_TRUE, HEIGHT_STATUS_OK, PUCK_IN_GATE_TRUE, METAL_DETECTION_TRUE, GATE_OPEN_TRUE, SLIDE_FULL_TRUE, RUNNING_OUT_TRUE, RUNNING_IN_FALSE, IN_HEIGHT_FALSE, HEIGHT_STATUS_NOTOK, PUCK_IN_GATE_FALSE, METAL_DETECTION_FALSE, GATE_OPEN_FALSE, SLIDE_FULL_FALSE, RUNNING_OUT_FALSE, NEVENTS};


// typedef: Method from Class "Transactions"
typedef void (Transitions::*method_t)(void);

class Dispatcher {
public:
	virtual ~Dispatcher();
	virtual void addListeners(Transitions* listener, EVENTS event);
	virtual void remListeners(Transitions* listener, EVENTS event);
	virtual void callListeners(EVENTS event);
	virtual void listenForEvents();
	static Dispatcher* getInstance(void);
	void printListeners();

private:
	Dispatcher();
	method_t methods[NEVENTS];
	Transitions* listeners_[NEVENTS][MAXLISTENERS];

	Dispatcher(const Dispatcher& other);
	Dispatcher& operator=(const Dispatcher& other);
};

#endif /* DISPATCHER_H_ */
