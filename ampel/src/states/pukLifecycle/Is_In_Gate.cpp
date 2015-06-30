/*
 * Is_In_Gate.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "../../HAL.h"

int lastMetal = 0;

Is_In_Gate::Is_In_Gate(Context* con) :
		State::State(con) {
	BandController* bc = BandController::getInstance();
	Dispatcher* dsp = Dispatcher::getInstance();
	CalibrateThread *cal = CalibrateThread::getInstance();

	HAL *hal = HAL::getInstance();
    cout << "Is In Gate --- PuckId: " << this->con_->getPuck()->getId()
				<< endl;


//    cout << "LAST PUCK METAL" << bc->getLastPuck()->isMetal() << endl;
//
//    if (cal->isBand()) { //Band2
//        // if( (LastPuckIsMetal && !ThisPuckIsMetal) || (!LastPuckIsMetal && ThisPuckIsMetal) )
//        if ((bc->getLastPuck()->isMetal() && !con_->getPuck()->isMetal())
//            || (!bc->getLastPuck()->isMetal()
//            && con_->getPuck()->isMetal())) {
//        	 this->con_->getPuck()->setSizeTyp(OK);
//             cout << "REIHENFOLGE OK" << endl;
//        } else {
//            this->con_->getPuck()->setSizeTyp(NOT_OK);
//            cout << "REIHENFOLGE NOT OK" << endl;
//
//        }
//    }

    // Auf jeden fall anmelden



	if (cal->isBand()) { //Band2

		cout << "LAST PUCK METAL " << lastMetal<< endl;
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
    dsp->addListeners(this->con_, METAL_DETECTION_TRUE);
    if (this->con_->getPuck()->getSizeTyp() == OK) {
        hal->open_gate();
		dsp->addListeners(this->con_, PUCK_IN_GATE_FALSE);
	} else {
//        if (!cal->isBand()) {//Band1
//            cout << "SHOULD NEVER HAPPEN" <<endl;//implement error
//        }
//        // Move to State Road_To_Sorting_Out
//        new (this) Road_To_Sorting_Out(this->con_);
    }
}

Is_In_Gate::~Is_In_Gate() {
	printf("~Is in Gate()\n");

}

void Is_In_Gate::Puck_in_Gate_false(void) {

	con_->getPuck()->setMetal(false);

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners(this->con_, PUCK_IN_GATE_FALSE);
	dsp->remListeners(this->con_, METAL_DETECTION_TRUE);

	// Move to State Road to Exit
	new (this) Road_To_Exit(this->con_);
}

void Is_In_Gate::Metal_detection_true(void) {

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners(this->con_, PUCK_IN_GATE_FALSE);
	dsp->remListeners(this->con_, METAL_DETECTION_TRUE);

	con_->getPuck()->setMetal(true);
	CalibrateThread *cal = CalibrateThread::getInstance();
	if (cal->isBand()) { //Band2

		cout << "LAST PUCK METAL " << lastMetal<< endl;
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
			new (this) Road_To_Sorting_Out(this->con_);
		}
	}

	// Move to State Road to Exit
	HAL *hal = HAL::getInstance();
	hal->open_gate();
	new (this) Road_To_Exit(this->con_);
}

