/*
 * Road_to_Sorting_Out.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Road_To_Sorting_Out::Road_To_Sorting_Out(Context* con): State::State(con){

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);
	cout << "Road To Sorting Out ----- PuckId: " << this->con_->getPuck()->getId() << endl;
}

Road_To_Sorting_Out::~Road_To_Sorting_Out(){
	printf("~Road to Sorting Out()\n");

}

void Road_To_Sorting_Out::Puck_in_Gate_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);

	// Move to State Road_To_Slide
	new (this) Road_To_Slide(this->con_);
}



