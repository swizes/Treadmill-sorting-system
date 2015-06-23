/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){


	Dispatcher* dsp = Dispatcher::getInstance();
	HAL *hal = HAL::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);
//
//	Timer *pulse = new Timer();
//	Timer timer;
//	pulse->waitForTimeOut(1,500000000);
//	BandController* bc = BandController::getInstance();
//	cout << "Timer Expire" << endl;


	//hal->band_right_slowly();
	cout << "Road To Height ----- PuckId: " << this->con_->getPuck()->getId() << endl;
}

Road_to_Height::~Road_to_Height(){
	printf("~Road to Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();

	HAL *hal = HAL::getInstance();
	//hal->turn_greenLight_on();
	hal->band_right_slowly();

	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height Measurement.
	new (this) Height_Measurement(this->con_);
}
