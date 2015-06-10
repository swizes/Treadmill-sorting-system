/*
 * Calibration.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Calibration::Calibration(Context* con): State::State(con){
//entry:	
//do:
	printf("Calibration()\n");
	//TODO: Calibrate Stuff..
	
	new (this) Ready(this->con_);
}

Calibration::~Calibration(){
	printf("~Calibration()\n");
}

