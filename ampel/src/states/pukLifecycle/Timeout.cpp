/*
 * Timeout.cpp
 *
 *  Created on: 31.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Timeout::Timeout(Context* con): State::State(con){
	printf("Timeout\n");
	//TODO: TIMEOUT Dispatcher
	HAL *hal = HAL::getInstance();
	hal->band_stop();
}

Timeout::~Timeout(){
	printf("~Timeout()\n");

}
//TODO: Timeout function go to state error handling


