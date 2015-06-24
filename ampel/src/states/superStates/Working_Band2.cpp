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
	printf("Working_Band2()\n");
    Dispatcher* dsp = Dispatcher::getInstance();
    dsp->addListeners( this->con_, RUNNING_IN_TRUE);
    cout << "Add Disp" << endl;
	
   
}

Working_Band2::~Working_Band2(){
	printf("~Working_Band2()\n");
}

void Working_Band2::Running_In_true(void){
	std::cout << "Running IN" << std::endl;
	BandController* bc = BandController::getInstance();
    Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_IN_TRUE);

	this->con_->getPuck()->runBandFast();
	bc->refreshBand();
	//HAL *hal = HAL::getInstance();
	//hal->band_right_normal();
    
    // Move to State: Give_New_Puck
	//new (this) Give_New_Puck(this->con_);
	new (this) Birth(this->con_);
}

