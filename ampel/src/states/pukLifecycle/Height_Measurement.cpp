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
	cout << 1 << endl;

	//TODO: HÖHENMESSUNG + SAVE DATA
	CalibrateThread* ct = CalibrateThread::getInstance();
	cout << "1.1" << endl;
	int height = hal->get_height_measure();
	cout << "1.2" << endl;
	con->getPuck()->setSize(height);
	cout << 2 << endl;
	//Variant value of Pucks  = > TODO: set right VariantValue!
	int variantValue = (ct->getSmallPuck() - ct->getBigPuck()) / 4;

	cout << 3 << endl;
	//Height is bigger if there is no object in Measurement
	//
	int minHeight = ct->getBigPuck()-50;
	int maxHeight = ct->getBigPuck()+50;
	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	cout << 4 << endl;
	cout << "HeigtMeasurement: " << height << "  HeightBigPuck: " << maxHeight << endl;
	if(height >=  minHeight && height <= maxHeight){
		cout << 5 << endl;
		cout << "Am I inside???" << con->getPuck()->getId() << endl;
		con->getPuck()->setSizeTyp(OK);
		cout << "sizeType after set: " << con->getPuck()->getSizeTyp() << "   Id:" << con->getPuck()->getId() << endl;
	}

	//TODO: PreCond is_Height_ok
	//Maybe go in ErrorHandling if is_Height_ok @ false

	//Lambda transition
	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Road_to_Height()\n");

}
