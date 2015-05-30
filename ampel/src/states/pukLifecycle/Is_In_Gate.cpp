/*
 * Is_In_Gate.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Is_In_Gate::Is_In_Gate(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_FALSE);
}

Is_In_Gate::~Is_In_Gate(){
	printf("~Road_to_Metal()\n");

}

void Is_In_Gate::Puck_in_Gate_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);

	// Move to State Metal_Detected
	new (this) Is_In_Gate(this->con_);
}



