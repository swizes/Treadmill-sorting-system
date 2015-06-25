/*
 * BandController.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "BandController.h"

using namespace std;


BandController* BandController::instance = NULL;
HAL *hal = HAL::getInstance();

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
	//std::cout << "ctor BandController" << std::endl;
	stopped = false;
	runSlowly = false;
	puckCounter = 0;
	errCode = 0;

	lastPuck.setHoleOnTop(false);
	lastPuck.setMetal(false);
	lastPuck.setUserInteractionNeeded(false);
	lastPuck.setSize(0);
	lastPuck.setSizeTyp(NOT_OK);

	reservedPuck.setHoleOnTop(false);
	reservedPuck.setMetal(false);
	reservedPuck.setUserInteractionNeeded(false);
	reservedPuck.setSize(0);
	reservedPuck.setSizeTyp(NOT_OK);
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
int BandController::getPuckCounter(void) {
	return puckCounter;
}

Puck* BandController::getReservedPuck(void){
	return &reservedPuck;
}

void BandController::setReservedPuck(Puck* puck){
	memcpy( getReservedPuck() , puck, sizeof(Puck));
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

	if(puckCounter == 0){
		hal->band_stop();
		return;
	}

	int stop = 0;
	int slow = 0;
	int fast = 0;


	for(int i = 0; i < puckCounter; i++){
		stop |= pucklist[i]->isBandStopped();
		slow |= pucklist[i]->isBandRunningSlowly();
		fast |= pucklist[i]->isBandRunningFast();

	}

	if(stop||hal->is_puck_running_out()){
		hal->band_stop();
	}else if(slow){
		hal->band_right_slowly();
	}else if(fast){
		hal->band_right_normal();
	}

}


Puck*  BandController::getRecentPuck(void){
	return pucklist[puckCounter-1];
}

Puck*  BandController::getLastPuck(void){
	return &lastPuck;
}

void  BandController::setLastPuck(Puck* puck){
	memcpy( getLastPuck() , puck, sizeof(Puck));
}

void  BandController::setRecenctPuck(Puck* puck){
	memcpy( getRecentPuck() , puck, sizeof(Puck));
}

int BandController::getErrcode(void){
	return errCode;
}

void BandController::setErrcode(int errCode){
	this->errCode=errCode;
}
