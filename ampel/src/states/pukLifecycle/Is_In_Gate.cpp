/*
 * Is_In_Gate.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Is_in_Gate::Is_in_Gate(Context* con): State::State(con){
	printf("Is in Gate()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_FALSE);
}

Is_in_Gate::~Is_in_Gate(){
	printf("~Is in Gate()\n");

}

void Is_in_Gate::Puck_in_Gate_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);

	// Move to State Road to Exit
	new (this) Road_to_Exit(this->con_);
}



