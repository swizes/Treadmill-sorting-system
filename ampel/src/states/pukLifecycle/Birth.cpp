/*
 * Birth.cpp
 *
 *  Created on: 28.05.2015
 *      Author: abl425
 */
#include "PuckStates.h"


Birth::Birth(Context* con): State::State(con){

	HAL *hal = HAL::getInstance();
	//hal->turn_greenLight_off();


	BandController* bc = BandController::getInstance();
	bc->addPuck(this->con_->getPuck());
	this->con_->getPuck()->runBandFast();
	bc->refreshBand();

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_IN_FALSE);

	cout << "Birth ----- PuckId: " << this->con_->getPuck()->getId() << endl;


}

Birth::~Birth(){
	printf("~Birth()\n");

}

void Birth::Running_In_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_IN_FALSE);

	// Move to State Road to Height.
	new (this) Road_to_Height(this->con_);
}



