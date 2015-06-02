/*
 * Is_in_Slide.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"

Is_in_Slide::Is_in_Slide(Context* con): State::State(con){
	printf("Is in Slide()\n");

	//TODO: Timeout
	/*After x Secs
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_TRUE);
	*/
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_FALSE);
}

Is_in_Slide::~Is_in_Slide(){
	printf("~Is in Slide()\n");

}

void Is_in_Slide::Slide_full_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_FALSE);

	//TODO: Move to State Sorted Out
	//new (this) Sorted Out(this->con_);
}

//TODO: void Is_in_Slide::Error_Handling(void)
