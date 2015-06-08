/*
 * Metal_Detected.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"

Metal_Detected::Metal_Detected(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);
}

Metal_Detected::~Metal_Detected(){
	printf("~Road_to_Metal()\n");

}

void Metal_Detected::Puck_in_Gate_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);

	// Move to State Metal_Detected
	new (this) Is_In_Gate(this->con_);
}


