/*
 * Error_Handling.cpp
 *
 *  Created on: 31.05.2015
 *      Author: swizes
 */

#include "Errors.h"
#include "PuckStates.h"


Error_Handling::Error_Handling(Context* con): State::State(con){
	printf("Error Handling()\n");
	HAL *hal = HAL::getInstance();
	BandController *bc = BandController::getInstance();
	this->con_->getPuck()->stopBand();
	bc->refreshBand();

	hal->turn_redLight_on();

	errors_print( con_->getErrcode() );

	cout << "Push <<RESET>>" << endl;
	while( !hal->is_resetButton_pushed() ){}

	hal->turn_redLight_off();

	bc->delPuck(this->con_->getPuck());
	bc->refreshBand();

	// Move to state: Ready
	//new (this) Ready(this->con_);
}

Error_Handling::~Error_Handling(){
	printf("~Error Handling()\n");
}


//Error for TimeOut => Puck ist weg
void Error_Handling::callError(int errcode){

	printf("Error Handling()\n");
		HAL *hal = HAL::getInstance();
		BandController *bc = BandController::getInstance();
		hal->band_stop();

		hal->turn_redLight_on();

		errors_print( errcode );

		cout << "Push <<RESET>>" << endl;
		while( !hal->is_resetButton_pushed() ){}

		hal->turn_redLight_off();


		bc->delPuck(bc->getPuck(bc->getPuckCounter()-1));
		bc->refreshBand();

}



