/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Road_to_Height()\n");
	//Kill TIMER! von Road_to_Height
	//HÖHENMESSUNG
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, HEIGHT_STATUS_OK);
}

Height_Measurement::~Height_Measurement(){
	printf("~Road_to_Height()\n");

}

void Height_Measurement::Height_Status_OK(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, HEIGHT_STATUS_OK);

	// Move to State Search_for_Hole.
	//new (this) Search_for_Hole(this->con_);
}
