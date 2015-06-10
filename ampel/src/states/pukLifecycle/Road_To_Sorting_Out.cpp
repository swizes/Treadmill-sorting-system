/*
 * Road_To_Sorting_Out.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Road_To_Sorting_Out::Road_To_Sorting_Out(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);
}

Road_To_Sorting_Out::~Road_To_Sorting_Out(){
	printf("~Road_to_Metal()\n");

}

void Road_To_Sorting_Out::Puck_in_Gate_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);

	// Move to State Metal_Detected
	new (this) Flipping_Puck(this->con_);
}



