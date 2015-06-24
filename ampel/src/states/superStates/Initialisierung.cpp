/*
 *  Initialisierung.cpp
 *
 *  Created on: 08.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

Initialisierung::Initialisierung(Context* con): State::State(con){
//entry:	
//do:
	printf("Initialisierung()\n");
	//TODO: Initialize Stuff..
	HAL* hal = HAL::getInstance();
	hal->turn_greenLight_on();
    // Move to State: Ready
	new (this) Ready(this->con_);
}

Initialisierung::~Initialisierung(){
	printf("~Initialisierung()\n");
}


