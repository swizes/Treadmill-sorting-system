/*
 * Road_To_Exit.cpp
 *
 *  Created on: 30.05.2015
 *      Author: Cumhur
 */
#include "PuckStates.h"


Road_To_Exit::Road_To_Exit(Context* con): State::State(con){
	printf("Road_to_Exit()\n");
	HAL *hal = HAL::getInstance();

	BandController* bc = BandController::getInstance();
	con->getPuck()->runBandFast();
	bc->refreshBand();
	//hal->band_right_normal();
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_OUT_TRUE);

	Timer* timer = new Timer();
	timer->waitForTimeOut(1,0);
	cout << "Timeout" << endl;
	//hal->close_gate();
}

Road_To_Exit::~Road_To_Exit(){
	printf("~Road_to_Exit()\n");

}

void Road_To_Exit::Running_out_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_OUT_TRUE);

	BandController* bc = BandController::getInstance();
	this->con_->getPuck()->stopBand();
	bc->refreshBand();

	HAL *hal = HAL::getInstance();
	//hal->band_stop();
	//hal->close_gate();

	//new (this) SerialCommunicationBand1(this->con_);
	// Move to State Band2
	new (this) User_Interaction_needed(this->con_);
}

