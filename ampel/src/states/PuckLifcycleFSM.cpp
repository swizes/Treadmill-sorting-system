/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "PuckLifcycleFSM.h"


PuckLifcycleFSM::PuckLifcycleFSM() {
	// TODO Auto-generated constructor stub

}

PuckLifcycleFSM::~PuckLifcycleFSM() {
	// TODO Auto-generated destructor stub
}



void PuckLifcycleFSM::execute(void* con){

	Context* c = (Context*) con;
	c->setState(new Birth(c));
}

void PuckLifcycleFSM::shutdown(){

}
