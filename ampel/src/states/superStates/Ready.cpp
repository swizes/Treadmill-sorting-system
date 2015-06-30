/*
 * Ready.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "PuckLifcycleFSM.h"

Ready::Ready(Context* con): State::State(con){
	CalibrateThread *cal = CalibrateThread::getInstance();
	cout << "Ready" << endl;

	cout << "-----------------------------------" << endl;
    this->con_ = new Context();
    this->con_->setState(this);



    if(!cal->isBand()){ //Band 1
        Dispatcher* dsp = Dispatcher::getInstance();
        dsp->addListeners( this->con_, RUNNING_IN_TRUE);
    }

    	/* TODO:Start is pressed and waiting for new puck
        * Start timer
        * Timer *timer = new Timer();
        * if(getTime == 10) {
        * new (this) Not_Exist || Error_Handling(this->con_)
        * }
        * If no puck after x sec, go to not exist(idle) or error_handling
        */
}

Ready::~Ready(){
	printf("~Ready()\n");
}

void Ready::Running_In_true(void){
	BandController* bc = BandController::getInstance();
	if(bc->getPuckCounter() == MAX_PUCKS){
		new (this) Error_Handling(this->con_);
	} else {
		Dispatcher* dsp = Dispatcher::getInstance();
		dsp->remListeners( this->con_, RUNNING_IN_TRUE);
		// Move to State: Working_Band1
		PuckLifcycleFSM* pfsm = new PuckLifcycleFSM();
		pfsm->start(this->con_);
		//Switch To Ready
		new (this) Ready(NULL);

	}
}




