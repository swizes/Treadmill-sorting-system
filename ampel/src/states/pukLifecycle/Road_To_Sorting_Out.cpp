/*
 * Road_to_Sorting_Out.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Road_To_Sorting_Out::Road_To_Sorting_Out(Context* con): State::State(con){

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_TRUE);
	cout << "Road To Sorting Out ----- PuckId: " << this->con_->getPuck()->getId() << endl;
}

Road_To_Sorting_Out::~Road_To_Sorting_Out(){
	printf("~Road to Sorting Out()\n");

}

void Road_To_Sorting_Out::Slide_full_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_TRUE);

	// Move to State Is_In_Slide
	new (this) Is_In_Slide(this->con_);
}



