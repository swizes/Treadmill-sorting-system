/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland, Tobi
 */
#include "PuckStates.h"

#define VARIANZ 50

Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Height_Measurement()\n");

	//TODO: Kill TIMER! von Road_to_Height
	HAL *hal = HAL::getInstance();
	hal->band_right_slowly();

	//TODO: HÖHENMESSUNG + SAVE DATA
	CalibrateThread* ct = CalibrateThread::getInstance();
	int height = hal->get_height_measure();
	con->getPuck()->setSize(height);
	cout << 2 << endl;
	//Variant value of Pucks  = > TODO: set right VariantValue!

	//Height is bigger if there is no object in Measurement
	//
	int minHeight = ct->getBigPuck()-VARIANZ;
	int maxHeight = ct->getBigPuck()+VARIANZ;
	int hole = ct->getHoleHeight();

	if(height >= hole-VARIANZ && height <= hole+VARIANZ){
		cout << "Hat Loch" << endl;
		con->getPuck()->setHoleOnTop(true);
		con->getPuck()->setSizeTyp(OK);
	}
	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	cout << "HeigtMeasurement: " << height << "  HeightBigPuck: " << maxHeight << endl;
	if(height >=  minHeight && height <= maxHeight){
		con->getPuck()->setSizeTyp(OK);
		cout << "sizeType after set: " << con->getPuck()->getSizeTyp() << "   Id:" << con->getPuck()->getId()  << endl;
	}

	//TODO: PreCond is_Height_ok
	//Maybe go in ErrorHandling if is_Height_ok @ false

	//Lambda transition
	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Road_to_Height()\n");

}
