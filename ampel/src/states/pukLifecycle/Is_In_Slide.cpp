/*
 * Is_in_Slide.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"


Is_In_Slide::Is_In_Slide(Context* con): State::State(con){
	//printf("Is in Slide()\n");
	BandController* bc = BandController::getInstance();
	bc->delPuck(this->con_->getPuck());
	bc->refreshBand();

	//TODO: Timeout
	/*After x Secs
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_TRUE);
	*/
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_FALSE);
	Timer *timer = new Timer();
	timer->waitForTimeOut(2,0);
//	cout << "Slide full";
	//HAL *hal = HAL::getInstance();
	//hal->turn_redLight_on();
	//hal->band_stop();

}

Is_In_Slide::~Is_In_Slide(){
	printf("~Is in Slide()\n");

}

void Is_In_Slide::Slide_full_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_FALSE);
	//HAL *hal = HAL::getInstance();

	//TODO: ERROR HANDLING
	//con->getPuck()->isBandStopped();


	//TODO: Move to State Sorted Out
	//new (this) Sorted_Out(this->con_);
}

//TODO: void Is_in_Slide::Error_Handling(void)
