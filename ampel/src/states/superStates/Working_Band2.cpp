/*
 *  Working_Band2.cpp
 *
 *  Created on: 08.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

Working_Band2::Working_Band2(Context* con): State::State(con){
//entry:	
    //TODO: Starte SubAutomatBand2
//do:
	//printf("Working_Band2()\n");
	cout << "Working Band 2" << endl;

    Dispatcher* dsp = Dispatcher::getInstance();
    dsp->addListeners( this->con_, RUNNING_IN_TRUE);
   
}

Working_Band2::~Working_Band2(){
	printf("~Working_Band2()\n");
}

void Working_Band2::Running_In_true(void){
//	BandController* bc = BandController::getInstance();
    Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_IN_TRUE);
	new (this) Birth(this->con_);
}

