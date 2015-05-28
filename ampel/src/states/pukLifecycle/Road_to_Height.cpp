/*
 * Birth.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){
	printf("Road_to_Height()\n");
	//STARTE TIMER!

}

Road_to_Height::~Road_to_Height(){
	printf("~Road_to_Height()\n");

}

void Road_to_Height:: /*Lambda???*/ (void){
	// Move to State Height_Measurement.
	//new (this) Height_Measurement(this->con_);
}
