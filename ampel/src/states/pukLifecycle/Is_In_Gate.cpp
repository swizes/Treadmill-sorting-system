/*
 * Is_In_Gate.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "../../HAL.h"

static int lastMetal = 0;

Is_In_Gate::Is_In_Gate(Context* con) :
		State::State(con) {

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners(this->con_, PUCK_IN_GATE_FALSE);
	CalibrateThread *cal = CalibrateThread::getInstance();
	HAL *hal = HAL::getInstance();

    cout << "Is In Gate --- PuckId: " << this->con_->getPuck()->getId() << endl;


	cal->msToTimespec((cal->getHeightToGateFast()), &this->con_->t_tooSoon);
	this->con_->timer_tooSoon->setTimer(this->con_->t_tooSoon.tv_sec, this->con_->t_tooSoon.tv_nsec, true);

	cal->msToTimespec(cal->getHeightToGateFast() + (3*cal->getHeightToGateFast2Sd()) , &this->con_->t_tooLate);
	this->con_->timer_tooLate->createSignalTimer(this->con_->t_tooLate.tv_sec, this->con_->t_tooLate.tv_nsec, ERROR_TIMOUT_IiG2RtoE);


	if (cal->isBand()) { //Band2
		cout << "LAST PUCK METAL " << lastMetal << endl;

		// if( (LastPuckIsMetal && !ThisPuckIsMetal) || (!LastPuckIsMetal && ThisPuckIsMetal) )
		if ( (lastMetal == 1 && this->con_->getPuck()->isMetal() == 0) ) {
				lastMetal = 0;
			this->con_->getPuck()->setSizeTyp(OK);
			cout << "REIHENFOLGE OK" << endl;
		}else if((lastMetal == 0 && this->con_->getPuck()->isMetal() == 1)){
				lastMetal = 1;
			this->con_->getPuck()->setSizeTyp(OK);
			cout << "REIHENFOLGE OK" << endl;
		}
		else {
			this->con_->getPuck()->setSizeTyp(NOT_OK);
			cout << "REIHENFOLGE NOT OK" << endl;
		}
	}

    if (this->con_->getPuck()->getSizeTyp() == OK) {
        hal->open_gate();
	} else {
        if (!cal->isBand()) {//Band1
            cout << "SHOULD NEVER HAPPEN" <<endl;//implement error
        }

        // Move to State Road_To_Sorting_Out
    	this->con_->timer_tooSoon->getTime(&this->con_->t_tooSoon);
    	if(this->con_->t_tooSoon.tv_sec > 0 && this->con_->t_tooSoon.tv_nsec > 0){
    		con_->setErrcode(ERROR_2SOON_IiG2RtoE);
			new (this) Error_Handling(this->con_);
    	}
        dsp->remListeners(this->con_, PUCK_IN_GATE_FALSE);
        new (this) Road_To_Sorting_Out(this->con_);
    }
}

Is_In_Gate::~Is_In_Gate() {
	printf("~Is in Gate()\n");

}

void Is_In_Gate::Puck_in_Gate_false(void) {

	this->con_->timer_tooLate->stopTimer();

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners(this->con_, PUCK_IN_GATE_FALSE);

	this->con_->timer_tooSoon->getTime(&this->con_->t_tooSoon);
	if(this->con_->t_tooSoon.tv_sec > 0 && this->con_->t_tooSoon.tv_nsec > 0){
		con_->setErrcode(ERROR_2SOON_IiG2RtoE);
		new (this) Error_Handling(this->con_);
	}

	new (this) Road_To_Exit(this->con_);

}

