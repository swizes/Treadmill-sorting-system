/*
 * Is_in_Slide.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"


Is_In_Slide::Is_In_Slide(Context* con): State::State(con){

	BandController* bc = BandController::getInstance();
	bc->delPuck(this->con_->getPuck());
	bc->refreshBand();

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_FALSE);

	cout << "Is In Slide ----- PuckId: " << this->con_->getPuck()->getId() << endl;
}

Is_In_Slide::~Is_In_Slide(){
	printf("~Is in Slide()\n");

}

void Is_In_Slide::Slide_full_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_FALSE);

}

//TODO: void Is_in_Slide::Error_Handling(void)
