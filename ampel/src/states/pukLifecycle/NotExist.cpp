/*
 * NotExist.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Cumhur
 */


#include "PuckStates.h"


NotExist::NotExist(Context* con): State::State(con){
	printf("NOTExist()\n");
	// Start listen on Event Transition1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_IN_TRUE);
}

NotExist::~NotExist(){
	printf("~NotExist()\n");
}

void NotExist::Running_In_true(void){
	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_IN_TRUE);

	// Move to State Birth.
	new (this) Birth(this->con_);
}





