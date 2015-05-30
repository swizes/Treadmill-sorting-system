/*
 * Is_In_Slide.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"

Is_In_Slide::Is_In_Slide(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_FALSE);
}

Is_In_Slide::~Is_In_Slide(){
	printf("~Road_to_Metal()\n");

}

void Is_In_Slide::Slide_full_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_FALSE);

	// Move to State Aussortiert
	//new (this) Is_In_Slide(this->con_);
}

