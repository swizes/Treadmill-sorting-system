/*
 * Flipping_Puck.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"

Flipping_Puck::Flipping_Puck(Context* con): State::State(con){
	printf("Flipping Puck()\n");
	HAL *hal = HAL::getInstance();
	hal->open_gate();
	Timer *timer = new Timer();
	timer->waitForTimeOut(0,100000000);
	hal->close_gate();
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_TRUE);
}

Flipping_Puck::~Flipping_Puck(){
	printf("~Flipping Puck()\n");

}

void Flipping_Puck::Slide_full_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_TRUE);

	// Move to Is in Slide
	new (this) Is_In_Slide(this->con_);
}



