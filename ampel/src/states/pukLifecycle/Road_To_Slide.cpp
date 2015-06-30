/*
 * Road_To_Slide.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"

Road_To_Slide::Road_To_Slide(Context* con): State::State(con){
	cout << "Road_To_Slide ----- PuckId: " << this->con_->getPuck()->getId() << endl;

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, SLIDE_FULL_TRUE);



}

Road_To_Slide::~Road_To_Slide(){
	printf("~Flipping Puck()\n");

}

void Road_To_Slide::Slide_full_true(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, SLIDE_FULL_TRUE);

	// Move to Is in Slide
	new (this) Is_In_Slide(this->con_);
}



