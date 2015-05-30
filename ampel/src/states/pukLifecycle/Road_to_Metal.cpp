/*
 * Road_to_Metal.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Road_to_Metal::Road_to_Metal(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, METAL_DETECTION_TRUE);
}

Road_to_Metal::~Road_to_Metal(){
	printf("~Road_to_Metal()\n");

}

void Road_to_Metal::Metal_detection_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, METAL_DETECTION_TRUE);

	// Move to State Metal_Detected
	new (this) Metal_Detected(this->con_);
}



