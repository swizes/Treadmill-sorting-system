/*
 * Error_Handling.cpp
 *
 *  Created on: 31.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"


Error_Handling::Error_Handling(Context* con): State::State(con){
	printf("Error Handling()\n");
	HAL *hal = HAL::getInstance();
	BandController *bc = BandController::getInstance();
	bc->addPuck(this->con_->getPuck());
	this->con_->getPuck()->stopBand();
	bc->refreshBand();
	hal->turn_redLight_on();
	//TODO: Print the error out
	printf("Error\n");


	while(hal->is_resetButton_pushed() == 0){

	}
	cout << "Reset" << endl;
	while(hal->is_resetButton_pushed() == 1) {

	}
	hal->turn_redLight_off();
	cout << "Reset out" << endl;
	bc->delPuck(this->con_->getPuck());
	new (this) Birth(this->con_);
}

Error_Handling::~Error_Handling(){
	printf("~Error Handling()\n");
}

//TODO: Error Handling function

