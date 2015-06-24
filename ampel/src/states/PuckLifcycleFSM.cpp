/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "PuckLifcycleFSM.h"
#include "DoorKeeper.h"


PuckLifcycleFSM::PuckLifcycleFSM() {

}

PuckLifcycleFSM::~PuckLifcycleFSM() {
	// TODO Auto-generated destructor stub
}



void PuckLifcycleFSM::execute(void* con){
	DoorKeeper* dk = DoorKeeper::getInstance();
	dk->startTimer((Context*) con);
//	Context* c = (Context*) con;
//	c->setState(new Birth(c));
}

void PuckLifcycleFSM::shutdown(){

}
