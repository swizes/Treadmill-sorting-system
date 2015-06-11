/*
 * Is_In_Gate.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Is_In_Gate::Is_In_Gate(Context* con): State::State(con){
	printf("Is in Gate()\n");
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_FALSE);
	//Check PuckHightIsOk ? open_gate : close_gate
	HAL* hal= HAL::getInstance();
	if(con_->getPuck()->getSizeTyp() == OK){
		hal->open_gate();
	}
}

Is_In_Gate::~Is_In_Gate(){
	printf("~Is in Gate()\n");

}

void Is_In_Gate::Puck_in_Gate_false(void){

	HAL* hal= HAL::getInstance();
	hal->close_gate();


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);

	// Move to State Road to Exit
	new (this) Road_To_Exit(this->con_);
}



