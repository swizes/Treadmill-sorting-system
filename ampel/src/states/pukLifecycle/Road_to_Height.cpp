/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){
	printf("Road_to_Height()\n");
	//TODO:STARTE TIMER!
	//TODO: TimeOut?!
	Dispatcher* dsp = Dispatcher::getInstance();
	//TODO: oder 	dsp->addListeners( this->con_, HEIGHT_STATUS_OK);
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);
}

Road_to_Height::~Road_to_Height(){
	printf("~Road_to_Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	//TODO: oder 	dsp->remListeners( this->con_, HEIGHT_STATUS_OK);
	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height_Measurement.
	new (this) Height_Measurement(this->con_);
}
