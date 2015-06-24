/*
 * Road_to_Metal.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
//TODO: Class name should be changed to Metal Detection
Road_to_Metal::Road_to_Metal(Context* con): State::State(con){
	Dispatcher* dsp = Dispatcher::getInstance();

	dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);

	cout << "Road To Metal ----- PuckId: " << this->con_->getPuck()->getId() << endl;

}

Road_to_Metal::~Road_to_Metal(){
	printf("~Road_to_Metal()\n");

}

void Road_to_Metal::Puck_in_Gate_true(void){


	// Stop listen to Event Transmission2
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);

	// Move to State Is In Gate
	new (this) Is_In_Gate(this->con_);
}



