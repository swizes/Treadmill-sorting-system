/*
 * Road_To_Exit.cpp
 *
 *  Created on: 30.05.2015
 *      Author: Cumhur
 */
#include "PuckStates.h"


Road_To_Exit::Road_To_Exit(Context* con): State::State(con){
	printf("Road_to_Exit PuckId: %d\n",  this->con_->getPuck()->getId());

	BandController* bc = BandController::getInstance();

	this->con_->getPuck()->runBandFast();
	bc->refreshBand();


	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_OUT_TRUE);

	Timer* timer = new Timer();
	timer->waitForTimeOut(0,300000000);
	HAL *hal= HAL::getInstance();
	hal->close_gate();


}

Road_To_Exit::~Road_To_Exit(){
	printf("~Road_to_Exit()\n");

}

void Road_To_Exit::Running_out_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_OUT_TRUE);

	CalibrateThread* ct = CalibrateThread::getInstance();

	//Band2
	if(ct->isBand() == 1){
		new (this) Give_New_Puck(NULL);
	}

	// Move to State User_Interaction_needed
	new (this) User_Interaction_needed(this->con_);

}

