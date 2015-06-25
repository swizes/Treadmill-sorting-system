/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);

	cout << "Road To Height ----- PuckId: " << this->con_->getPuck()->getId() << endl;

}

Road_to_Height::~Road_to_Height(){
	printf("~Road to Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	BandController* bc = BandController::getInstance();

//	HAL *hal = HAL::getInstance();
//	hal->band_right_slowly();

	//TODO: Check, da eig nicht ueber HAL auf Band zugegriffen werden soll
	this->con_->getPuck()->runBandSlowly();
	bc->refreshBand();

	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height Measurement.
	new (this) Height_Measurement(this->con_);
}
