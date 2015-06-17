/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){
	printf("Road to Height()\n");
	//TODO:STARTE TIMER!
	//TODO: TimeOut?!
	Dispatcher* dsp = Dispatcher::getInstance();
	HAL *hal = HAL::getInstance();
	//TODO: oder 	dsp->addListeners( this->con_, HEIGHT_STATUS_OK);
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);

	Timer *pulse = new Timer();
	//Timer timer;
	pulse->waitForTimeOut(1,500000000);

//	BandController* bc = BandController::getInstance();

	//cout << "Timer expire" << endl;

//	this->con_->getPuck()->runBandSlowly();
//	bc->refreshBand();
	hal->turn_greenLight_on();

	cout << "RoadToHeight PuckId: " << this->con_->getPuck()->getId() << endl;
	//hal->band_right_slowly();

}

Road_to_Height::~Road_to_Height(){
	printf("~Road to Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	HAL *hal = HAL::getInstance();
	//TODO: or?	dsp->remListeners( this->con_, HEIGHT_STATUS_OK);
	//cout << "IS_IN_HEIGHT ::" << hal->is_puck_in_height_determination() << endl;
	//cout << "GOTO HeightMeasurement" << endl;
	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height Measurement.
	new (this) Height_Measurement(this->con_);
}
