/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland, Tobi
 */
#include "PuckStates.h"

#define VARIANZ 150

Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Height_Measurement()\n");

	BandController* bc = BandController::getInstance();
	//TODO: Kill TIMER! von Road_to_Height
	HAL *hal = HAL::getInstance();

	//hal->band_right_slowly();

	//TODO: HÖHENMESSUNG + SAVE DATA
	CalibrateThread* ct = CalibrateThread::getInstance();
	int height = hal->get_height_measure();
	this->con_->getPuck()->setSize(height);
	//Variant value of Pucks  = > TODO: set right VariantValue!

	//Height is bigger if there is no object in Measurement
	//
	int minHeight = ct->getBigPuck()-VARIANZ;
	int maxHeight = ct->getBigPuck()+VARIANZ;
	int hole = ct->getHoleHeight();

//	if(height >= hole-VARIANZ && height <= hole+VARIANZ){
//		cout << "Hat Loch" << endl;
//		con->getPuck()->setHoleOnTop(true);
//		con->getPuck()->setUserInteractionNeeded(false);
//		con->getPuck()->setSizeTyp(OK);
//	}
	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	//cout << "HeigtMeasurement: " << height << "  HeightBigPuck: " << (maxHeight - VARIANZ) << endl;
	//cout << "HeigtMeasurement PuckId: " << this->con_->getPuck()->getId() << endl;
	this->con_->getPuck()->setSizeTyp(NOT_OK);
	if(height >=  minHeight && height <= maxHeight){
		this->con_->getPuck()->setSizeTyp(OK);
		this->con_->getPuck()->setUserInteractionNeeded(true);
//		cout << "sizeType after set: " << con->getPuck()->getSizeTyp() << "   Id:" << con->getPuck()->getId()  << endl;
	}

	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->printListeners();

	/*while(hal->is_startButton_pushed()==1){
		hal->band_stop();
		delay(100);
	}*/
	//hal->band_right_slowly();

	if(height >= hole-VARIANZ && height <= hole+VARIANZ){
//		cout << "Hat Loch" << endl;
		this->con_->getPuck()->setHoleOnTop(true);
		this->con_->getPuck()->setUserInteractionNeeded(false);
		this->con_->getPuck()->setSizeTyp(OK);
	}

	//TODO: PreCond is_Height_ok
	//Maybe go in ErrorHandling if is_Height_ok @ false

	//Lambda transition
	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Height_Measurement()\n");

}
