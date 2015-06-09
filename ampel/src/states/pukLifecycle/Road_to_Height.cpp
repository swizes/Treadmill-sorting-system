/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){
	printf("Road to Height()\n");
	//TODO:STARTE TIMER!
	//TODO: TimeOut?!
	Dispatcher* dsp = Dispatcher::getInstance();
	HAL *hal = HAL::getInstance();
	//TODO: oder 	dsp->addListeners( this->con_, HEIGHT_STATUS_OK);
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);

	Timer *pulse = new Timer();
	//Timer timer;
	pulse->waitForTimeOut(1,500000000);



	cout << "Timer expire" << endl;

	hal->band_right_slowly();
	cout << "Timer expire" << endl;
}

Road_to_Height::~Road_to_Height(){
	printf("~Road to Height()\n");

}

void Road_to_Height::In_Height_true (void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	//TODO: or?	dsp->remListeners( this->con_, HEIGHT_STATUS_OK);
	dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

	// Move to State Height Measurement.
	new (this) Height_Measurement(this->con_);
}
