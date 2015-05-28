/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){
	printf("Road_to_Height()\n");
	//STARTE TIMER!
	//TimeOut?!
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);
}

Road_to_Height::~Road_to_Height(){
	printf("~Road_to_Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height_Measurement.
	//new (this) Height_Measurement(this->con_);
}
