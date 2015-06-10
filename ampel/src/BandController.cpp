/*
 * BandController.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "BandController.h"

BandController* BandController::getInstance(){
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new BandController();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}

BandController::BandController() {
	std::cout << "ctor BandController" << std::endl;
	stopped = false;
	runSlowly = false;
	hal = HAL::getInstance();
}

BandController::~BandController() {
	std::cout << "dtor BandController" << std::endl;
}


void BandController::setBandIsStopped(bool stop){
	stopped =stop;
}
void BandController::setBandRunSlowly(bool slow){
	runSlowly = slow;
}

bool BandController::isBandStopped(){
	return stopped;
}

bool BandController::isBandRunningSlowly(){
	return runSlowly;
}
