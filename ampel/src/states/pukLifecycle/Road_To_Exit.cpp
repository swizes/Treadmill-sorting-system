/*
 * Road_To_Exit.cpp
 *
 *  Created on: 30.05.2015
 *      Author: Cumhur
 */
#include "PuckStates.h"

Road_To_Exit::Road_To_Exit(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_OUT_TRUE);
	/*
	TODO: AFTER X SECONDS
	HAL *hal = HAL::getInstance();
	hal->close_gate();
	TODO: TIMEOUT AFTER X SECONDS
	*/
}

Road_To_Exit::~Road_To_Exit(){
	printf("~Road_to_Metal()\n");

}

void Road_To_Exit::Running_out_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_OUT_TRUE);

	// Move to State Band2
	//new (this) Is_Band2_Free?(this->con_);
}

