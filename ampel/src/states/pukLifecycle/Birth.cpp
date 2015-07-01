/*
 * Birth.cpp
 *
 *  Created on: 28.05.2015
 *      Author: abl425
 */
#include "PuckStates.h"

Birth::Birth(Context* con): State::State(con){

	BandController* bc = BandController::getInstance();
	bc->addPuck(this->con_->getPuck());
	this->con_->getPuck()->runBandFast();
	bc->refreshBand();

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_IN_FALSE);

	std::cout << "Birth ----- PuckId: " << this->con_->getPuck()->getId() << std::endl;
	cout << "create timer" << endl;
	//timer->waitForTimeOut(10,0);
	cout << "after create timer" << endl;
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
	cout << "after road to height create" << endl;
	//delete(this);
}



