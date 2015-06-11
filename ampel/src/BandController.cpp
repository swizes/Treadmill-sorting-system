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

void BandController::delPuck(Puck* puck){
	int j = -1;
	for(int i=0; i < puckCounter; i++){
		if(j >= 0){
			memcpy(pucklist[j] , pucklist[i], sizeof(Puck));
		}
		if( memcmp(puck, pucklist[i], sizeof(Puck)) == 0 ){
			memset( pucklist[i], 0, sizeof(Puck) );
			j = i;
		}
	}
	puckCounter--;
}

void BandController::refreshBand(){
	int i = 0;

	int stop = 0;
	int slow = 0;
	int fast = 0;

	for(i = 0; i < puckCounter; i++){
		stop |= pucklist[i]->isBandStopped();
	}

	for(i = 0; i < puckCounter; i++){
		slow |= pucklist[i]->isBandRunningSlowly();
	}

	for(i = 0; i < puckCounter; i++){
		fast |= pucklist[i]->isBandRunningFast();
	}

	printf("BandControl: stop: %d Slow: %d Fast: %d\n", stop, slow, fast);

	if(stop){
		hal->band_stop();
	}else if(slow){
		hal->band_right_slowly();
	}else if(fast){
		hal->band_right_normal();
	}
}