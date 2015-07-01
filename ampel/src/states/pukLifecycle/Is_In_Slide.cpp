/*
 * Is_in_Slide.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"

Timer* timer;

Is_In_Slide::Is_In_Slide(Context* con): State::State(con){

	cout << "Is In Slide ----- PuckId: " << this->con_->getPuck()->getId() << endl;


	//When puck is in slide, increase the counter by 1
	BandController *bc = BandController::getInstance();
	bc->incSlideCounter();


	//Slide ist voll, oder Puck haengt fest => UserInteraktion!
	//Maximum allowed amount of pucks inside the slide is 4. If Max is reached, go to error handling
	//TODO: Errcode etc.
	if (bc->getSlideCounter() == 4){
		new (this) Error_Handling(NULL);
	} else {
		Dispatcher* dsp = Dispatcher::getInstance();
		dsp->addListeners( this->con_, SLIDE_FULL_FALSE);
	}


	//TODO: ErrorHandling => After Timeout und EVENT nicht eingetreten

	Timer* timer = new Timer();
	timer->setTimer(2,0);
	struct timespec t;

	HAL *hal = HAL::getInstance();
	timer->getTime(&t);
	while(t.tv_sec != 0 && t.tv_nsec != 0){
		timer->getTime(&t);
		if(!hal->is_slide_full()){
			timer->deleteTimer();
			break;
		}
		delay(100);
	}

	if(hal->is_slide_full()){
		hal->band_stop();
		cout << "ERROR SLIDE FULL" << endl;
	}

}

Is_In_Slide::~Is_In_Slide(){
	printf("~Is in Slide()\n");

}

void Is_In_Slide::Slide_full_false(void){

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_FALSE);


	BandController* bc = BandController::getInstance();

	bc->delPuck(this->con_->getPuck());
	bc->refreshBand();


	//Band 2
	if(CalibrateThread::getInstance()->isBand() == 1){
		new (this) Give_New_Puck(NULL);
	}

}

