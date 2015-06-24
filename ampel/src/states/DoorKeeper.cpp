/*
 * DoorKeeper.cpp
 *
 *  Created on: 23.06.2015
 *      Author: abl425
 */

#include <unistd.h>
#include <time.h>
#include "DoorKeeper.h"
#include "PuckStates.h"

DoorKeeper* DoorKeeper::instance_ = NULL;
bool DoorKeeper::right_ = true;

/**
 * c'tor for the Thread-safe singleton Calibration implementation
 * @param none
 * @return A Pointer to the Singleton Calibration Object
 */
DoorKeeper* DoorKeeper::getInstance() {
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new DoorKeeper();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}



DoorKeeper::DoorKeeper(void ) {
	greenLight = true;
	right = right_;
}



DoorKeeper::~DoorKeeper() {
    cout << "dtor: DoorKeeper" << endl;
}



void DoorKeeper::startTimer(void* con){
	HAL *hal= HAL::getInstance();
	Context* c = (Context*) con;
	Timer* timer = new Timer();
	if(!greenLight) {
		right = false;
	} else {
		hal->turn_greenLight_off();
		greenLight = false;
		c->setState(new Birth(c));
		timer->waitForTimeOut(1,500000000);
		if(!right) {
			c->setState(new Error_Handling(c));
		} else {
			hal->turn_greenLight_on();
			greenLight = true;
			right = true;
		}

	}


}



void DoorKeeper::shutdown(){
    cout << "DoorKeeper shutdown" << endl;
}






