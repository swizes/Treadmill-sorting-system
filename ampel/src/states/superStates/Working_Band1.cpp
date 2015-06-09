/*
 *  Working_Band1.cpp
 *
 *  Created on: 08.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

Working_Band1::Working_Band1(Context* con): State::State(con){
//entry:	
    //TODO: Generate NEW PUCKID
//do:
    //TODO: Sind PucksIDs auf FiFo ? Bleibe in Band1Automat : Gehe in Ready zurück & stoppe das Band1
	printf("Working_Band1()\n");
    
    Dispatcher* dsp = Dispatcher::getInstance();
    dsp->addListeners( this->con_, RUNNING_OUT_TRUE);
    dsp->addListeners( this->con_, RUNNING_IN_TRUE);
	
	new (this) Ready(this->con_);
}

Working_Band1::~Working_Band1(){
	printf("~Working_Band1()\n");
}

void Working_Band1::Running_In_true(void){
    Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_IN_TRUE);
    dsp->remListeners( this->con_, RUNNING_OUT_TRUE);
    // Move to State: Working_Band1
    new (this) Working_Band1(this->con_);
}

void Working_Band1::Running_out_true(void){
    Dispatcher* dsp = Dispatcher::getInstance();
    HAL *hal = HAL::getInstance();
    hal->band_stop();
	dsp->remListeners( this->con_, RUNNING_IN_TRUE);
    dsp->remListeners( this->con_, RUNNING_OUT_TRUE);
    // Move to State: User_Interaction_needed
    new (this) User_Interaction_needed(this->con_);
}



