/*
 * BandController.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "BandController.h"
#include <stdio.h>
#include <string.h>

using namespace std;


BandController* BandController::instance = NULL;

BandController* BandController::getInstance(){
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance == NULL) {
			instance = new BandController();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance;
}

BandController::BandController() {
	std::cout << "ctor BandController" << std::endl;
	stopped = false;
	runSlowly = false;
	reservedPuck = NULL;
	hal = HAL::getInstance();
	puckCounter = 0;
}

BandController::~BandController() {
	std::cout << "dtor BandController" << std::endl;
}

void BandController::addPuck(Puck* puck){
	if(puckCounter >= MAX_PUCKS){
		printf("Maximum Pucks reached\n");
	}else{
		pucklist[puckCounter] = puck;
		puckCounter++;
	}
}

void BandController::setReservedPuck(Puck* puck){
	memcpy(reservedPuck , puck, sizeof(Puck));
}
Puck* BandController::getReservedPuck(void){
	return reservedPuck;
}

void BandController::switchWithReservedPuck(Puck* puck){
	Puck* temp;
	memcpy(temp , reservedPuck, sizeof(Puck));
	memcpy(reservedPuck , puck, sizeof(Puck));
	memcpy(puck , temp, sizeof(Puck));
}

void BandController::delPuck(Puck* puck){
	int j = -1;
	for(int i=0; i < puckCounter; i++){
		if(j >= 0){
			memcpy(pucklist[j] , pucklist[i], sizeof(Puck));
			memset( pucklist[i], 0, sizeof(Puck) );
		}
		if( memcmp(puck, pucklist[i], sizeof(Puck)) == 0 ){
			memset( pucklist[i], 0, sizeof(Puck) );
			j = i;
		}
	}
	puckCounter--;
}

void BandController::refreshBand(){

	int stop = 0;
	int slow = 0;
	int fast = 0;


	for(int i = 0; i < puckCounter; i++){
		stop |= pucklist[i]->isBandStopped();
		slow |= pucklist[i]->isBandRunningSlowly();
		fast |= pucklist[i]->isBandRunningFast();

	}



//	printf("BandControl: stop: %d Slow: %d Fast: %d\n", stop, slow, fast);

	if(stop){
		hal->band_stop();
	}else if(slow){
		hal->band_right_slowly();
	}else if(fast){
		hal->band_right_normal();
	}

	if(puckCounter == 0){
		hal->band_stop();
	}

}

void BandController:: refreshGate(){

	int gate_open = 0;
	int gate_close = 0;

	for(int i = 0; i < puckCounter; i++){

		gate_open |= pucklist[i]->isGateOpen();
		gate_close |= pucklist[i]->isGateClosed();
	}


	if(gate_open){
		hal->open_gate();
	}else if(gate_close){
		hal->close_gate();
	}

	if(puckCounter == 0){
		hal->close_gate();
	}

}

Puck*  BandController::getRecentPuck(void){
	return pucklist[puckCounter];
}

Puck*  BandController::getLastPuck(void){
	return pucklist[puckCounter-1];
}
