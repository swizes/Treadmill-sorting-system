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
	hal->band_stop();
	//TODO: Print the error out
	printf("Error\n");
	if(hal->is_resetButton_pushed() == 1) {
		new (this) Birth(this->con_);
	}
}

Error_Handling::~Error_Handling(){
	printf("~Error Handling()\n");
}

//TODO: Error Handling function

