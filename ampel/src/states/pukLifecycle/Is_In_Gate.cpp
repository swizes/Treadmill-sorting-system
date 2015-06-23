/*
 * Is_In_Gate.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "../../HAL.h"

Is_In_Gate::Is_In_Gate(Context* con): State::State(con){
	printf("Is in Gate PuckId. %d\n",  this->con_->getPuck()->getId());
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_FALSE);
	dsp->addListeners( this->con_, METAL_DETECTION_TRUE);
	HAL *hal= HAL::getInstance();
	hal->open_gate();

	if(this->con_->getPuck()->getSizeTyp() == OK){
			printf("Puck OK PuckId:%d\n",this->con_->getPuck()->getId());
		}

}

Is_In_Gate::~Is_In_Gate(){
	printf("~Is in Gate()\n");

}

void Is_In_Gate::Puck_in_Gate_false(void){




	con_->getPuck()->setMetal(false);

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);
	dsp->remListeners( this->con_, METAL_DETECTION_TRUE);

	// Move to State Road to Exit
	new (this) Road_To_Exit(this->con_);
}

void Is_In_Gate::Metal_detection_true(void){



	con_->getPuck()->setMetal(true);

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);
	dsp->remListeners( this->con_, METAL_DETECTION_TRUE);

	// Move to State Road to Exit
	new (this) Road_To_Exit(this->con_);
}



