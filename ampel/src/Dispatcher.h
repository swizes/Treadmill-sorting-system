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
enum EVENTS{
	RUNNING_IN_TRUE,	//0
	IN_HEIGHT_TRUE,		//1
	HEIGHT_STATUS_OK, 	//2
	PUCK_IN_GATE_TRUE, 	//3
	METAL_DETECTION_TRUE, //4
	GATE_OPEN_TRUE, 	//5
	SLIDE_FULL_TRUE, 	//6
	RUNNING_OUT_TRUE, 	//7
	RUNNING_IN_FALSE, 	//8
	IN_HEIGHT_FALSE, 	//9
	HEIGHT_STATUS_NOTOK,//10
	PUCK_IN_GATE_FALSE, //11
	METAL_DETECTION_FALSE,//12
	GATE_OPEN_FALSE, 	//13
	SLIDE_FULL_FALSE, 	//14
	RUNNING_OUT_FALSE,  //15
	NEVENTS			    //16
};


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
