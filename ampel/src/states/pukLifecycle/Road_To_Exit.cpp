/*
 * Road_To_Exit.cpp
 *
 *  Created on: 30.05.2015
 *      Author: Cumhur
 */
#include "PuckStates.h"


Road_To_Exit::Road_To_Exit(Context* con): State::State(con){
	HAL *hal= HAL::getInstance();
	BandController* bc = BandController::getInstance();
	CalibrateThread *cal = CalibrateThread::getInstance();


	cal->msToTimespec((cal->getOutGateToL1Fast() - cal->getOutGateToL1Fast2Sd()), &this->con_->t_tooSoon);
	this->con_->timer_tooSoon->setTimer(this->con_->t_tooSoon.tv_sec, this->con_->t_tooSoon.tv_nsec, true);

//	cal->msToTimespec((cal->getOutGateToL1Fast() + cal->getOutGateToL1Fast2Sd()) , &this->con_->t_tooLate);
//	this->con_->timer_tooLate->createSignalTimer(this->con_->t_tooLate.tv_sec, this->con_->t_tooLate.tv_nsec, ERROR_TIMOUT_IiG2RtoE);


	this->con_->getPuck()->runBandFast();
	bc->refreshBand();


	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_OUT_TRUE);

	delay(300);
	hal->close_gate();

	cout << "Road To Exit ----- PuckId: " << this->con_->getPuck()->getId() << endl;
	cout << "METAL   : " << this->con_->getPuck()->isMetal() << endl;
	cout << "HOLE IS : " << this->con_->getPuck()->isHoleOnTop() << endl;

}

Road_To_Exit::~Road_To_Exit(){
	printf("~Road_to_Exit()\n");

}

void Road_To_Exit::Running_out_true(void){

//	this->con_->timer_tooLate->stopTimer();
	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_OUT_TRUE);
	CalibrateThread* ct = CalibrateThread::getInstance();

	this->con_->timer_tooSoon->getTime(&this->con_->t_tooSoon);
	if(this->con_->t_tooSoon.tv_sec > 0 && this->con_->t_tooSoon.tv_nsec > 0){
		con_->setErrcode(ERROR_2SOON_RtoE);
		new (this) Error_Handling(this->con_);
	}

	//Band2
	if(ct->isBand() == 1){
		BandController* bc = BandController::getInstance();

		bc->delPuck(this->con_->getPuck());
		bc->refreshBand();

		new (this) Give_New_Puck(NULL);
	}else{
		new (this) User_Interaction_needed(this->con_);
	}

}

