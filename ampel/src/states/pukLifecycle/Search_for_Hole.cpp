/*
 * Search_For_Hole.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "../HoleDetector.h"

Search_for_Hole::Search_for_Hole(Context* con): State::State(con){
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_FALSE);

	cout << "Search For Hole ----- PuckId: " << this->con_->getPuck()->getId() << endl;
}

Search_for_Hole::~Search_for_Hole(){
	printf("~Search for Hole()\n");

}

void Search_for_Hole::In_Height_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, IN_HEIGHT_FALSE);


	BandController* bc = BandController::getInstance();
	this->con_->getPuck()->runBandFast();
	bc->refreshBand();

	cout << "PuckType: " << this->con_->getPuck()->getSizeTyp()  << "  ID: " << this->con_->getPuck()->getId() << endl;

	Puck *puck = this->con_->getPuck();

	if(puck->getSizeTyp() == OK){
		if(puck->isHoleOnTop()){
			puck->setUserInteractionNeeded(true);
		}

		new (this) Road_to_Metal(this->con_);
	}else{
		new (this) Road_To_Sorting_Out(this->con_);
	}

}


