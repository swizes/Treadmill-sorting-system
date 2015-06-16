/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland, Tobi
 */
#include "PuckStates.h"

#define VARIANZ 75

Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Height_Measurement()\n");

	BandController* bc = BandController::getInstance();
	//TODO: Kill TIMER! von Road_to_Height
	HAL *hal = HAL::getInstance();
	con->getPuck()->runBandSlowly();
	bc->refreshBand();
	//hal->band_right_slowly();

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

//	if(height >= hole-VARIANZ && height <= hole+VARIANZ){
//		cout << "Hat Loch" << endl;
//		con->getPuck()->setHoleOnTop(true);
//		con->getPuck()->setUserInteractionNeeded(false);
//		con->getPuck()->setSizeTyp(OK);
//	}
	//Height is equal or bigger than an incorrect Type
	//and equal or less than a CorrectType
	cout << "HeigtMeasurement: " << height << "  HeightBigPuck: " << maxHeight << endl;
	if(height >=  minHeight && height <= maxHeight){
		con->getPuck()->setSizeTyp(OK);
		con->getPuck()->setUserInteractionNeeded(true);
		cout << "sizeType after set: " << con->getPuck()->getSizeTyp() << "   Id:" << con->getPuck()->getId()  << endl;
	}
	time_t time_of_day;
	time_of_day = time( NULL );
	printf( "It is now: %s\n", ctime( &time_of_day ) );
	while(hal->is_startButton_pushed()==1){
		hal->band_stop();
	}

	hal->band_right_slowly();

	if(height >= hole-VARIANZ && height <= hole+VARIANZ){
		cout << "Hat Loch" << endl;
		con->getPuck()->setHoleOnTop(true);
		con->getPuck()->setUserInteractionNeeded(false);
		con->getPuck()->setSizeTyp(OK);
	}

	//TODO: PreCond is_Height_ok
	//Maybe go in ErrorHandling if is_Height_ok @ false

	//Lambda transition
	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Height_Measurement()\n");

}
