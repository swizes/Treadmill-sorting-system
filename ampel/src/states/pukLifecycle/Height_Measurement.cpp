/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Road_to_Height()\n");
	//TODO: Kill TIMER! von Road_to_Height
	//TODO: HÖHENMESSUNG + SAVE DATA
	HAL *hal = HAL::getInstance();
	hal->band_right_slowly();
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, GATE_OPEN_TRUE);
}

Height_Measurement::~Height_Measurement(){
	printf("~Road_to_Height()\n");

}

void Height_Measurement::Gate_open_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, GATE_OPEN_TRUE);

	// Move to State Search_for_Hole.
	new (this) Search_for_Hole(this->con_);
}
