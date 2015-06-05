/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland, Tobi
 */
#include "PuckStates.h"


Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Height_Measurement()\n");

	//TODO: Kill TIMER! von Road_to_Height
	HAL *hal = HAL::getInstance();
	hal->band_right_slowly();

	//TODO: HÖHENMESSUNG + SAVE DATA
	CalibrateThread* ct = CalibrateThread::getInstance();
	int height = hal->get_height_measure();
	con->getPuck().setSize(height);

	//Variant value of Pucks  = > TODO: set right VariantValue!
	int variantValue = (ct->getSmallPuck() - ct->getBigPuck()) / 4;

	//Height is bigger if there is no object in Measurement
	//
	int minHeight = ct->getSmallPuck()-variantValue;
	int maxHeight = ct->getBigPuck()-variantValue;
	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	if(height <=  minHeight && height >= maxHeight){
		con->getPuck().setSizeTyp(OK);
	}

	//TODO: PreCond is_Height_ok
	//Maybe go in ErrorHandling if is_Height_ok @ false

	//Lambda transition
	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Road_to_Height()\n");

}
