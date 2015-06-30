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

DoorKeeper::DoorKeeper(void) {
	greenLightOn = true;
	allowPuck = right_;
}

DoorKeeper::~DoorKeeper() {
	cout << "dtor: DoorKeeper" << endl;
}

void DoorKeeper::startTimer(void* con) {
	HAL *hal = HAL::getInstance();
	Context* c = (Context*) con;

	//If greenlight is not on, do not let another puck
	if (!greenLightOn) {
		allowPuck = false;
	} else {
		hal->turn_greenLight_off();
		greenLightOn = false;
		c->setState(new Birth(c));
		delay(1500);
		//If next puck is not allowed, go to Error Handling, otherwise turn green light on and let the puck.
		if (!allowPuck) {
			c->setState(new Error_Handling(c));
		} else {
			hal->turn_greenLight_on();
			greenLightOn = true;
			allowPuck = true;
		}
	}
}

void DoorKeeper::shutdown() {
	cout << "DoorKeeper shutdown" << endl;
}

