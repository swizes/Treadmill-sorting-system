/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){

	Dispatcher* dsp = Dispatcher::getInstance();
	CalibrateThread *cal = CalibrateThread::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);


	cal->msToTimespec(cal->getL0toHeightFast() - cal->getL0toHeightFast2Sd(), &this->con_->t_tooSoon);
	this->con_->timer_tooSoon->setTimer(this->con_->t_tooSoon.tv_sec, this->con_->t_tooSoon.tv_nsec);

	cout << "Road To Height ----- PuckId: " << this->con_->getPuck()->getId() << endl;

}

Road_to_Height::~Road_to_Height(){
	printf("~Road to Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	BandController* bc = BandController::getInstance();
//	CalibrateThread *cal = CalibrateThread::getInstance();

	this->con_->timer_tooSoon->getTime(&this->con_->t_tooSoon);
	if(this->con_->t_tooSoon.tv_sec > 0 && this->con_->t_tooSoon.tv_nsec > 0){
		cout << "ERROR: PUCK ZUVIEL AUF BAND" << endl;
	}

//	HAL *hal = HAL::getInstance();
//	hal->band_right_slowly();

	//TODO: Check, da eig nicht ueber HAL auf Band zugegriffen werden soll
	this->con_->getPuck()->runBandSlowly();
	bc->refreshBand();

	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height Measurement.
	new (this) Height_Measurement(this->con_);
}
