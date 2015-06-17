/*
 * Search_For_Hole.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "../HoleDetector.h"

Search_for_Hole::Search_for_Hole(Context* con): State::State(con){
//	printf("SearchSearch_for_Hole for Hole\n");
	//TODO: Set the type of Puck and save it
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_FALSE);

	//HAL* hal = HAL::getInstance();
	//hal->band_right_slowly();
	//hal->open_gate();

	//HoleDetector* hd = new HoleDetector();
	//this->con_->getPuck()->setHoleOnTop(hd->detectHole(hal, true));
}

Search_for_Hole::~Search_for_Hole(){
	printf("~Search for Hole()\n");

}

void Search_for_Hole::In_Height_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, IN_HEIGHT_FALSE);


	//band_right_normal()
	BandController* bc = BandController::getInstance();
	con_->getPuck()->runBandFast();
	bc->refreshBand();

	Puck *puck = this->con_->getPuck();

	cout << "PuckType: " << puck->getSizeTyp()  << "  ID: " << con_->getPuck()->getId() << endl;
	if(puck->getSizeTyp() == OK){
		if(puck->isHoleOnTop()){
			puck->setUserInteractionNeeded(true);
		}

		new (this) Road_to_Metal(this->con_);
	}else{
		new (this) Road_To_Sorting_Out(this->con_);
	}

}


