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

	this->con_->getPuck()->runBandFast();
	bc->refreshBand();
	CalibrateThread *cal = CalibrateThread::getInstance();

	uint64_t time = cal->getOutGateToL1Fast();
	timespec *t;
	cal->msToTimespec(time,t);
	con_->timer->setTimer(t->tv_sec,t->tv_nsec);

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_OUT_TRUE);

	Timer* timer = new Timer();
	timer->waitForTimeOut(0,300000000);

	hal->close_gate();

	cout << "Road To Exit ----- PuckId: " << this->con_->getPuck()->getId() << endl;
}

Road_To_Exit::~Road_To_Exit(){
	CalibrateThread *cal = CalibrateThread::getInstance();
	printf("~Road_to_Exit()\n");
	timespec *t;
	con_->timer->getTime(t);
	int ms = cal->timespecToMs(t);
	if(ms <= 0){
		printf("To Late Puk: %d\n", con_->getPuck()->getId());
	}

}

void Road_To_Exit::Running_out_true(void){

	HAL *hal= HAL::getInstance();
	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_OUT_TRUE);

	CalibrateThread* ct = CalibrateThread::getInstance();

	//Band2
	if(ct->isBand() == 1){
		//hal->band_stop();
		BandController* bc = BandController::getInstance();

		bc->delPuck(this->con_->getPuck());
		bc->refreshBand();

		new (this) Give_New_Puck(NULL);
	}else{
		new (this) User_Interaction_needed(this->con_);
	}

}

