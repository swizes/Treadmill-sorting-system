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
	BandController* bc = BandController::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_FALSE);
	//Check PuckHightIsOk ? open_gate : close_gate


	if(this->con_->getPuck()->getSizeTyp() == OK){
		//this->con_->getPuck()->openGate();
		//bc->refreshGate();
		printf("Puck OK PuckId:%d\n",this->con_->getPuck()->getId());
		//HAL *hal = HAL::getInstance();
		//hal->open_gate();
	}

}

Is_In_Gate::~Is_In_Gate(){
	printf("~Is in Gate()\n");

}

void Is_In_Gate::Puck_in_Gate_false(void){


	//BandController* bc = BandController::getInstance();
	//this->con_->getPuck()->closeGate();
	//bc->refreshGate();

	/*Timer *timer = new Timer();
	timer->waitForTimeOut(0,700000000);
	HAL *hal = HAL::getInstance();
	hal->close_gate();*/


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);

	// Move to State Road to Exit
	new (this) Road_To_Exit(this->con_);
}



