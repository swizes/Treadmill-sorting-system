/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland, Tobi
 */
#include "PuckStates.h"

#define VARIANZ 150

Height_Measurement::Height_Measurement(Context* con): State::State(con){

	cout << "Height Measurement ----- PuckId: " << this->con_->getPuck()->getId() << endl;

	HAL *hal = HAL::getInstance();

	CalibrateThread* ct = CalibrateThread::getInstance();
	int height = 0;
	for(int i = 0; i  < 5;i++){
		height += hal->get_height_measure();
	}
	height = height/5;
	this->con_->getPuck()->setSize(height);


	//Height is bigger if there is no object in Measurement
	//
	int minHeight = ct->getBigPuck()-VARIANZ;
	int maxHeight = ct->getBigPuck()+VARIANZ;
	int hole = ct->getHoleHeight();


	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	cout << "HeigtMeasurement: " << height << "  HeightBigPuck: " << maxHeight << endl;
	this->con_->getPuck()->setSizeTyp(NOT_OK);
	if(height >=  minHeight && height <= maxHeight){
		this->con_->getPuck()->setSizeTyp(OK);
		this->con_->getPuck()->setUserInteractionNeeded(true);

	}

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->printListeners();



	if(height >= hole-VARIANZ && height <= hole+VARIANZ){
		this->con_->getPuck()->setHoleOnTop(true);
		this->con_->getPuck()->setUserInteractionNeeded(false);
		this->con_->getPuck()->setSizeTyp(OK);
	}

	//Lambda transition
	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Height_Measurement()\n");

}
