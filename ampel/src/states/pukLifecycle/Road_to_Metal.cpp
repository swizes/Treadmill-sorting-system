/*
 * Road_to_Metal.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
//TODO: Class name should be changed to Metal Detection
Road_to_Metal::Road_to_Metal(Context* con): State::State(con){
	Dispatcher* dsp = Dispatcher::getInstance();
	CalibrateThread *cal = CalibrateThread::getInstance();
	dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);
	BandController *bc = BandController::getInstance();
	this->con_->getPuck()->runBandFast();
	bc->refreshBand();

	cout << "Road To Metal ----- PuckId: " << this->con_->getPuck()->getId() << endl;

	cal->msToTimespec((cal->getHeightToGateFast() - cal->getHeightToGateFast2Sd()), &this->con_->t_tooSoon);
	this->con_->timer_tooSoon->setTimer(this->con_->t_tooSoon.tv_sec, this->con_->t_tooSoon.tv_nsec, true);

	cal->msToTimespec(cal->getHeightToGateFast() + cal->getHeightToGateFast2Sd() , &this->con_->t_tooLate);
	this->con_->timer_tooLate->createSignalTimer(this->con_->t_tooLate.tv_sec, this->con_->t_tooLate.tv_nsec, true);

}

Road_to_Metal::~Road_to_Metal(){
	printf("~Road_to_Metal()\n");

}

void Road_to_Metal::Puck_in_Gate_true(void){

	// Stop listen to Event Transmission2
	HAL *hal = HAL::getInstance();
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);

	this->con_->timer_tooSoon->getTime(&this->con_->t_tooSoon);
	if(this->con_->t_tooSoon.tv_sec > 0 && this->con_->t_tooSoon.tv_nsec > 0){
		con_->setErrcode(ERROR_2SOON_RtoM2IiG);
		new (this) Error_Handling(this->con_);
	}


	if(hal->is_metal_detected()){
		this->con_->getPuck()->setMetal(true);
		cout << "HAT METAL" << endl;
	}else{
		this->con_->getPuck()->setMetal(false);
	}

	// Move to State Is In Gate
	new (this) Is_In_Gate(this->con_);
}






