/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland, Tobi
 */
#include "PuckStates.h"
#include "Errors.h"

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
	int holeNonMetal = ct->getHoleHeight();
	int holeMetal = ct->getHoleHeightMetal();

	//If height is bigger than maximum allowed height, go to error handling
	//TODO: err code
	if (height > maxHeight) {
		new (this) Error_Handling(this->con_);
	} else {

	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	cout << "HeigtMeasurement: " << height << "  HeightBigPuck: " << maxHeight << endl;
	this->con_->getPuck()->setSizeTyp(NOT_OK);
	if(height >=  minHeight && height <= maxHeight){
		this->con_->getPuck()->setSizeTyp(OK);
		if(ct->isBand()){
			this->con_->getPuck()->setSizeTyp(NOT_OK);
		}
		this->con_->getPuck()->setUserInteractionNeeded(true);

	}
	if(height > maxHeight){
		con_->setErrcode(ERROR_2BIG4PUCK);
		printf("ErrCode: %d\n", con_->getErrcode());
		new (this) Error_Handling(this->con_);
	}

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->printListeners();

	if((height >= holeNonMetal-VARIANZ && height <= holeNonMetal+VARIANZ) ||
			(height >= holeMetal- VARIANZ && height <= holeMetal+VARIANZ) ){
		this->con_->getPuck()->setHoleOnTop(true);
		this->con_->getPuck()->setUserInteractionNeeded(false);
		this->con_->getPuck()->setSizeTyp(OK);
	}

		//Lambda transition
		new (this) Search_for_Hole(this->con_);
	}//else
}

Height_Measurement::~Height_Measurement(){
	printf("~Height_Measurement()\n");

}
