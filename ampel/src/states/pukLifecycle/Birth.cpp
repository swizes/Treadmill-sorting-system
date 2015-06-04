/*
 * Birth.cpp
 *
 *  Created on: 28.05.2015
 *      Author: abl425
 */
#include "PuckStates.h"


Birth::Birth(Context* con): State::State(con){
	printf("Birth()\n");
	HAL *hal = HAL::getInstance();
	hal->band_right_normal();
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_IN_FALSE);

}

Birth::~Birth(){
	printf("~Birth()\n");

}

void Birth::Running_In_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_IN_FALSE);

	// Move to State Road_to_Height.
	new (this) Road_to_Height(this->con_);
}



